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

	protected:
		static void _bind_methods();

	public:
		FmodAudioStreamPlayer();
		~FmodAudioStreamPlayer();

		FmodSystem* system = nullptr;
		Ref<FmodAudioStream> stream;
		bool playing = false;

		void set_stream(Ref<FmodAudioStream> new_stream);
		Ref<FmodAudioStream> get_stream() const;

		void play(double from_position = 0.0);
		void set_playing(bool play);
		bool is_playing() const;
	};
}

#endif // !FMOD_AUDIO_STREAM_PLAYER_H