extends Node2D

var image_texture : ImageTexture
var pix_canvas : PixelCanvas

var scene_sprite : Sprite2D

func _init() -> void:
	pass

func _ready() -> void:
	pix_canvas = PixelCanvas.new()
	if !pix_canvas.start():
		printerr("[ERR] PixelCanvas could not start")
	#print("has started = %s" % pix_canvas.is_started())
	print("test is working = %s " % pix_canvas.test_is_working());
	
	pix_canvas.current_color = Color.REBECCA_PURPLE
	print("Current color = %s" % pix_canvas.current_color)
	
	pix_canvas.draw_line_l(Vector2i(0,0),Vector2i(10,10));
	print("Draw line l");
	
	print("DEFAULT COLOR  = %s" % PixelCanvas.DEFAULT_COLOR())
	scene_sprite = %Sprite2D
	test_pixel_canvas()
	pass

func test_pixel_canvas():
	scene_sprite.texture = pix_canvas.get_texture()
	#print("DEFAULT HEIGHT = %s"  % PixelCanvas.DEFAULT_HEIGHT);
	#print("DEFAULT WIDTH = %s"  % PixelCanvas.DEFAULT_WIDTH);
	pass
