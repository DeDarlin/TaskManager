#pragma once

namespace Console
{
	void DisableResize();

	void LockConsoleBuffer(short width, short height);

	void InitUtf8();

	void SleepMs(int ms);

	void Clear();
}