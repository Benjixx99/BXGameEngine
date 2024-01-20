#include <math.h>
#include "../../Headerfiles/Common/Vector2.hpp"


bx::Vector2::Vector2() {}

bx::Vector2::Vector2(double x) 
	: x (x), y (x) {}

bx::Vector2::Vector2(double x, double y)
	: x (x), y (y) {}

bx::Vector2::Vector2(const sf::Vector2f& vector)
	: x (vector.x), y (vector.y) {}

bx::Vector2::Vector2(const sf::Vector2i& vector)
	: x (vector.x), y (vector.y) {}

bx::Vector2::Vector2(const sf::Vector2u& vector)
	: x(vector.x), y(vector.y) {}

bool bx::Vector2::operator==(const bx::Vector2& vector) {
	return (x == vector.x && y == vector.y);
}

bool bx::Vector2::operator==(const bx::Vector2& vector) const {
	return (x == vector.x && y == vector.y);
}

bool bx::Vector2::operator!=(const bx::Vector2& vector) {
	return !(*this == vector);
}

bool bx::Vector2::operator!=(const bx::Vector2& vector) const {
	return !(*this == vector);
}

bx::Vector2& bx::Vector2::operator +=(const bx::Vector2& vector) {
	x += vector.x;
	y += vector.y;
	return *this;
}

bx::Vector2& bx::Vector2::operator -=(const bx::Vector2& vector) {
	x -= vector.x;
	y -= vector.y;
	return *this;
}

bx::Vector2& bx::Vector2::operator *=(const bx::Vector2& vector) {
	x *= vector.x;
	y *= vector.y;
	return *this;
}

bx::Vector2& bx::Vector2::operator *=(const double scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

bx::Vector2& bx::Vector2::operator /=(const bx::Vector2& vector) {
	x /= vector.x;
	y /= vector.y;
	return *this;
}

bx::Vector2& bx::Vector2::operator /=(const double scalar) {
	x /= scalar;
	y /= scalar;
	return *this;
}

bx::Vector2 bx::Vector2::operator +(const bx::Vector2& vector) const {
	return (bx::Vector2(x + vector.x, y + vector.y));
}

bx::Vector2 bx::Vector2::operator -(const bx::Vector2& vector) const {
	return (bx::Vector2(x - vector.x, y - vector.y));
}

bx::Vector2 bx::Vector2::operator *(const bx::Vector2& vector) const {
	return (bx::Vector2(x * vector.x, y * vector.y));
}

bx::Vector2 bx::Vector2::operator *(const double scalar) const {
	return (bx::Vector2(x * scalar, y * scalar));
}

bx::Vector2 bx::Vector2::operator /(const bx::Vector2& vector) const {
	return (bx::Vector2(x / vector.x, y / vector.y));
}

bx::Vector2 bx::Vector2::operator /(const double scalar) const {
	return (bx::Vector2(x / scalar, y / scalar));
}

void bx::Vector2::normalize() {
	double length = 1 / this->length();
	*this *= length;
}

double bx::Vector2::length() const {
	return std::sqrt((x * x + y * y));
}

double bx::Vector2::distance(const Vector2& vector) const {
	return std::sqrt(std::pow((x - vector.x), 2) + std::pow((y - vector.y), 2));
}

std::string bx::Vector2::toString() {
	return (std::to_string(x) + " : " + std::to_string(y));
}

// Global functions
std::ostream& operator<<(std::ostream& output, const bx::Vector2& vector) {
	return output << vector.x << " : " << vector.y << "\n";
}

