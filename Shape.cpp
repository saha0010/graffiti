#include "Shape.h"

/*
 * Nur Getter und Setter hier
 */

float Shape::getX(void)
{return myX;}
float Shape::getY(void)
{return myY;}
float Shape::getZ(void)
{return myZ;}
bool Shape::getFilled(void)
{return filled;}

void Shape::setX(float x)
{ myX = x;}
void Shape::setY(float y)
{ myY = y;}
void Shape::setZ(float z)
{ myZ = z;}
void Shape::setFilled(bool fill)
{ filled = fill;}