#ifndef __MATH_VEC2D_H__
#define __MATH_VEC2D_H__

#include <cmath>
#include <stdint.h>

namespace Niski
{
	namespace Math
	{
		template<class T>
		class Vector2D
		{
		public:
			Vector2D(T inX, T inY) : x(inX), y(inY)	{}
			Vector2D(const Vector2D& vec) : x(vec.x), y(vec.y) {}
			~Vector2D(void)	{}

			inline bool			operator ==(const Vector2D<T>& vec);

			inline bool			operator !=(const Vector2D<T>& vec);

			inline Vector2D<T>&	operator +=(const Vector2D<T>& vec);
			inline Vector2D<T>&	operator -=(const Vector2D<T>& vec);
			inline Vector2D<T>&	operator *=(const Vector2D<T>& vec);
			inline Vector2D<T>&	operator *=(T point);
			inline Vector2D<T>&	operator /=(const Vector2D<T>& vec);

			inline Vector2D<T>	operator +(const Vector2D<T>& vec) const;
			inline Vector2D<T>	operator -(const Vector2D<T>& vec) const;
			inline Vector2D<T>		operator *(const Vector2D<T>& vec) const;
			inline Vector2D<T>		operator *(T point) const;
			inline Vector2D<T>		operator /(const Vector2D<T>& vec) const;

			inline float		length(void)	const;

		public:
			T x;
			T y;
		};

		template<class T>
		bool Vector2D<T>::operator ==(const Vector2D<T>& vec)
		{
			if(vec.x == x && vec.y == y)
			{
				return true;
			}

			return false;
		}

		template<class T>
		bool Vector2D<T>::operator !=(const Vector2D<T>& vec)
		{
			if(vec.x != x || vec.y != y)
			{
				return true;
			}

			return false;
		}

		template<class T>
		Vector2D<T>& Vector2D<T>::operator +=(const Vector2D<T>& vec)
		{
			x += vec.x;
			y += vec.y;

			return *this;
		}

		template<class T>
		Vector2D<T>& Vector2D<T>::operator -=(const Vector2D<T>& vec)
		{
			x -= vec.x;
			y -= vec.y;

			return *this;
		}

		template<class T>
		Vector2D<T>& Vector2D<T>::operator *=(const Vector2D<T>& vec)
		{
			x *= vec.x;
			y *= vec.y;

			return *this;
		}

		template<class T>
		Vector2D<T>& Vector2D<T>::operator *=(T point)
		{
			x *= point;
			y *= point;

			return *this;
		}

		template<class T>
		Vector2D<T> Vector2D<T>::operator +(const Vector2D& vec) const
		{
			return Vector2D<T>(x + vec.x, y + vec.y);
		}

		template<class T>
		Vector2D<T> Vector2D<T>::operator -(const Vector2D& vec) const
		{
			return Vector2D<T>(x - vec.x, y - vec.y);
		}

		template<class T>
		Vector2D<T> Vector2D<T>::operator *(const Vector2D& vec) const
		{
			return Vector2D<T>(x * vec.x, y * vec.y);
		}

		template<class T>
		Vector2D<T> Vector2D<T>::operator *(T point) const
		{
			return Vector2D<T>(x * point, y * point);
		}

		template<class T>
		Vector2D<T> Vector2D<T>::operator /(const Vector2D& vec) const
		{
			return Vector2D<T>(x / vec.x, y / vec.y);
		}

		template<class T>
		float Vector2D<T>::length(void) const
		{
			return ::sqrt(x * x + y * y);
		}

		typedef Vector2D<int32_t> Point;
	}
}

#endif