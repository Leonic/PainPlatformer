#pragma once
#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__

class CVector2D
{
public:
	CVector2D() : m_x(0), m_y(0) {}
	CVector2D(float x, float y) : m_x(x), m_y(y) {}

	// Returns the X value of the vector
	float GetX() const { return m_x; }
	// Returns the Y value of the vector
	float GetY() const { return m_y; }

	// Assigns a new X value to the vector
	void SetX(float x) { m_x = x; }
	// Assigns a new Y value to the vector
	void SetY(float y) { m_y = y; }

private:
	float m_x;
	float m_y;

public:
	// Various common mathmatical functions to a vector
	CVector2D operator+(const CVector2D& v2) const
	{
		return CVector2D(m_x + v2.m_x, m_y + v2.m_y);
	}

	CVector2D operator+(float i) const
	{
		return CVector2D(m_x + i, m_y + i);
	}

	friend CVector2D& operator+=(CVector2D& v1, const CVector2D& v2)
	{
		v1.m_x += v2.m_x;
		v1.m_y += v2.m_y;

		return v1;
	}

	CVector2D operator*(float scalar)
	{
		return CVector2D(m_x * scalar, m_y * scalar);
	}

	CVector2D& operator*=(float scalar)
	{
		m_x *= scalar;
		m_y *= scalar;

		return *this;
	}

	CVector2D operator-(const CVector2D& v2) const
	{
		return CVector2D(m_x - v2.m_x, m_y - v2.m_y);
	}

	CVector2D operator-(float i) const
	{
		return CVector2D(m_x - i, m_y - i);
	}

	friend CVector2D& operator-=(CVector2D& v1, const CVector2D& v2)
	{
		v1.m_x -= v2.m_x;
		v1.m_y -= v2.m_y;

		return v1;
	}

	CVector2D operator/(float scalar)
	{
		return CVector2D(m_x / scalar, m_y / scalar);
	}

	CVector2D& operator/=(float scalar)
	{
		m_x /= scalar;
		m_y /= scalar;

		return *this;
	}

	bool operator==(CVector2D& b)
	{
		return (m_x == b.m_x) && (m_y == b.m_y);
	}

	bool operator!=(CVector2D& b)
	{
		return (m_x != b.m_x) && (m_y != b.m_y);
	}
};
#endif