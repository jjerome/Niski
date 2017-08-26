#include <string>
#include "../../deps/tinyscheme-1.41/scheme.h"

class SchemeVM
{
public:
	SchemeVM(const std::string& identifier);
	~SchemeVM(void);

private:
	std::string identifier_;
	scheme*	vm_;
};

SchemeVM::SchemeVM(const std::string& identifier) : identifier_(identifier)
{
	vm_ = scheme_init_new();

	if(vm_ == nullptr)
	{
		//
		// error out
	}
}

SchemeVM::~SchemeVM(void)
{
	scheme_deinit(vm_);
}