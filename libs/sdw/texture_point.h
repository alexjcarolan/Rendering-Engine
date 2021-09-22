#ifndef TEXTURE_POINT_H
#define TEXTURE_POINT_H
#include <iostream>

class TexturePoint
{
public:
  float x;
  float y;

  TexturePoint()
  {
  }

  TexturePoint(float xPos, float yPos)
  {
    x = xPos;
    y = yPos;
  }
};

std::ostream &operator<<(std::ostream &os, const TexturePoint &point)
{
  os << "(" << point.x << ", " << point.y << ")" << std::endl;
  return os;
}
#endif