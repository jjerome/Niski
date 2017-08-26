#include "scripting/PawnScript.h"
#include <vector>

class Pawn
{
public:
	Pawn(void);
	~Pawn(void);

	PawnScript& createPawnScript(const std::string& fileName);

	//
	// Gets memory usage (in bytes).
	uint32_t getMemoryUsage(void) const;

	//
	// Gets number of loaded scripts.
	uint32_t getNumScripts(void) const;

private:
	std::vector<PawnScript*> scripts_;
	std::vector<int>			natives_;
};

Pawn::Pawn(void)
{}

Pawn::~Pawn(void)
{
	auto it = scripts_.begin();

	while(it != scripts_.end())
	{
		PawnScript* script = *it;
		it = scripts_.erase(it);
		delete script;
	}
}

PawnScript& Pawn::createPawnScript(const std::string& fileName)
{
	PawnScript* pawnScript = new PawnScript(fileName);

	scripts_.push_back(pawnScript);

	return *scripts_.back();
}

uint32_t Pawn::getMemoryUsage(void) const
{
	uint32_t memoryUsage = 0;

	for(auto script : scripts_)
	{
		memoryUsage += script->getMemorySize();
	}

	return memoryUsage;
}

uint32_t Pawn::getNumScripts(void) const
{
	return scripts_.size();
}