extends Node

var channel
var sound

func _ready() -> void:
	sound = FmodServer.create_sound("I:/音乐/Athletics - IV.mp3")
	print(FmodServer.get_master_channel_group())
	channel = FmodServer.play_sound(sound, FmodServer.get_master_channel_group(), false)	
