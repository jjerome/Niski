#ifndef __ENGINE_PLAYER_H__
#define __ENGINE_PLAYER_H__

#include "engine/Entity.h"
#include "engine/World.h"

namespace Niski
{
	namespace Engine
	{
		class Player : public Entity
		{
		public:
			//
			// Need a player list that players automatically add themselves to. 
		public:
			Player(World* parent, const std::string& name);
			~Player(void);
		};
	}
}

#endif