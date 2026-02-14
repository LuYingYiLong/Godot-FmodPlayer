#include "fmod_audio_stream_player.h"

namespace godot {
	void FmodAudioStreamPlayer::_bind_methods() {
		ClassDB::bind_method(D_METHOD("set_stream", "stream"), &FmodAudioStreamPlayer::set_stream);
		ClassDB::bind_method(D_METHOD("get_stream"), &FmodAudioStreamPlayer::get_stream);
		ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "stream", PROPERTY_HINT_RESOURCE_TYPE, "FmodAudioStream"), "set_stream", "get_stream");
		ClassDB::bind_method(D_METHOD("play", "from_position"), &FmodAudioStreamPlayer::play, DEFVAL(0.0));
		ClassDB::bind_method(D_METHOD("set_playing", "play"), &FmodAudioStreamPlayer::set_playing);
		ClassDB::bind_method(D_METHOD("is_playing"), &FmodAudioStreamPlayer::is_playing);
		ClassDB::bind_method(D_METHOD("set_volume_db", "volume_db"), &FmodAudioStreamPlayer::set_volume_db);
		ClassDB::bind_method(D_METHOD("get_volume_db"), &FmodAudioStreamPlayer::get_volume_db);
		ADD_PROPERTY(PropertyInfo(Variant::BOOL, "playing"), "set_playing", "is_playing");
		ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "volume_db", PROPERTY_HINT_RANGE, "-80,24,0.1,suffix:dB"), "set_volume_db", "get_volume_db");

		ADD_SIGNAL(MethodInfo("finished"));
	}

	FmodAudioStreamPlayer::FmodAudioStreamPlayer() {
		internal_channel = memnew(FmodChannel);
		system = FmodServer::get_main_system();
		internal_channel_group = system->get_master_channel_group();
	}

	FmodAudioStreamPlayer::~FmodAudioStreamPlayer() {
		if (internal_channel) {
			memdelete(internal_channel);
			internal_channel = nullptr;
		}
		system = nullptr;
	}

	void FmodAudioStreamPlayer::_on_internal_channel_ended() {
		set_playing(false);
		emit_signal("finished");
	}

	void FmodAudioStreamPlayer::set_stream(Ref<FmodAudioStream> new_stream) {
		stream = new_stream;
		set_playing(false);
		if (stream.is_valid()) {
			FmodSystem* system = FmodServer::get_main_system();
			internal_channel = system->play_sound(stream->sound, internal_channel_group);
			if (!internal_channel) {
				UtilityFunctions::push_error("Failed to get Fmod Channel!");
				return;
			}
			internal_channel->connect("ended", callable_mp(this, &FmodAudioStreamPlayer::_on_internal_channel_ended), CONNECT_DEFERRED);
		}
		else {
			memdelete(internal_channel);
			internal_channel = nullptr;
		}
	}

	Ref<FmodAudioStream> FmodAudioStreamPlayer::get_stream() const {
		return stream;
	}

	void FmodAudioStreamPlayer::play(const double from_position) {
		if (!internal_channel) {
			return;
		}
		internal_channel->set_position(int(from_position * 1000));
		set_playing(true);
	}

	void FmodAudioStreamPlayer::set_playing(const bool play) {
		if (!internal_channel) {
			return;
		}
		playing = play;
		internal_channel->set_paused(!playing);
	}

	bool FmodAudioStreamPlayer::is_playing() const {
		return playing;
	}

	void FmodAudioStreamPlayer::set_volume_db(const double volume_db) {
		if (!internal_channel) return;
		internal_channel->set_volume_db(volume_db);
	}

	double FmodAudioStreamPlayer::get_volume_db() const {
		if (!internal_channel) return 0.0;
		return internal_channel->get_volume_db();
	}
}