#ifndef FMOD_SERVER_H
#define FMOD_SERVER_H

#include <fmod.hpp>
#include <fmod_errors.h>
#include <godot_cpp/classes/main_loop.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#define FMOD_CHECK(result) \
    do { \
        FMOD_RESULT _r = (result); \
        if (_r != FMOD_OK) { \
            godot::UtilityFunctions::push_error( \
                "FMOD Error at ", __FILE__, ":", __LINE__, \
                " - ", FMOD_ErrorString(_r) \
            ); \
        } \
    } while(0)

namespace godot {
	class FmodSound;
	class FmodChannelGroup;
	class FmodChannel;

	class FmodServer : public MainLoop {
		GDCLASS(FmodServer, MainLoop)
		static FmodServer* singleton;

	private:

	protected:
		static void _bind_methods();

	public:
		FmodServer();
		~FmodServer();

		enum FMODInitFlags {
			INIT_NORMAL						= 0x00000000,
			INIT_STREAM_FROM_UPDATE			= 0x00000001,
			INIT_MIX_FROM_UPDATE			= 0x00000002,
			INIT_3D_RIGHTHANDED				= 0x00000004,
			INIT_CLIP_OUTPUT				= 0x00000008,
			INIT_CHANNEL_LOWPASS			= 0x00000100,
			INIT_CHANNEL_DISTANCEFILTER		= 0x00000200,
			INIT_PROFILE_ENABLE				= 0x00010000,
			INIT_VOL0_BECOMES_VIRTUAL		= 0x00020000,
			INIT_GEOMETRY_USECLOSEST		= 0x00040000,
			INIT_PREFER_DOLBY_DOWNMIX		= 0x00080000,
			INIT_THREAD_UNSAFE				= 0x00100000,
			INIT_PROFILE_METER_ALL			= 0x00200000,
			INIT_MEMORY_TRACKING			= 0x00400000
		};

		static FMOD::System* fmod_system;
		static Ref<FmodChannelGroup> master_channel_group;

		static FmodServer* get_singleton();

		bool _process(double p_delta) override;

		static int get_version();														// 获取 Fmod 版本

		static Ref<FmodChannelGroup> get_master_channel_group();
		static Ref<FmodSound> create_sound(const String& p_path);						// 创建 FmodSound
		static Ref<FmodChannelGroup> create_channel_group(const String& p_name);		// 创建 FmodChannelGroup
		static Ref<FmodChannel> play_sound(Ref<FmodSound> sound, Ref<FmodChannelGroup> channel_group, bool paused); // 创建 FmodChannel

	};
}

VARIANT_ENUM_CAST(FmodServer::FMODInitFlags);

#endif // !FMOD_SERVER_H
