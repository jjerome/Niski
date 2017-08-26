#include "scripting/PawnScript.h"

PawnScript::PawnScript(const std::string& filename) : memoryBlock_(nullptr)
{
	std::ifstream file(filename);

	file.read((char*)&header_, sizeof(header_));

	amx_Align16(&header_.magic);
	amx_Align32((uint32_t *)&header_.size);
	amx_Align32((uint32_t *)&header_.stp);

	if(header_.magic != AMX_MAGIC)
	{
		throw PawnScriptFailedToLoad("Invalid header. Are you sure this is a Pawn script?");
	}
	
	//
	// Allocate memory for the abstract machine. 
	memoryBlock_ = new char[header_.size];

	//
	// Load the file into our memory block. 
	file.seekg(std::ios_base::beg);
	file.read(memoryBlock_, header_.size);
	file.close();

	memset(&amx_, 0, sizeof(AMX));

	if(amx_Init(&amx_, memoryBlock_) != AMX_ERR_NONE)
	{
		amx_.base = nullptr;

		throw PawnScriptFailedToLoad("Failed to initialize abstract machine.");
	}
}

PawnScript::~PawnScript(void)
{
	if(amx_.base != nullptr)
	{
		amx_Cleanup(&amx_);
	}

	if(memoryBlock_ != nullptr)
	{
		delete memoryBlock_;
	}
}

uint32_t PawnScript::getMemorySize(void) const
{
	return header_.size;
}