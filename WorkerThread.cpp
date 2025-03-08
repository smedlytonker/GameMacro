#include "WorkerThread.h"

#pragma comment(lib, "User32.lib")

bool WorkerThread::Create()
{
	bool ret = false;

	if (settings.Init("Keys.ini"))
	{
		m_bContinue = true;
		m_thread = std::make_shared<std::thread>(Work, this);
		ret = true;
	}
	
	return ret;
}

bool WorkerThread::Destroy()
{
	m_bContinue = false;
	
	if (m_thread->joinable())
	{
		m_thread->join();
	}

	return true;
}

void WorkerThread::Work(WorkerThread* pThis)
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

void WorkerThread::DoWork()
{
	static uint8_t _keyboardState[256] = { 0 };

	GetKeyState(0);
	uint8_t keyboardState[256] = { 0 };
	if(GetKeyboardState(keyboardState))
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
					if (settings.IsValidMacroKey(i))
					{
						KeyPressed key = { 0 };
						key.name = settings.DecodeKey(i);
						key.keyCode = i;

						//Toggle keys
						if (keyboardState[VK_CAPITAL]  & 0x01) key.bCapital    = true;
						if (keyboardState[VK_NUMLOCK]  & 0x01) key.bNumLock    = true;
						if (keyboardState[VK_SCROLL]   & 0x01) key.bScrollLock = true;
						if (keyboardState[VK_INSERT]   & 0x01) key.bInsert     = true;

						// Keys that can be held down with other keys
						if (keyboardState[VK_LSHIFT]   & 0x80) key.bLeftShift  = true;
						if (keyboardState[VK_RSHIFT]   & 0x80) key.bRightShift = true;
						if (keyboardState[VK_LCONTROL] & 0x80) key.bLeftCtrl   = true;
						if (keyboardState[VK_RCONTROL] & 0x80) key.bRightCtrl  = true;
						if (keyboardState[VK_LMENU]    & 0x80) key.bLeftAlt    = true;
						if (keyboardState[VK_RMENU]    & 0x80) key.bRightAlt   = true;
						if (keyboardState[VK_LWIN]     & 0x80) key.bLeftWKey   = true;
						if (keyboardState[VK_RWIN]     & 0x80) key.bRightWKey  = true;

#ifdef _DEBUG
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

						KeySettings::MacroKey macroKey;
						if (settings.GetMacroKey(key.keyCode, macroKey, true))
						{
							// user pressed a macro key
							break; // can stop looking now
						}
					}
				}
			}
		}
	}
}