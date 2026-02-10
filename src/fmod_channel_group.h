#ifndef FMOD_CHANNEL_GROUP_H
#define FMOD_CHANNEL_GROUP_H

#include <fmod.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/class_db.hpp>
#include "fmod_server.h"

namespace godot {
	class FmodChannelGroup : public RefCounted {
		GDCLASS(FmodChannelGroup, RefCounted)

	private:

	protected:
		static void _bind_methods();

	public:
		FmodChannelGroup();
		~FmodChannelGroup();

		FMOD::ChannelGroup* channel_group = nullptr;

		void add_group(Ref<FmodChannelGroup> channel_group, bool propagatedspclock = true);
	};
}

#endif // !FMOD_CHANNEL_GROUP_H