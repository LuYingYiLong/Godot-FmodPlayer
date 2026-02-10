#ifndef FMOD_STREAM_PLAYER_H
#define FMOD_STREAM_PLAYER_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/audio_stream.hpp>

namespace godot {
	class FmodStreamPlayer : public Node {
		GDCLASS(FmodStreamPlayer, Node)

	private:

	protected:
		static void _bind_methods();

	public:
		AudioStream* stream;
	};
}

#endif // !FMOD_STREAM_PLAYER_H