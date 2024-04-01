#pragma once

enum class Material
{
	Undefined,
	Steel,
	Aluminium,
	Carbon,
	Magnesium
};
class Wheel
{
	int radius;
	Material material;
public:
	Wheel();
	Wheel(int radius, Material material);
	int getRadius() const;
	void setRadius(int radius);
	Material getMaterial() const;
	void setMaterial(Material material);
};