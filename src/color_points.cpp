#include "color_points.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/error_macros.hpp"
#include "godot_cpp/variant/color.hpp"
#include "godot_cpp/variant/vector2i.hpp"
#include "helpers_for_godot.hpp"

namespace g = godot;

void
ColorPoints::add_color_point (const godot::Vector2i point,
                              const godot::Color color)
{
  colors.push_back (color);
  points.push_back (point);
}

int64_t
ColorPoints::get_count () const
{
  return colors.size ();
}

godot::Color
ColorPoints::get_color (const int64_t index) const
{
  const i64 size = colors.size ();
  CRASH_BAD_INDEX_MSG (index, size, "[ERR] OUT OF INDEX ");

  return colors[index];
}

g::Vector2i
ColorPoints::get_point (const int64_t index) const
{
  const i64 size = colors.size ();
  CRASH_BAD_INDEX_MSG (index, size, "[ERR] OUT OF INDEX ");
  return points[index];
}

void
ColorPoints::remove_at (const i64 index)
{
  const i64 color_size = colors.size ();
  const i64 point_size = points.size ();
  DEV_ASSERT (color_size == point_size);

  colors.remove_at (index);
  points.remove_at (index);
}

void
ColorPoints::set_color(const i64 index,const g::Color& new_color)
{
  const i64 size = colors.size();
  CRASH_BAD_INDEX_MSG (index, size, "[ERR] OUT OF INDEX ");
  colors.set(index,new_color);
}

void
ColorPoints::set_point(const i64 index,const g::Vector2i new_point)
{
  const i64 size = points.size();
  CRASH_BAD_INDEX_MSG (index, size, "[ERR] OUT OF INDEX ");
  points.set(index,new_point);
}

void
ColorPoints::_bind_methods ()
{
  using godot::ClassDB;
  using godot::D_METHOD;
  ClassDB::bind_method (D_METHOD ("add_color_point", "point", "color"),
                        &ColorPoints::add_color_point);
  BIND_METHOD_NO_ARGS (ColorPoints, get_count);

  ClassDB::bind_method (D_METHOD ("get_color", "index"),
                        &ColorPoints::get_color);

  ClassDB::bind_method (D_METHOD ("get_point", "index"),
                        &ColorPoints::get_point);

  ClassDB::bind_method (D_METHOD ("set_color", "index"),
                        &ColorPoints::set_color);

  ClassDB::bind_method (D_METHOD ("set_point", "index"),
                        &ColorPoints::set_point);
}