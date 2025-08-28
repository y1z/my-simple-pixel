#pragma  once
#include "godot_cpp/classes/node2d.hpp"
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/image_texture.hpp>


class PixelCanvas : public godot::Node2D
{
    private:
	GDCLASS(PixelCanvas, Node2D)
        
    protected:
	static void _bind_methods();
    
    public:
    bool test_is_working()const;
};