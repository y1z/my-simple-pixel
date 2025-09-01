#include "pixel_canvas.hpp"
#include "godot_cpp/classes/canvas_item.hpp"
#include "godot_cpp/classes/image.hpp"
#include "godot_cpp/classes/image_texture.hpp"
#include "godot_cpp/classes/packed_data_container.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/object.hpp"
#include "godot_cpp/core/print_string.hpp"
#include "godot_cpp/core/property_info.hpp"
#include "godot_cpp/variant/color.hpp"
#include "godot_cpp/variant/packed_byte_array.hpp"
#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "helpers_for_godot.hpp"

namespace gd = godot;

bool
PixelCanvas::start ()
{
  ref_image = create_image_default ();
  ref_texture = godot::ImageTexture::create_from_image (ref_image);
  // this->create_from_image(ref_image);
  ref_texture->set_image (ref_image);
  has_started = true;
  return has_started;
}

bool
PixelCanvas::is_started ()
{
  return has_started;
}

bool
PixelCanvas::test_is_working () const
{
  return true;
}

void
PixelCanvas::draw_line_l (const godot::Vector2i start,
                          const godot::Vector2i end)
{
  gd::print_line (gd::String ("[TODO]: Implement draw line"));

  for (int32_t i = 0; i < ref_image->get_width () - 1; ++i)
    {
      for (int32_t j = 0; j < ref_image->get_height () - 1; ++j)
        {

          ref_image->set_pixel (i, j, godot::Color("#FF00FFFF"));
        }
    }

  ref_texture->update(ref_image);
}

godot::Ref<godot::Image>
PixelCanvas::create_image_default ()
{
  return godot::Image::create_empty (PixelCanvas::DEFAULT_WIDTH,
                                     PixelCanvas::DEFAULT_HEIGHT, true,
                                     gd::Image::FORMAT_RGBA8);
}

godot::Ref<godot::Image>
PixelCanvas::get_image () const
{
  return ref_image;
}

godot::Ref<godot::ImageTexture>
PixelCanvas::get_texture() 
{
  return ref_texture;
}

int32_t
PixelCanvas::get_width () const
{
  return width;
}

int32_t
PixelCanvas::get_height () const
{
  return height;
}

godot::Color
PixelCanvas::get_color () const
{
  return current_color;
}

void
PixelCanvas::set_image (const godot::Ref<godot::Image> new_image)
{
  if (ref_image == new_image)
    {
      return;
    }
  ref_image = new_image;
}

void
PixelCanvas::set_width (int32_t new_width)
{
  width = new_width;
}

void
PixelCanvas::set_height (int32_t new_height)
{
  height = new_height;
}

void
PixelCanvas::set_color (const gd::Color new_color)
{
  current_color = new_color;
}

gd::Color
PixelCanvas::DEFAULT_COLOR ()
{

  // I tried to define this in the .hpp file but godot stops reconizing the
  // class if I do that
  static gd::Color s_DEFAULT_COLOR = gd::Color (1, 12, 1);
  return s_DEFAULT_COLOR;
}

void
PixelCanvas::_bind_methods ()
{
  using godot::ClassDB;
  using godot::D_METHOD;
  using godot::PropertyInfo;
  using godot::Variant;

  /// METHODS
  // gd::ClassDB::bind_method (D_METHOD ("test_is_working"),
  //&PixelCanvas::test_is_working);
  BIND_METHOD_NO_ARGS (PixelCanvas, test_is_working)
  BIND_METHOD_NO_ARGS (PixelCanvas, start)
  BIND_METHOD_NO_ARGS (PixelCanvas, is_started);

  gd::ClassDB::bind_method (D_METHOD ("draw_line_l", "start", "end"),
                            &PixelCanvas::draw_line_l);

  gd::ClassDB::bind_method (D_METHOD ("get_image"), &PixelCanvas::get_image);

  gd::ClassDB::bind_method (D_METHOD ("get_texture"), &PixelCanvas::get_texture);

  gd::ClassDB::bind_static_method (get_class_static (),
                                   D_METHOD ("DEFAULT_COLOR"),
                                   &PixelCanvas::DEFAULT_COLOR);

  gd::ClassDB::bind_static_method (get_class_static (),
                                   D_METHOD ("create_image_default"),
                                   &PixelCanvas::create_image_default);

  /// PROPERTIES
  gd::ClassDB::bind_method (D_METHOD ("set_width", "new_width"),
                            &PixelCanvas::set_width);
  gd::ClassDB::bind_method (D_METHOD ("get_width"), &PixelCanvas::get_width);
  ADD_PROPERTY (PropertyInfo (Variant::INT, "width"), "set_width",
                "get_width");

  gd::ClassDB::bind_method (D_METHOD ("set_height", "new_height"),
                            &PixelCanvas::set_height);
  gd::ClassDB::bind_method (D_METHOD ("get_height"), &PixelCanvas::get_height);
  ADD_PROPERTY (PropertyInfo (Variant::INT, "height"), "set_height",
                "get_height");

  /// CONSTANTS
  ///
  gd::ClassDB::bind_integer_constant (
      get_class_static (), "", "DEFAULT_HEIGHT", PixelCanvas::DEFAULT_HEIGHT);

  gd::ClassDB::bind_integer_constant (get_class_static (), "", "DEFAULT_WIDTH",
                                      PixelCanvas::DEFAULT_WIDTH);

  gd::ClassDB::bind_method (D_METHOD ("set_color"), &PixelCanvas::set_color);
  gd::ClassDB::bind_method (D_METHOD ("get_color"), &PixelCanvas::get_color);

  ADD_PROPERTY (PropertyInfo (Variant::COLOR, "current_color"), "set_color",
                "get_color");

  // BIND_CONSTANT(PixelCanvas::DEFAULT_HEIGHT);
}