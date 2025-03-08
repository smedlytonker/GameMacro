#include "MainForm.h"
#include "WorkerThread.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace GameMacro;

// How to make a C++ WinForms Application
//https://www.youtube.com/watch?v=zv8DkkhBNR0

//In C++ / CLI, the^ symbol is called a "handle to object operator." It declares a handle, which is similar to a pointer but with automatic garbage collection.
//https://en.wikipedia.org/wiki/C%2B%2B/CLI

int main(array<String^>^ args)
{
	WorkerThread workerThread;

	if (workerThread.Create())
	{
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		MainForm form;
		Application::Run(% form);

		workerThread.Destroy();
	}

	return 0;
}