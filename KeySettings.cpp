#include <Windows.h>
#include "KeySettings.h"

#define MAX_KEYS 30

KeySettings settings;

bool KeySettings::Init(char* fileNameOnly)
{
	bool ret = false;

	WCHAR path[MAX_PATH] = { 0 };
	if (GetModuleFileName(NULL, path, MAX_PATH))
	{
		LPTSTR pStrPos = wcsrchr(path, '\\');
		if (pStrPos)
		{
			*pStrPos = NULL; // Strip filename - get just the path

			wsprintf(m_fullPathToFile, L"%s\\%S", path, fileNameOnly);
			
			SI_Error rc = m_ini.LoadFile(m_fullPathToFile);
			if (rc == SI_OK)
			{
				ret = ParseIni(m_ini);
			}
		}
	}

	return ret;
}

const char* KeySettings::DecodeKey(uint8_t keyCode)
{
	return keyCodeArray[keyCode].name;
}

bool KeySettings::ParseSection(CSimpleIniA& ini, MacroKey& key, const char* sectionName)
{
	bool ret = false;
	char szBuff[64] = { 0 };
	key.bLoop = ini.GetBoolValue(sectionName, "Loop", false);

	for (int i = 1; i < MAX_KEYS; i++)
	{
		const char* pKey = _itoa(i, szBuff, 10);
		const char* pValue = ini.GetValue(sectionName, pKey, "");
		if (*pValue == NULL)
		{
			break;
		}
		else
		{
			char szTmp[64] = { 0 };
			strncpy(szTmp, pValue, _countof(szTmp) - 1);
			char* pKey = strtok(szTmp, ",");
			if (pKey != NULL)
			{
				char* pDelay = strtok(NULL, ",");
				if (pDelay != NULL)
				{
					char* pCtrl = strtok(NULL, ",");
					if (pCtrl != NULL)
					{
						char* pAlt = strtok(NULL, ",");
						if (pAlt != NULL)
						{
							char* pShift = strtok(NULL, ",");
							if (pShift != NULL)
							{
								char* pWKey = strtok(NULL, ",");
								if (pWKey != NULL)
								{
									PlaybackKey playbackKey;
									playbackKey.keyCode   = (uint8_t)atoi(pKey);
									playbackKey.delayInMS = (uint16_t)atoi(pDelay);
									playbackKey.bCtrl     = (bool)atoi(pCtrl);
									playbackKey.bAlt      = (bool)atoi(pAlt);
									playbackKey.bShift    = (bool)atoi(pShift);
									playbackKey.bWKey     = (bool)atoi(pWKey);
									
									if ((playbackKey.delayInMS > 0) && (playbackKey.keyCode > 0))
									{
										ret = true;
										key.keys.push_back(playbackKey);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return ret;
}

bool KeySettings::ParseIni(CSimpleIniA& ini)
{
	bool ret = false;

	m_macroKeys.clear();

	CSimpleIniA::TNamesDepend sections;
	ini.GetAllSections(sections);
	for (auto& section : sections)
	{
		uint16_t key = atoi(section.pItem);
		if ((key > 0) && (key < 255))
		{
			MacroKey macroKey;
			macroKey.keyCode = (uint8_t)key;
			if (ParseSection(ini, macroKey, section.pItem))
			{
				m_macroKeys[macroKey.keyCode] = macroKey;
			}

			ret = true;
		}
	}

	return ret;
}

bool KeySettings::GetAvialableMacroKeys(std::vector<KeyInList>& keys, uint8_t currentKeyCode)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	//for (int i = 1; i < 256; ++i)
	for (int i = 1; i < 0x7F; ++i) // Don't need to go thru all the keys
	{
		if (keyCodeArray[i].bMacroValid)
		{
			if (currentKeyCode == i)
			{
				// Add the macro key that is already selected
				KeyInList key;
				key.keyCode = (uint8_t)i;
				key.name = keyCodeArray[i].name;
				keys.push_back(key);
				ret = true;
			}
			else
			{
				// See if it is already assigned to be a macro key
				auto it = m_macroKeys.find(i);
				if (it == m_macroKeys.end())
				{
					// Key not being used
					KeyInList key;
					key.keyCode = (uint8_t)i;
					key.name = keyCodeArray[i].name;
					keys.push_back(key);
					ret = true;
				}
			}
		}
	}

	return ret;
}

bool KeySettings::GetAvialablePlaybackKeys(std::vector<KeyInList>& keys)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	//for (int i = 1; i < 256; ++i)
	for (int i = 1; i < 0x7F; ++i) // Don't need to go thru all the keys
	{
		if (keyCodeArray[i].bPlaybackValid)
		{
			KeyInList key;
			key.keyCode = (uint8_t)i;
			key.name = keyCodeArray[i].name;
			keys.push_back(key);
			ret = true;
		}
	}

	return ret;
}

bool KeySettings::AddMacroKey(MacroKey& macroKey)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	if (macroKey.keyCode > 0)
	{
		if (m_macroKeys.size() < MAX_KEYS)
		{
			
			char szSection[32] = { 0 };
			_itoa(macroKey.keyCode, szSection, 10);

			m_ini.Delete(szSection, NULL, true);
			m_ini.SetBoolValue(szSection, "Loop", macroKey.bLoop);

			uint8_t nPlaybackKeys = 1;
			for (auto& playbackKey : macroKey.keys)
			{
				if (nPlaybackKeys <= MAX_KEYS)
				{
					char szKey[32] = { 0 };
					char szTmp[64] = { 0 };

					_itoa(nPlaybackKeys, szKey, 10);
					nPlaybackKeys++;

					sprintf(szTmp, "%u,%u,%u,%u,%u,%u",
						playbackKey.keyCode,
						playbackKey.delayInMS,
						playbackKey.bCtrl,
						playbackKey.bAlt,
						playbackKey.bShift,
						playbackKey.bWKey);

					m_ini.SetValue(szSection, szKey, szTmp);
				}
			}

			m_macroKeys[macroKey.keyCode] = macroKey;
			ret = true;
		}
	}

	if (ret)
	{
		// Don't save it without out playback keys
		if (macroKey.keys.size())
		{
			SI_Error rc = m_ini.SaveFile(m_fullPathToFile, false);
			if (rc != SI_OK)
			{
				ret = false;
			}
		}
	}

	return ret;
}

bool KeySettings::DeleteMacroKey(uint8_t keyCode)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	auto it = m_macroKeys.find(keyCode);
	if (it != m_macroKeys.end())
	{
		m_macroKeys.erase(it);

		char szSection[32] = { 0 };
		_itoa(keyCode, szSection, 10);
		m_ini.Delete(szSection, NULL, true);

		SI_Error rc = m_ini.SaveFile(m_fullPathToFile, false);
		if (rc == SI_OK)
		{
			ret = true;
		}
	}

	return ret;
}

bool KeySettings::IsValidMacroKey(uint8_t keyCode)
{
	return keyCodeArray[keyCode].bMacroValid;
}

bool KeySettings::GetMacroKey(uint8_t keyCode, MacroKey& macroKey, bool bNoDecode)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	if (keyCode > 0)
	{
		auto it = m_macroKeys.find(keyCode);
		if (it != m_macroKeys.end())
		{
			macroKey = it->second;
			
			if (!bNoDecode)
			{
				// Update values for UI
				char szTmp[32] = { 0 };
				for (PlaybackKey& playbackKey : macroKey.keys)
				{
					playbackKey.name = DecodeKey(playbackKey.keyCode);
					playbackKey.keyCodeStr = _itoa(playbackKey.keyCode, szTmp, 10);
					playbackKey.delayInMSStr = _itoa(playbackKey.delayInMS, szTmp, 10);
				}
			}

			ret = true;
		}
	}

	return ret;
}

bool KeySettings::GetMacroKeyList(std::vector<KeyInList>& keys)
{
	bool ret = false;
	char szTmp[32] = { 0 };

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	for(auto macroKey : m_macroKeys)
	{
		KeyInList key;
		key.keyCode = macroKey.second.keyCode;
		key.keyCodeStr = _itoa(key.keyCode, szTmp, 10);
		key.name = keyCodeArray[key.keyCode].name;
		keys.push_back(key);
		ret = true;
	}

	return ret;
}

bool KeySettings::AddPlaybackKey(uint8_t macroKeyCode, int playbackKeyVectorIdx, PlaybackKey& playbackKey)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	MacroKey macroKey;
	if (GetMacroKey(macroKeyCode, macroKey))
	{
		playbackKey.name = keyCodeArray[playbackKey.keyCode].name;

		if (playbackKeyVectorIdx < 0)
		{
			macroKey.keys.push_back(playbackKey);
			ret = true;
		}
		else
		{
			// playbackKeyVectorIdx is a zero based index and must be less
			// then the number of items in the vector by 1
			int numberOfPlaybackKeys = (int)macroKey.keys.size();
			if (numberOfPlaybackKeys > playbackKeyVectorIdx)
			{
				try
				{
					macroKey.keys[playbackKeyVectorIdx] = playbackKey;
					ret = true;
				}
				catch (const std::out_of_range& e)
				{
					// Don't be a bone head and write good code
					UNREFERENCED_PARAMETER(e);
				}
			}
		}

		if (ret)
		{
			// Need to replace only macro key entry with new one
			m_macroKeys[macroKeyCode] = macroKey;
		}
	}

	return ret;
}

bool KeySettings::GetPlaybackKey(uint8_t macroKeyCode, int playbackKeyVectorIdx, PlaybackKey& playbackKey)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	if(playbackKeyVectorIdx >= 0)
	{
		MacroKey macroKey;
		if (GetMacroKey(macroKeyCode, macroKey))
		{
			// playbackKeyVectorIdx is a zero based index and must be less
			// then the number of items in the vector by 1
			int numberOfPlaybackKeys = (int) macroKey.keys.size();
			if (numberOfPlaybackKeys > playbackKeyVectorIdx)
			{
				try
				{
					char szTmp[32] = { 0 };
					playbackKey = macroKey.keys[playbackKeyVectorIdx];
					playbackKey.keyCodeStr = _itoa(playbackKey.keyCode, szTmp, 10);
					playbackKey.name = keyCodeArray[playbackKey.keyCode].name;
				}
				catch (const std::out_of_range& e)
				{
					// Don't be a bone head and write good code
					UNREFERENCED_PARAMETER(e);
				}

				ret = true;
			}
		}
	}

	return ret;
}

bool KeySettings::DeletePlaybackKey(uint8_t macroKeyCode, int playbackKeyVectorIdx)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	MacroKey macroKey;
	if (GetMacroKey(macroKeyCode, macroKey))
	{
		if (playbackKeyVectorIdx >= 0)
		{
			// playbackKeyVectorIdx is a zero based index and must be less
			// then the number of items in the vector by 1
			int numberOfPlaybackKeys = (int)macroKey.keys.size();
			if (numberOfPlaybackKeys > playbackKeyVectorIdx)
			{
				try
				{
					macroKey.keys.erase(macroKey.keys.begin() + playbackKeyVectorIdx);
					ret = true;
				}
				catch (const std::out_of_range& e)
				{
					// Don't be a bone head and write good code
					UNREFERENCED_PARAMETER(e);
				}
			}
		}

		if (ret)
		{
			// Need to replace only macro key entry with new one
			m_macroKeys[macroKeyCode] = macroKey;
		}
	}

	return ret;
}