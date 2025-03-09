#include "BackgroundProcessing.h"
#include "StopWatch.h"

#pragma comment(lib, "User32.lib")

#define NO_DELAY_AFTER_LAST_KEY

bool BackgroundProcessing::Create()
{
	bool ret = false;

	if (globalSettings.Init(L"Keys.ini"))
	{
		m_bContinue = true;
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

void BackgroundProcessing::DebugMsg(char* szDbg)
{
#ifndef _DEBUG
	UNREFERENCED_PARAMETER(szDbg);
#else
	// Sends to the 'Output' Windows in Visual Studio
	OutputDebugStringA(szDbg);
#endif
}

void BackgroundProcessing::Work(BackgroundProcessing* pThis)
{
	if (pThis != nullptr)
	{
		pThis->DoWork();
	}
}

void BackgroundProcessing::DoWork()
{
	while (m_bContinue)
	{
		uint8_t macroKeyCode = MacroKeyWasPressed();

		while (m_bContinue && (macroKeyCode != 0))
		{
			KeySettings::MacroKey macroKey;
			if (globalSettings.Macro_Get(macroKeyCode, macroKey))
			{
				if (macroKey.keys.size() > 0) // Macros need keys to playback
				{
					macroKeyCode = ProcessMacroKey(macroKey);
				}
			}
		}

		if (m_bContinue)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeInMS));
		}
	}
}

uint8_t BackgroundProcessing::MacroKeyWasPressed()
{
	static uint8_t _keyboardState[256] = { 0 };
	uint8_t retKeyCode = 0;

	GetKeyState(0);
	uint8_t keyboardState[256] = { 0 };
	if (GetKeyboardState(keyboardState))
	{
		// See if anything changed since the last time we called 'GetKeyboardState'
		if (std::memcmp(_keyboardState, keyboardState, sizeof(_keyboardState)) != 0)
		{
			std::memcpy(_keyboardState, keyboardState, sizeof(_keyboardState));

			//for (int i = 0; (i < 256) && m_bContinue; ++i)
			for (int i = 1; (i < 0x7F) && m_bContinue; ++i) // Only go thru keys that are on a regular US keyboard
			{
				//https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getkeystate?redirectedfrom=MSDN
				// If the high order bit is 1, the key is down; 
				// otherwise it is up. To test if key is down 
				// bitwise and with 0x80
				if (keyboardState[i] & 0x80)
				{
					if (globalSettings.Macro_IsActive(i))
					{
						//DebugKeyPressed(i, keyboardState); // This is only needed for debug
						retKeyCode = i;
						break;
					}
				}
			}
		}
	}

	return retKeyCode;
}

uint8_t BackgroundProcessing::ProcessMacroKey(KeySettings::MacroKey macroKey)
{
	Stopwatch stopWatch;
	uint8_t   keyIndex   = 0;
	uint8_t   retKeyCode = 0;
	uint8_t   nKeys      = (uint8_t) macroKey.keys.size();
	
#ifdef _DEBUG
	// Can't use 'std::format' in c++20 because of the C++/CLI mode does not support C++ versions newer than C++17
	// have to use sprintf_s instead
	char szDbg[128] = { 0 };
	sprintf_s(szDbg, _countof(szDbg) - 1, "Macro started: %s\r\n", macroKey.name.c_str());
	DebugMsg(szDbg);
#endif

	while (m_bContinue && (keyIndex < nKeys))
	{
		if (stopWatch.IsStarted())
		{
			if (stopWatch.Elapsed() >= macroKey.keys[keyIndex].delayInMS)
			{
				//Waited the delay amount following the key.
				//Its time to advance to the next key.
				stopWatch.Stop();
				keyIndex++;
			}
		}
		else
		{
			stopWatch.Start();
			PlayKey(macroKey.keys[keyIndex]);
			
#ifdef NO_DELAY_AFTER_LAST_KEY
			//If we don't want a delay after the last key 
			//played when its not a looping macro.
			if (((keyIndex + 1) >= nKeys) && !macroKey.bLoop)
			{
#ifdef _DEBUG
				DebugMsg("Done(1)\r\n");
#endif
				break;
			}
#endif
		}

		if (keyIndex >= nKeys)
		{
			// We have reached the end of the keys to
			// playback

			if (macroKey.bLoop)
			{
				// If this is a loop macro, start over 
				// from the first key
				keyIndex = 0;
				stopWatch.Stop();
			}
			else
			{
				// Finished playing macro - exit
			
				// If we exit playing the macro here this means 
				// we waited for the delay at the end of the 
				// last key. To prevent this:
				// #define NO_DELAY_AFTER_LAST_KEY
#ifdef _DEBUG
				DebugMsg("Done(2)\r\n");
#endif
				break;
			}
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeInMS));

			// Check to see if a macro key is pressed while 
			// playing back the current macro
			retKeyCode = MacroKeyWasPressed();
			if (retKeyCode != 0)
			{
				if (!macroKey.bLoop)
				{
					// Current macro is cancled to start
					// playing another macro
#ifdef _DEBUG
					DebugMsg("Cancelled\r\n");
#endif
				}
				else
				{
					// If we are playing a loop macro then
					// stop playback of the current macro
					if (retKeyCode == macroKey.keyCode)
					{
						// If they pressed the same key as the 
						// current loop macro, make sure this 
						// just cancels the current macro
						// and does not start the macro
						// re-playing.
						retKeyCode = 0;
#ifdef _DEBUG
						DebugMsg("Loop ended\r\n");
#endif
					}
				}

				break;
			}
		}
	}

	return retKeyCode;
}

void BackgroundProcessing::PlayKey(KeySettings::PlaybackKey key)
{
#ifndef _DEBUG
	UNREFERENCED_PARAMETER(key);
#else
	// Can't use 'std::format' in c++20 because of the C++/CLI mode does not support C++ versions newer than C++17
	// have to use sprintf_s instead
	char szDbg[128] = { 0 };
	sprintf_s(szDbg, _countof(szDbg) - 1, "Key: %s\r\n", key.name.c_str());
	DebugMsg(szDbg);
#endif

	// *** Tyler put your code here ***
	//
}