#pragma once
#include <cmath>

struct Vector2 {
    constexpr Vector2(const float x = 0.0f, const float y = 0.0f) noexcept : x(x), y(y) {}

    constexpr const Vector2& operator-(const Vector2& other) const noexcept {
        return Vector2{x - other.x, y - other.y};
    }

    constexpr const Vector2& operator+(const Vector2& other) const noexcept {
        return Vector2{x + other.x, y + other.y};
    }

    constexpr const Vector2& operator/(const Vector2& other) const noexcept {
        return Vector2{x / other.x, y / other.y};
    }

    constexpr const Vector2& operator*(const Vector2& other) const noexcept {
        return Vector2{x * other.x, y * other.y};
    }

    constexpr const Vector2& operator%(const Vector2& other) const noexcept {
        return Vector2{x % other.x, y % other.y};
    }

    constexpr const Vector2& operator-=(const Vector2& other) const noexcept {
        return Vector2{x -= other.x, y -= other.y};
    }

    constexpr const Vector2& operator+=(const Vector2& other) const noexcept {
        return Vector2{x += other.x, y += other.y};
    }

    constexpr const Vector2& operator/=(const Vector2& other) const noexcept {
        return Vector2{x /= other.x, y /= other.y};
    }

    constexpr const Vector2& operator*=(const Vector2& other) const noexcept {
        return Vector2{x *= other.x, y *= other.y};
    }

    constexpr const Vector2& operator%=(const Vector2& other) const noexcept {
        return Vector2{x %= other.x, y %= other.y};
    }

    float x, y;
};


struct Vector3 {
    constexpr Vector3(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f) noexcept : x(x), y(y), z(z) {}

    constexpr const Vector3& operator-(const Vector3& other) const noexcept {
        return Vector3{x - other.x, y - other.y, z - other.z};
    }

    constexpr const Vector3& operator+(const Vector3& other) const noexcept {
        return Vector3{x + other.x, y + other.y, z + other.z};
    }

    constexpr const Vector3& operator/(const Vector3& other) const noexcept {
        return Vector3{x / other.x, y / other.y, z / other.z};
    }

    constexpr const Vector3& operator*(const Vector3& other) const noexcept {
        return Vector3{x * other.x, y * other.y, z * other.z};
    }

    constexpr const Vector3& operator%(const Vector3& other) const noexcept {
        return Vector3{x % other.x, y % other.y, z % other.z};
    }

    constexpr const Vector3& operator-=(const Vector3& other) const noexcept {
        return Vector3{x -= other.x, y -= other.y, z -= other.z};
    }

    constexpr const Vector3& operator+=(const Vector3& other) const noexcept {
        return Vector3{x += other.x, y += other.y, z += other.z};
    }

    constexpr const Vector3& operator/=(const Vector3& other) const noexcept {
        return Vector3{x /= other.x, y /= other.y, z /= other.z};
    }

    constexpr const Vector3& operator*=(const Vector3& other) const noexcept {
        return Vector3{x *= other.x, y *= other.y, z *= other.z};
    }

    constexpr const Vector3& operator%=(const Vector3& other) const noexcept {
        return Vector3{x %= other.x, y %= other.y, z %= other.z};
    }

    float x, y, z;
};

struct Vector4 {
    constexpr Vector4(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f, const float w = 0.0f) noexcept : x(x), y(y), z(z), w(w) {}

    constexpr const Vector4& operator-(const Vector4& other) const noexcept {
        return Vector4{x - other.x, y - other.y, z - other.z, w - other.w};
    }

    constexpr const Vector4& operator+(const Vector4& other) const noexcept {
        return Vector4{x + other.x, y + other.y, z + other.z, w + other.w};
    }

    constexpr const Vector4& operator/(const Vector4& other) const noexcept {
        return Vector4{x / other.x, y / other.y, z / other.z, w / other.w};
    }

    constexpr const Vector4& operator*(const Vector4& other) const noexcept {
        return Vector4{x * other.x, y * other.y, z * other.z, w * other.w};
    }

    constexpr const Vector4& operator%(const Vector4& other) const noexcept {
        return Vector4{x % other.x, y % other.y, z % other.z, w % other.w};
    }

    constexpr const Vector4& operator-=(const Vector4& other) const noexcept {
        return Vector4{x -= other.x, y -= other.y, z -= other.z, w -= other.w};
    }

    constexpr const Vector4& operator+=(const Vector4& other) const noexcept {
        return Vector4{x += other.x, y += other.y, z += other.z, w += other.w};
    }

    constexpr const Vector4& operator/=(const Vector4& other) const noexcept {
        return Vector4{x /= other.x, y /= other.y, z /= other.z, w /= other.w};
    }

    constexpr const Vector4& operator*=(const Vector4& other) const noexcept {
        return Vector4{x *= other.x, y *= other.y, z *= other.z, w *= other.w};
    }

    constexpr const Vector4& operator%=(const Vector4& other) const noexcept {
        return Vector4{x %= other.x, y %= other.y, z %= other.z, w %= other.w};
    }

    float x, y, z, w;
};