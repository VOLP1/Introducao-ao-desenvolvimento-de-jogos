#include "../include/Vec2.h"
#include <cmath>

Vec2::Vec2() : x(0), y(0) {}
Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2& v) const {
    return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::operator-(const Vec2& v) const {
    return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::operator*(const float scalar) const {
    return Vec2(x * scalar, y * scalar);
}

float Vec2::Magnitude() const {
    return sqrt(x * x + y * y);
}

Vec2 Vec2::Normalized() const {
    float mag = Magnitude();
    if (mag == 0) return *this;
    return *this * (1.0f / mag);
}

float Vec2::Distance(const Vec2& v) const {
    return (*this - v).Magnitude();
}

float Vec2::Angle() const {
    return atan2(y, x);
}

Vec2 Vec2::Rotated(float angle) const {
    float cs = cos(angle);
    float sn = sin(angle);
    return Vec2(x * cs - y * sn, y * cs + x * sn);
}
