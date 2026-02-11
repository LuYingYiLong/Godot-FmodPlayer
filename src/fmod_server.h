#ifndef FMOD_SERVER_H
#define FMOD_SERVER_H

#include <fmod.hpp>
#include <fmod_errors.h>
#include <godot_cpp/classes/main_loop.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/performance.hpp>

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
		double _get_dsp() const;
		double _get_stream() const;
		double _get_geometry() const;
		double _get_update() const;
		double _get_convolution1() const;
		double _get_convolution2() const;

	protected:
		static void _bind_methods();

	public:
		FmodServer();
		~FmodServer();

		enum FmodInitFlags {
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

		enum FmodSoundMode {
			MODE_DEFAULT				  = 0x00000000,
			MODE_LOOP_OFF				  = 0x00000001,
			MODE_LOOP_NORMAL			  = 0x00000002,
			MODE_LOOP_BIDI				  = 0x00000004,
			MODE_2D						  = 0x00000008,
			MODE_3D						  = 0x00000010,
			MODE_CREATESTREAM			  = 0x00000080,
			MODE_CREATESAMPLE			  = 0x00000100,
			MODE_CREATECOMPRESSEDSAMPLE	  = 0x00000200,
			MODE_OPENUSER				  = 0x00000400,
			MODE_OPENMEMORY				  = 0x00000800,
			MODE_OPENMEMORY_POINT		  = 0x10000000,
			MODE_OPENRAW				  = 0x00001000,
			MODE_OPENONLY				  = 0x00002000,
			MODE_ACCURATETIME			  = 0x00004000,
			MODE_MPEGSEARCH				  = 0x00008000,
			MODE_NONBLOCKING			  = 0x00010000,
			MODE_UNIQUE                   = 0x00020000,
			MODE_3D_HEADRELATIVE		  = 0x00040000,
			MODE_3D_WORLDRELATIVE         = 0x00080000,
			MODE_3D_INVERSEROLLOFF        = 0x00100000,
			MODE_3D_LINEARROLLOFF         = 0x00200000,
			MODE_3D_LINEARSQUAREROLLOFF   = 0x00400000,
			MODE_3D_INVERSETAPEREDROLLOFF = 0x00800000,
			MODE_3D_CUSTOMROLLOFF         = 0x04000000,
		 	MODE_3D_IGNOREGEOMETRY        = 0x40000000,
			MODE_IGNORETAGS               = 0x02000000,
		    MODE_LOWMEM                   = 0x08000000,
		    MODE_VIRTUAL_PLAYFROMSTART    = 0x80000000
		};

		enum Timeunit {
			TIMEUNIT_MS = 0x00000001,
			TIMEUNIT_PCM = 0x00000002,
			TIMEUNIT_PCMBYTES = 0x00000004,
			TIMEUNIT_RAWBYTES = 0x00000008,
			TIMEUNIT_PCMFRACTION = 0x00000010,
			TIMEUNIT_MODORDER = 0x00000100,
			TIMEUNIT_MODROW = 0x00000200,
			TIMEUNIT_MODPATTERN = 0x00000400
		};

		static FMOD::System* fmod_system;
		static Ref<FmodChannelGroup> master_channel_group;

		static FmodServer* get_singleton();

		bool _process(double p_delta) override;

		static int get_version();																					// 获取 Fmod 版本

		static Ref<FmodChannelGroup> get_master_channel_group();
		static Ref<FmodSound> create_sound_from_file(const String p_path, unsigned int mode);						// 从文件创建 FmodSound
		static Ref<FmodSound> create_sound_from_memory(const PackedByteArray& data, unsigned int mode);			// 从内存创建 FmodSound
		static Ref<FmodSound> create_sound_from_res(const String p_path, unsigned int mode);						// 从资源文件创建 FmodSound
		static Ref<FmodChannelGroup> create_channel_group(const String& p_name);									// 创建 FmodChannelGroup
		static Ref<FmodChannel> play_sound(Ref<FmodSound> sound, Ref<FmodChannelGroup> channel_group, bool paused = false); // 创建 FmodChannel
		static Ref<FmodChannel> play_sound_use_master_channel_group(Ref<FmodSound> sound, bool paused = false);		// 使用 MasterChannelGroup 创建 FmodChannel
		static double get_latency_ms();
		static Dictionary get_cpu_usage();
	};
}

VARIANT_ENUM_CAST(FmodServer::FmodInitFlags);
VARIANT_ENUM_CAST(FmodServer::FmodSoundMode);
VARIANT_ENUM_CAST(FmodServer::Timeunit);

#endif // !FMOD_SERVER_H
