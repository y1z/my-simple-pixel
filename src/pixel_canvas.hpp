#pragma once

#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/variant/color.hpp"
#include "godot_cpp/variant/packed_byte_array.hpp"
#include "godot_cpp/variant/packed_vector2_array.hpp"
#include "godot_cpp/variant/vector2i.hpp"
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/resource.hpp>

#include <cstdint>

class ColorPoints;

class PixelCanvas : public godot::Resource
{
  GDCLASS (PixelCanvas, godot::Resource)

public:
  static constexpr int32_t DEFAULT_WIDTH = 64;
  static constexpr int32_t DEFAULT_HEIGHT = 64;

public:
  bool start ();
  bool is_started ();

  bool test_is_working () const;

  // Draw
  void draw_points (const godot::PackedVector2Array &points_to_draw);
  void draw_line_l (const godot::Vector2i start, const godot::Vector2i end);
  void draw_rainbow_effect ();
  void draw_on_data ();
  void draw_diagnal_rgb_effect ();
  void draw_pure_white_canvas ();
  void draw_color_points(const ColorPoints*ptr_color_points);

  /// GETTERS
  godot::Ref<godot::Image> get_image () const;
  godot::Ref<godot::ImageTexture> get_texture ();
  int32_t get_width () const;
  int32_t get_height () const;
  godot::Color get_color () const;

  /// SETTERS
  void set_image (const godot::Ref<godot::Image> new_image);
  void set_texture (const godot::Ref<godot::ImageTexture> new_texture_image);
  void set_width (int32_t new_width);
  void set_height (int32_t new_height);
  void set_color (const godot::Color new_color);

private:
  int64_t get_format_color_offset () const;
  void update_texture (const godot::PackedByteArray &texture_update);
  bool check_if_pixel_canvas_was_started () const;

  //draw
  void draw_vertical_line(const godot::Vector2i start, const int64_t length, const bool go_up );
  void draw_horizontal_line(const godot::Vector2i start, const int64_t length, const bool go_right );

public:
  static godot::Ref<godot::Image> create_image_default ();
  static godot::Color DEFAULT_COLOR ();

protected:
  static void _bind_methods ();

private:
  godot::Ref<godot::Image> ref_image = create_image_default ();

  godot::Ref<godot::ImageTexture> ref_texture
      = godot::Ref<godot::ImageTexture> ();

  godot::Color current_color = godot::Color ("#c01111c0");
  
  godot::PackedByteArray data_array = godot::PackedByteArray();
  int32_t width = DEFAULT_WIDTH;
  int32_t height = DEFAULT_HEIGHT;
  bool has_started = false;
};