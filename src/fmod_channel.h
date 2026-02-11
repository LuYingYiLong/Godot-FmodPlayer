#ifndef FMOD_CHANNEL_H
#define FMOD_CHANNEL_H

#include <fmod.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/class_db.hpp>
#include "fmod_server.h"

namespace godot {
	class FmodChannel : public RefCounted {
		GDCLASS(FmodChannel, RefCounted)

	private:

	protected:
		static void _bind_methods();

	public:
		FmodChannel();
		~FmodChannel();
		
		FMOD::Channel* channel = nullptr;

		void set_paused(bool paused);
		void set_volume(float volume);
		void set_pitch(float pitch);
		void set_position(int position, FmodSystem::Timeunit timeunit = FmodSystem::TIMEUNIT_MS);
	};
}

#endif // !FMOD_CHANNEL_H
