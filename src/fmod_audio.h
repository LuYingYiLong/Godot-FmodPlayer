#ifndef FMOD_AUDIO_H
#define FMOD_AUDIO_H

#include "fmod_sound.h"
#include "fmod_server.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/resource.hpp>

namespace godot {
	class FmodAudio : public Resource {
		GDCLASS(FmodAudio, Resource)

	private:

	protected:
		static void _bind_methods();

	public:
		FmodAudio();
		~FmodAudio();

        Ref<FmodSound> sound;
        String file_path;

        double get_length() const;
        Ref<FmodSound> get_sound() const;

		virtual void set_file_path(const String& p_path) { file_path = p_path; };
		String get_file_path() const;
	};
}

#endif // !FMOD_AUDIO_H

