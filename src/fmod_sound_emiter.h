#ifndef FMOD_SOUND_EMITER_H
#define FMOD_SOUND_EMITER_H

#include "fmod_system.h"
#include "fmod_audio_sample.h"
#include "fmod_channel_group.h"
#include "fmod_channel.h"
#include <fmod.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {
	class FmodSoundEmiter : public Node {
		GDCLASS(FmodSoundEmiter, Node)

	private:
		void _on_channel_ended(FmodChannel* channel);

	protected:
		static void _bind_methods();

	public:
		FmodSoundEmiter();
		~FmodSoundEmiter();

		FmodSystem* system = nullptr;
		FmodChannelGroup* channels = nullptr;
		Ref<FmodAudioSample> sample;

		void emit();

		void set_sample(Ref<FmodAudioSample> new_sample);
		Ref<FmodAudioSample> get_sample() const;
	};
}

#endif // !FMOD_SOUND_EMITER_H
