#pragma once

#include <iostream>
#include <string>
#include <SFML/System/Vector2.hpp>

namespace bx {

	class Vector2 {
	public:
		double x, y;

		Vector2();
		Vector2(double);
		Vector2(double, double);
		Vector2(const sf::Vector2f& vector);
		Vector2(const sf::Vector2i& vector);
		Vector2(const sf::Vector2u& vector);

		bool operator ==(const Vector2&);
		bool operator ==(const Vector2&) const;
		bool operator !=(const Vector2&);
		bool operator !=(const Vector2&) const;

		Vector2& operator +=(const Vector2&);
		Vector2& operator -=(const Vector2&);
		Vector2& operator *=(const Vector2&);
		Vector2& operator *=(const double);
		Vector2& operator /=(const Vector2&);
		Vector2& operator /=(const double);
		Vector2 operator +(const Vector2&) const;
		Vector2 operator -(const Vector2&) const;
		Vector2 operator *(const double) const;
		Vector2 operator *(const Vector2&) const;
		Vector2 operator /(const double) const;
		Vector2 operator /(const Vector2&) const;

		void normalize();
		double length() const;
		double distance(const Vector2&) const;

		std::string toString();
	};
}

std::ostream& operator <<(std::ostream&, const bx::Vector2&);
