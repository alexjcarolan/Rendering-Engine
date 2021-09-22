#ifndef TEXTURE_TRIANGLE_H
#define TEXTURE_TRIANGLE_H
#include "texture_point.h"
#include <iostream>

class TextureTriangle
{
public:
  TexturePoint vertices[3];

  TextureTriangle()
  {
  }

  TextureTriangle(TexturePoint v0, TexturePoint v1, TexturePoint v2)
  {
    vertices[0] = v0;
    vertices[1] = v1;
    vertices[2] = v2;
  }
};

std::ostream &operator<<(std::ostream &os, const TextureTriangle &triangle)
{
  os << triangle.vertices[0] << triangle.vertices[1] << triangle.vertices[2] << std::endl;
  return os;
}
#endif