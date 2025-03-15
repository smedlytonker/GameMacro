#include "KeySettings.h"
#include <sstream>

KeySettings globalSettings;


void KeySettings::KeyEntry::Init()
{
	Init(keyCode);
}

void KeySettings::KeyEntry::Init(uint8_t vKeyCode)
{
	struct KeyLookUp
	{
		uint8_t     keyCode;
		const char* name;
		bool        bMacroValid;
		bool        bPlaybackValid;
		bool        bExtended;
	};

	// Virtual key code list
	//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

	// Extended key list:
	//https://github.com/microsoft/Windows-driver-samples/blob/main/input/layout/kbdus/kbdus.c
	//https://github.com/go-vgo/robotgo/blob/master/key/keypress_c.h

	const KeyLookUp vkArray[256] = {
		{ 0x00, "Invalid", 0, 0, 0},
		{ VK_LBUTTON, "Left Mouse Button", 0, 0, 0},
		{ VK_RBUTTON, "Right Mouse Button", 0, 0, 0},
		{ VK_CANCEL, "Control-break processing", 0, 0, 0},
		{ VK_MBUTTON, "Middle Mouse Button", 0, 0, 0},
		{ VK_XBUTTON1, "X1 Mouse Button", 0, 0, 0},
		{ VK_XBUTTON2, "X2 Mouse Button", 0, 0, 0},
		{ 0x07, "Reserved", 0, 0, 0},
		{ VK_BACK, "Backspace", 0, 0, 0},
		{ VK_TAB, "Tab", 0, 0, 0},
		{ 0x0A, "Reserved", 0, 0, 0},
		{ 0x0B, "Reserved", 0, 0, 0},
		{ VK_CLEAR, "Clear", 0, 0, 0},
		{ VK_RETURN, "Enter", 0, 0, 0},
		{ 0x0E, "Unassigned", 0, 0, 0},
		{ 0x0F, "Unassigned", 0, 0, 0},
		{ VK_SHIFT, "Shift", 0, 0, 0},
		{ VK_CONTROL, "Control", 0, 0, 0},
		{ VK_MENU, "Alt", 0, 0, 0},
		{ VK_PAUSE, "Pause", 0, 0, 1},
		{ VK_CAPITAL, "Caps Lock", 0, 0, 0},
		{ VK_KANA, "IME Kana mode", 0, 0, 0},
		{ VK_IME_ON, "IME On", 0, 0, 0},
		{ VK_JUNJA, "IME Junja mode", 0, 0, 0},
		{ VK_FINAL, "IME final mode", 0, 0, 0},
		{ VK_HANJA, "IME Hanja mode", 0, 0, 0},
		{ VK_IME_OFF, "IME Off", 0, 0, 0},
		{ VK_ESCAPE, "Escape", 0, 0, 0},
		{ VK_CONVERT, "IME convert", 0, 0, 0},
		{ VK_NONCONVERT, "IME nonconvert", 0, 0, 0},
		{ VK_ACCEPT, "IME accept", 0, 0, 0},
		{ VK_MODECHANGE, "IME mode change request", 0, 0, 0},
		{ VK_SPACE, "Spacebar", 0, 0, 0},
		{ VK_PRIOR, "Page Up", 0, 0, 1},
		{ VK_NEXT, "Page Down", 0, 0, 1},
		{ VK_END, "End", 0, 0, 1},
		{ VK_HOME, "Home", 0, 0, 1},
		{ VK_LEFT, "Left Arrow", 0, 0, 1},
		{ VK_UP, "Up Arrow", 0, 0, 1},
		{ VK_RIGHT, "Right Arrow", 0, 0, 1},
		{ VK_DOWN, "Down Arrow", 0, 0, 1},
		{ VK_SELECT, "Select", 0, 0, 0},
		{ VK_PRINT, "Print", 0, 0, 0},
		{ VK_EXECUTE, "Execute", 0, 0, 0},
		{ VK_SNAPSHOT, "Print Screen", 0, 0, 1},
		{ VK_INSERT, "Insert", 0, 0, 1},
		{ VK_DELETE, "Delete", 0, 0, 1},
		{ VK_HELP, "Help", 0, 0, 0},
		{ 0x30, "0", 1, 1, 0},
		{ 0x31, "1", 1, 1, 0},
		{ 0x32, "2", 1, 1, 0},
		{ 0x33, "3", 1, 1, 0},
		{ 0x34, "4", 1, 1, 0},
		{ 0x35, "5", 1, 1, 0},
		{ 0x36, "6", 1, 1, 0},
		{ 0x37, "7", 1, 1, 0},
		{ 0x38, "8", 1, 1, 0},
		{ 0x39, "9", 1, 1, 0},
		{ 0x3A, "Reserved", 0, 0, 0},
		{ 0x3B, "Reserved", 0, 0, 0},
		{ 0x3C, "Reserved", 0, 0, 0},
		{ 0x3D, "Reserved", 0, 0, 0},
		{ 0x3E, "Reserved", 0, 0, 0},
		{ 0x3F, "Reserved", 0, 0, 0},
		{ 0x40, "Reserved", 0, 0, 0},
		{ 0x41, "A", 1, 1, 0},
		{ 0x42, "B", 1, 1, 0},
		{ 0x43, "C", 1, 1, 0},
		{ 0x44, "D", 1, 1, 0},
		{ 0x45, "E", 1, 1, 0},
		{ 0x46, "F", 1, 1, 0},
		{ 0x47, "G", 1, 1, 0},
		{ 0x48, "H", 1, 1, 0},
		{ 0x49, "I", 1, 1, 0},
		{ 0x4A, "J", 1, 1, 0},
		{ 0x4B, "K", 1, 1, 0},
		{ 0x4C, "L", 1, 1, 0},
		{ 0x4D, "M", 1, 1, 0},
		{ 0x4E, "N", 1, 1, 0},
		{ 0x4F, "O", 1, 1, 0},
		{ 0x50, "P", 1, 1, 0},
		{ 0x51, "Q", 1, 1, 0},
		{ 0x52, "R", 1, 1, 0},
		{ 0x53, "S", 1, 1, 0},
		{ 0x54, "T", 1, 1, 0},
		{ 0x55, "U", 1, 1, 0},
		{ 0x56, "V", 1, 1, 0},
		{ 0x57, "W", 1, 1, 0},
		{ 0x58, "X", 1, 1, 0},
		{ 0x59, "Y", 1, 1, 0},
		{ 0x5A, "Z", 1, 1, 0},
		{ VK_LWIN, "Left Windows Key", 0, 0, 1},
		{ VK_RWIN, "Right Windows Key", 0, 0, 1},
		{ VK_APPS, "Applications Key", 0, 0, 1},
		{ 0x93, "Reserved", 0, 0, 0},
		{ VK_SLEEP, "Sleep", 0, 0, 0},
		{ VK_NUMPAD0, "Numeric Keypad 0", 1, 1, 0},
		{ VK_NUMPAD1, "Numeric Keypad 1", 1, 1, 0},
		{ VK_NUMPAD2, "Numeric Keypad 2", 1, 1, 0},
		{ VK_NUMPAD3, "Numeric Keypad 3", 1, 1, 0},
		{ VK_NUMPAD4, "Numeric Keypad 4", 1, 1, 0},
		{ VK_NUMPAD5, "Numeric Keypad 5", 1, 1, 0},
		{ VK_NUMPAD6, "Numeric Keypad 6", 1, 1, 0},
		{ VK_NUMPAD7, "Numeric Keypad 7", 1, 1, 0},
		{ VK_NUMPAD8, "Numeric Keypad 8", 1, 1, 0},
		{ VK_NUMPAD9, "Numeric Keypad 9", 1, 1, 0},
		{ VK_MULTIPLY, "Multiply", 0, 0, 0},
		{ VK_ADD, "Add", 0, 0, 0},
		{ VK_SEPARATOR, "Separator", 0, 0, 0},
		{ VK_SUBTRACT, "Subtract", 0, 0, 0},
		{ VK_DECIMAL, "Decimal", 0, 0, 0},
		{ VK_DIVIDE, "Divide", 0, 0, 0},
		{ VK_F1, "F1", 1, 1, 0},
		{ VK_F2, "F2", 1, 1, 0},
		{ VK_F3, "F3", 1, 1, 0},
		{ VK_F4, "F4", 1, 1, 0},
		{ VK_F5, "F5", 1, 1, 0},
		{ VK_F6, "F6", 1, 1, 0},
		{ VK_F7, "F7", 1, 1, 0},
		{ VK_F8, "F8", 1, 1, 0},
		{ VK_F9, "F9", 1, 1, 0},
		{ VK_F10, "F10", 1, 1, 0},
		{ VK_F11, "F11", 1, 1, 0},
		{ VK_F12, "F12", 1, 1, 0},
		{ VK_F13, "F13", 0, 0, 0},
		{ VK_F14, "F14", 0, 0, 0},
		{ VK_F15, "F15", 0, 0, 0},
		{ VK_F16, "F16", 0, 0, 0},
		{ VK_F17, "F17", 0, 0, 0},
		{ VK_F18, "F18", 0, 0, 0},
		{ VK_F19, "F19", 0, 0, 0},
		{ VK_F20, "F20", 0, 0, 0},
		{ VK_F21, "F21", 0, 0, 0},
		{ VK_F22, "F22", 0, 0, 0},
		{ VK_F23, "F23", 0, 0, 0},
		{ VK_F24, "F24", 0, 0, 0},
		{ VK_NAVIGATION_VIEW, "Reserved", 0, 0, 0},
		{ VK_NAVIGATION_MENU, "Reserved", 0, 0, 0},
		{ VK_NAVIGATION_UP, "Reserved", 0, 0, 0},
		{ VK_NAVIGATION_DOWN, "Reserved", 0, 0, 0},
		{ VK_NAVIGATION_LEFT, "Reserved", 0, 0, 0},
		{ VK_NAVIGATION_RIGHT, "Reserved", 0, 0, 0},
		{ VK_NAVIGATION_ACCEPT, "Reserved", 0, 0, 0},
		{ VK_NAVIGATION_CANCEL, "Reserved", 0, 0, 0},
		{ VK_NUMLOCK, "Num Lock", 0, 0, 1},
		{ VK_SCROLL, "Scroll Lock", 0, 0, 0},
		{ 0x92, "= key on numpad", 0, 0, 0},
		{ 0x93, "Unregister word", 0, 0, 0},
		{ 0x94, "Register word", 0, 0, 0},
		{ 0x95, "Left OYAYUBI", 0, 0, 0},
		{ 0x96, "Right OYAYUBI", 0, 0, 0},
		{ 0x97, "Unassigned", 0, 0, 0},
		{ 0x98, "Unassigned", 0, 0, 0},
		{ 0x99, "Unassigned", 0, 0, 0},
		{ 0x9A, "Unassigned", 0, 0, 0},
		{ 0x9B, "Unassigned", 0, 0, 0},
		{ 0x9C, "Unassigned", 0, 0, 0},
		{ 0x9D, "Unassigned", 0, 0, 0},
		{ 0x9E, "Unassigned", 0, 0, 0},
		{ 0x9F, "Unassigned", 0, 0, 0},
		{ VK_LSHIFT,	"Left SHIFT key", 0, 0, 0},
		{ VK_RSHIFT,	"Right SHIFT key", 0, 0, 0},
		{ VK_LCONTROL, "Left CONTROL key", 0, 0, 0},
		{ VK_RCONTROL, "Right CONTROL key", 0, 0, 1},
		{ VK_LMENU, "Left ALT key", 0, 0, 0},
		{ VK_RMENU, "Right ALT key", 0, 0, 1},
		{ VK_BROWSER_BACK, "Browser Back key", 0, 0, 1},
		{ VK_BROWSER_FORWARD, "Browser Forward key", 0, 0, 1},
		{ VK_BROWSER_REFRESH, "Browser Refresh key", 0, 0, 1},
		{ VK_BROWSER_STOP, "Browser Stop key", 0, 0, 1},
		{ VK_BROWSER_SEARCH, "Browser Search key", 0, 0, 1},
		{ VK_BROWSER_FAVORITES, "Browser Favorites key", 0, 0, 1},
		{ VK_BROWSER_HOME, "Browser Start and Home key", 0, 0, 1},
		{ VK_VOLUME_MUTE, "Volume Mute key", 0, 0, 1},
		{ VK_VOLUME_DOWN, "Volume Down key", 0, 0, 1},
		{ VK_VOLUME_UP, "Volume Up key", 0, 0, 1},
		{ VK_MEDIA_NEXT_TRACK, "Next Track key", 0, 0, 1},
		{ VK_MEDIA_PREV_TRACK, "Previous Track key", 0, 0, 1},
		{ VK_MEDIA_STOP, "Stop Media key", 0, 0, 1},
		{ VK_MEDIA_PLAY_PAUSE, "Play/Pause Media key", 0, 0, 1},
		{ VK_LAUNCH_MAIL, "Start Mail key", 0, 0, 1},
		{ VK_LAUNCH_MEDIA_SELECT, "Select Media key", 0, 0, 1},
		{ VK_LAUNCH_APP1, "Start Application 1 key", 0, 0, 1},
		{ VK_LAUNCH_APP2, "Start Application 2 key", 0, 0, 1},
		{ 0xB8, "Reserved", 0, 0, 0},
		{ 0xB9, "Reserved", 0, 0, 0},
		{ VK_OEM_1, ";: key US", 0, 0, 0},
		{ VK_OEM_PLUS, "+ key US", 0, 0, 0},
		{ VK_OEM_COMMA, ", key US", 0, 0, 0},
		{ VK_OEM_MINUS, "- key US", 0, 0, 0},
		{ VK_OEM_PERIOD, ". key US", 0, 0, 0},
		{ VK_OEM_2, "/? key US", 0, 0, 0},
		{ VK_OEM_3, "~ key US", 0, 0, 0},
		{ 0xC1, "Reserved", 0, 0, 0},
		{ 0xC2, "Reserved", 0, 0, 0},
		{ VK_GAMEPAD_A, "VK_GAMEPAD_A", 0, 0, 0},
		{ VK_GAMEPAD_B, "VK_GAMEPAD_B", 0, 0, 0},
		{ VK_GAMEPAD_X, "VK_GAMEPAD_X", 0, 0, 0},
		{ VK_GAMEPAD_Y, "VK_GAMEPAD_Y", 0, 0, 0},
		{ VK_GAMEPAD_RIGHT_SHOULDER, "VK_GAMEPAD_RIGHT_SHOULDER", 0, 0, 0},
		{ VK_GAMEPAD_LEFT_SHOULDER, "VK_GAMEPAD_LEFT_SHOULDER", 0, 0, 0},
		{ VK_GAMEPAD_LEFT_TRIGGER, "VK_GAMEPAD_LEFT_TRIGGER", 0, 0, 0},
		{ VK_GAMEPAD_RIGHT_TRIGGER, "VK_GAMEPAD_RIGHT_TRIGGER", 0, 0, 0},
		{ VK_GAMEPAD_DPAD_UP, "VK_GAMEPAD_DPAD_UP", 0, 0, 0},
		{ VK_GAMEPAD_DPAD_DOWN, "VK_GAMEPAD_DPAD_DOWN", 0, 0, 0},
		{ VK_GAMEPAD_DPAD_LEFT, "VK_GAMEPAD_DPAD_LEFT", 0, 0, 0},
		{ VK_GAMEPAD_DPAD_RIGHT, "VK_GAMEPAD_DPAD_RIGHT", 0, 0, 0},
		{ VK_GAMEPAD_MENU, "VK_GAMEPAD_MENU", 0, 0, 0},
		{ VK_GAMEPAD_VIEW, "VK_GAMEPAD_VIEW", 0, 0, 0},
		{ VK_GAMEPAD_LEFT_THUMBSTICK_BUTTON, "VK_GAMEPAD_LEFT_THUMBSTICK_BUTTON", 0, 0, 0},
		{ VK_GAMEPAD_RIGHT_THUMBSTICK_BUTTON, "VK_GAMEPAD_RIGHT_THUMBSTICK_BUTTON", 0, 0, 0},
		{ VK_GAMEPAD_LEFT_THUMBSTICK_UP, "VK_GAMEPAD_LEFT_THUMBSTICK_UP", 0, 0, 0},
		{ VK_GAMEPAD_LEFT_THUMBSTICK_DOWN, "VK_GAMEPAD_LEFT_THUMBSTICK_DOWN", 0, 0, 0},
		{ VK_GAMEPAD_LEFT_THUMBSTICK_RIGHT, "VK_GAMEPAD_LEFT_THUMBSTICK_RIGHT", 0, 0, 0},
		{ VK_GAMEPAD_LEFT_THUMBSTICK_LEFT, "VK_GAMEPAD_LEFT_THUMBSTICK_LEFT", 0, 0, 0},
		{ VK_GAMEPAD_RIGHT_THUMBSTICK_UP, "VK_GAMEPAD_RIGHT_THUMBSTICK_UP", 0, 0, 0},
		{ VK_GAMEPAD_RIGHT_THUMBSTICK_DOWN, "VK_GAMEPAD_RIGHT_THUMBSTICK_DOWN", 0, 0, 0},
		{ VK_GAMEPAD_RIGHT_THUMBSTICK_RIGHT, "VK_GAMEPAD_RIGHT_THUMBSTICK_RIGHT", 0, 0, 0},
		{ VK_GAMEPAD_RIGHT_THUMBSTICK_LEFT, "VK_GAMEPAD_RIGHT_THUMBSTICK_LEFT", 0, 0, 0},
		{ VK_OEM_4, "[{ for US", 0, 0, 0},
		{ VK_OEM_5, "\\| for US", 0, 0, 0},
		{ VK_OEM_6, "]} for US", 0, 0, 0},
		{ VK_OEM_7, "'\" for US", 0, 0, 0},
		{ VK_OEM_8, "Undefined", 0, 0, 0},
		{ 0xE0, "Reserved", 0, 0, 0},
		{ VK_OEM_AX, "'AX' key on Japanese AX kbd", 0, 0, 0},
		{ VK_OEM_102, "<> or \\| on RT 102-key kbd", 0, 0, 0},
		{ VK_ICO_HELP, "Help key on ICO", 0, 0, 0},
		{ VK_ICO_00, "00 key on ICO", 0, 0, 0},
		{ VK_PROCESSKEY, "VK_PROCESSKEY", 0, 0, 0},
		{ VK_ICO_CLEAR, "VK_ICO_CLEAR", 0, 0, 0},
		{ VK_PACKET, "VK_PACKET", 0, 0, 0},
		{ 0xE8, "Unassigned", 0, 0, 0},
		{ VK_OEM_RESET, "VK_OEM_RESET", 0, 0, 0},
		{ VK_OEM_JUMP, "VK_OEM_JUMP", 0, 0, 0},
		{ VK_OEM_PA1, "VK_OEM_PA1", 0, 0, 0},
		{ VK_OEM_PA2, "VK_OEM_PA2", 0, 0, 0},
		{ VK_OEM_PA3, "VK_OEM_PA3", 0, 0, 0},
		{ VK_OEM_WSCTRL, "VK_OEM_WSCTRL", 0, 0, 0},
		{ VK_OEM_CUSEL, "VK_OEM_CUSEL", 0, 0, 0},
		{ VK_OEM_ATTN, "VK_OEM_ATTN", 0, 0, 0},
		{ VK_OEM_FINISH, "VK_OEM_FINISH", 0, 0, 0},
		{ VK_OEM_COPY, "VK_OEM_COPY", 0, 0, 0},
		{ VK_OEM_AUTO, "VK_OEM_AUTO", 0, 0, 0},
		{ VK_OEM_ENLW, "VK_OEM_ENLW", 0, 0, 0},
		{ VK_OEM_BACKTAB, "VK_OEM_BACKTAB", 0, 0, 0},
		{ VK_ATTN, "VK_ATTN", 0, 0, 0},
		{ VK_CRSEL, "VK_CRSEL", 0, 0, 0},
		{ VK_EXSEL, "VK_EXSEL", 0, 0, 0},
		{ VK_EREOF, "VK_EREOF", 0, 0, 0},
		{ VK_PLAY, "VK_PLAY", 0, 0, 0},
		{ VK_ZOOM, "VK_ZOOM", 0, 0, 0},
		{ VK_NONAME, "VK_NONAME", 0, 0, 0},
		{ VK_PA1, "VK_PA1", 0, 0, 0},
		{ VK_OEM_CLEAR, "VK_OEM_CLEAR", 0, 0, 0},
		{ 0xFF, "Reserved", 0, 0, 0} };
	
	keyCode = vKeyCode;
	name = vkArray[keyCode].name;
	bMacroValid = vkArray[keyCode].bMacroValid;
	bPlaybackValid = vkArray[keyCode].bPlaybackValid;
	bExtended = vkArray[keyCode].bExtended;
	keyCodeStr = std::to_string(keyCode);
}

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

bool KeySettings::Ini_ParseSection(CSimpleIniA& ini, MacroKey& macroKey, const char* sectionName)
{
	bool ret = false;

	macroKey.bLoop = ini.GetBoolValue(sectionName, "Loop", false);
	
	for (int i = 1; i < maxKeysAllowed; i++)
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
				// Read into a WORD in case some manually edited the file and added a scan code greater than 255
				uint16_t keyCode16 = (uint16_t)std::stoi(fields[0]);
				if((keyCode16 > 0) && (keyCode16 <= 255))
				{
					uint16_t delayInMS = (uint16_t) std::stoi(fields[1]);
					PlaybackKey playbackKey((uint8_t)keyCode16, delayInMS);
					playbackKey.bCtrl  = (bool) (std::stoi(fields[2]) > 0) ? true : false;
					playbackKey.bAlt   = (bool) (std::stoi(fields[3]) > 0) ? true : false;
					playbackKey.bShift = (bool) (std::stoi(fields[4]) > 0) ? true : false;
					playbackKey.bWKey  = (bool) (std::stoi(fields[5]) > 0) ? true : false;

					if (playbackKey.delayInMS >= 10)
					{
						macroKey.keys.push_back(playbackKey);
						ret = true;
					}
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
		uint16_t key16 = std::stoi(section.pItem);
		if ((key16 > 0) && (key16 <= 255))
		{
			MacroKey macroKey((uint8_t)key16);
			if (Ini_ParseSection(ini, macroKey, section.pItem))
			{
				m_macroKeys[macroKey.keyCode] =  macroKey;
				m_macroIsActive[macroKey.keyCode] = 1;
			}

			ret = true;
		}
	}

	return ret;
}

bool KeySettings::Macro_ListAvailable(std::vector<KeyEntry>& keys, uint8_t currentKeyCode)
{
	bool ret = false;

	std::unique_lock<std::shared_mutex> lock(protectSettings);

	// Don't need to go thru all the keys (i.e. 256 - just the one on a US keyboard)
	for (uint8_t keyCode = 1; keyCode < 0x7F; keyCode++)
	{
		KeyEntry key(keyCode);

		if (key.bMacroValid)
		{
			if (currentKeyCode == keyCode)
			{
				// Add the macro key that is already selected
				keys.push_back(key);
				ret = true;
			}
			else
			{
				// See if it is already assigned to be a macro key
				auto it = m_macroKeys.find(keyCode);
				if (it == m_macroKeys.end())
				{
					// Key not being used
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

	// Don't need to go thru all the keys (i.e. 256 - just the one on a US keyboard)
	for (uint8_t keyCode = 1; keyCode < 0x7F; keyCode++)
	{
		KeyEntry key(keyCode);
		if (key.bPlaybackValid)
		{
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
		if (m_macroKeys.size() < maxKeysAllowed)
		{
			std::string sectionStr = std::to_string(macroKey.keyCode);
			m_ini.Delete(sectionStr.c_str(), nullptr, true);
			m_ini.SetBoolValue(sectionStr.c_str(), "Loop", macroKey.bLoop);

			uint8_t nPlaybackKeys = 1;
			for (auto& playbackKey : macroKey.keys)
			{
				if (nPlaybackKeys <= maxKeysAllowed)
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
		keys.push_back((KeyEntry) macroKey.second);
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