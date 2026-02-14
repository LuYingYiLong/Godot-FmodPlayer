#include "fmod_audio_sample_emitter.h"

namespace godot {
	void FmodAudioSampleEmitter::_bind_methods() {
		ClassDB::bind_method(D_METHOD("emit"), &FmodAudioSampleEmitter::emit);
		ClassDB::bind_method(D_METHOD("set_sample", "sample"), &FmodAudioSampleEmitter::set_sample);
		ClassDB::bind_method(D_METHOD("get_sample"), &FmodAudioSampleEmitter::get_sample);
		ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sample", PROPERTY_HINT_RESOURCE_TYPE, "FmodAudioSample"), "set_sample", "get_sample");
	}

	FmodAudioSampleEmitter::FmodAudioSampleEmitter() {
		system = FmodServer::get_main_system();
		channel_group = system->create_channel_group(get_name());
		FmodChannelGroup* master_group = system->get_master_channel_group();
		master_group->add_group(channel_group);
		memdelete(master_group);
		master_group = nullptr;
	}
	FmodAudioSampleEmitter::~FmodAudioSampleEmitter() {
		memdelete(channel_group);

		system = nullptr;
		channel_group = nullptr;
	}

	void FmodAudioSampleEmitter::_on_channel_ended(FmodChannel* channel) {
		if (!channel) return;
		channel->disconnect("ended", callable_mp(this, &FmodAudioSampleEmitter::_on_channel_ended));
		memdelete(channel);
		channel = nullptr;
	}

	void FmodAudioSampleEmitter::emit() {
		ERR_FAIL_COND(!system || sample.is_null() || !channel_group);
		FmodChannel* channel = system->play_sound(sample->sound, channel_group);
		channel->connect("ended", callable_mp(this, &FmodAudioSampleEmitter::_on_channel_ended).bind(channel), CONNECT_DEFERRED);
	}

	void FmodAudioSampleEmitter::set_sample(Ref<FmodAudioSample> new_sample) {
		sample = new_sample;
	}

	Ref<FmodAudioSample> FmodAudioSampleEmitter::get_sample() const {
		return sample;
	}
}