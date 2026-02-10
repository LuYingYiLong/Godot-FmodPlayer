#include "fmod_sound_player.h"

namespace godot {
	void FmodSoundPlayer::_bind_methods() {
		ClassDB::bind_method(D_METHOD("set_stream", "stream"), &FmodSoundPlayer::set_stream);
		ClassDB::bind_method(D_METHOD("get_stream"), &FmodSoundPlayer::get_stream);
		ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "stream", PropertyHint::PROPERTY_HINT_RESOURCE_TYPE, "AudioStream"), "set_stream", "get_stream");
	}

	void FmodSoundPlayer::set_stream(Ref<AudioStream> p_stream) {
		stream = p_stream;
	}

	Ref<AudioStream> FmodSoundPlayer::get_stream() const {
		return stream;
	}
}