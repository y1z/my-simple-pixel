#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/variant/color.hpp"
#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/string_name.hpp"
#if !HELPERS_FOR_GODOT_HPP
#define HELPERS_FOR_GODOT_HPP
#include "godot_cpp/core/class_db.hpp"

#define BIND_METHOD_NO_ARGS(class,                                            \
                            method) /********************************** */    \
  ::godot::ClassDB::bind_method (::godot::D_METHOD (#method), &class ::method);

#define BIND_CONSTANT_VECTOR2I(vector2i_constant)                             \
  ::godot::ClassDB::bind_integer_constant (                                   \
      get_class_static (), "", vector2i_constant##_x, vector2i_constant.x);   \
  ::godot::ClassDB::bind_integer_constant (                                   \
      get_class_static (), "", vector2i_constant##_y, vector2i_constant.y);

namespace helper
{

/**
 * \param class_static : use the function get_class_static in the first
 * parameter.
 *
 * \param color_constant : the color that is going to become a constant
 *
 * \param constant_name : the name of the constant
 */
static inline void
bind_color_constant (const godot::StringName &class_static,
                     const godot::Color &color_constant,
                     const godot::String &constant_name)
{
    const int64_t length = constant_name.length();
  ::godot::ClassDB::bind_integer_constant (class_static, "", constant_name.insert(length, "_r"),
                                           color_constant.get_r8 ());

  ::godot::ClassDB::bind_integer_constant (class_static, "", constant_name.insert(length, "_g"),
                                           color_constant.get_g8 ());

  ::godot::ClassDB::bind_integer_constant (class_static, "", constant_name.insert(length,"_b"),
                                           color_constant.get_b8 ());

  ::godot::ClassDB::bind_integer_constant (class_static, "", constant_name.insert(length,"_a"),
                                           color_constant.get_a8 ());
}

}

#endif // UTIL_FOR_GODOT_HPP