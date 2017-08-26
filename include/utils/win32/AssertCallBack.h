#ifndef __UTILS_WIN32_ASSERTCALLBACK_H__
#define __UTILS_WIN32_ASSERTCALLBACK_H__

#include "utils/Assert.h"
#include "utils/win32/Win32Includes.h"
#include <string>
#include <cstdint>
#include <sstream>

namespace Niski
{
	namespace Utils
	{
		namespace Win32
		{
			LRESULT CALLBACK cbtProc(int code, WPARAM wParam, LPARAM lParam)
			{
				switch(code)
				{
				case HCBT_ACTIVATE:
					{
						//
						HWND hWnd = HWND(wParam);

						::SetDlgItemTextA(hWnd, IDYES, "Debug");
						::SetDlgItemTextA(hWnd, IDNO, "Ignore");
						::SetDlgItemTextA(hWnd, IDCANCEL, "Ignore All");

						return 0;
					}
					break;

				default:
					return CallNextHookEx(nullptr, code, wParam, lParam);
				}
			}

			Assert::callBackReturnVal win32AssertCallBack(const std::string& errorMessage, const std::string& fileName, const std::string& functionName, int32_t line)
			{
				std::ostringstream text;
				text << "Assertion failed!\n\nLine: " << line << "\n\nFile: " << fileName << "\n\nFunction " << functionName << "\n\n"; 
				text << "Error: " << errorMessage << "\n\n";
 
				HHOOK cbtHook = ::SetWindowsHookEx(WH_CBT, cbtProc, NULL, GetCurrentThreadId());
				int result = ::MessageBoxA(nullptr, text.str().c_str(), "Assertion Failed", MB_YESNOCANCEL | MB_ICONERROR);
				::UnhookWindowsHookEx(cbtHook);

				Assert::callBackReturnVal retVal;

				switch(result)
				{
				case IDYES:
					retVal = Assert::debug;
					break;

				case IDNO:
					retVal = Assert::ignore;
					break;

				case IDCANCEL:
				default:
					retVal = Assert::ignoreAll;
					break;
				}

				return retVal;
			}
		}
	}
}

#endif