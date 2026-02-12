@tool
extends Node

@export var play_sound: bool = false:
	set(value):
		play_sound = false
		_play_sound()

var system: FmodSystem

var channel: FmodChannel
var channel_group: FmodChannelGroup
var sound: FmodSound

@onready var label: Label = %Label
@onready var fmod_sound_emiter: FmodSoundEmiter = %FmodSoundEmiter

#func _ready() -> void:
	#system = FmodServer.get_main_system()
	#channel_group = system.get_master_channel_group()
	#system.set_network_proxy("127.0.0.1:9264")
	#print("Current proxy: ", system.get_network_proxy())
	#print(system.get_file_usage())

func _play_sound() -> void:
	## 使用底层播放音频
	sound = system.create_sound_from_res(
		"res://Athletics - IV_01.wav",
		FmodSystem.MODE_LOOP_OFF
	)
	channel = system.play_sound(sound, channel_group, false)
	#FmodServer.get_main_system().play_sound(sound, channel_group, false)
	channel.ended.connect(func() -> void:
		print("ended!!")
	)
	pass

func _process(_delta: float) -> void:
	if (Engine.is_editor_hint()): return
	@warning_ignore("narrowing_conversion")
	label.text = "RAM: %s" %String.humanize_size(Performance.get_monitor(Performance.MEMORY_STATIC))

func _on_timer_timeout() -> void:
	fmod_sound_emiter.emit()
