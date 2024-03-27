#include "Wheel.h"

void Wheel::copyFrom(const Wheel& other)
{
    setRadius(other.radius);
    setMaterial(other.material);
}

Wheel::Wheel() : radius(0), material(Material::Undefined) {}

Wheel::Wheel(int radius, Material material)
{
    setRadius(radius);
    setMaterial(material);
}

int Wheel::getRadius() const
{
    return radius;
}

void Wheel::setRadius(int radius)
{
    if (radius <= 0)
    {
        return;
    }

    this->radius = radius;
}

Material Wheel::getMaterial() const
{
    return material;
}

void Wheel::setMaterial(Material material)
{
    this->material = material;
}
