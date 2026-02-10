#ifndef FMOD_SOUND_H
#define FMOD_SOUND_H

#include "fmod_server.h"
#include "fmod_channel.h"
#include <fmod.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <string>

namespace godot {
	class FmodSound : public RefCounted {
		GDCLASS(FmodSound, RefCounted)

	protected:
		static void _bind_methods();

	public:
		FmodSound();
		~FmodSound();

		FMOD::Sound* sound = nullptr;
		String file_path;
		PackedByteArray data;
		int length = 0;

		Ref<FmodSound> load_from_file(const String& p_path);
		PackedByteArray get_data() const { return data; }
		int get_length() const { return length; }
	};
}

#endif // !FMOD_SOUND_H
