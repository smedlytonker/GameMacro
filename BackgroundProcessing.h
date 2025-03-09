#pragma once

#include "KeySettings.h"
#include <thread>

class BackgroundProcessing
{
public:
	bool Create();
	bool Destroy();
	
protected:
	static void Work(BackgroundProcessing* pThis);
private:
	void    DebugMsg(char* szDbg);
	void    DoWork();
	void    PlayKey(KeySettings::PlaybackKey key);
	uint8_t ProcessMacroKey(KeySettings::MacroKey macroKey);
	uint8_t BackgroundProcessing::MacroKeyWasPressed();

private:
	std::thread    m_mainThread;
	bool           m_bContinue = false;
	const uint32_t sleepTimeInMS = 1;

};
