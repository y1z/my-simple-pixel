#include "pixel_canvas.hpp"
#include "color_points.hpp"
#include "godot_cpp/classes/image.hpp"
#include "godot_cpp/classes/image_texture.hpp"
#include "godot_cpp/classes/packed_data_container.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/error_macros.hpp"
#include "godot_cpp/core/object.hpp"
#include "godot_cpp/core/print_string.hpp"
#include "godot_cpp/core/property_info.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/color.hpp"
#include "godot_cpp/variant/packed_byte_array.hpp"
#include "godot_cpp/variant/packed_color_array.hpp"
#include "godot_cpp/variant/packed_vector2_array.hpp"
#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/variant/vector2i.hpp"
#include "helper_types.hpp"
#include "helpers_for_godot.hpp"

#include <array>
#include <cstdint>

namespace gd = godot;

static constexpr int64_t red[4] = { 0xbb, 0x00, 0x00, 0xff };
static constexpr int64_t blue[4] = { 0x00, 0xbb, 0x00, 0xff };
static constexpr int64_t green[4] = { 0x00, 0x00, 0xbb, 0xff };
static constexpr int64_t half_transparent[4] = { 0x00, 0x00, 0x00, 0xff / 2 };

bool
PixelCanvas::start ()
{
  ref_image = create_image_default ();
  ref_texture = godot::ImageTexture::create_from_image (ref_image);
  data_array.resize (DEFAULT_HEIGHT * DEFAULT_WIDTH
                     * get_format_color_offset ());
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
PixelCanvas::draw_points (const godot::PackedVector2Array &points_to_draw)
{
  if (!check_if_pixel_canvas_was_started ())
    {
      return;
    }

  godot::PackedByteArray data = ref_image->get_data ();
  const int64_t format_color_offset = get_format_color_offset ();
  const int64_t row_offset = ref_image->get_width ();

  for (const gd::Vector2 &vec : points_to_draw)
    {
      const int64_t byte_index
          = (row_offset * static_cast<int64_t> (vec.y) * format_color_offset)
            + (static_cast<int64_t> (vec.x) * format_color_offset);
      data.set (byte_index + 0, current_color.get_r8 ());
      data.set (byte_index + 1, current_color.get_g8 ());
      data.set (byte_index + 2, current_color.get_b8 ());
      data.set (byte_index + 3, current_color.get_a8 ());
    }

  update_texture (data);
}

// Bresenham's Line algorithm
void
PixelCanvas::draw_line_l (const godot::Vector2i start,
                          const godot::Vector2i end)
{
  if (!check_if_pixel_canvas_was_started ())
    {
      return;
    }
  gd::print_line (gd::String ("[TODO]: Implement draw line"));

  godot::Vector2i max_in_x = (start.x > end.x) ? start : end;

  godot::Vector2i current_point = start;
  const godot::Vector2i delta = end - start;
  const godot::Vector2 f_start = start;
  const godot::Vector2 f_end = end;
  float slope = (f_start.x - f_end.x) / (f_start.y - f_end.y);
}

void
PixelCanvas::draw_vertical_line (const gd::Vector2i start,
                                 const int64_t length, const bool go_up)
{
  if (length < 0)
    {
      gd::String error_string = godot::vformat (
          "CAN'T have a negative length, the length is %d", length);
      gd::print_error (error_string);
      return;
    }

  int64_t current_y_value = start.y;
  const int64_t format_color_offset = get_format_color_offset ();
  const int64_t row_offset = format_color_offset * width;
  const int64_t colum_that_is_always_drawn = format_color_offset * start.x;
  const int64_t increase_in_y = (go_up) ? -1 : 1;

  for (i64 i = 0; i < length; ++i)
    {
      const int64_t final_index
          = (current_y_value * row_offset) + colum_that_is_always_drawn;

      data_array.set (final_index + 0, current_color.get_r8 ());
      data_array.set (final_index + 1, current_color.get_g8 ());
      data_array.set (final_index + 2, current_color.get_b8 ());
      data_array.set (final_index + 3, current_color.get_a8 ());

      current_y_value = current_y_value + increase_in_y;
    }

  update_texture (data_array);
}

void
PixelCanvas::draw_horizontal_line (const godot::Vector2i start,
                                   const int64_t length, const bool go_right)
{
  if (length < 0)
    {
      gd::String error_string = godot::vformat (
          "CAN'T have a negative length, the length is %d", length);
      gd::print_error (error_string);
      return;
    }

  i64 current_x_value = start.x;
  const i64 increase_in_x = (go_right) ? 1 : -1;
  const i64 format_color_offset = get_format_color_offset ();
  const i64 row_offset = format_color_offset * width;
  const i64 constant_row_index = row_offset * start.y;

  for (i64 i = 0; i < length; ++i)
    {
      const i64 final_index
          = constant_row_index + (current_x_value * format_color_offset);

      data_array.set (final_index + 0, current_color.get_r8 ());
      data_array.set (final_index + 1, current_color.get_g8 ());
      data_array.set (final_index + 2, current_color.get_b8 ());
      data_array.set (final_index + 3, current_color.get_a8 ());

      current_x_value = current_x_value + increase_in_x;
    }

  update_texture (data_array);
}

void
PixelCanvas::draw_rainbow_effect ()
{

  if (!check_if_pixel_canvas_was_started ())
    {
      return;
    }
  const float inverse_width = 1.0f / ref_image->get_width ();
  const float inverse_height = 1.0f / ref_image->get_height ();
  const float inverse_size
      = 1.0f / ref_image->get_width () + ref_image->get_height ();
  for (int32_t i = 0; i < ref_image->get_width () - 1; ++i)
    {
      for (int32_t j = 0; j < ref_image->get_height () - 1; ++j)
        {
          gd::Color pixel_color = godot::Color (
              inverse_width * i, inverse_height * j, 0.5f, 1.0f);
          ref_image->set_pixel (i, j, pixel_color);
        }
    }

  ref_texture->update (ref_image);
}

void
PixelCanvas::draw_on_data ()
{

  if (!check_if_pixel_canvas_was_started ())
    {
      return;
    }
  gd::print_line ("start 'draw_on_data'");
  gd::PackedByteArray data = ref_image->get_data ();

  const int64_t row_offset = ref_image->get_width ();
  int64_t colum_offset = 0;
  const int64_t format_color_offset = get_format_color_offset ();

  for (int64_t row = 0; row < ref_image->get_height (); ++row)
    {
      int64_t index = (row_offset * row * format_color_offset)
                      + (colum_offset * format_color_offset);
      data.set (index + 0, red[0]);
      data.set (index + 1, red[1]);
      data.set (index + 2, red[2]);
      data.set (index + 3, red[3]);
      colum_offset += 1;
    }
  gd::print_line (gd::String ("size of data = %s") % data.size ());

  update_texture (data);

  gd::print_line ("end 'draw_on_data'");
}

void
PixelCanvas::draw_diagnal_rgb_effect ()
{
  if (!check_if_pixel_canvas_was_started ())
    {
      return;
    }

  gd::PackedByteArray data = ref_image->get_data ();

  std::array<std::array<int64_t, 4>, 4> meta_color_array;
  meta_color_array[0]
      = std::array<int64_t, 4>{ red[0], red[1], red[2], red[3] };
  meta_color_array[1]
      = std::array<int64_t, 4>{ blue[0], blue[1], blue[2], blue[3] };
  meta_color_array[2]
      = std::array<int64_t, 4>{ green[0], green[1], green[2], green[3] };
  meta_color_array[3]
      = std::array<int64_t, 4>{ half_transparent[0], half_transparent[1],
                                half_transparent[2], half_transparent[3] };
  int64_t iterations = 0;
  int64_t meta_iteration = 0;
  for (int64_t i = 0; i < data.size (); i += 4)
    {
      int64_t color_to_select = (iterations + meta_iteration) % 4;
      std::array<int64_t, 4> chosen_color = meta_color_array[color_to_select];

      data.set (i, chosen_color[0]);
      data.set (i + 1, chosen_color[1]);
      data.set (i + 2, chosen_color[2]);
      data.set (i + 3, chosen_color[3]);
      ++iterations;

      if (iterations % width == 0)
        {
          meta_iteration = meta_iteration + 1;
        }
    }

  update_texture (data);
}

void
PixelCanvas::draw_pure_white_canvas ()
{

  if (!check_if_pixel_canvas_was_started ())
    {
      return;
    }
  gd::PackedByteArray data = ref_image->get_data ();
  gd::print_line (gd::String ("size of data = %s") % data.size ());

  for (int64_t byte = 0; byte < data.size (); ++byte)
    {
      data.set (byte, 0xff);
    }

  update_texture (data);
}

void
PixelCanvas::draw_color_points (const ColorPoints *color_points)
{
  if (!check_if_pixel_canvas_was_started ())
    {
      return;
    }

  if (color_points == nullptr)
    {
      ERR_PRINT ("[ERR]:passed null pointer as argument (don't do that)");
      return;
    }

  const i64 colors_len = color_points->colors.size ();
  const i64 points_len = color_points->points.size ();
  DEV_ASSERT (colors_len == points_len);

  const i64 format_color_offset = get_format_color_offset ();
  const i64 offset_per_row = format_color_offset * ref_image->get_width ();
  const i64 colum_offset = format_color_offset;

  gd::PackedByteArray data = ref_image->get_data ();

  for (i64 i = 0; i < points_len; ++i)
    {
      const godot::Vector2i point = color_points->points[i];
      const bool is_out_of_bounds
          = (point.x >= ref_image->get_width () || point.x < 0)
            || (point.y >= ref_image->get_height () || point.y < 0);
      if (is_out_of_bounds)
        {
          gd::String err_string = "Point is out of bounds [%s]";
          gd::print_error (err_string % point);
          return;
        }

      const i64 base_index
          = (point.y * offset_per_row) + (point.x * colum_offset);
      const gd::Color &color = color_points->colors[i];
      data.set (base_index, color.get_r8 ());
      data.set (base_index + 1, color.get_g8 ());
      data.set (base_index + 2, color.get_b8 ());
      data.set (base_index + 3, color.get_a8 ());
    }

  update_texture (data);
}

godot::Ref<godot::Image>
PixelCanvas::create_image_default ()
{
  return godot::Image::create_empty (PixelCanvas::DEFAULT_WIDTH,
                                     PixelCanvas::DEFAULT_HEIGHT, false,
                                     gd::Image::FORMAT_RGBA8);
}

gd::Color
PixelCanvas::DEFAULT_COLOR ()
{

  // I tried to define this in the .hpp file but godot stops reconizing the
  // class if I do that
  static gd::Color s_DEFAULT_COLOR = gd::Color (0.615f, 0.f, 1.f);
  return s_DEFAULT_COLOR;
}

gd::Vector2i
PixelCanvas::TOP_LEFT_CANVAS ()
{
  static gd::Vector2i s_TOP_LEFT_CANVAS = gd::Vector2i (0, 0);

  return s_TOP_LEFT_CANVAS;
}

godot::Ref<godot::Image>
PixelCanvas::get_image () const
{
  return ref_image;
}

godot::Ref<godot::ImageTexture>
PixelCanvas::get_texture ()
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

int64_t
PixelCanvas::get_format_color_offset () const
{

  int64_t color_component_offset = 0;
  const gd::Image::Format current_format = ref_image->get_format ();
  switch (current_format)
    {
    case gd::Image::Format::FORMAT_RGB8:
      color_component_offset = 3;
      break;

    case gd::Image::Format::FORMAT_RGBA8:
      color_component_offset = 4;
      break;

    default:
      gd::String error_string = gd::vformat ("ONLY SUPPORT THE FORMATS %s, %s",
                                             "FORMAT_RGB8", "FORMAT_RGBA8");
      gd::print_error (error_string);

      error_string = gd::vformat ("\nWe don't support the format of %d",
                                  static_cast<int64_t> (current_format));
      gd::print_error (error_string);

      break;
    }

  return color_component_offset;
}

void
PixelCanvas::update_texture (const godot::PackedByteArray &texture_update)
{
  auto format = ref_image->get_format ();
  ref_image->set_data (width, height, false, format, texture_update);

  ref_texture->update (ref_image);
}

bool
PixelCanvas::check_if_pixel_canvas_was_started () const
{
  if (!has_started)
    {
      gd::print_error (
          "you need to call the 'start' function for this to work");
      return has_started;
    }

  return has_started;
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
  BIND_METHOD_NO_ARGS (PixelCanvas, draw_rainbow_effect);
  BIND_METHOD_NO_ARGS (PixelCanvas, draw_on_data);
  BIND_METHOD_NO_ARGS (PixelCanvas, draw_diagnal_rgb_effect);
  BIND_METHOD_NO_ARGS (PixelCanvas, draw_pure_white_canvas);
  //  BIND_METHOD_NO_ARGS (PixelCanvas, draw_points);

  ClassDB::bind_method (D_METHOD ("draw_points", "Points"),
                        &PixelCanvas::draw_points);
  ClassDB::bind_method (D_METHOD ("draw_line_l", "start", "end"),
                        &PixelCanvas::draw_line_l);

  ClassDB::bind_method (D_METHOD ("draw_color_points", "color_points"),
                        &PixelCanvas::draw_color_points);

  ClassDB::bind_method (D_METHOD ("get_image"), &PixelCanvas::get_image);

  ClassDB::bind_method (D_METHOD ("get_texture"), &PixelCanvas::get_texture);

  ClassDB::bind_static_method (get_class_static (), D_METHOD ("DEFAULT_COLOR"),
                               &PixelCanvas::DEFAULT_COLOR);

  ClassDB::bind_static_method (get_class_static (),
                               D_METHOD ("create_image_default"),
                               &PixelCanvas::create_image_default);

  const godot::Color default_color = DEFAULT_COLOR ();
  helper::bind_color_constant (get_class_static (), default_color,
                               "DEFAULT_COLOR");

  /// PROPERTIES
  ClassDB::bind_method (D_METHOD ("set_width", "new_width"),
                        &PixelCanvas::set_width);
  ClassDB::bind_method (D_METHOD ("get_width"), &PixelCanvas::get_width);
  ADD_PROPERTY (PropertyInfo (Variant::INT, "width"), "set_width",
                "get_width");

  ClassDB::bind_method (D_METHOD ("set_height", "new_height"),
                        &PixelCanvas::set_height);
  ClassDB::bind_method (D_METHOD ("get_height"), &PixelCanvas::get_height);
  ADD_PROPERTY (PropertyInfo (Variant::INT, "height"), "set_height",
                "get_height");

  ClassDB::bind_method (D_METHOD ("set_color"), &PixelCanvas::set_color);
  ClassDB::bind_method (D_METHOD ("get_color"), &PixelCanvas::get_color);

  ADD_PROPERTY (PropertyInfo (Variant::COLOR, "current_color"), "set_color",
                "get_color");

  /// CONSTANTS
  ///
  ClassDB::bind_integer_constant (get_class_static (), "", "DEFAULT_HEIGHT",
                                  PixelCanvas::DEFAULT_HEIGHT);

  ClassDB::bind_integer_constant (get_class_static (), "", "DEFAULT_WIDTH",
                                  PixelCanvas::DEFAULT_WIDTH);

  {
    const gd::Vector2i TOP_LEFT_CANVAS = PixelCanvas::TOP_LEFT_CANVAS();
    BIND_CONSTANT_VECTOR2I(TOP_LEFT_CANVAS);
  }

  // BIND_CONSTANT(PixelCanvas::DEFAULT_HEIGHT);
}