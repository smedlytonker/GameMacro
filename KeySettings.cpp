#include <Windows.h>
#include "KeySettings.h"

#define MAX_KEYS 30

KeySettings::KeyLookUp keyCodeArray[] = {
		{ 0x00, "Invalid", 0},
		{ VK_LBUTTON, "Left Mouse Button", 0},
		{ VK_RBUTTON, "Right Mouse Button", 0},
		{ VK_CANCEL, "Control-break processing", 0},
		{ VK_MBUTTON, "Middle Mouse Button", 0},
		{ VK_XBUTTON1, "X1 Mouse Button", 0},
		{ VK_XBUTTON2, "X2 Mouse Button", 0},
		{ 0x07, "Reserved", 0},
		{ VK_BACK, "Backspace", 0},
		{ VK_TAB, "Tab", 0},
		{ 0x0A, "Reserved", 0},
		{ 0x0B, "Reserved", 0},
		{ VK_CLEAR, "Clear", 0},
		{ VK_RETURN, "Enter", 0},
		{ 0x0E, "Unassigned", 0},
		{ 0x0F, "Unassigned", 0},
		{ VK_SHIFT, "Shift", 0},
		{ VK_CONTROL, "Control", 0},
		{ VK_MENU, "Alt", 0},
		{ VK_PAUSE, "Pause", 0},
		{ VK_CAPITAL, "Caps Lock", 0},
		{ VK_KANA, "IME Kana mode", 0},
		{ VK_IME_ON, "IME On", 0},
		{ VK_JUNJA, "IME Junja mode", 0},
		{ VK_FINAL, "IME final mode", 0},
		{ VK_HANJA, "IME Hanja mode", 0},
		{ VK_IME_OFF, "IME Off", 0},
		{ VK_ESCAPE, "Escape", 0},
		{ VK_CONVERT, "IME convert", 0},
		{ VK_NONCONVERT, "IME nonconvert", 0},
		{ VK_ACCEPT, "IME accept", 0},
		{ VK_MODECHANGE, "IME mode change request", 0},
		{ VK_SPACE, "Spacebar", 0},
		{ VK_PRIOR, "Page Up", 0},
		{ VK_NEXT, "Page Down", 0},
		{ VK_END, "End", 0},
		{ VK_HOME, "Home", 0},
		{ VK_LEFT, "Left Arrow", 0},
		{ VK_UP, "Up Arrow", 0},
		{ VK_RIGHT, "Right Arrow", 0},
		{ VK_DOWN, "Down Arrow", 0},
		{ VK_SELECT, "Select", 0},
		{ VK_PRINT, "Print", 0},
		{ VK_EXECUTE, "Execute", 0},
		{ VK_SNAPSHOT, "Print Screen", 0},
		{ VK_INSERT, "Insert", 0},
		{ VK_DELETE, "Delete", 0},
		{ VK_HELP, "Help", 0},
		{ 0x30, "0", 1},
		{ 0x31, "1", 1},
		{ 0x32, "2", 1},
		{ 0x33, "3", 1},
		{ 0x34, "4", 1},
		{ 0x35, "5", 1},
		{ 0x36, "6", 1},
		{ 0x37, "7", 1},
		{ 0x38, "8", 1},
		{ 0x39, "9", 1},
		{ 0x3A, "Reserved", 0},
		{ 0x3B, "Reserved", 0},
		{ 0x3C, "Reserved", 0},
		{ 0x3D, "Reserved", 0},
		{ 0x3E, "Reserved", 0},
		{ 0x3F, "Reserved", 0},
		{ 0x40, "Reserved", 0},
		{ 0x41, "A", 1},
		{ 0x42, "B", 1},
		{ 0x43, "C", 1},
		{ 0x44, "D", 1},
		{ 0x45, "E", 1},
		{ 0x46, "F", 1},
		{ 0x47, "G", 1},
		{ 0x48, "H", 1},
		{ 0x49, "I", 1},
		{ 0x4A, "J", 1},
		{ 0x4B, "K", 1},
		{ 0x4C, "L", 1},
		{ 0x4D, "M", 1},
		{ 0x4E, "N", 1},
		{ 0x4F, "O", 1},
		{ 0x50, "P", 1},
		{ 0x51, "Q", 1},
		{ 0x52, "R", 1},
		{ 0x53, "S", 1},
		{ 0x54, "T", 1},
		{ 0x55, "U", 1},
		{ 0x56, "V", 1},
		{ 0x57, "W", 1},
		{ 0x58, "X", 1},
		{ 0x59, "Y", 1},
		{ 0x5A, "Z", 1},
		{ VK_LWIN, "Left Windows Key", 0},
		{ VK_RWIN, "Right Windows Key", 0},
		{ VK_APPS, "Applications Key", 0},
		{ 0x93, "Reserved", 0},
		{ VK_SLEEP, "Sleep", 0},
		{ VK_NUMPAD0, "Numeric Keypad 0", 1},
		{ VK_NUMPAD1, "Numeric Keypad 1", 1},
		{ VK_NUMPAD2, "Numeric Keypad 2", 1},
		{ VK_NUMPAD3, "Numeric Keypad 3", 1},
		{ VK_NUMPAD4, "Numeric Keypad 4", 1},
		{ VK_NUMPAD5, "Numeric Keypad 5", 1},
		{ VK_NUMPAD6, "Numeric Keypad 6", 1},
		{ VK_NUMPAD7, "Numeric Keypad 7", 1},
		{ VK_NUMPAD8, "Numeric Keypad 8", 1},
		{ VK_NUMPAD9, "Numeric Keypad 9", 1},
		{ VK_MULTIPLY, "Multiply", 0},
		{ VK_ADD, "Add", 0},
		{ VK_SEPARATOR, "Separator", 0},
		{ VK_SUBTRACT, "Subtract", 0},
		{ VK_DECIMAL, "Decimal", 0},
		{ VK_DIVIDE, "Divide", 0},
		{ VK_F1, "F1", 1},
		{ VK_F2, "F2", 1},
		{ VK_F3, "F3", 1},
		{ VK_F4, "F4", 1},
		{ VK_F5, "F5", 1},
		{ VK_F6, "F6", 1},
		{ VK_F7, "F7", 1},
		{ VK_F8, "F8", 1},
		{ VK_F9, "F9", 1},
		{ VK_F10, "F10", 1},
		{ VK_F11, "F11", 1},
		{ VK_F12, "F12", 1},
		{ VK_F13, "F13", 0},
		{ VK_F14, "F14", 0},
		{ VK_F15, "F15", 0},
		{ VK_F16, "F16", 0},
		{ VK_F17, "F17", 0},
		{ VK_F18, "F18", 0},
		{ VK_F19, "F19", 0},
		{ VK_F20, "F20", 0},
		{ VK_F21, "F21", 0},
		{ VK_F22, "F22", 0},
		{ VK_F23, "F23", 0},
		{ VK_F24, "F24", 0},
		{ VK_NAVIGATION_VIEW, "Reserved", 0},
		{ VK_NAVIGATION_MENU, "Reserved", 0},
		{ VK_NAVIGATION_UP, "Reserved", 0},
		{ VK_NAVIGATION_DOWN, "Reserved", 0},
		{ VK_NAVIGATION_LEFT, "Reserved", 0},
		{ VK_NAVIGATION_RIGHT, "Reserved", 0},
		{ VK_NAVIGATION_ACCEPT, "Reserved", 0},
		{ VK_NAVIGATION_CANCEL, "Reserved", 0},
		{ VK_NUMLOCK, "Num Lock", 0},
		{ VK_SCROLL, "Scroll Lock", 0},
		{ 0x92, "= key on numpad", 0},
		{ 0x93, "Unregister word", 0},
		{ 0x94, "Register word", 0},
		{ 0x95, "Left OYAYUBI", 0},
		{ 0x96, "Right OYAYUBI", 0},
		{ 0x97, "Unassigned", 0},
		{ 0x98, "Unassigned", 0},
		{ 0x99, "Unassigned", 0},
		{ 0x9A, "Unassigned", 0},
		{ 0x9B, "Unassigned", 0},
		{ 0x9C, "Unassigned", 0},
		{ 0x9D, "Unassigned", 0},
		{ 0x9E, "Unassigned", 0},
		{ 0x9F, "Unassigned", 0},
		{ VK_LSHIFT,	"Left SHIFT key", 0},
		{ VK_RSHIFT,	"Right SHIFT key", 0},
		{ VK_LCONTROL, "Left CONTROL key", 0},
		{ VK_RCONTROL, "Right CONTROL key", 0},
		{ VK_LMENU, "Left ALT key", 0},
		{ VK_RMENU, "Right ALT key", 0},
		{ VK_BROWSER_BACK, "Browser Back key", 0},
		{ VK_BROWSER_FORWARD, "Browser Forward key", 0},
		{ VK_BROWSER_REFRESH, "Browser Refresh key", 0},
		{ VK_BROWSER_STOP, "Browser Stop key", 0},
		{ VK_BROWSER_SEARCH, "Browser Search key", 0},
		{ VK_BROWSER_FAVORITES, "Browser Favorites key", 0},
		{ VK_BROWSER_HOME, "Browser Start and Home key", 0},
		{ VK_VOLUME_MUTE, "Volume Mute key", 0},
		{ VK_VOLUME_DOWN, "Volume Down key", 0},
		{ VK_VOLUME_UP, "Volume Up key", 0},
		{ VK_MEDIA_NEXT_TRACK, "Next Track key", 0},
		{ VK_MEDIA_PREV_TRACK, "Previous Track key", 0},
		{ VK_MEDIA_STOP, "Stop Media key", 0},
		{ VK_MEDIA_PLAY_PAUSE, "Play/Pause Media key", 0},
		{ VK_LAUNCH_MAIL, "Start Mail key", 0},
		{ VK_LAUNCH_MEDIA_SELECT, "Select Media key", 0},
		{ VK_LAUNCH_APP1, "Start Application 1 key", 0},
		{ VK_LAUNCH_APP2, "Start Application 2 key", 0},
		{ 0xB8, "Reserved", 0},
		{ 0xB9, "Reserved", 0},
		{ VK_OEM_1, ";: key US", 0},
		{ VK_OEM_PLUS, "+ key US", 0},
		{ VK_OEM_COMMA, ", key US", 0},
		{ VK_OEM_MINUS, "- key US", 0},
		{ VK_OEM_PERIOD, ". key US", 0},
		{ VK_OEM_2, "/? key US", 0},
		{ VK_OEM_3, "~ key US", 0},
		{ 0xC1, "Reserved", 0},
		{ 0xC2, "Reserved", 0},
		{ VK_GAMEPAD_A, "VK_GAMEPAD_A", 0},
		{ VK_GAMEPAD_B, "VK_GAMEPAD_B", 0},
		{ VK_GAMEPAD_X, "VK_GAMEPAD_X", 0},
		{ VK_GAMEPAD_Y, "VK_GAMEPAD_Y", 0},
		{ VK_GAMEPAD_RIGHT_SHOULDER, "VK_GAMEPAD_RIGHT_SHOULDER", 0},
		{ VK_GAMEPAD_LEFT_SHOULDER, "VK_GAMEPAD_LEFT_SHOULDER", 0},
		{ VK_GAMEPAD_LEFT_TRIGGER, "VK_GAMEPAD_LEFT_TRIGGER", 0},
		{ VK_GAMEPAD_RIGHT_TRIGGER, "VK_GAMEPAD_RIGHT_TRIGGER", 0},
		{ VK_GAMEPAD_DPAD_UP, "VK_GAMEPAD_DPAD_UP", 0},
		{ VK_GAMEPAD_DPAD_DOWN, "VK_GAMEPAD_DPAD_DOWN", 0},
		{ VK_GAMEPAD_DPAD_LEFT, "VK_GAMEPAD_DPAD_LEFT", 0},
		{ VK_GAMEPAD_DPAD_RIGHT, "VK_GAMEPAD_DPAD_RIGHT", 0},
		{ VK_GAMEPAD_MENU, "VK_GAMEPAD_MENU", 0},
		{ VK_GAMEPAD_VIEW, "VK_GAMEPAD_VIEW", 0},
		{ VK_GAMEPAD_LEFT_THUMBSTICK_BUTTON, "VK_GAMEPAD_LEFT_THUMBSTICK_BUTTON", 0},
		{ VK_GAMEPAD_RIGHT_THUMBSTICK_BUTTON, "VK_GAMEPAD_RIGHT_THUMBSTICK_BUTTON", 0},
		{ VK_GAMEPAD_LEFT_THUMBSTICK_UP, "VK_GAMEPAD_LEFT_THUMBSTICK_UP", 0},
		{ VK_GAMEPAD_LEFT_THUMBSTICK_DOWN, "VK_GAMEPAD_LEFT_THUMBSTICK_DOWN", 0},
		{ VK_GAMEPAD_LEFT_THUMBSTICK_RIGHT, "VK_GAMEPAD_LEFT_THUMBSTICK_RIGHT", 0},
		{ VK_GAMEPAD_LEFT_THUMBSTICK_LEFT, "VK_GAMEPAD_LEFT_THUMBSTICK_LEFT", 0},
		{ VK_GAMEPAD_RIGHT_THUMBSTICK_UP, "VK_GAMEPAD_RIGHT_THUMBSTICK_UP", 0},
		{ VK_GAMEPAD_RIGHT_THUMBSTICK_DOWN, "VK_GAMEPAD_RIGHT_THUMBSTICK_DOWN", 0},
		{ VK_GAMEPAD_RIGHT_THUMBSTICK_RIGHT, "VK_GAMEPAD_RIGHT_THUMBSTICK_RIGHT", 0},
		{ VK_GAMEPAD_RIGHT_THUMBSTICK_LEFT, "VK_GAMEPAD_RIGHT_THUMBSTICK_LEFT", 0},
		{ VK_OEM_4, "[{ for US", 0},
		{ VK_OEM_5, "\\| for US", 0},
		{ VK_OEM_6, "]} for US", 0},
		{ VK_OEM_7, "'\" for US", 0},
		{ VK_OEM_8, "Undefined", 0},
		{ 0xE0, "Reserved", 0},
		{ VK_OEM_AX, "'AX' key on Japanese AX kbd", 0},
		{ VK_OEM_102, "<> or \\| on RT 102-key kbd", 0},
		{ VK_ICO_HELP, "Help key on ICO", 0},
		{ VK_ICO_00, "00 key on ICO", 0},
		{ VK_PROCESSKEY, "VK_PROCESSKEY", 0},
		{ VK_ICO_CLEAR, "VK_ICO_CLEAR", 0},
		{ VK_PACKET, "VK_PACKET", 0},
		{ 0xE8, "Unassigned", 0},
		{ VK_OEM_RESET, "VK_OEM_RESET", 0},
		{ VK_OEM_JUMP, "VK_OEM_JUMP", 0},
		{ VK_OEM_PA1, "VK_OEM_PA1", 0},
		{ VK_OEM_PA2, "VK_OEM_PA2", 0},
		{ VK_OEM_PA3, "VK_OEM_PA3", 0},
		{ VK_OEM_WSCTRL, "VK_OEM_WSCTRL", 0},
		{ VK_OEM_CUSEL, "VK_OEM_CUSEL", 0},
		{ VK_OEM_ATTN, "VK_OEM_ATTN", 0},
		{ VK_OEM_FINISH, "VK_OEM_FINISH", 0},
		{ VK_OEM_COPY, "VK_OEM_COPY", 0},
		{ VK_OEM_AUTO, "VK_OEM_AUTO", 0},
		{ VK_OEM_ENLW, "VK_OEM_ENLW", 0},
		{ VK_OEM_BACKTAB, "VK_OEM_BACKTAB", 0},
		{ VK_ATTN, "VK_ATTN", 0},
		{ VK_CRSEL, "VK_CRSEL", 0},
		{ VK_EXSEL, "VK_EXSEL", 0},
		{ VK_EREOF, "VK_EREOF", 0},
		{ VK_PLAY, "VK_PLAY", 0},
		{ VK_ZOOM, "VK_ZOOM", 0},
		{ VK_NONAME, "VK_NONAME", 0},
		{ VK_PA1, "VK_PA1", 0},
		{ VK_OEM_CLEAR, "VK_OEM_CLEAR", 0},
		{ 0xFF, "Reserved", 0} };

KeySettings settings;

bool KeySettings::Create(char* fileNameOnly)
{
	bool ret = false;

	//https://www.geeksforgeeks.org/std-shared_mutex-in-cpp/
	std::unique_lock<std::shared_mutex> lock(protectSettings);

	WCHAR path[MAX_PATH] = { 0 };
	if (GetModuleFileName(NULL, path, MAX_PATH))
	{
		LPTSTR pStrPos = wcsrchr(path, '\\');
		if (pStrPos)
		{
			*pStrPos = NULL; // Strip filename - get just the path

			wsprintf(fullPathToFile, L"%s\\%S", path, fileNameOnly);
			
			SI_Error rc = m_ini.LoadFile(fullPathToFile);
			if (rc == SI_OK)
			{
				ret = ParseIni(m_ini);
			}
		}
	}

	return ret;
}

bool KeySettings::Destroy()
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);	

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

bool KeySettings::IsMacroKey(uint8_t keyCode)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	std::map<uint8_t, MacroKey>::iterator it = m_macroKeys.find(keyCode);
	if (it != m_macroKeys.end())
	{
		ret = true;
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
		if (keyCodeArray[i].bValid)
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
		if (keyCodeArray[i].bValid)
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

	if (macroKey.keyCode > 0)
	{
		std::unique_lock<std::shared_mutex> lock(protectSettings);

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
			SI_Error rc = m_ini.SaveFile(fullPathToFile, false);
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

		SI_Error rc = m_ini.SaveFile(fullPathToFile, false);
		if (rc == SI_OK)
		{
			ret = true;
		}
	}

	return ret;
}

bool KeySettings::IsValidMacroKey(uint8_t keyCode)
{
	return keyCodeArray[keyCode].bValid;
}

bool KeySettings::GetMacroKey(uint8_t keyCode, MacroKey& macroKey, bool bNoDecode)
{
	bool ret = false;

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