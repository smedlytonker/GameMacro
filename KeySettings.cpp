#include "KeySettings.h"
#include <sstream>

#define MAX_KEYS 30

KeySettings globalSettings;

bool KeySettings::Init(char* fileNameOnly)
{
	bool ret = false;

	WCHAR path[MAX_PATH] = { 0 };
	if (GetModuleFileName(nullptr, path, MAX_PATH))
	{
		WCHAR* pStrPos = std::wcsrchr(path, '\\');
		if (pStrPos)
		{
			// Strip executable file name & get just the path
			*pStrPos = (WCHAR) 0;

			// Assume that the .ini file is in the same folder as 
			// this program is running from
			swprintf_s(m_fullPathToFile, _countof(m_fullPathToFile) - 1, L"%ls\\%hs", path, fileNameOnly);
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

std::vector<std::string> KeySettings::Split(const char* str, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(str);
	while (std::getline(tokenStream, token, delimiter)) 
	{
		tokens.push_back(token);
	}

	return tokens;
}
bool KeySettings::ParseSection(CSimpleIniA& ini, MacroKey& key, const char* sectionName)
{
	bool ret = false;

	key.bLoop = ini.GetBoolValue(sectionName, "Loop", false);

	for (int i = 1; i < MAX_KEYS; i++)
	{
		std::string keyStr = std::to_string(i);
		const char* fieldsStr = ini.GetValue(sectionName, keyStr.c_str(), "");
		if ((fieldsStr == nullptr) || (*fieldsStr == ((char) 0)))
		{
			break;
		}
		else
		{
			std::vector<std::string> fields = Split(fieldsStr, ',');
			if (fields.size() >= 6)
			{
				PlaybackKey playbackKey;
				playbackKey.keyCode   = (uint8_t)   std::stoi(fields[0]);
				playbackKey.delayInMS = (uint16_t)  std::stoi(fields[1]);
				playbackKey.bCtrl     = (bool)     (std::stoi(fields[2]) > 0) ? true : false;
				playbackKey.bAlt      = (bool)     (std::stoi(fields[3]) > 0) ? true : false;
				playbackKey.bShift    = (bool)     (std::stoi(fields[4]) > 0) ? true : false;
				playbackKey.bWKey     = (bool)     (std::stoi(fields[5]) > 0) ? true : false;

				if ((playbackKey.delayInMS > 0) && (playbackKey.keyCode > 0))
				{
					ret = true;
					key.keys.push_back(playbackKey);
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
	std::memset(m_macroIsActive, 0, sizeof(m_macroIsActive));
	
	CSimpleIniA::TNamesDepend sections;
	ini.GetAllSections(sections);
	for (auto& section : sections)
	{
		uint16_t key = std::stoi(section.pItem);
		if ((key > 0) && (key < 255))
		{
			MacroKey macroKey;
			macroKey.keyCode = (uint8_t)key;
			if (ParseSection(ini, macroKey, section.pItem))
			{
				m_macroKeys[macroKey.keyCode] = macroKey;
				m_macroIsActive[macroKey.keyCode] = 1;
			}

			ret = true;
		}
	}

	return ret;
}

bool KeySettings::GetAvialableMacroKeys(std::vector<KeyEntry>& keys, uint8_t currentKeyCode)
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
				KeyEntry key;
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
					KeyEntry key;
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

bool KeySettings::GetAvialablePlaybackKeys(std::vector<KeyEntry>& keys)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	//for (int i = 1; i < 256; ++i)
	for (int i = 1; i < 0x7F; ++i) // Don't need to go thru all the keys
	{
		if (keyCodeArray[i].bPlaybackValid)
		{
			KeyEntry key;
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
			std::string sectionStr = std::to_string(macroKey.keyCode);
			m_ini.Delete(sectionStr.c_str(), nullptr, true);
			m_ini.SetBoolValue(sectionStr.c_str(), "Loop", macroKey.bLoop);

			uint8_t nPlaybackKeys = 1;
			for (auto& playbackKey : macroKey.keys)
			{
				if (nPlaybackKeys <= MAX_KEYS)
				{
					// Can't use 'std::format' in c++20 because of the C++/CLI mode does not support C++ versions newer than C++17
					// have to use sprintf_s instead
					char szTmp[64] = { 0 };
					sprintf_s(szTmp, _countof(szTmp) - 1, 
						"%u,%u,%u,%u,%u,%u",
						playbackKey.keyCode,
						playbackKey.delayInMS,
						playbackKey.bCtrl,
						playbackKey.bAlt,
						playbackKey.bShift,
						playbackKey.bWKey);

					std::string keyStr = std::to_string(nPlaybackKeys);
					nPlaybackKeys++;
					m_ini.SetValue(sectionStr.c_str(), keyStr.c_str(), szTmp);
				}
			}

			m_macroKeys[macroKey.keyCode] = macroKey;
			m_macroIsActive[macroKey.keyCode] = 1;

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
		m_macroIsActive[keyCode] = 0;
		
		std::string sectionStr = std::to_string(keyCode);
		m_ini.Delete(sectionStr.c_str(), nullptr, true);

		SI_Error rc = m_ini.SaveFile(m_fullPathToFile, false);
		if (rc == SI_OK)
		{
			ret = true;
		}
	}

	return ret;
}

bool KeySettings::IsActiveMacroKey(uint8_t keyCode)
{
	// This is a lookup table is much faster than looking it up in
	// std::map 'm_macroKeys'. This is because the map has to be protected 
	// with a mutex since this is a multi-thread app. So this should lower
	// the overhead of checking.

	return (m_macroIsActive[keyCode] > 0) ? true : false;
}

bool KeySettings::GetMacroKey(uint8_t keyCode, MacroKey& macroKey, bool bNoDecode)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	if (keyCode > 0)
	{
		auto it = m_macroKeys.find(keyCode);
		if (it == m_macroKeys.end())
		{
			// Error - 'm_macroKeys' & 'macroIsActive' should match 
			// each other. Some how they got out of sync.
			m_macroIsActive[keyCode] = 0; // Make it match
		}
		else
		{
			macroKey = it->second;
			m_macroIsActive[keyCode] = 1;
			ret = true;
			
			if (!bNoDecode)
			{
				// Update values for UI
				for (PlaybackKey& playbackKey : macroKey.keys)
				{
					playbackKey.name = DecodeKey(playbackKey.keyCode);
					playbackKey.keyCodeStr = std::to_string(playbackKey.keyCode);
					playbackKey.delayInMSStr = std::to_string(playbackKey.delayInMS);
				}
			}
		}
	}

	return ret;
}

bool KeySettings::GetMacroKeyList(std::vector<KeyEntry>& keys)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	for(auto macroKey : m_macroKeys)
	{
		KeyEntry key;
		key.keyCode = macroKey.second.keyCode;
		key.keyCodeStr = std::to_string(key.keyCode);
		key.name = keyCodeArray[key.keyCode].name;
		keys.push_back(key);
		ret = true;
	}

	return ret;
}

bool KeySettings::AddPlaybackKey(uint8_t macroKeyCode, int playbackIdx, PlaybackKey& playbackKey)
{
	bool ret = false;

	MacroKey macroKey;
	if (GetMacroKey(macroKeyCode, macroKey))
	{
		// Mutex need to be locked after 'GetMacroKey' because this function locks the mutex
		std::unique_lock<std::shared_mutex> lock(protectSettings);

		playbackKey.name = keyCodeArray[playbackKey.keyCode].name;

		if (playbackIdx < 0)
		{
			macroKey.keys.push_back(playbackKey);
			ret = true;
		}
		else
		{
			// playbackIdx is a zero based index and must be less
			// then the number of items in the vector by 1
			int numberOfPlaybackKeys = (int)macroKey.keys.size();
			if (numberOfPlaybackKeys > playbackIdx)
			{
				macroKey.keys[playbackIdx] = playbackKey;
				ret = true;
			}
		}

		if (ret)
		{
			// Need to replace only macro key entry with new one
			m_macroKeys[macroKeyCode] = macroKey;
			m_macroIsActive[macroKeyCode] = 1;
		}
	}

	return ret;
}

bool KeySettings::GetPlaybackKey(uint8_t macroKeyCode, int playbackIdx, PlaybackKey& playbackKey)
{
	bool ret = false;


	if(playbackIdx >= 0)
	{
		MacroKey macroKey;
		if (GetMacroKey(macroKeyCode, macroKey))
		{
			// Mutex need to be locked after 'GetMacroKey' because this function locks the mutex
			std::unique_lock<std::shared_mutex> lock(protectSettings);

			// playbackIdx is a zero based index and must be less
			// then the number of items in the vector by 1
			int numberOfPlaybackKeys = (int) macroKey.keys.size();
			if (numberOfPlaybackKeys > playbackIdx)
			{
				playbackKey = macroKey.keys[playbackIdx];
				playbackKey.keyCodeStr = std::to_string(playbackKey.keyCode);
				playbackKey.name = keyCodeArray[playbackKey.keyCode].name;
				ret = true;
			}
		}
	}

	return ret;
}

bool KeySettings::DeletePlaybackKey(uint8_t macroKeyCode, int playbackIdx)
{
	bool ret = false;

	MacroKey macroKey;
	if (GetMacroKey(macroKeyCode, macroKey))
	{
		// Mutex need to be locked after 'GetMacroKey' because this function locks the mutex
		std::unique_lock<std::shared_mutex> lock(protectSettings);

		if (playbackIdx >= 0)
		{
			// playbackIdx is a zero based index and must be less
			// then the number of items in the vector by 1
			int numberOfPlaybackKeys = (int)macroKey.keys.size();
			if (numberOfPlaybackKeys > playbackIdx)
			{
				macroKey.keys.erase(macroKey.keys.begin() + playbackIdx);
				ret = true;
			}
		}

		if (ret)
		{
			// Need to replace only macro key entry with new one
			m_macroKeys[macroKeyCode] = macroKey;
			m_macroIsActive[macroKeyCode] = 1;
		}
	}

	return ret;
}