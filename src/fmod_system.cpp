#include "fmod_system.h"

#include "fmod_sound.h"
#include "fmod_channel.h"
#include "fmod_channel_group.h"

namespace godot {
	void FmodSystem::_bind_methods() {
		BIND_ENUM_CONSTANT(INIT_NORMAL);
		BIND_ENUM_CONSTANT(INIT_STREAM_FROM_UPDATE);
		BIND_ENUM_CONSTANT(INIT_MIX_FROM_UPDATE);
		BIND_ENUM_CONSTANT(INIT_3D_RIGHTHANDED);
		BIND_ENUM_CONSTANT(INIT_CLIP_OUTPUT);
		BIND_ENUM_CONSTANT(INIT_CHANNEL_LOWPASS);
		BIND_ENUM_CONSTANT(INIT_CHANNEL_DISTANCEFILTER);
		BIND_ENUM_CONSTANT(INIT_PROFILE_ENABLE);
		BIND_ENUM_CONSTANT(INIT_VOL0_BECOMES_VIRTUAL);
		BIND_ENUM_CONSTANT(INIT_GEOMETRY_USECLOSEST);
		BIND_ENUM_CONSTANT(INIT_PREFER_DOLBY_DOWNMIX);
		BIND_ENUM_CONSTANT(INIT_THREAD_UNSAFE);
		BIND_ENUM_CONSTANT(INIT_PROFILE_METER_ALL);
		BIND_ENUM_CONSTANT(INIT_MEMORY_TRACKING);

		BIND_ENUM_CONSTANT(OUTPUTTYPE_AUTODETECT);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_UNKNOWN);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_NOSOUND);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_WAVWRITER);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_NOSOUND_NRT);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_WAVWRITER_NRT);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_WASAPI);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_ASIO);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_PULSEAUDIO);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_ALSA);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_COREAUDIO);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_AUDIOTRACK);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_OPENSL);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_AUDIOOUT);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_AUDIO3D);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_WEBAUDIO);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_NNAUDIO);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_WINSONIC);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_AAUDIO);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_AUDIOWORKLET);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_PHASE);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_OHAUDIO);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_MAX);
		BIND_ENUM_CONSTANT(OUTPUTTYPE_FORCEINT);

		BIND_ENUM_CONSTANT(SPEAKERMODE_DEFAULT);
		BIND_ENUM_CONSTANT(SPEAKERMODE_RAW);
		BIND_ENUM_CONSTANT(SPEAKERMODE_MONO);
		BIND_ENUM_CONSTANT(SPEAKERMODE_STEREO);
		BIND_ENUM_CONSTANT(SPEAKERMODE_QUAD);
		BIND_ENUM_CONSTANT(SPEAKERMODE_SURROUND);
		BIND_ENUM_CONSTANT(SPEAKERMODE_5POINT1);
		BIND_ENUM_CONSTANT(SPEAKERMODE_7POINT1);
		BIND_ENUM_CONSTANT(SPEAKERMODE_7POINT1POINT4);
		BIND_ENUM_CONSTANT(SPEAKERMODE_MAX);
		BIND_ENUM_CONSTANT(SPEAKERMODE_FORCEINT);

		BIND_ENUM_CONSTANT(MODE_DEFAULT);
		BIND_ENUM_CONSTANT(MODE_LOOP_OFF);
		BIND_ENUM_CONSTANT(MODE_LOOP_NORMAL);
		BIND_ENUM_CONSTANT(MODE_LOOP_BIDI);
		BIND_ENUM_CONSTANT(MODE_2D);
		BIND_ENUM_CONSTANT(MODE_3D);
		BIND_ENUM_CONSTANT(MODE_CREATESTREAM);
		BIND_ENUM_CONSTANT(MODE_CREATESAMPLE);
		BIND_ENUM_CONSTANT(MODE_CREATECOMPRESSEDSAMPLE);
		BIND_ENUM_CONSTANT(MODE_OPENUSER);
		BIND_ENUM_CONSTANT(MODE_OPENMEMORY);
		BIND_ENUM_CONSTANT(MODE_OPENMEMORY_POINT);
		BIND_ENUM_CONSTANT(MODE_OPENRAW);
		BIND_ENUM_CONSTANT(MODE_OPENONLY);
		BIND_ENUM_CONSTANT(MODE_ACCURATETIME);
		BIND_ENUM_CONSTANT(MODE_MPEGSEARCH);
		BIND_ENUM_CONSTANT(MODE_NONBLOCKING);
		BIND_ENUM_CONSTANT(MODE_UNIQUE);
		BIND_ENUM_CONSTANT(MODE_3D_HEADRELATIVE);
		BIND_ENUM_CONSTANT(MODE_3D_WORLDRELATIVE);
		BIND_ENUM_CONSTANT(MODE_3D_INVERSEROLLOFF);
		BIND_ENUM_CONSTANT(MODE_3D_LINEARROLLOFF);
		BIND_ENUM_CONSTANT(MODE_3D_LINEARSQUAREROLLOFF);
		BIND_ENUM_CONSTANT(MODE_3D_INVERSETAPEREDROLLOFF);
		BIND_ENUM_CONSTANT(MODE_3D_CUSTOMROLLOFF);
		BIND_ENUM_CONSTANT(MODE_3D_IGNOREGEOMETRY);
		BIND_ENUM_CONSTANT(MODE_IGNORETAGS);
		BIND_ENUM_CONSTANT(MODE_LOWMEM);
		BIND_ENUM_CONSTANT(MODE_VIRTUAL_PLAYFROMSTART);

		BIND_ENUM_CONSTANT(TIMEUNIT_MS);
		BIND_ENUM_CONSTANT(TIMEUNIT_PCM);
		BIND_ENUM_CONSTANT(TIMEUNIT_PCMBYTES);
		BIND_ENUM_CONSTANT(TIMEUNIT_RAWBYTES);
		BIND_ENUM_CONSTANT(TIMEUNIT_PCMFRACTION);
		BIND_ENUM_CONSTANT(TIMEUNIT_MODORDER);
		BIND_ENUM_CONSTANT(TIMEUNIT_MODROW);
		BIND_ENUM_CONSTANT(TIMEUNIT_MODPATTERN);

		ClassDB::bind_method(D_METHOD("update"), &FmodSystem::update);
		ClassDB::bind_method(D_METHOD("set_output", "output_type"), &FmodSystem::set_output);
		ClassDB::bind_method(D_METHOD("get_output"), &FmodSystem::get_output);
		ClassDB::bind_method(D_METHOD("get_num_drivers"), &FmodSystem::get_num_drivers);
		ClassDB::bind_method(D_METHOD("get_driver_info", "id"), &FmodSystem::get_driver_info);
		ClassDB::bind_method(D_METHOD("set_driver", "driver"), &FmodSystem::set_driver);
		ClassDB::bind_method(D_METHOD("get_driver"), &FmodSystem::get_driver);
		ClassDB::bind_method(D_METHOD("set_network_proxy", "proxy"), &FmodSystem::set_network_proxy);
		ClassDB::bind_method(D_METHOD("get_network_proxy"), &FmodSystem::get_network_proxy);
		ClassDB::bind_method(D_METHOD("set_network_timeout", "timeout"), &FmodSystem::set_network_timeout);
		ClassDB::bind_method(D_METHOD("get_network_timeout"), &FmodSystem::get_network_timeout);
		ClassDB::bind_method(D_METHOD("get_version"), &FmodSystem::get_version);
		ClassDB::bind_method(D_METHOD("get_output_handle"), &FmodSystem::get_output_handle);
		ClassDB::bind_method(D_METHOD("get_channels_playing"), &FmodSystem::get_channels_playing);
		ClassDB::bind_method(D_METHOD("get_cpu_usage"), &FmodSystem::get_cpu_usage);
		ClassDB::bind_method(D_METHOD("get_file_usage"), &FmodSystem::get_file_usage);
		ClassDB::bind_method(D_METHOD("get_default_mix_matrix", "source_speaker_mode", "target_speaker_mode", "array_length", "hop"), &FmodSystem::get_default_mix_matrix);
		ClassDB::bind_method(D_METHOD("get_speaker_mode_channels", "mode"), &FmodSystem::get_speaker_mode_channels);
		ClassDB::bind_method(D_METHOD("create_sound_from_file", "path", "mode"), &FmodSystem::create_sound_from_file, DEFVAL(MODE_DEFAULT));
		ClassDB::bind_method(D_METHOD("create_sound_from_memory", "data", "mode"), &FmodSystem::create_sound_from_memory, DEFVAL(MODE_DEFAULT));
		ClassDB::bind_method(D_METHOD("create_sound_from_res", "path", "mod"), &FmodSystem::create_sound_from_res, DEFVAL(MODE_DEFAULT));
		ClassDB::bind_method(D_METHOD("create_channel_group", "name"), &FmodSystem::create_channel_group);
		ClassDB::bind_method(D_METHOD("play_sound", "sound", "channel_group", "paused"), &FmodSystem::play_sound);
		ClassDB::bind_method(D_METHOD("get_master_channel_group"), &FmodSystem::get_master_channel_group);
	}

	bool FmodSystem::_check_error(FMOD_RESULT result) {
		if (result != FMOD_OK)
			UtilityFunctions::push_error("FMOD System Error at ", __FILE__, ":", __LINE__, " - ", FMOD_ErrorString(result));
		return result != FMOD_OK;
	}

	FmodSystem::FmodSystem() {
		if (FMOD_CHECK_ERR(FMOD::System_Create(&system))) return;
		if (FMOD_CHECK_ERR(system->init(32, FMOD_INIT_NORMAL, nullptr))) return;
	}

	FmodSystem::~FmodSystem() {
		if (system) {
			FMOD_CHECK(system->release());
			system = nullptr;
		}
	}

	void FmodSystem::update() {
		if (system->update() != FMOD_OK)
			UtilityFunctions::push_error("Fmod Sytem update failed!");;
	}

	void FmodSystem::set_output(FmodOutputType output_type) {
		auto fmod_output_type = static_cast<FMOD_OUTPUTTYPE>((int)output_type);
		FMOD_CHECK(system->setOutput(fmod_output_type));
	}

	FmodSystem::FmodOutputType FmodSystem::get_output() const {
		FMOD_OUTPUTTYPE fmod_output_type = FMOD_OUTPUTTYPE_UNKNOWN;
		FMOD_CALL_CHECK_V(system->getOutput(&fmod_output_type), OUTPUTTYPE_UNKNOWN);
		FmodOutputType output_type = static_cast<FmodOutputType>((int)fmod_output_type);
		return output_type;
	}

	int64_t FmodSystem::get_num_drivers() const {
		int num = 0;
		FMOD_CALL_CHECK_V(system->getNumDrivers(&num), 0);
		return (int64_t)num;
	}

	Dictionary FmodSystem::get_driver_info(int id) const {
		char name[256] = { 0 };
		FMOD_GUID guid;
		int system_rate = 0;
		FMOD_SPEAKERMODE speaker_mode = FMOD_SPEAKERMODE_DEFAULT;
		int speaker_mode_channels = 0;
		FMOD_CALL_CHECK_V(system->getDriverInfo(
			id, name, 256, &guid, &system_rate, &speaker_mode, &speaker_mode_channels),
			Dictionary()
		);
		Dictionary result;
		result["name"] = String::utf8(name);
		// 生成标准GUID格式: {XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}
		String guid_string = vformat("{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
			guid.Data1,
			guid.Data2,
			guid.Data3,
			guid.Data4[0], guid.Data4[1],
			guid.Data4[2], guid.Data4[3],
			guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]
		);
		result["guid"] = guid_string;
		result["system_rate"] = system_rate;
		result["speaker_mode"] = static_cast<FmodSpeakerMode>((int)speaker_mode);
		result["speaker_mode_channels"] = speaker_mode_channels;
		return result;
	}

	void FmodSystem::set_driver(int driver) {
		FMOD_CHECK(system->setDriver(driver));
	}

	int64_t FmodSystem::get_driver() const {
		int driver = -1;
		FMOD_CALL_CHECK_V(system->getDriver(&driver), -1);
		return (int64_t)driver;
	}

	void FmodSystem::set_network_proxy(const String& p_proxy) {
		// 指定代理格式，例如: (如果没有指定端口，则默认为8888端口) host:portwww.fmod.com:8888
		// 支持基本认证，格式如下: user:password@host:portbob:sekrit123@www.fmod.com:8888
		const char* data = p_proxy.utf8().get_data();
		FMOD_CHECK(system->setNetworkProxy(data));
	}

	String FmodSystem::get_network_proxy() const {
		char proxy[256] = { 0 };
		FMOD_CALL_CHECK_V(system->getNetworkProxy(proxy, 256), String());
		return String::utf8(proxy);
	}

	void FmodSystem::set_network_timeout(int timeout) {
		FMOD_CHECK(system->setNetworkTimeout(timeout));
	}

	int64_t FmodSystem::get_network_timeout() const {
		int timeout = -1;
		FMOD_CALL_CHECK_V(system->getNetworkTimeout(&timeout), -1);
		return (int64_t)timeout;
	}

	Dictionary FmodSystem::get_version() const {
		ERR_FAIL_COND_V(!system, Dictionary());
		unsigned int version = 0;
		unsigned int buildnumber = 0;
		FMOD_CALL_CHECK_V(system->getVersion(&version, &buildnumber), Dictionary());
		Dictionary result;
		result["version"] = version;
		result["build_number"] = buildnumber;
		return result;
	}

	uint64_t FmodSystem::get_output_handle() const {
		ERR_FAIL_COND_V(!system, 0);
		void* handle = nullptr;
		FMOD_CALL_CHECK_V(system->getOutputHandle(&handle), 0);
		return reinterpret_cast<uint64_t>(handle);
	}

	Dictionary FmodSystem::get_channels_playing() const {
		int channels = 0;
		int real_channels = 0;
		FMOD_CALL_CHECK_V(system->getChannelsPlaying(&channels, &real_channels), Dictionary());
		Dictionary result;
		result["channels"] = channels;
		result["real_channels"] = real_channels;
		return result;
	}

	Dictionary FmodSystem::get_cpu_usage() const {
		ERR_FAIL_COND_V(!system, Dictionary());
		Dictionary result;
		FMOD_CPU_USAGE cpu_usage;
		FMOD_CALL_CHECK_V(system->getCPUUsage(&cpu_usage), Dictionary());
		result["dsp"] = cpu_usage.dsp;
		result["stream"] = cpu_usage.stream;
		result["geometry"] = cpu_usage.geometry;
		result["update"] = cpu_usage.update;
		result["convolution1"] = cpu_usage.convolution1;
		result["convolution2"] = cpu_usage.convolution2;
		return result;
	}

	Dictionary FmodSystem::get_file_usage() const {
		long long sample_bytes_read = 0;
		long long stream_bytes_read = 0;
		long long other_bytes_read = 0;
		FMOD_CALL_CHECK_V(system->getFileUsage(&sample_bytes_read, &stream_bytes_read, &other_bytes_read), Dictionary());
		Dictionary result;
		result["sample_bytes_read"] = sample_bytes_read;
		result["stream_bytes_read"] = stream_bytes_read;
		result["other_bytes_read"] = other_bytes_read;
		return result;
	}

	PackedFloat32Array FmodSystem::get_default_mix_matrix(
		FmodSpeakerMode source_speaker_mode,
		FmodSpeakerMode target_speaker_mode,
		int array_length,
		int hop) const {
		ERR_FAIL_COND_V(!system, PackedFloat32Array());

		FMOD_SPEAKERMODE fmod_source = static_cast<FMOD_SPEAKERMODE>((int)source_speaker_mode);
		FMOD_SPEAKERMODE fmod_target = static_cast<FMOD_SPEAKERMODE>((int)target_speaker_mode);

		// 获取实际需要的声道数
		int source_channels = 0;
		int target_channels = 0;
		FMOD_CALL_CHECK_V(system->getSpeakerModeChannels(fmod_source, &source_channels), PackedFloat32Array());
		FMOD_CALL_CHECK_V(system->getSpeakerModeChannels(fmod_target, &target_channels), PackedFloat32Array());

		int needed_size = source_channels * target_channels;

		// 如果没指定array_length，使用需要的尺寸
		if (array_length <= 0) {
			array_length = needed_size;
		}

		// 分配数组
		float* matrix = (float*)memalloc(array_length * sizeof(float));
		ERR_FAIL_COND_V(!matrix, PackedFloat32Array());

		// 初始化为0
		for (int i = 0; i < array_length; i++) {
			matrix[i] = 0.0f;
		}

		// 获取默认混音矩阵
		FMOD_RESULT result = system->getDefaultMixMatrix(
			fmod_source,
			fmod_target,
			matrix,
			hop
		);

		if (result != FMOD_OK) {
			memfree(matrix);
			FMOD_CALL_CHECK_V(result, PackedFloat32Array());
			return PackedFloat32Array();
		}

		// 转换为PackedFloat32Array
		PackedFloat32Array mix_matrix;
		mix_matrix.resize(needed_size);				// 只返回实际有用的数据
		for (int i = 0; i < needed_size; i++) {
			mix_matrix[i] = matrix[i * hop];		// 应用跳步
		}

		memfree(matrix);
		return mix_matrix;
	}

	int64_t FmodSystem::get_speaker_mode_channels(FmodSpeakerMode mode) const {
		FMOD_SPEAKERMODE fmod_speaker_mode = static_cast<FMOD_SPEAKERMODE>((int)mode);
		int channels = 0;
		FMOD_CALL_CHECK_V(system->getSpeakerModeChannels(fmod_speaker_mode, &channels), -1);
		return (int64_t)channels;
	}

	// Creation and retrieval

	Ref<FmodSound> FmodSystem::create_sound_from_file(const String p_path, unsigned int mode) {
		ERR_FAIL_COND_V(!system, Ref<FmodSound>());
		// 检查是否为资源文件，如果是则改用从资源文件创建 FmodSound
		if (p_path.begins_with("res://")) {
			return create_sound_from_res(p_path, mode);
		}

		// 保留字符串对象，防止悬空指针
		CharString path_utf8 = ProjectSettings::get_singleton()->globalize_path(p_path).utf8();
		const char* path_cstr = path_utf8.get_data();

		// 实例化 FmodSound
		Ref<FmodSound> fmod_sound;
		fmod_sound.instantiate();

		FMOD_CALL_CHECK_V(system->createSound(
			path_cstr,
			mode,
			nullptr,							// 文件加载不需要 exinfo
			&fmod_sound->sound
		), Ref<FmodSound>());

		return fmod_sound;
	}

	Ref<FmodSound> FmodSystem::create_sound_from_memory(const PackedByteArray& data, unsigned int mode) {
		ERR_FAIL_COND_V(!system || data.is_empty(), nullptr);

		// 实例化 FmodSound
		Ref<FmodSound> sound;
		sound.instantiate();
		sound->data = data;
		FMOD_CREATESOUNDEXINFO exinfo = {};
		exinfo.cbsize = sizeof(exinfo);
		exinfo.length = sound->data.size();

		// 从 FmodSystem 创建音频
		FMOD_CALL_CHECK_V(system->createSound(
			(const char*)sound->data.ptr(),
			mode |= FMOD_OPENMEMORY,
			&exinfo,
			&sound->sound
		), nullptr);

		return sound;
	}

	Ref<FmodSound> FmodSystem::create_sound_from_res(const String p_path, unsigned int mode) {
		ERR_FAIL_COND_V(!system, Ref<FmodSound>());
		// 打开文件
		Ref<FileAccess> file = FileAccess::open(p_path, FileAccess::READ);
		ERR_FAIL_COND_V(file.is_null(), Ref<FmodSound>());

		// 读取文件数据到内存
		PackedByteArray data = file->get_buffer(file->get_length());
		ERR_FAIL_COND_V(data.is_empty(), Ref<FmodSound>());

		// 用内存模式创建 FMOD Sound

		return create_sound_from_memory(data, mode);
	}

	Ref<FmodChannelGroup> FmodSystem::create_channel_group(const String& p_name) {
		ERR_FAIL_COND_V(!system, Ref<FmodChannelGroup>());
		Ref<FmodChannelGroup> channel_group;
		channel_group.instantiate();
		FMOD_CALL_CHECK_V(
			system->createChannelGroup(p_name.utf8().get_data(), &channel_group->channel_group),
			Ref<FmodChannelGroup>()
		);
		return channel_group;
	}

	Ref<FmodChannel> FmodSystem::play_sound(Ref<FmodSound> sound, Ref<FmodChannelGroup> channel_group, bool paused) {
		ERR_FAIL_COND_V(
			!system || sound.is_null() || !sound->sound || channel_group.is_null() || !channel_group->channel_group,
			Ref<FmodChannel>()
		);

		// 创建 channel（不 instantiate，等 playSound 成功后再创建）
		FMOD::Channel* fmod_channel = nullptr;
		FMOD_CALL_CHECK_V(system->playSound(
			sound->sound,
			channel_group->channel_group,
			paused,
			&fmod_channel
		), Ref<FmodChannel>());

		// 关键：检查 fmod_channel 是否被填充
		if (!fmod_channel) {
			UtilityFunctions::push_error("playSound returned null channel");
			return Ref<FmodChannel>();
		}

		// 现在创建 Godot 包装对象
		Ref<FmodChannel> channel;
		channel.instantiate();
		channel->setup(fmod_channel);
		return channel;
	}

	Ref<FmodChannelGroup> FmodSystem::get_master_channel_group() {
		Ref<FmodChannelGroup> channel_group;
		channel_group.instantiate();
		FMOD_CALL_CHECK_V(system->getMasterChannelGroup(&channel_group->channel_group), Ref<FmodChannelGroup>());
		return channel_group;
	}
}