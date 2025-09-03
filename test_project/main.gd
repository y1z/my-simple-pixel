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
	print("has started = %s" % pix_canvas.is_started())
	print("test is working = %s " % pix_canvas.test_is_working());
	
	pix_canvas.current_color = Color.REBECCA_PURPLE
	print("Current color = %s" % pix_canvas.current_color)
	
	print("DEFAULT COLOR  = %s" % PixelCanvas.DEFAULT_COLOR())
	scene_sprite = %Sprite2D
	test_pixel_canvas()
	pass

func _input(event: InputEvent) -> void:
	
	## Debug only functions
	if !OS.is_debug_build() : return;
	Input.is_key_pressed(KEY_P)
	if event is InputEventKey:
		var keycode_and_mod = event.get_keycode_with_modifiers();
		if event.keycode == KEY_0:
			print("key 0")

		pass
	pass

func test_pixel_canvas():
	pix_canvas.draw_pure_white_canvas();
	pix_canvas.draw_on_data();
	pix_canvas.draw_diagnal_rgb_effect();
	scene_sprite.texture = pix_canvas.get_texture()
	#print("DEFAULT HEIGHT = %s"  % PixelCanvas.DEFAULT_HEIGHT);
	#print("DEFAULT WIDTH = %s"  % PixelCanvas.DEFAULT_WIDTH);
	pass
