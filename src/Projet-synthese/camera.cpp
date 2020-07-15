#include "camera.h"

void Camera::lookAt(const Point & center,const float size)
{
    m_center= center;
    m_position= vec2(0, 0);
    m_rotation= vec2(45,0);
    m_size= size;
    m_radius= size*50;
}
