#include "utils/win32/Win32Includes.h"

class AutoHandle
{
public:
	AutoHandle(HANDLE handle) : handle_(handle)
	{}

	~AutoHandle(void)
	{
		if(isValid())
		{
			CloseHandle(handle_);
		}
	}

	HANDLE get(void) const
	{
		return handle_;
	}

	bool isValid(void) const
	{
		return handle_ != nullptr;
	}

private:
	HANDLE handle_;
};