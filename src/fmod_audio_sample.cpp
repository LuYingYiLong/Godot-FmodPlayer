#include "fmod_audio_sample.h"

namespace godot {
	void FmodAudioSample::_bind_methods() {

	}

	FmodAudioSample::FmodAudioSample() {

	}

	FmodAudioSample::~FmodAudioSample() {

	}

    void FmodAudioSample::set_file_path(const String& p_path) {
        file_path = p_path;
		sound = FmodServer::create_sound_from_file(p_path, FmodServer::MODE_CREATESAMPLE | FmodServer::MODE_OPENMEMORY);
    }

}