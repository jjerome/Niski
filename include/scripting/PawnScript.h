#ifndef __SCRIPTING_PAWNSCRIPT_H__
#define __SCRIPTING_PAWNSCRIPT_H__

#include "amx.h"

#include <string>
#include <fstream>

class PawnScript
{
public:
	PawnScript(const std::string& filename);
	~PawnScript(void);

	uint32_t getMemorySize(void) const;
private:
	AMX amx_;
	AMX_HEADER header_;
	char* memoryBlock_;
};

class PawnScriptFailedToLoad : public std::runtime_error
{
public:
	PawnScriptFailedToLoad(const std::string& message) : std::runtime_error(message)
	{}
};

#endif