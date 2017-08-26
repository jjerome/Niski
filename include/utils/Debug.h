#ifndef __UTILS_DEBUG_H__
#define __UTILS_DEBUG_H__

//
// _DEBUG is only defined when compiling for debug mode, so 
// just disable it here if it's not a debug build
#	ifndef _DEBUG
#		define _DEBUG 0
#	endif

#endif