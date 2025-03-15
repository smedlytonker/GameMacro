#include "BackgroundProcessing.h"
#include "StopWatch.h"
#include "SimulateKey.h"

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
		uint8_t keyCode = MacroKeyWasPressed();

		while (m_bContinue && (keyCode != 0))
		{
			KeySettings::MacroKey macroKey;
			if (globalSettings.Macro_Get(keyCode, macroKey))
			{
				if (macroKey.keys.size() > 0) // Macros need keys to playback
				{
					keyCode = ProcessMacroKey(macroKey);
				}
			}
		}

		if (m_bContinue)
		{
			SleeInMS(1);
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
				// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getkeystate?redirectedfrom=MSDN
				// If the high order bit is 1, the key is down; otherwise it is up.
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
	
	Logging::DebugMsg("Macro started: %s", macroKey.name.c_str());

	while (m_bContinue && (keyIndex < nKeys))
	{
		if (!stopWatch.IsStarted())
		{
			stopWatch.Start();
			PlayKey(macroKey.keys[keyIndex]);
		}
		else
		{
			uint32_t elapsedTime   = stopWatch.Elapsed();
			if (elapsedTime >= macroKey.keys[keyIndex].delayInMS)
			{
				//Waited the delay amount following the key.
				//Its time to advance to the next key.
				stopWatch.Stop();
				keyIndex++;

				Logging::DebugMsg("Delay: %u", elapsedTime);
				
				if (keyIndex < nKeys)
				{
					// Prevents adding unwanted delay
					continue;
				}
			}
		}

		if (keyIndex >= nKeys)
		{
			// We have reached the end of the keys to playback
			if (!macroKey.bLoop)
			{
				// Finished playing macro - exit
				Logging::DebugMsg("Done");
				break;
			}
			else
			{
				// If this is a loop macro, start over from the 
				//first key
				keyIndex = 0;
				stopWatch.Stop();
			}
		}
		else
		{
			SleeInMS(1);

			// Check to see if a macro key is pressed while 
			// playing back the current macro
			retKeyCode = MacroKeyWasPressed();
			if (retKeyCode != 0)
			{
				if ((retKeyCode == macroKey.keys[keyIndex].keyCode) ||
					(retKeyCode == macroKey.keyCode))
				{
					// Don't process key we are playing back, or the
					// macro key because its still being held down
					retKeyCode = 0;
				}
				else
				{
					if (!macroKey.bLoop)
					{
						// Current macro is cancled to start
						// playing another macro
						Logging::DebugMsg("Cancelled");
					}
					else
					{
						// If we are playing a loop macro then
						// stop playback of the current macro
						if (retKeyCode != macroKey.keyCode)
						{
							Logging::DebugMsg("Cancelled");
						}
						else
						{
							// If they pressed the same key as the 
							// current loop macro, make sure this 
							// just cancels the current macro
							// and does not start the macro
							// re-playing.
							retKeyCode = 0;
							Logging::DebugMsg("Loop ended");
						}
					}

					break;
				}
			}
		}
	}

	return retKeyCode;
}

void BackgroundProcessing::PlayKey(KeySettings::PlaybackKey key)
{
#if 1
	SimulateKey simulateKey(key.keyCode, key.bExtended, key.bShift, key.bCtrl, key.bAlt, key.bWKey);
#endif
}