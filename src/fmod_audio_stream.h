#ifndef FMOD_AUDIO_STREAM_H
#define FMOD_AUDIO_STREAM_H

#include "fmod_audio.h"
#include "fmod_server.h"
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {
	class FmodAudioStream : public FmodAudio {
		GDCLASS(FmodAudioStream, FmodAudio)

	private:

	protected:
		static void _bind_methods();

	public:
		FmodAudioStream();
		~FmodAudioStream();

		void set_file_path(const String& p_path) override;
	};
}

#endif // !FMOD_AUDIO_STREAM_H

