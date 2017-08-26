#ifndef __ENGINE_ENTITY_H__
#define __ENGINE_ENTITY_H__

#include <string>
#include <vector>
#include <map>
#include "renderer/Renderer.h"
#include "math/Vec2d.h"

namespace Niski
{
	namespace Engine
	{
		/*
		===============================================================================
		
			Base entity class. All entities are derived from this. Automatically
			adds itself to the list of children of its parent. 
		
		===============================================================================
		*/
		
		class Entity
		{
		public:
			typedef std::vector<Niski::Engine::Entity*> EntList;
			typedef std::vector<Niski::Engine::Entity*>::size_type EntId;

		public:
			static EntList&		getEntityList(void);
			static EntId		insertEntity(Niski::Engine::Entity* ent);
			static void			removeEntity(EntId id);

			static EntId		getEntityId(Niski::Engine::Entity* ent);

		public:
			Entity(Entity* parent, const std::string& name);
			virtual ~Entity(void);

			void									setParent(Entity* parent);
			Entity *								getParent(void)		const;

			EntId									getId(void) const;

			void									setName(const std::string& name);
			const std::string &						getName(void)		const;

			void									setPosition(const Niski::Math::Vector2D<float>& position);
			const Niski::Math::Vector2D<float> &	getPosition(void)	const;

			void									setVelocity(const Niski::Math::Vector2D<float>& velocity);
			const Niski::Math::Vector2D<float> &	getVelocity(void)	const;

			virtual void							think(const double deltaTime);
			virtual void							render(Niski::Renderer::Renderer& renderer) const;

			//
			// Child related junk
			void									addChild(Entity* child);
			void									removeChild(Entity* child);
			void									removeAllChildren(void);

			Entity*									findChild(const std::string& name);
					
			bool									hasChild(Entity* child);

		private:
			Entity*							parent_;
			EntId							id_;
			std::string						name_;
			Niski::Math::Vector2D<float>	position_;
			Niski::Math::Vector2D<float>	velocity_;
			EntList							children_;
		};
	}
}

#endif