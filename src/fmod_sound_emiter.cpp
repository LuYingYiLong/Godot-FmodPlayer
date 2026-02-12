#include "fmod_sound_emiter.h"

namespace godot {
	void FmodSoundEmiter::_bind_methods() {
		ClassDB::bind_method(D_METHOD("emit"), &FmodSoundEmiter::emit);
		ClassDB::bind_method(D_METHOD("set_sample", "sample"), &FmodSoundEmiter::set_sample);
		ClassDB::bind_method(D_METHOD("get_sample"), &FmodSoundEmiter::get_sample);
		ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sample", PROPERTY_HINT_RESOURCE_TYPE, "FmodAudioSample"), "set_sample", "get_sample");
	}

	FmodSoundEmiter::FmodSoundEmiter() {
		system = FmodServer::get_main_system();
		channels = system->create_channel_group(get_name());
		FmodChannelGroup* master_group = system->get_master_channel_group();
		master_group->add_group(channels);
		memdelete(master_group);
		master_group = nullptr;
	}
	FmodSoundEmiter::~FmodSoundEmiter() {
		memdelete(channels);

		system = nullptr;
		channels = nullptr;
	}

	void FmodSoundEmiter::_on_channel_ended(FmodChannel* channel) {
		channel->disconnect("ended", callable_mp(this, &FmodSoundEmiter::_on_channel_ended));
		memdelete(channel);
		channel = nullptr;
	}

	void FmodSoundEmiter::emit() {
		FmodChannel* channel = system->play_sound(sample->sound, channels);
		channel->connect("ended", callable_mp(this, &FmodSoundEmiter::_on_channel_ended).bind(channel), CONNECT_DEFERRED);
	}

	void FmodSoundEmiter::set_sample(Ref<FmodAudioSample> new_sample) {
		sample = new_sample;
	}

	Ref<FmodAudioSample> FmodSoundEmiter::get_sample() const {
		return sample;
	}
}