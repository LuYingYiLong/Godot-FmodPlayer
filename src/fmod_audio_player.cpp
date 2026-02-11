#include "fmod_audio_player.h"

namespace godot {
	void FmodAudioPlayer::_bind_methods() {
		ClassDB::bind_method(D_METHOD("set_audio", "audio"), &FmodAudioPlayer::set_audio);
		ClassDB::bind_method(D_METHOD("get_audio"), &FmodAudioPlayer::get_audio);
		ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "audio", PROPERTY_HINT_RESOURCE_TYPE, "FmodAudio"), "set_audio", "get_audio");
		ClassDB::bind_method(D_METHOD("set_playing", "play"), &FmodAudioPlayer::set_playing);
		ClassDB::bind_method(D_METHOD("is_playing"), &FmodAudioPlayer::is_playing);
		ADD_PROPERTY(PropertyInfo(Variant::BOOL, "playing"), "set_playing", "is_playing");
	}

	void FmodAudioPlayer::_process(double delta) {

	}

	void FmodAudioPlayer::set_audio(Ref<FmodAudio> new_audio) {
		audio = new_audio;
		if (audio.is_valid()) {
			internal_channel = FmodServer::play_sound_use_master_channel_group(audio->sound, false);
			if (internal_channel.is_null()) {
				UtilityFunctions::push_error("Failed to get Fmod Channel!");
				return;
			}
		}
		set_playing(false);
	}

	Ref<FmodAudio> FmodAudioPlayer::get_audio() const {
		return audio;
	}

	void FmodAudioPlayer::set_playing(bool play) {
		if (internal_channel.is_null()) {
			return;
		}
		playing = play;
		internal_channel->set_position(0);
		internal_channel->set_paused(!playing);
	}

	bool FmodAudioPlayer::is_playing() const {
		return playing;
	}
}