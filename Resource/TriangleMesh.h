/*****************************
 * Copyright 2025 Cracklings *
 * Created Feb 22 2025       *
 *****************************/

#pragma once

#include <vector>


namespace Prism
{
  class Triangle_mesh
  {
  public:
    // return vertex positions of a triangle
    static std::vector<float> get_vertex_positions()
    {
      return {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
      };
    }
  };
}
