#pragma once
#include "Logging.h"

class SimulateKey
{
public:
	SimulateKey(uint8_t keyCode, bool bExtended = false, bool bShift = false, bool bCtrl = false, bool bAlt = false, bool bWKey = false)
	{
		if (keyCode > 0)
		{
			INPUT   inputs[10] = { 0 }; //Array larger than we need
			uint8_t idx = 0;
			bool    bOtherKeysHeldDown = (bShift || bCtrl || bAlt || bWKey) ? true : false;
			
			// Down
			if (bOtherKeysHeldDown)
			{
				if (bShift) AddInput(VK_SHIFT,   false, true, inputs, idx);
				if (bCtrl)  AddInput(VK_CONTROL, false, true, inputs, idx);
				if (bAlt)   AddInput(VK_MENU,    false, true, inputs, idx);
				if (bWKey)  AddInput(VK_LWIN,    true,  true, inputs, idx);
				if (!SendKeys(inputs, idx))
				{
					Logging::DebugMsg("Error extra keys down: %u,%u,%u,%u", 
							bShift, bCtrl, bAlt, bWKey);
				}

				SleepInMS(1);
			}

			AddInput(keyCode, bExtended, true, inputs, idx);
			if (!SendKeys(inputs, idx))
			{
				Logging::DebugMsg("Error key down: %u", keyCode);
			}
			// Down finished

			SleepInMS(1); // Delay after key down

			//Up
			AddInput(keyCode, bExtended, false, inputs, idx);
			if (!SendKeys(inputs, idx))
			{
				Logging::DebugMsg("Error key up: %u", keyCode);
			}

			if (bOtherKeysHeldDown)
			{
				SleepInMS(1); // Release other keys after main key is up
				if (bShift) AddInput(VK_SHIFT, false, false, inputs, idx);
				if (bCtrl)  AddInput(VK_SHIFT, false, false, inputs, idx);
				if (bAlt)   AddInput(VK_MENU,  false, false, inputs, idx);
				if (bWKey)  AddInput(VK_LWIN,  true,  false, inputs, idx);
				if (!SendKeys(inputs, idx))
				{
					Logging::DebugMsg("Error extra keys up: %u,%u,%u,%u",
						bShift, bCtrl, bAlt, bWKey);
				}
			}
			// Up finished
		}
	}

private:
	inline void SleepInMS(uint32_t timeInMS)
	{
		// Think the standard library uses the multi-media timers and 
		// is a little more accurate than the normal Windows Sleep().
		std::this_thread::sleep_for(std::chrono::milliseconds(timeInMS));
	}

	bool SendKeys(INPUT inputs[], uint8_t& idx)
	{
		bool ret = false;

		uint32_t inputsToSend = idx + 1;
		uint32_t inputsSent   = SendInput(inputsToSend, inputs, sizeof(INPUT));
		
		if (inputsToSend == inputsSent)
		{
			ret = true;
		}

		idx = 0;

		return ret;
	}

	void AddInput(uint8_t keyCode, bool bExtended, bool bDown, INPUT inputs[], uint8_t& idx)
	{
		INPUT input = { 0 };
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = keyCode;
		if (!bDown)
			input.ki.dwFlags |= KEYEVENTF_KEYUP;
		if(bExtended)
			input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;

		inputs[idx] = input;
		idx++;
	}
};