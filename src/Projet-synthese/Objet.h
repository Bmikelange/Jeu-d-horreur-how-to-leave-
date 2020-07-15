#ifndef _OBJET_H
#define _OBJET_H


#include "mesh.h"
#include "box.h"
#include <vector>

class Objet
{   
public:
    Objet();
    ~Objet();

    //ajoute une boite de collision autour de l'objet
    void AddBox(Point pmin, Point pmax, Transform T);

    // l'objet
    Mesh mesh;
    //la liste des boites de collisions autour de l'objet 
    std::vector<Box> boxes;
};




#endif