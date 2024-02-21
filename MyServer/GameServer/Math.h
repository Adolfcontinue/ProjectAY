#pragma once
#include "Define.h"
#include "Protocol.pb.h"
#include <cmath>

#define PI 3.141592 
static class Math
{
public:
	static double DegreeToRadian(double degree)
	{
		return degree * PI / 180;
	}

	static double RadianToDegree(double radian)
	{
		return radian * 180 / PI;
	}
};

struct Vector2
{
public:
	Vector2() {}
	Vector2(float x, float y) : X(x), Y(y) {}
	Vector2(float num) : X(num), Y(num) {}

	float X;
	float Y;
	
	void Clear()
	{
		X = 0;
		Y = 0;
	}

	Vector2 Normalize()
	{
		return Vector2(X / Size(), Y / Size());
	}

	int64 Size()
	{
		return sqrt(pow(X, 2) + pow(Y, 2));
	}

	void CopyFrom(float x, float y)
	{
		X = x;
		Y = y;
	}

	void CopyFrom(Vector2& other)
	{
		X = other.X;
		Y = other.Y;
	}

	float RotationYaw()
	{
		return Math::DegreeToRadian(atan2(Y, X));
	}


#pragma region Operator Overloading

	Vector2 operator+(const Vector2& other)
	{
		return Vector2(X + other.X, Y + other.Y);
	}

	Vector2 operator-(const Vector2& other)
	{
		return Vector2(X - other.X, Y - other.Y);
	}

	Vector2 operator*(float scalar)
	{
		return Vector2(X * scalar, Y * scalar);
	}

	Vector2 operator/(float scalar)
	{
		return Vector2(X / scalar, Y / scalar);
	}

	bool operator==(const Vector2 other)
	{
		return ((X == other.X) && (Y == other.Y));
	}

	bool operator!=(const Vector2 other)
	{
		return ((X != other.X) || (Y != other.Y));
	}

	bool operator >(const Vector2 other)
	{
		return ((X > other.X) && (Y > other.Y));
	}

	bool operator >=(const Vector2 other)
	{
		return ((X >= other.X) && (Y >= other.Y));
	}

	bool operator <(const Vector2& other)
	{
		return ((X < other.X) && (Y < other.Y));
	}

	bool operator <=(const Vector2& other)
	{
		return ((X <= other.X) && (Y <= other.Y));
	}

	void operator +=(const Vector2& other)
	{
		X += other.X;
		Y += other.Y;
	}

	void operator -=(const Vector2& other)
	{
		X -= other.X;
		Y -= other.Y;
	}

	void operator *=(float scalar)
	{
		X *= scalar;
		Y *= scalar;
	}

	void operator /=(float scalar)
	{
		X /= scalar;
		Y /= scalar;
	}

	void operator ++()
	{
		++X;
		++Y;
	}

	void operator ++(int)
	{
		X++;
		Y++;
	}

	void operator --()
	{
		--X;
		--Y;
	}

	void operator --(int)
	{
		X--;
		Y--;
	}

#pragma endregion
};


struct Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3(int x, int y, int z) : X(static_cast<float>(x)), Y(static_cast<float>(y)), Z(static_cast<float>(z)) {}
	Vector3(float num) : X(num), Y(num), Z(num) {}

	float X;
	float Y;
	float Z;

	void Clear()
	{
		X = 0;
		Y = 0;
		Z = 0;
	}

	Vector3 Normalize()
	{
		return Vector3(X / Size(), Y / Size(), Z / Size());
	}

	int64 Size()
	{
		return sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));
	}

	float Dot(Vector3 desc)
	{
		Vector3 normal = Normalize();
		Vector3 descNormal = desc.Normalize();
		float retVal = (normal.X * descNormal.X) + (normal.Y * descNormal.Y) + (normal.Z * descNormal.Z);
		retVal = Math::RadianToDegree(acos(retVal));
		return retVal;
	}

	Vector3 Cross(Vector3 other)
	{
		return Vector3(Y * other.Z - Z * other.Y, Z * other.X - X * other.Z, X * other.Y - Y * other.X);
	}

	void CopyFrom(Protocol::TransFormData& transform)
	{
		X = transform.x();
		Y = transform.y();
		Z = transform.z();
	}

	void CopyFrom(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	void CopyFrom(Vector3& other)
	{
		X = other.X;
		Y = other.Y;
		Z = other.Z;
	}

	float RotationYaw()
	{
		return Math::DegreeToRadian(atan2(Y, X));
	}


#pragma region Operator Overloading

	Vector3 operator+(const Vector3& other)
	{
		return Vector3(X + other.X, Y + other.Y, Z + other.Z);
	}

	Vector3 operator-(const Vector3& other)
	{
		return Vector3(X - other.X, Y - other.Y, Z - other.Z);
	}

	Vector3 operator*(float scalar)
	{
		return Vector3(X * scalar, Y * scalar, Z * scalar);
	}

	Vector3 operator/(float scalar)
	{
		return Vector3(X / scalar, Y / scalar, Z / scalar);
	}

	bool operator==(const Vector3& other)
	{
		return ((X == other.X) && (Y == other.Y) && (Z == other.Z));
	}

	bool operator!=(const Vector3& other)
	{
		return ((X != other.X) || (Y != other.Y) || (Z != other.Z));
	}

	bool operator >(const Vector3& other)
	{
		return ((X > other.X) && (Y > other.Y) && (Z > other.Z));
	}

	bool operator >=(const Vector3& other)
	{
		return ((X >= other.X) && (Y >= other.Y) && (Z >= other.Z));
	}

	bool operator <(const Vector3& other)
	{
		return ((X < other.X) && (Y < other.Y) && (Z < other.Z));
	}

	bool operator <=(const Vector3& other)
	{
		return ((X <= other.X) && (Y <= other.Y) && (Z <= other.Z));
	}

	void operator +=(const Vector3& other)
	{
		X += other.X;
		Y += other.Y;
		Z += other.Z;
	}

	void operator -=(const Vector3& other)
	{
		X -= other.X;
		Y -= other.Y;
		Z -= other.Z;
	}

	void operator *=(float scalar)
	{
		X *= scalar;
		Y *= scalar;
		Z *= scalar;
	}

	void operator /=(float scalar)
	{
		X /= scalar;
		Y /= scalar;
		Z /= scalar;
	}

	void operator ++()
	{
		++X;
		++Y;
		++Z;
	}

	void operator ++(int)
	{
		X++;
		Y++;
		Z++;
	}

	void operator --()
	{
		--X;
		--Y;
		--Z;
	}

	void operator --(int)
	{
		X--;
		Y--;
		Z--;
	}


#pragma endregion
};
