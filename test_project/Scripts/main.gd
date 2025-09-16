extends Node2D

var pix_canvas: PixelCanvas

var scene_sprite: Sprite2D

var buttons_container: VBoxContainer
var buttons: Array[Button]

var function_dict: Dictionary = {0: test_color_point,
1: draw_horizontal_lines,
2: test_color_points,
3: test_draw_points,
4: test_draw_pure_white_canvas,
5: draw_vertical_lines,
}

var color_dic:Dictionary = {0: Color.INDIAN_RED,
	 1: Color.SEA_GREEN,
	 2: Color.AQUA,
	 3: Color.REBECCA_PURPLE,
	 4: Color.DARK_RED,
	 5: Color.CHARTREUSE,
	 6: Color.CADET_BLUE,
	 7: Color.WEB_PURPLE,
	 8: Color.MEDIUM_VIOLET_RED,
	}


func _ready() -> void:
	buttons_container = %"Buttons Container"
	var temp_to_get_the_buttons = buttons_container.get_children()

	for b in temp_to_get_the_buttons:
		if (is_instance_of(b, Button)):
			print("found button")
			buttons.append(b)

		pass

	var how_many_buttons_to_assign = min(function_dict.size(),buttons.size())

	for i in how_many_buttons_to_assign:
		buttons[i].text = str(function_dict[i])
		buttons[i].pressed.connect(function_dict[i])
		pass

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
	print("green = %s" % pix_canvas.DEFAULT_COLOR_g);
	print("blue = %s" % pix_canvas.DEFAULT_COLOR_b);
	print("alpha = %s" % pix_canvas.DEFAULT_COLOR_a);

	print("top_left_canvas.x = %s" % pix_canvas.TOP_LEFT_CANVAS_x)
	print("top_left_canvas.y = %s" % pix_canvas.TOP_LEFT_CANVAS_y)
	test_color_point()
	pass


func _input(event: InputEvent) -> void:
	## Debug only functions
	if !OS.is_debug_build(): return;
	debug_key_input(event)
	pass


func test_color_point():
	var color_and_point = ColorPoints.new()
	print("count = %s" % color_and_point.get_count())

	for i in 10:
		var is_even:bool = i % 2 == 0;
		var result_color:Color = Color.AQUA;

		if is_even: result_color = Color.INDIAN_RED

		color_and_point.add_color_point(Vector2i(i,i),result_color);
		pass

	print("AFTER ADDING count = %s" % color_and_point.get_count())
	pix_canvas.draw_color_points(color_and_point)
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
		test_draw_points()
		pass

	if event.is_action_pressed("DEBUG_K"):
		test_color_point()

	if event.is_action_pressed("DEBUG_L"):
		draw_horizontal_lines()
		pass

	pass


func draw_horizontal_lines() ->void:
	print("DRAW LINES")
	print("horizontal lines")

	var current_color_copy: Color = pix_canvas.current_color
	var new_color: Color = Color.INDIAN_RED
	var start_horizontal_line = Vector2i(0,0);
	var end_horizontal_line = Vector2i(pix_canvas.width - 1,0);

	for i in pix_canvas.height - 1:
		var color_index:int = i % color_dic.size();
		new_color = color_dic[color_index];
		pix_canvas.current_color = new_color;

		pix_canvas.draw_line_l(start_horizontal_line, end_horizontal_line)
		start_horizontal_line.y = start_horizontal_line.y + 1;
		end_horizontal_line.y = end_horizontal_line.y + 1;

		pass

	pix_canvas.current_color = current_color_copy;
	pass


func draw_vertical_lines() -> void:
	var current_color_copy: Color = pix_canvas.current_color
	var new_color: Color = Color.INDIAN_RED
	var start_vertical_line := Vector2i(0,0);
	var end_vertical_line := Vector2i(0, pix_canvas.height - 1);

	for i in pix_canvas.width - 1:

		var color_index:int = i % color_dic.size();
		new_color = color_dic[color_index];
		pix_canvas.current_color = new_color;

		pix_canvas.draw_line_l(start_vertical_line, end_vertical_line)
		start_vertical_line.x = start_vertical_line.x + 1;
		end_vertical_line.x = end_vertical_line.x + 1;
		pass

	pix_canvas.current_color = current_color_copy;
	pass


func test_color_points() -> void:
	var color_points: ColorPoints = ColorPoints.new()

	for i in pix_canvas.width:
		var result_color:Color = Color.INDIAN_RED;

		if i % 2 == 0: result_color = Color.SKY_BLUE;
		color_points.add_color_point(Vector2i(i,i),result_color)

	pass
	pix_canvas.draw_color_points(color_points);
pass


func test_draw_points() -> void:

	var t = PackedVector2Array(
		[Vector2(1,1),
		Vector2(2,2),
		Vector2(3,2),
		Vector2(2,3),
		Vector2(4,4)
		]);

	pix_canvas.draw_points(t)
	pass


func test_draw_pure_white_canvas() -> void:
	pix_canvas.draw_pure_white_canvas()
	pass
