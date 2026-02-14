#ifndef FMOD_AUDIO_SAMPLE_EMITTER_H
#define FMOD_AUDIO_SAMPLE_EMITTER_H

#include "fmod_audio_sample.h"
#include "fmod_channel.h"
#include "fmod_channel_group.h"
#include "fmod_system.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {
	class FmodAudioSampleEmitter : public Node {
		GDCLASS(FmodAudioSampleEmitter, Node)

	private:
		void _on_channel_ended(FmodChannel* channel);

	protected:
		static void _bind_methods();

	public:
		FmodAudioSampleEmitter();
		~FmodAudioSampleEmitter();

		FmodSystem* system = nullptr;
		FmodChannelGroup* channel_group = nullptr;
		Ref<FmodAudioSample> sample;

		void emit();

		void set_sample(Ref<FmodAudioSample> new_sample);
		Ref<FmodAudioSample> get_sample() const;
	};
}

#endif // !FMOD_AUDIO_SAMPLE_EMITTER_H
