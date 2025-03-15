#pragma once

#include "KeySettings.h"

class BackgroundProcessing
{
public:
	bool Create();
	bool Destroy();
	
protected:
	static void Work(BackgroundProcessing* pThis);
private:
	void    DoWork();
	void    PlayKey(KeySettings::PlaybackKey key);
	uint8_t ProcessMacroKey(KeySettings::MacroKey macroKey);
	uint8_t MacroKeyWasPressed();
	
	inline void SleeInMS(uint32_t timeInMS)
	{
		// Think the standard library uses the multi-media timers and 
		// is a little more accurate than the normal Windows Sleep().
		std::this_thread::sleep_for(std::chrono::milliseconds(timeInMS));
	}

private:
	std::thread m_mainThread;
	bool        m_bContinue = false;
};
