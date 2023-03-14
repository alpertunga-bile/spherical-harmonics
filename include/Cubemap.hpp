#pragma once

#include <utility>
#include "Vector3D.h"

struct Vector2D
{
	Vector2D() = default;
	Vector2D(double a, double b) : x(a), y(b) {}

	double x = 0.0;
	double y = 0.0;
};

Vector3D Abs(Vector3D& v)
{
	Vector3D res;

	res.x = v.x < 0.0 ? v.x * -1.0 : v.x;
	res.y = v.y < 0.0 ? v.y * -1.0 : v.y;
	res.z = v.z < 0.0 ? v.z * -1.0 : v.z;

	return res;
}

Vector2D Abs(Vector2D& v)
{
	Vector2D res;

	res.x = v.x < 0.0 ? v.x * -1.0 : v.x;
	res.y = v.y < 0.0 ? v.y * -1.0 : v.y;

	return res;
}

std::pair<Vector2D, int> GetCubemapUVFace(Vector3D& pos)
{
	int face = 0;
	Vector3D posAbs = Abs(pos);
	double ma;
	Vector2D uv;

	if (posAbs.z >= posAbs.x && posAbs.z >= posAbs.y)
	{
		face = pos.z < 0.0 ? 5 : 4;
		ma = 0.5 / posAbs.z;
		uv = Vector2D(pos.z < 0.0 ? -pos.x : pos.x, -pos.y);
	}
	else if (posAbs.y >= posAbs.x)
	{
		face = pos.y < 0.0 ? 3 : 2;
		ma = 0.5 / posAbs.y;
		uv = Vector2D(pos.x, pos.y < 0.0 ? -pos.z : pos.z);
	}
	else
	{
		face = pos.x < 0.0 ? 1 : 0;
		ma = 0.5 / posAbs.x;
		uv = Vector2D(pos.x < 0.0 ? pos.z : -pos.z, -pos.y);
	}

	uv.x = uv.x * ma + 0.5;
	uv.y = uv.y * ma + 0.5;
	return std::pair<Vector2D, int>(Abs(uv), face);
}