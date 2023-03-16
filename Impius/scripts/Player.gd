extends KinematicBody2D

export var SPEED = 30

var velocity = Vector2.ZERO

onready var animationPlayer = $AnimationPlayer

func _ready():
	Engine.set_target_fps(30) #de adaugat la node-urile principale (level scenes)

func _physics_process(delta):
	var input_vector = Vector2.ZERO
	input_vector.x = Input.get_action_strength("ui_right") - Input.get_action_strength("ui_left")
	input_vector.y = Input.get_action_strength("ui_down") - Input.get_action_strength("ui_up")
	input_vector = input_vector.normalized()
	
	if (input_vector != Vector2.ZERO):
		if (input_vector.x > 0):
			animationPlayer.play("RunRight")
		else:
			animationPlayer.play("RunLeft")
		velocity = input_vector * SPEED
	else:
		velocity = Vector2.ZERO
		
	velocity = move_and_slide(velocity)
