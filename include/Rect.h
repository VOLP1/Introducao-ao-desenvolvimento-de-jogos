#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect {
public:
    float x, y, w, h;
    
    Rect();
    Rect(float x, float y, float w, float h);
    
    bool Contains(const Vec2& point) const;
    Vec2 Center() const;
    void SetCenter(const Vec2& center);
    
    Rect operator+(const Vec2& v) const;
};

#endif