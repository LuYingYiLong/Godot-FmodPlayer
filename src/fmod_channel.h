#ifndef FMOD_CHANNEL_H
#define FMOD_CHANNEL_H

#include "fmod_system.h"
#include <fmod.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

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

		void setup(FMOD::Channel* p_channel);

		void set_paused(bool paused);
		bool get_paused() const;

		void set_volume(float volume);
		float get_volume() const;

		void set_pitch(float pitch);
		float get_pitch() const;
		
		void set_position(int position, FmodSystem::Timeunit timeunit = FmodSystem::TIMEUNIT_MS);
		int get_position(FmodSystem::Timeunit timeunit = FmodSystem::TIMEUNIT_MS) const;

		// 回调设置方法
		void set_callback();
		void clear_callback();
	};
}

extern "C" {
	FMOD_RESULT F_CALL fmod_channel_control_callback(
		FMOD_CHANNELCONTROL* channelcontrol,
		FMOD_CHANNELCONTROL_TYPE controltype,
		FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype,
		void* commanddata1,
		void* commanddata2
	);
}

#endif // !FMOD_CHANNEL_H
