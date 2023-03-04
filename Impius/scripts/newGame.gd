extends Button

export var ref_path = ""
export(bool) var focused = false

func _ready():
	if (focused):
		grab_focus()
	
	connect("pressed", self, "_on_Button_Pressed")

	if (get_node("../Continue").disabled == false):
		focus_neighbour_bottom = NodePath("../Continue")

func _on_Button_Pressed():
	if (ref_path != ""):
		get_tree().change_scene(ref_path)
	else:
		get_tree().quit()
