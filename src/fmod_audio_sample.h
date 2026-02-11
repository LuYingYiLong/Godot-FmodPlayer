#ifndef FMOD_AUDIO_SAMPLE_H
#define FMOD_AUDIO_SAMPLE_H

#include "fmod_audio.h"
#include "fmod_server.h"
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {
	class FmodAudioSample : public FmodAudio {
		GDCLASS(FmodAudioSample, FmodAudio)

	private:

	protected:
		static void _bind_methods();

	public:
		FmodAudioSample();
		~FmodAudioSample();

		void set_file_path(const String& p_path) override;
	};
}

#endif // !FMOD_AUDIO_SAMPLE_H

