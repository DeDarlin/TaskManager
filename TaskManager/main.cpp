#include <iostream>
#include "TaskManager.h"
#include "Console.h"

int main()
{
	Console::DisableResize();
	Console::LockConsoleBuffer(100, 30);

	TaskManager app;
	app.run();

	return 0;
}