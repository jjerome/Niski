#ifndef __ENGINE_CONVAR_H__
#define __ENGINE_CONVAR_H__

#include <string>
#include <list>

namespace Niski
{
	namespace Engine
	{
		/*
		===============================================================================
		
			Base Console Variable class - all console variables derive from this class.
			Automatically inserts your console variable into the global list for 
			the console system to access, among other things.
		
		===============================================================================
		*/

		class ConVar 
		{
		public:
			typedef void (*callBackFn)(ConVar* var, const std::string& oldValue, const std::string& newValue);

		public:
			//
			// Static methods..
			typedef std::list<ConVar*> List;

			static List &	getConVars(void);
			static ConVar *	getConVar(const std::string& name);
			static void		addConVar(ConVar* var);
			static void		removeConVar(const std::string& name);
			static void		removeConVar(ConVar* var);

		public:
			ConVar(const std::string& name, const std::string& value, const std::string& helpText = "", callBackFn callBack = nullptr);
			ConVar(const std::string& name, int value, const std::string& helpText = "", callBackFn callBack = nullptr);
			ConVar(const std::string& name, float value, const std::string& helpText = "", callBackFn callBack = nullptr);
			~ConVar(void);

			const	std::string	&	getName(void)		const;

			void					setStrValue(const std::string& value);
			const	std::string &	getStrValue(void)	const;

			void					setIntValue(int value);
			const	int				getIntValue(void)	const;

			void					setFloatValue(float value);
			const	float			getFloatValue(void)	const;

			void					setHelpText(const std::string& helpText);
			const	std::string	&	getHelpText(void)	const;

		private:
			std::string	name_;
			std::string	strValue_;
			int			intValue_;
			float		floatValue_;
			std::string	helpText_;
			callBackFn	callBack_;
		};
	}
}

#endif