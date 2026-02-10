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

		enum Timeunit {
			TIMEUNIT_MS          = 0x00000001,
			TIMEUNIT_PCM         = 0x00000002,
			TIMEUNIT_PCMBYTES    = 0x00000004,
			TIMEUNIT_RAWBYTES    = 0x00000008,
			TIMEUNIT_PCMFRACTION = 0x00000010,
			TIMEUNIT_MODORDER    = 0x00000100,
			TIMEUNIT_MODROW      = 0x00000200,
			TIMEUNIT_MODPATTERN  = 0x00000400
		};

		void set_paused(bool paused);
		void set_volume(float volume);
		void set_pitch(float pitch);
		void set_position(int position, Timeunit timeunit = TIMEUNIT_MS);
	};
}

VARIANT_ENUM_CAST(FmodChannel::Timeunit);

#endif // !FMOD_CHANNEL_H
