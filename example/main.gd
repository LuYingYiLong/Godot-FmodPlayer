extends Node

var channel: FmodChannel
var sound: FmodSound

func _ready() -> void:
	sound = FmodServer.create_sound_from_res(
		"res://Approaching Nirvana - Frontier.mp3",
		FmodServer.MODE_CREATESAMPLE | FmodServer.MODE_CREATECOMPRESSEDSAMPLE | FmodServer.MODE_OPENMEMORY
	)
	print(sound)
	channel = FmodServer.play_sound(sound, FmodServer.get_master_channel_group(), false)
