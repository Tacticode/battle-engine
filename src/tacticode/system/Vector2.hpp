#pragma once

#include <cstdint>
#include <cmath>
#include <iostream>

#include "tacticode/system/error/DivideByZeroError.hpp"

namespace tacticode
{
	namespace engine
	{
		template<typename T>
		class Vector2
		{
		public:
			T x;
			T y;

		public:
			Vector2() : x(0), y(0)
			{
			}

			Vector2(T x_, T y_) : x(x_), y(y_)
			{
			}

		public:
			Vector2<T> operator+(const Vector2<T>& v) const
			{
				return (Vector2<T>(x + v.x, y + v.y));
			}

			Vector2<T>& operator+=(const Vector2<T>& v)
			{
				x += v.x;
				y += v.y;
				return *this;
			}

			Vector2<T> operator-(const Vector2<T>& v) const
			{
				return (Vector2<T>(x - v.x, y - v.y));
			}

			Vector2<T>& operator-=(const Vector2<T>& v)
			{
				x -= v.x;
				y -= v.y;
				return *this;
			}

			Vector2<T> operator*(const Vector2<T>& v) const
			{
				return (Vector2<T>(x * v.x, y * v.y));
			}

			Vector2<T>& operator*=(const Vector2<T>& v)
			{
				x *= v.x;
				y *= v.y;
				return *this;
			}

			Vector2<T> operator*(T v) const
			{
				return (Vector2<T>(x * v, y * v));
			}

			Vector2<T>& operator*=(T v)
			{
				x *= v;
				y *= v;
				return *this;
			}

			Vector2<T> operator/(T v) const
			{
				if (v == 0.f)
					throw system::DivideByZeroError();
				return Vector2<T>(x / v, y / v);
			}

			Vector2<T> &operator/=(T v) const
			{
				if (v == 0.f)
					throw system::DivideByZeroError();
				x /= v;
				y /= v;
				return *this;
			}

			T distance(const Vector2<T>& v) const
			{
				return std::sqrt(std::pow(v.x - x, 2) + std::pow(v.y - y, 2));
			}

			Vector2<T> rotate(float angle) const
			{
				Vector2<T> rt;
				rt.x = x * cos(angle) - y * sin(angle);
				rt.y = x * sin(angle) + y * cos(angle);
				return rt;
			}

			T length() const
			{
				return std::sqrt(x * x + y * y);
			}

			Vector2<T> normalize() const
			{
				T len = length();

				Vector2<T> norm;
				if (len != 0)
				{
					norm.x = x / len;
					norm.y = y / len;
				}
				return norm;
			}
		};

		typedef Vector2<float> Vector2f;
		typedef Vector2<int32_t> Vector2i;
		typedef Vector2<uint32_t> Vector2u;

		template <typename T>
		std::ostream & operator<<(std::ostream & os, const Vector2<T> &vec)
		{
			os << "{" << vec.x << "," << vec.y << "}";
			return os;
		}

	} // namespace engine
} // namespace melon
