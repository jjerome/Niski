#ifndef __PHYSICS_BODY_H__
#define __PHYSICS_BODY_H__

#include <cstdint>
#include <vector>
#include "Math/Rectangle.h"
#include "Math/Vec2d.h"

namespace Niski
{
	namespace Physics
	{
		class World
		{
		public:
			World(const Niski::Math::Rect2D& bounds);
			~World(void);

			Body* createBody(const Niski::Math::Vector2D<float>& initialPosition);

			void simulate(const float deltaTime);

			void setGravity(const Niski::Math::Vector2D<float>& gravity);

		private:
			Niski::Math::Rect2D bounds_;
			std::vector<Body*> children_;
		};

		class IShape
		{
		public:
			IShape(void);
			~IShape(void);
		};

		class Rectangle : public IShape
		{
		public:
			Rectangle(const Niski::Math::Rect2D& bounds);
			~Rectangle(void);


		};

		class Body
		{
		public:
			Body(const Niski::Math::Vector2D<float>& initialPosition);
			~Body(void);

			void addForce(const Niski::Math::Vector2D<float>& force);

			void simulate(const float deltaTime);

		private:
			Niski::Math::Vector2D<float> position_;
			Niski::Math::Vector2D<float> velocity_;
			std::vector<Niski::Math::Vector2D<float>> forces_;
		};
	}
}

#endif

using namespace Niski::Physics;

World::World(const Niski::Math::Rect2D& bounds) : bounds_(bounds)
{

}

World::~World(void)
{
	//
	// Delete our children
	auto it = children_.begin();

	while(it != children_.end())
	{
		auto child = *it;
		it = children_.erase(it);
		delete child;
	}
}