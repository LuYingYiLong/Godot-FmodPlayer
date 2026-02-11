extends Node

@onready var fmod_audio_player: FmodAudioPlayer = %FmodAudioPlayer

var system: FmodSystem

var channel: FmodChannel
var channel_group: FmodChannelGroup
var sound: FmodSound

func _ready() -> void:
	## 使用底层播放音频
	#system = FmodServer.get_main_system()
	#sound = system.create_sound_from_res(
		#"res://Approaching Nirvana - Frontier.mp3",
		#FmodSystem.MODE_DEFAULT | FmodSystem.MODE_OPENMEMORY
	#)
	#channel_group = system.get_master_channel_group()
	#channel = system.play_sound(sound, channel_group, false)
	fmod_audio_player.play()
	pass
