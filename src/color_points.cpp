
#include "color_points.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "helpers_for_godot.hpp"
#include <cassert>
#include <cstdint>

void
ColorPoints::add_color_point (const godot::Vector2i point,
                              const godot::Color color)
{
  colors.push_back (color);
  points.push_back (point);
}

int64_t
ColorPoints::get_count()const
{
    assert(colors.size() == points.size());
    return colors.size();
}

void
ColorPoints::_bind_methods ()
{
  using godot::ClassDB;
  using godot::D_METHOD;
  ClassDB::bind_method (D_METHOD ("add_color_point", "point", "color"),
                        &ColorPoints::add_color_point);
  BIND_METHOD_NO_ARGS(ColorPoints, get_count);
}