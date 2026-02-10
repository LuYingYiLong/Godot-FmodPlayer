#include "fmod_channel.h"

namespace godot {
	void FmodChannel::_bind_methods() {
		BIND_ENUM_CONSTANT(TIMEUNIT_MS);
		BIND_ENUM_CONSTANT(TIMEUNIT_PCM);
		BIND_ENUM_CONSTANT(TIMEUNIT_PCMBYTES);
		BIND_ENUM_CONSTANT(TIMEUNIT_RAWBYTES);
		BIND_ENUM_CONSTANT(TIMEUNIT_PCMFRACTION);
		BIND_ENUM_CONSTANT(TIMEUNIT_MODORDER);
		BIND_ENUM_CONSTANT(TIMEUNIT_MODROW);
		BIND_ENUM_CONSTANT(TIMEUNIT_MODPATTERN);
		ClassDB::bind_method(D_METHOD("set_paused", "paused"), &FmodChannel::set_paused);
		ClassDB::bind_method(D_METHOD("set_volume", "volume"), &FmodChannel::set_volume);
		ClassDB::bind_method(D_METHOD("set_pitch", "pitch"), &FmodChannel::set_pitch);
		ClassDB::bind_method(D_METHOD("set_position", "position", "timeunit"), &FmodChannel::set_position, DEFVAL(TIMEUNIT_MS));
	}

	FmodChannel::FmodChannel() {

	}

	FmodChannel::~FmodChannel() {
		if (channel) {
			channel->stop();
			channel = nullptr;
		}
	}

	void FmodChannel::set_paused(bool paused) {
		FMOD_CHECK(channel->setPaused(paused));
	}

	void FmodChannel::set_volume(float volume) {
		FMOD_CHECK(channel->setVolume(volume));
	}

	void FmodChannel::set_pitch(float pitch) {
		FMOD_CHECK(channel->setPitch(pitch));
	}
		
	void FmodChannel::set_position(int position, Timeunit timeunit) {
		FMOD_CHECK(channel->setPosition(position, timeunit));
	}
}