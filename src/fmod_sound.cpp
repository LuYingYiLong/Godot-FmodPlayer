#include "fmod_sound.h"

namespace godot {
	void FmodSound::_bind_methods() {
		ClassDB::bind_static_method("FmodSound", D_METHOD("load_from_file", "path"), &FmodSound::load_from_file);
		ClassDB::bind_method(D_METHOD("get_length"), &FmodSound::get_length);
	}

	FmodSound::FmodSound() {
		
	}

	FmodSound::~FmodSound() {
		if (sound) {
			FMOD_CHECK(sound->release());
			sound = nullptr;
		}
	}

	Ref<FmodSound> FmodSound::load_from_file(const String& p_path) {
		return FmodServer::get_main_system()->create_sound_from_file(p_path, FmodSystem::MODE_DEFAULT);
	}

	double FmodSound::get_length() const {
		unsigned int length = 0;
        FMOD_CHECK(sound->getLength(&length, FMOD_TIMEUNIT_MS));
        return (double)length / 1000.0;
	}
}