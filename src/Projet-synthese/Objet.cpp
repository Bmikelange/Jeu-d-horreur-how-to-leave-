#include "Objet.h"

void Objet::AddBox(Point pmin, Point pmax, Transform T)
{   
    Box b = Box(pmin, pmax);
    b.T = T;
    boxes.push_back(b);
}

Objet::Objet()
{
}

Objet::~Objet()
{
}