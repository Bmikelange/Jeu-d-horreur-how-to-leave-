#include "box.h"

Box::Box()
{
  pmin = Origin();
  pmax = Origin();
  T = Identity();
  createMesh();
}

Box::Box(const Point &i_pmin, const Point &i_pmax)
{
  pmin = i_pmin;
  pmax = i_pmax;
  T = Identity();
  createMesh();
}

void Box::createMesh()
{
  meshcollider = Mesh(GL_LINES);
  meshcollider.default_color(Color(1.f, 0.f, 0.f));
  Point p1(pmin);
  Point p2(pmax);
  Point p3(p1.x, p1.y, p2.z);
  Point p4(p1.x, p2.y, p1.z);
  Point p5(p2.x, p1.y, p1.z);
  Point p6(p1.x, p2.y, p2.z);
  Point p7(p2.x, p1.y, p2.z);
  Point p8(p2.x, p2.y, p1.z);
  meshcollider.vertex(p6);
  meshcollider.vertex(p2);
  meshcollider.vertex(p2);
  meshcollider.vertex(p8);
  meshcollider.vertex(p8);
  meshcollider.vertex(p4);
  meshcollider.vertex(p4);
  meshcollider.vertex(p6);
  meshcollider.vertex(p3);
  meshcollider.vertex(p7);
  meshcollider.vertex(p7);
  meshcollider.vertex(p5);
  meshcollider.vertex(p5);
  meshcollider.vertex(p1);
  meshcollider.vertex(p1);
  meshcollider.vertex(p3);
  meshcollider.vertex(p6);
  meshcollider.vertex(p3);
  meshcollider.vertex(p2);
  meshcollider.vertex(p7);
  meshcollider.vertex(p8);
  meshcollider.vertex(p5);
  meshcollider.vertex(p4);
  meshcollider.vertex(p1);
}

void Box::updateColor(Color c) {
  meshcollider.default_color(c);
}
bool Box::collides3d(Box &rhs, Vector &x)
{
  Vector d[6] = {
      Vector(-1, 0, 0),
      Vector(0, -1, 0),
      Vector(0, 0, -1),
      Vector(1, 0, 0),
      Vector(0, 1, 0),
      Vector(0, 0, 1)};
  Point p[6];

  for (int i = 0; i < 6; ++i)
  {
    Vector v = rhs.T.inverse()(T(d[i]));
    p[i].x = v.x > 0 ? rhs.pmin.x : rhs.pmax.x;
    p[i].y = v.y > 0 ? rhs.pmin.y : rhs.pmax.y;
    p[i].z = v.z > 0 ? rhs.pmin.z : rhs.pmax.z;
    p[i] = T.inverse()(rhs.T(p[i]));
    if ((i < 3 && p[i](i) <= pmin(i)) || (i >= 3 && p[i](i - 3) >= pmax(i - 3)))
    {
      x = -T(d[i]);
      meshcollider.default_color(Color(1.f, 0.f, 0.f));
      rhs.meshcollider.default_color(Color(1.f, 0.f, 0.f));

      return false;
    }
  }

  for (int i = 0; i < 6; ++i)
  {
    Vector v = T.inverse()(rhs.T(d[i]));
    p[i].x = v.x > 0 ? pmin.x : pmax.x;
    p[i].y = v.y > 0 ? pmin.y : pmax.y;
    p[i].z = v.z > 0 ? pmin.z : pmax.z;
    p[i] = rhs.T.inverse()(T(p[i]));
    if ((i < 3 && p[i](i) <= rhs.pmin(i)) || (i >= 3 && p[i](i - 3) >= rhs.pmax(i - 3)))
    {
      x = rhs.T(d[i]);
      meshcollider.default_color(Color(1.f, 0.f, 0.f));
      rhs.meshcollider.default_color(Color(1.f, 0.f, 0.f));
      return false;
    }
  }
  meshcollider.default_color(Color(0.f, 1.f, 0.f));
  rhs.meshcollider.default_color(Color(0.f, 1.f, 0.f));
  return true;
}
