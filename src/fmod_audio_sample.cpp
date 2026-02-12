#include "fmod_audio_sample.h"

namespace godot {
	void FmodAudioSample::_bind_methods() { }

	FmodAudioSample::FmodAudioSample() { }

	FmodAudioSample::~FmodAudioSample() { }

    void FmodAudioSample::set_file_path(const String& p_path) {
        file_path = p_path;
		sound = FmodServer::get_main_system()->create_sound_from_file(p_path, FmodSystem::MODE_CREATESAMPLE | FmodSystem::MODE_OPENMEMORY | FmodSystem::MODE_LOOP_OFF);
	}
}