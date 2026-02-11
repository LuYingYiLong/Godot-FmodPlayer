extends Node

var channel: FmodChannel
var sound: FmodSound

func _ready() -> void:
	# 使用底层播放音频
	sound = FmodServer.create_sound_from_res(
		"res://hit.wav",
		FmodServer.MODE_DEFAULT
	)
	channel = FmodServer.play_sound(sound, FmodServer.get_master_channel_group(), false)
	pass
