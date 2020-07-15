#ifndef _CAMERA_H
#define _CAMERA_H

#include "orbiter.h"
#include "vec.h"
#include "mat.h"

class Camera : public Orbiter
{
    public:
        //définie la position de la caméra
        void lookAt(const Point & center,const float size);
    private:
        Transform camT;

};
#endif