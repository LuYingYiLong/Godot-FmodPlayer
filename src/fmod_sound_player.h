#ifndef FMOD_SOUND_PLAYER_H
#define FMOD_SOUND_PLAYER_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/audio_stream.hpp>

namespace godot {
	class FmodSoundPlayer : public Node {
		GDCLASS(FmodSoundPlayer, Node)

	private:

	protected:
		static void _bind_methods();

	public:
		Ref<AudioStream> stream = nullptr;

		void set_stream(Ref<AudioStream> p_stream);
		Ref<AudioStream> get_stream() const;
	};
}

#endif // !FMOD_SOUND_PLAYER_H
