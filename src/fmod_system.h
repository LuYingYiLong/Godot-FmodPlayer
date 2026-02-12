#ifndef FMOD_SYSTEM_H
#define FMOD_SYSTEM_H

#include <fmod.hpp>
#include <fmod_errors.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include "fmod_utils.hpp"

namespace godot {
	class FmodSound;
	class FmodChannel;
	class FmodChannelGroup;

	class FmodSystem : public RefCounted {
		GDCLASS(FmodSystem, RefCounted)

	private:
		FMOD::System* system = nullptr;

		bool _check_error(FMOD_RESULT result);

	protected:
		static void _bind_methods();

	public:
		FmodSystem();
		~FmodSystem();

		enum FmodInitFlags {
			INIT_NORMAL = 0x00000000,
			INIT_STREAM_FROM_UPDATE = 0x00000001,
			INIT_MIX_FROM_UPDATE = 0x00000002,
			INIT_3D_RIGHTHANDED = 0x00000004,
			INIT_CLIP_OUTPUT = 0x00000008,
			INIT_CHANNEL_LOWPASS = 0x00000100,
			INIT_CHANNEL_DISTANCEFILTER = 0x00000200,
			INIT_PROFILE_ENABLE = 0x00010000,
			INIT_VOL0_BECOMES_VIRTUAL = 0x00020000,
			INIT_GEOMETRY_USECLOSEST = 0x00040000,
			INIT_PREFER_DOLBY_DOWNMIX = 0x00080000,
			INIT_THREAD_UNSAFE = 0x00100000,
			INIT_PROFILE_METER_ALL = 0x00200000,
			INIT_MEMORY_TRACKING = 0x00400000
		};

		enum FmodOutputType {
			OUTPUTTYPE_AUTODETECT,
			OUTPUTTYPE_UNKNOWN,
			OUTPUTTYPE_NOSOUND,
			OUTPUTTYPE_WAVWRITER,
			OUTPUTTYPE_NOSOUND_NRT,
			OUTPUTTYPE_WAVWRITER_NRT,
			OUTPUTTYPE_WASAPI,
			OUTPUTTYPE_ASIO,
			OUTPUTTYPE_PULSEAUDIO,
			OUTPUTTYPE_ALSA,
			OUTPUTTYPE_COREAUDIO,
			OUTPUTTYPE_AUDIOTRACK,
			OUTPUTTYPE_OPENSL,
			OUTPUTTYPE_AUDIOOUT,
			OUTPUTTYPE_AUDIO3D,
			OUTPUTTYPE_WEBAUDIO,
			OUTPUTTYPE_NNAUDIO,
			OUTPUTTYPE_WINSONIC,
			OUTPUTTYPE_AAUDIO,
			OUTPUTTYPE_AUDIOWORKLET,
			OUTPUTTYPE_PHASE,
			OUTPUTTYPE_OHAUDIO,

			OUTPUTTYPE_MAX,
			OUTPUTTYPE_FORCEINT = 65536
		};

		enum FmodSpeakerMode
		{
			SPEAKERMODE_DEFAULT,
			SPEAKERMODE_RAW,
			SPEAKERMODE_MONO,
			SPEAKERMODE_STEREO,
			SPEAKERMODE_QUAD,
			SPEAKERMODE_SURROUND,
			SPEAKERMODE_5POINT1,
			SPEAKERMODE_7POINT1,
			SPEAKERMODE_7POINT1POINT4,

			SPEAKERMODE_MAX,
			SPEAKERMODE_FORCEINT = 65536
		};

		enum FmodSoundMode {
			MODE_DEFAULT = 0x00000000,
			MODE_LOOP_OFF = 0x00000001,
			MODE_LOOP_NORMAL = 0x00000002,
			MODE_LOOP_BIDI = 0x00000004,
			MODE_2D = 0x00000008,
			MODE_3D = 0x00000010,
			MODE_CREATESTREAM = 0x00000080,
			MODE_CREATESAMPLE = 0x00000100,
			MODE_CREATECOMPRESSEDSAMPLE = 0x00000200,
			MODE_OPENUSER = 0x00000400,
			MODE_OPENMEMORY = 0x00000800,
			MODE_OPENMEMORY_POINT = 0x10000000,
			MODE_OPENRAW = 0x00001000,
			MODE_OPENONLY = 0x00002000,
			MODE_ACCURATETIME = 0x00004000,
			MODE_MPEGSEARCH = 0x00008000,
			MODE_NONBLOCKING = 0x00010000,
			MODE_UNIQUE = 0x00020000,
			MODE_3D_HEADRELATIVE = 0x00040000,
			MODE_3D_WORLDRELATIVE = 0x00080000,
			MODE_3D_INVERSEROLLOFF = 0x00100000,
			MODE_3D_LINEARROLLOFF = 0x00200000,
			MODE_3D_LINEARSQUAREROLLOFF = 0x00400000,
			MODE_3D_INVERSETAPEREDROLLOFF = 0x00800000,
			MODE_3D_CUSTOMROLLOFF = 0x04000000,
			MODE_3D_IGNOREGEOMETRY = 0x40000000,
			MODE_IGNORETAGS = 0x02000000,
			MODE_LOWMEM = 0x08000000,
			MODE_VIRTUAL_PLAYFROMSTART = 0x80000000
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
		
		void update();

		void set_output(FmodOutputType output_type);
		FmodOutputType get_output() const;
		int64_t get_num_drivers() const;
		Dictionary get_driver_info(int id) const;
		void set_driver(int driver);
		int64_t get_driver() const;

		void set_network_proxy(const String& p_proxy);
		String get_network_proxy() const;
		void set_network_timeout(int timeout);
		int64_t get_network_timeout() const;

		Dictionary get_version() const;																		// 获取 Fmod 版本
		uint64_t get_output_handle() const;
		Dictionary get_channels_playing() const;
		Dictionary get_cpu_usage() const;
		Dictionary get_file_usage() const;
		PackedFloat32Array get_default_mix_matrix(
			FmodSpeakerMode source_speaker_mode, FmodSpeakerMode target_speaker_mode, int array_length, int hop) const;
		int64_t get_speaker_mode_channels(FmodSpeakerMode mode) const;

		Ref<FmodSound> create_sound_from_file(const String p_path, unsigned int mode);						// 从文件创建 FmodSound
		Ref<FmodSound> create_sound_from_memory(const PackedByteArray& data, unsigned int mode);			// 从内存创建 FmodSound
		Ref<FmodSound> create_sound_from_res(const String p_path, unsigned int mode);						// 从资源文件创建 FmodSound
		Ref<FmodChannelGroup> create_channel_group(const String& p_name);									// 创建 ChannelGroup
		Ref<FmodChannel> play_sound(
			Ref<FmodSound> sound, Ref<FmodChannelGroup> channel_group, bool paused = false);				// 创建 FmodChannel
		Ref<FmodChannelGroup> get_master_channel_group();													// 获取所有声音最终路由到的主通道组
		
	};
}

VARIANT_ENUM_CAST(FmodSystem::FmodInitFlags);
VARIANT_ENUM_CAST(FmodSystem::FmodOutputType);
VARIANT_ENUM_CAST(FmodSystem::FmodSpeakerMode);
VARIANT_ENUM_CAST(FmodSystem::FmodSoundMode);
VARIANT_ENUM_CAST(FmodSystem::Timeunit);

#endif // !FMOD_SYSTEM_H

