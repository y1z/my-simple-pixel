extends Node2D

#var image_texture : ImageTexture
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
	pix_canvas.draw_pure_white_canvas()
	scene_sprite.texture = pix_canvas.get_texture()
	
	print("red = %s" % pix_canvas.DEFAULT_COLOR_r);
	print("green = %s" %pix_canvas.DEFAULT_COLOR_g);
	print("blue = %s" %pix_canvas.DEFAULT_COLOR_b);
	print("alpha = %s" %pix_canvas.DEFAULT_COLOR_a);
	test_pixel_canvas()
	test_color_point()
	pass

func _input(event: InputEvent) -> void:
	## Debug only functions
	if !OS.is_debug_build() : return;
	debug_key_input(event)
	pass

func test_pixel_canvas():
	#print("DEFAULT HEIGHT = %s"  % PixelCanvas.DEFAULT_HEIGHT);
	#print("DEFAULT WIDTH = %s"  % PixelCanvas.DEFAULT_WIDTH);
	pass

func test_color_point():
	var color_and_point = ColorPoints.new()
	print("count = %s" % color_and_point.get_count())
	for i in 10:
		var is_even :bool = i % 2 == 0;
		var result_color :Color = Color.AQUA;
		if is_even: result_color = Color.INDIAN_RED
		
		color_and_point.add_color_point(Vector2i(i,i),result_color);
		pass
	print("AFTER ADDING count = %s" % color_and_point.get_count())
	
	pass

func debug_key_input(event: InputEvent) -> void:
	var has_pressed_p := event.is_action_pressed("DEBUG_P")
	var has_pressed_o := event.is_action_pressed("DEBUG_I")
	var has_pressed_i := event.is_action_pressed("DEBUG_O")
	if has_pressed_i:
		print("pressed I")
		pix_canvas.draw_diagnal_rgb_effect()
		pass
	if has_pressed_o:
		print("pressed O")
		pix_canvas.draw_pure_white_canvas()
		pass
	if has_pressed_p:
		print("pressed P")
		var t = PackedVector2Array(
			[Vector2(1,1),
			Vector2(2,2),
			Vector2(3,2),
			Vector2(2,3),
			Vector2(4,4)
			]);
		pix_canvas.draw_points(t)
		pass
	if event.is_action_pressed("DEBUG_K"):
		var color_points: ColorPoints = ColorPoints.new()
		for i in 100:
			var result_color:Color = Color.INDIAN_RED;
			if i % 2 == 0: result_color = Color.SKY_BLUE;
			color_points.add_color_point(Vector2i(i,i),result_color)
		pass
		pix_canvas.draw_color_points(color_points);
	pass
