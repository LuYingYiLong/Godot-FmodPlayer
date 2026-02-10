#include "fmod_channel_group.h"

namespace godot {
	void FmodChannelGroup::_bind_methods() {

	}

	FmodChannelGroup::FmodChannelGroup() {

	}
	
	FmodChannelGroup::~FmodChannelGroup() {
		FMOD_CHECK(channel_group->release());
	}

	void FmodChannelGroup::add_group(Ref<FmodChannelGroup> child_group, bool propagatedspclock) {
		FMOD_CHECK(channel_group->addGroup(child_group->channel_group, propagatedspclock));
	}
}