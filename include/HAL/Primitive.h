#pragma once

namespace Prism::HAL
{
  enum class Polygon_mode
  {
    Fill,
    Line,
    Point
  };

  enum class Cull_mode
  {
    None,
    Front,
    Back,
    Front_and_back
  };

  enum class Front_face
  {
    Counter_clockwise,
    Clockwise
  };

  enum class Primitive_topology
  {
    Point_list,
    Line_list,
    Line_strip,
    Triangle_list,
    Triangle_strip,
    Triangle_fan
  };
} // namespace Prism::HAL
