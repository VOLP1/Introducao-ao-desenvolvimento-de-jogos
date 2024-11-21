#include "../include/Rect.h"

Rect::Rect() : x(0), y(0), w(0), h(0) {}
Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

bool Rect::Contains(const Vec2& point) const {
    return (point.x >= x && point.x <= (x + w) &&
            point.y >= y && point.y <= (y + h));
}

Vec2 Rect::Center() const {
    return Vec2(x + w/2, y + h/2);
}

void Rect::SetCenter(const Vec2& center) {
    x = center.x - w/2;
    y = center.y - h/2;
}

Rect Rect::operator+(const Vec2& v) const {
    return Rect(x + v.x, y + v.y, w, h);
}