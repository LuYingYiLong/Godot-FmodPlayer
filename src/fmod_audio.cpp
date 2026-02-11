#include "fmod_audio.h"

namespace godot {
	void FmodAudio::_bind_methods() {
		ClassDB::bind_method(D_METHOD("get_length"), &FmodAudio::get_length);
		ClassDB::bind_method(D_METHOD("get_sound"), &FmodAudio::get_sound);
		ClassDB::bind_method(D_METHOD("set_file_path", "path"), &FmodAudio::set_file_path);
		ClassDB::bind_method(D_METHOD("get_file_path"), &FmodAudio::get_file_path);
		ADD_PROPERTY(PropertyInfo(Variant::STRING, "file_path", PROPERTY_HINT_FILE_PATH), "set_file_path", "get_file_path");
	}

	FmodAudio::FmodAudio() {

	}

	FmodAudio::~FmodAudio() {

	}

	double FmodAudio::get_length() const {
        return sound->get_length();
	}

	Ref<FmodSound> FmodAudio::get_sound() const {
        return sound;
	}

	String FmodAudio::get_file_path() const {
		return file_path;
	}
}