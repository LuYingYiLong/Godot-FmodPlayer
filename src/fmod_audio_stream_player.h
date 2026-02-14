#ifndef FMOD_AUDIO_STREAM_PLAYER_H
#define FMOD_AUDIO_STREAM_PLAYER_H

#include "fmod_audio_stream.h"
#include "fmod_channel_group.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {
	class FmodAudioStreamPlayer : public Node {
		GDCLASS(FmodAudioStreamPlayer, Node)

	private:
		FmodChannel* internal_channel = nullptr;
		FmodChannelGroup* internal_channel_group = nullptr;

		void _on_internal_channel_ended();

	protected:
		static void _bind_methods();

	public:
		FmodAudioStreamPlayer();
		~FmodAudioStreamPlayer();

		FmodSystem* system = nullptr;
		Ref<FmodAudioStream> stream;

		void set_stream(Ref<FmodAudioStream> new_stream);
		Ref<FmodAudioStream> get_stream() const;

		bool playing = false;
		void play(const double from_position = 0.0);
		void set_playing(const bool play);
		bool is_playing() const;

		void set_volume_db(const double new_volume_db);
		double get_volume_db() const;
	};
}

#endif // !FMOD_AUDIO_STREAM_PLAYER_H