#pragma once

#include "KeySettings.h"
#include <thread>

class WorkerThread
{
private:
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

public:
	bool Create();
	bool Destroy();
	
protected:
	static void Work(WorkerThread* pThis);
private:
	void DoWork();

public:
	bool m_bContinue = false;

private:
	std::shared_ptr<std::thread> m_thread;

};
