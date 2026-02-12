#ifndef FMOD_STREAM_PLAYER_H
#define FMOD_STREAM_PLAYER_H

#include "fmod_audio.h"
#include "fmod_channel_group.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {
	class FmodAudioPlayer : public Node {
		GDCLASS(FmodAudioPlayer, Node)

	private:
		Ref<FmodChannel> internal_channel;
		Ref<FmodChannelGroup> internal_channel_group;

	protected:
		static void _bind_methods();

	public:
		FmodAudioPlayer();
		~FmodAudioPlayer();

		Ref<FmodSystem> system;
		Ref<FmodAudio> audio;
		bool playing = false;

		void set_audio(Ref<FmodAudio> new_audio);
		Ref<FmodAudio> get_audio() const;

		void play(double from_position = 0.0);
		void set_playing(bool play);
		bool is_playing() const;
	};
}

#endif // !FMOD_STREAM_PLAYER_H