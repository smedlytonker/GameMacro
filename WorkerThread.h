#pragma once

#include <stack>
#include <thread>
#include <shared_mutex>
#include <vector>

class WorkerThread
{
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
