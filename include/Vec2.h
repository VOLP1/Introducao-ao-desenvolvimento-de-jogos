#ifndef VEC2_H
#define VEC2_H

class Vec2 {
public:
    float x, y;
    
    Vec2();
    Vec2(float x, float y);
    
    Vec2 operator+(const Vec2& v) const;
    Vec2 operator-(const Vec2& v) const;
    Vec2 operator*(const float scalar) const;
    
    float Magnitude() const;
    Vec2 Normalized() const;
    float Distance(const Vec2& v) const;
    float Angle() const;
    Vec2 Rotated(float angle) const;
};

#endif