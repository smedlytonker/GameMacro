#include "BackgroundProcessing.h"

#pragma comment(lib, "User32.lib")

bool BackgroundProcessing::Create()
{
	bool ret = false;

	if (globalSettings.Init("Keys.ini"))
	{
		m_bContinue  = true;
		m_mainThread = std::thread(Work, this);
		ret = true;
	}
	
	return ret;
}

bool BackgroundProcessing::Destroy()
{
	m_bContinue = false;
	
	if (m_mainThread.joinable())
	{
		m_mainThread.join();
	}

	return true;
}

void BackgroundProcessing::Work(BackgroundProcessing* pThis)
{
	if (pThis != nullptr)
	{
		while (pThis->m_bContinue)
		{
			pThis->DoWork();
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
}

void BackgroundProcessing::PlayKey(KeySettings::PlaybackKey key)
	{
#ifndef _DEBUG
	UNREFERENCED_PARAMETER(key);
#else
	char szDbg[128] = { 0 };
	const char* name = globalSettings.DecodeKey(key.keyCode);
	sprintf_s(szDbg, _countof(szDbg) - 1, "Key: %s\r\n", name);
	OutputDebugStringA(szDbg);
#endif
	}

uint8_t BackgroundProcessing::ProcessMacroKey(KeySettings::MacroKey macroKey)
{
	const uint8_t delayInMS     = 1;
	uint32_t      startPlayback = 0;
	uint8_t       keyIndex      = 0;
	size_t        nKeys         = macroKey.keys.size();
	uint8_t       macroKeyCode  = 0;

	while (m_bContinue && (keyIndex < nKeys))
	{
		if (startPlayback == 0)
		{
			startPlayback = GetTickCount();
			PlayKey(macroKey.keys[keyIndex]);
		}
		else
		{
			uint32_t elapsed = GetTickCount() - startPlayback;

			if (elapsed >= macroKey.keys[keyIndex].delayInMS)
			{
				//Advance to next key
				startPlayback = 0;
				keyIndex++;
			}
		}

		if (keyIndex >= nKeys)
		{
			if (macroKey.bLoop)
			{
				keyIndex = 0;
				startPlayback = 0;
			}
			else
			{
#ifdef _DEBUG
				OutputDebugStringA("Done\r\n");
#endif
				break; // Done
			}
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(delayInMS));
			macroKeyCode = MacroKeyWasPressed();
			if (macroKeyCode != 0)
			{
				if (!macroKey.bLoop)
				{
#ifdef _DEBUG
					OutputDebugStringA("Cancelled\r\n");
#endif
				}
				else
				{
					if (macroKeyCode == macroKey.keyCode)
					{
						macroKeyCode = 0;
#ifdef _DEBUG
						OutputDebugStringA("Loop ended\r\n");
#endif
					}
				}

				break;
			}
		}
	}

	return macroKeyCode;
}

void BackgroundProcessing::DebugKeyPressed(uint8_t keyCode, uint8_t keyboardState[])
{
#ifndef _DEBUG
	UNREFERENCED_PARAMETER(keyCode);
	UNREFERENCED_PARAMETER(keyboardState);
#else
	struct KeyPressed
	{
		uint8_t keyCode = 0;
		const char* name = nullptr;
		bool bCapital = false;
		bool bNumLock = false;
		bool bScrollLock = false;
		bool bInsert = false;
		bool bLeftShift = false;
		bool bRightShift = false;
		bool bLeftCtrl = false;
		bool bRightCtrl = false;
		bool bLeftAlt = false;
		bool bRightAlt = false;
		bool bLeftWKey = false;
		bool bRightWKey = false;
	};

	KeyPressed key = { 0 };
	key.name = globalSettings.DecodeKey(keyCode);
	key.keyCode = keyCode;

	//Toggle keys
	if (keyboardState[VK_CAPITAL] & 0x01) key.bCapital = true;
	if (keyboardState[VK_NUMLOCK] & 0x01) key.bNumLock = true;
	if (keyboardState[VK_SCROLL] & 0x01) key.bScrollLock = true;
	if (keyboardState[VK_INSERT] & 0x01) key.bInsert = true;

	// Keys that can be held down with other keys
	if (keyboardState[VK_LSHIFT] & 0x80) key.bLeftShift = true;
	if (keyboardState[VK_RSHIFT] & 0x80) key.bRightShift = true;
	if (keyboardState[VK_LCONTROL] & 0x80) key.bLeftCtrl = true;
	if (keyboardState[VK_RCONTROL] & 0x80) key.bRightCtrl = true;
	if (keyboardState[VK_LMENU] & 0x80) key.bLeftAlt = true;
	if (keyboardState[VK_RMENU] & 0x80) key.bRightAlt = true;
	if (keyboardState[VK_LWIN] & 0x80) key.bLeftWKey = true;
	if (keyboardState[VK_RWIN] & 0x80) key.bRightWKey = true;

	char szDbg[128] = { 0 };
	sprintf_s(szDbg, _countof(szDbg) - 1,
		"Key(%u)(%u, %u, %u, %u)(%u, %u)(%u, %u)(%u, %u)[%u, %u]: %s\r\n",
		key.keyCode,
		key.bCapital, key.bNumLock, key.bScrollLock, key.bInsert,
		key.bLeftShift, key.bRightShift,
		key.bLeftCtrl, key.bRightCtrl,
		key.bLeftAlt, key.bRightAlt,
		key.bLeftWKey, key.bRightWKey,
		key.name);

	OutputDebugStringA(szDbg);
#endif
}

uint8_t BackgroundProcessing::MacroKeyWasPressed()
{
	static uint8_t _keyboardState[256] = { 0 };
	uint8_t macroKeyCode = 0;

	GetKeyState(0);
	uint8_t keyboardState[256] = { 0 };
	if (GetKeyboardState(keyboardState))
	{
		// See if anything changed since the last time we called 'GetKeyboardState'
		if (memcmp(_keyboardState, keyboardState, sizeof(_keyboardState)) != 0)
		{
			memcpy(_keyboardState, keyboardState, sizeof(_keyboardState));

			//for (int i = 0; i < 256; ++i)
			for (int i = 1; i < 0x7F; ++i) // Only go thru keys that are on a regular US keyboard
			{
				//https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getkeystate?redirectedfrom=MSDN
				// If the high order bit is 1, the key is down; 
				// otherwise it is up. To test if key is down 
				// bitwise and with 0x80
				if (keyboardState[i] & 0x80)
				{
					if (globalSettings.IsActiveMacroKey(i))
					{
						//DebugKeyPressed(i, keyboardState); // This is only needed for debug
						macroKeyCode = i;
						break;
					}
				}
			}
		}
	}

	return macroKeyCode;
}

void BackgroundProcessing::DoWork()
{
	uint8_t macroKeyCode = MacroKeyWasPressed();
	
	while(macroKeyCode != 0)
	{
		KeySettings::MacroKey macroKey;
		if (globalSettings.GetMacroKey(macroKeyCode, macroKey, true))
		{
			if (macroKey.keys.size() > 0) // Macros need keys to playback
			{
				macroKeyCode = ProcessMacroKey(macroKey);
			}
		}
	}
}