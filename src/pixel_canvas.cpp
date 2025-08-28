#include "pixel_canvas.hpp"
#include "godot_cpp/core/class_db.hpp"

namespace gd = godot;

void PixelCanvas::_bind_methods()
{
    gd::ClassDB::bind_method(gd::D_METHOD("test_is_working"), &PixelCanvas::test_is_working);

}

bool PixelCanvas::test_is_working()const
{
    return true;    
}