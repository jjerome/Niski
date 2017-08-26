#ifndef __ENGINE_CONCOMMAND_H__
#define __ENGINE_CONCOMMAND_H__

#include <string>
#include <list>

namespace Niski
{
	namespace Engine
	{
		/*
		===============================================================================
		
			Base console command - all console commands are derived from this class
			Automatically adds you to the global list of console commands (that the 
			console, key bind system, etc can access). 
		
		===============================================================================
		*/
		class ConCommand
		{
		public:
			//
			// Static methods
			typedef std::list<ConCommand*> List;
			static List &		getList(void);
			static ConCommand *	getCommand(const std::string& name);
			static void			addCommand(ConCommand* cmd);
			static void			removeCommand(ConCommand* cmd);

		public:
			ConCommand(const std::string& name);
			~ConCommand(void);

			const std::string &	getName(void) const;

			virtual void		run(void/*std::list<std::string&>& args*/);

		private:
			std::string name_;
		};
	}
}

#endif