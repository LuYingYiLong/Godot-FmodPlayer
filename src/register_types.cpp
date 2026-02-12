#include "register_types.h"

#include "fmod_audio.h"
#include "fmod_audio_sample.h"
#include "fmod_audio_stream.h"
#include "fmod_audio_stream_player.h"
#include "fmod_channel.h"
#include "fmod_channel_group.h"
#include "fmod_sound.h"
#include "fmod_sound_emiter.h"
#include "fmod_server.h"
#include "fmod_system.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

static FmodServer* fmod_server_instance = nullptr;

void initialize_example_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_CLASS(FmodChannel);
	GDREGISTER_CLASS(FmodChannelGroup);
	GDREGISTER_CLASS(FmodSound);
	GDREGISTER_CLASS(FmodSystem);

	GDREGISTER_ABSTRACT_CLASS(FmodAudio);
	GDREGISTER_CLASS(FmodAudioSample);
	GDREGISTER_CLASS(FmodAudioStream);
	GDREGISTER_CLASS(FmodAudioStreamPlayer);
	GDREGISTER_CLASS(FmodSoundEmiter);

	GDREGISTER_CLASS(FmodServer);
	fmod_server_instance = memnew(FmodServer);												// 初始化 FmodServer
	Engine::get_singleton()->register_singleton("FmodServer", FmodServer::get_singleton());	// 注册进 Engine 单例
}

void uninitialize_example_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	if (fmod_server_instance) {
		Engine::get_singleton()->unregister_singleton("FmodServer");						// 先从 Engine 移除单例
		memdelete(fmod_server_instance);													// 再释放 FmodServer
		fmod_server_instance = nullptr;														// 最后将 FmodServer 置空
	}
}

extern "C" {
	// Initialization.
	GDExtensionBool GDE_EXPORT example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization* r_initialization) {
		godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

		init_obj.register_initializer(initialize_example_module);
		init_obj.register_terminator(uninitialize_example_module);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}