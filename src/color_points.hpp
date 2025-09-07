#pragma once
#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/templates/vector.hpp"
#include "godot_cpp/variant/color.hpp"
#include "godot_cpp/variant/vector2i.hpp"
#include "helper_types.hpp"


/**
 * \class ColorPoints
 * \brief represents a series of points and an associated color
 */
class ColorPoints : public godot::Object
{
  GDCLASS (ColorPoints, godot::Object)

public:
  //! Adds a new point and color to the class
  void add_color_point (const godot::Vector2i point, const godot::Color color);
  //! \returns how many color points does the object have.
  i64 get_count()const;

  godot::Color get_color (const i64 index) const;
  godot::Vector2i get_point (const i64 index) const;

  void remove_at (const i64 index) ;

  void set_color (const i64 index, const godot::Color& new_color) ;
  void set_point (const i64 index, const godot::Vector2i new_point) ;

protected:
  static void _bind_methods ();

public:
  godot::Vector<godot::Color> colors = godot::Vector<godot::Color> ();
  godot::Vector<godot::Vector2i> points = godot::Vector<godot::Vector2i> ();
};