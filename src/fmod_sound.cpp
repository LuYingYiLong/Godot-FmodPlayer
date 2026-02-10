#include "fmod_sound.h"

namespace godot {
	void FmodSound::_bind_methods() {
		ClassDB::bind_method(D_METHOD("get_data"), &FmodSound::get_data);
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
		return FmodServer::create_sound(p_path);
	}
}