//
// Self contained header for all of windows includes we have
// Dunno if this is shitty.
#ifdef ENABLE_DIRECTX
#	include <d3d9.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
#	ifndef UNICODE
#		define UNICODE
#	endif
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#	include <windows.h>
#	include <windowsx.h>
#	include <tchar.h>
#	include <Shlobj.h>
#	include <Shlwapi.h>
#endif