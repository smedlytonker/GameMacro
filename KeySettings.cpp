#include "KeySettings.h"
#include <sstream>

#define MAX_KEYS 30

KeySettings globalSettings;

bool KeySettings::Init(WCHAR* fileNameOnly)
{
	bool ret = false;

	// Return full patch to this program
	WCHAR path[MAX_PATH] = { 0 };
	if (GetModuleFileName(nullptr, path, MAX_PATH))
	{
		WCHAR* pStrPos = std::wcsrchr(path, '\\');
		if (pStrPos)
		{
			// Strip off program name leaving just the path
			*pStrPos = (WCHAR) 0;

			// Assume that the .ini file is in the same folder as 
			// this program is running from
			swprintf_s(m_fullPathToFile, _countof(m_fullPathToFile) - 1, L"%ls\\%ls", path, fileNameOnly);
			SI_Error rc = m_ini.LoadFile(m_fullPathToFile);
			if (rc == SI_OK)
			{
				ret = Ini_Parse(m_ini);
			}
		}
	}

	return ret;
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

bool KeySettings::Ini_ParseSection(CSimpleIniA& ini, MacroKey& key, const char* sectionName)
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

bool KeySettings::Ini_Parse(CSimpleIniA& ini)
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
			if (Ini_ParseSection(ini, macroKey, section.pItem))
			{
				m_macroKeys[macroKey.keyCode] = macroKey;
				m_macroIsActive[macroKey.keyCode] = 1;
			}

			ret = true;
		}
	}

	return ret;
}

KeySettings::KeyEntry KeySettings::KeyCodeToEntry(uint8_t keyCode)
{
	KeyEntry key;
	key.keyCode = keyCode;
	key.name = vkArray[keyCode].name;
	key.keyCodeStr = std::to_string(keyCode);

	return key;
}

bool KeySettings::Macro_ListAvailable(std::vector<KeyEntry>& keys, uint8_t currentKeyCode)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	//for (int i = 1; i < 256; ++i)
	for (int i = 1; i < 0x7F; ++i) // Don't need to go thru all the keys
	{
		if (vkArray[i].bMacroValid)
		{
			if (currentKeyCode == i)
			{
				// Add the macro key that is already selected
				KeyEntry key = KeyCodeToEntry(i);
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
					KeyEntry key = KeyCodeToEntry(i);
					keys.push_back(key);
					ret = true;
				}
			}
		}
	}

	return ret;
}

bool KeySettings::Playback_ListAvailable(std::vector<KeyEntry>& keys)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	//for (int i = 1; i < 256; ++i)
	for (int i = 1; i < 0x7F; ++i) // Don't need to go thru all the keys
	{
		if (vkArray[i].bPlaybackValid)
		{
			KeyEntry key = KeyCodeToEntry(i);
			keys.push_back(key);
			ret = true;
		}
	}

	return ret;
}

bool KeySettings::Macro_Add(MacroKey& macroKey)
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

bool KeySettings::Macro_Delete(uint8_t keyCode)
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

bool KeySettings::Macro_IsActive(uint8_t keyCode)
{
	// This is a lookup table is much faster than looking it up in
	// std::map 'm_macroKeys'. This is because the map has to be protected 
	// with a mutex since this is a multi-thread app. So this should lower
	// the overhead of checking.
	return (m_macroIsActive[keyCode] > 0) ? true : false;
}

bool KeySettings::GetMacro(uint8_t keyCode, MacroKey& macroKey)
{
	bool ret = false;

	if (keyCode > 0)
	{
		auto it = m_macroKeys.find(keyCode);
		if (it == m_macroKeys.end())
		{
			// Error - 'm_macroKeys' & 'macroIsActive' should match 
			m_macroIsActive[keyCode] = 0; // Make it match
		}
		else
		{
			macroKey = it->second;
			m_macroIsActive[keyCode] = 1;
			ret = true;

			// Update values for UI
			macroKey.name = vkArray[macroKey.keyCode].name;
			macroKey.keyCodeStr = std::to_string(macroKey.keyCode);
			for (PlaybackKey& playbackKey : macroKey.keys)
			{
				playbackKey.name = vkArray[playbackKey.keyCode].name;
				playbackKey.keyCodeStr = std::to_string(playbackKey.keyCode);
				playbackKey.delayInMSStr = std::to_string(playbackKey.delayInMS);
			}
		}
	}

	return ret;
}

bool KeySettings::Macro_Get(uint8_t keyCode, MacroKey& macroKey)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);
	ret = GetMacro(keyCode, macroKey);

	return ret;
}

bool KeySettings::Macro_ListActive(std::vector<KeyEntry>& keys)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	for(auto macroKey : m_macroKeys)
	{
		KeyEntry key = KeyCodeToEntry(macroKey.second.keyCode);
		keys.push_back(key);
		ret = true;
	}

	return ret;
}

bool KeySettings::Playback_Add(uint8_t macroKeyCode, int playbackIdx, PlaybackKey& playbackKey)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	MacroKey macroKey;
	if (GetMacro(macroKeyCode, macroKey))
	{
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

bool KeySettings::Playback_Get(uint8_t macroKeyCode, int playbackIdx, PlaybackKey& playbackKey)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	if(playbackIdx >= 0)
	{
		MacroKey macroKey;
		if (GetMacro(macroKeyCode, macroKey))
		{	
			// playbackIdx is a zero based index and must be less
			// then the number of items in the vector by 1
			int numberOfPlaybackKeys = (int) macroKey.keys.size();
			if (numberOfPlaybackKeys > playbackIdx)
			{
				playbackKey = macroKey.keys[playbackIdx];
				ret = true;
			}
		}
	}

	return ret;
}

bool KeySettings::Playback_Delete(uint8_t macroKeyCode, int playbackIdx)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	MacroKey macroKey;
	if (GetMacro(macroKeyCode, macroKey))
	{
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