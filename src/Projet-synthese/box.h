#ifndef BOX_HPP
#define BOX_HPP

#include "vec.h"
#include "mat.h"
#include "mesh.h"

class Box
{
public:
  Box();
  Box(const Point &pmin, const Point &pmax);

  //vérifie si une boite de collision en touche une autre
  bool collides3d(Box &rhs, Vector &x);
  void updateColor(Color c);
  Point pmin, pmax;
  Transform T;
  Mesh meshcollider;

private:
  void createMesh();
};

#endif
