
#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/templates/vector.hpp"
#include "godot_cpp/variant/color.hpp"
#include "godot_cpp/variant/vector2i.hpp"
#include <cstdint>


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
  int64_t get_count()const;

  godot::Color get_color (const int64_t index) const;
  godot::Vector2i get_point (const int64_t index) const;

  godot::Color& get_color_ref (const int64_t index);
  godot::Vector2i& get_point_ref (const int64_t index);

  void remove_at (const int64_t index) const;

  void set_color (const int64_t index) const;
  void set_point (const int64_t index) const;

protected:
  static void _bind_methods ();

public:
  godot::Vector<godot::Color> colors = godot::Vector<godot::Color> ();
  godot::Vector<godot::Vector2i> points = godot::Vector<godot::Vector2i> ();
};