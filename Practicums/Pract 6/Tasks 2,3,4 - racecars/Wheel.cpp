#include "Wheel.h"

void Wheel::copyFrom(const Wheel& other)
{
    setRadius(other.radius);
    setMaterial(other.material);
}

Wheel::Wheel() : Wheel(0, Material::Undefined) {}

Wheel::Wheel(int radius, Material material)
{
    setRadius(radius);
    setMaterial(material);
}

Wheel::Wheel(const Wheel& other)
{
    copyFrom(other);
}

Wheel& Wheel::operator=(const Wheel& other)
{
    if (this != &other)
    {
        copyFrom(other);
    }
    return *this;
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
