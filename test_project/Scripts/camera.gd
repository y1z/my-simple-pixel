extends Camera2D

### BIT-FLAGS ENUM
### explanation https://youtu.be/FD8sEMIHPrs
## keeps track of what the camera can do in a given time
enum CameraFunctions {NONE = 0,
 	MOVE = (1 << 0),
 	ZOOM = (1 << 1)}

var last_position := Vector2(0,0)
var start_click_position := Vector2(0,0)
var end_click_position := Vector2(0,0)
var click_delta := Vector2(0,0)
var track_mouse_position := false;
var camera_function_state:CameraFunctions = CameraFunctions.NONE


func _ready() -> void:
	for i in range(64):
		var power_of_2 := 1 <<i

		print("does power_of_2 = %s get accepted in a if block" % power_of_2)
		if power_of_2:
			print('YES')

	for i in range(63):
		print("does if accept the nagative number %s" % (-i))
		if -i:
			print("	yes")
		else:
			print("	no")


func _process(delta: float) -> void:
	if Input.is_action_just_pressed("mouse_r"):
		last_position = self.position
		start_click_position= get_local_mouse_position();
		camera_function_state = camera_function_state | CameraFunctions.MOVE

	if Input.is_action_just_released("mouse_r"):
		self.position = last_position + click_delta
		track_mouse_position = false;
		camera_function_state = camera_function_state ^ CameraFunctions.MOVE
		pass

	if camera_function_state & CameraFunctions.MOVE:
		track_mouse_mode()


func _input(event: InputEvent) -> void:
	if event.is_action("scroll_up"):
		self.zoom.x += 0.4
		self.zoom.y += 0.4

	if event.is_action("scroll_down"):
		self.zoom.x -= 0.4
		self.zoom.y -= 0.4


func track_mouse_mode() -> void:
	end_click_position = get_local_mouse_position();
	click_delta = start_click_position - end_click_position;
	self.position= last_position + click_delta
