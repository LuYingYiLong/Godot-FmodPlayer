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
		ClassDB::bind_method(D_METHOD("get_version"), &FmodSystem::get_version);
		ClassDB::bind_method(D_METHOD("create_sound_from_file", "path", "mode"), &FmodSystem::create_sound_from_file, DEFVAL(MODE_DEFAULT));
		ClassDB::bind_method(D_METHOD("create_sound_from_memory", "data", "mode"), &FmodSystem::create_sound_from_memory, DEFVAL(MODE_DEFAULT));
		ClassDB::bind_method(D_METHOD("create_sound_from_res", "path", "mod"), &FmodSystem::create_sound_from_res, DEFVAL(MODE_DEFAULT));
		ClassDB::bind_method(D_METHOD("create_channel_group", "name"), &FmodSystem::create_channel_group);
		ClassDB::bind_method(D_METHOD("play_sound", "sound", "channel_group", "paused"), &FmodSystem::play_sound);
		ClassDB::bind_method(D_METHOD("get_master_channel_group"), &FmodSystem::get_master_channel_group);
		ClassDB::bind_method(D_METHOD("get_cpu_usage"), &FmodSystem::get_cpu_usage);
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

	Dictionary FmodSystem::get_version() {
		ERR_FAIL_COND_V(!system, Dictionary());
		unsigned int version = 0;
		unsigned int buildnumber = 0;
		FMOD_CALL_CHECK_V(system->getVersion(&version, &buildnumber), Dictionary());
		Dictionary result;
		result["version"] = version;
		result["build_number"] = buildnumber;
		return result;
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

	Dictionary FmodSystem::get_cpu_usage() {
		ERR_FAIL_COND_V(!system, Dictionary());
		Dictionary result;
		FMOD_CPU_USAGE cpu_usage;
		FMOD_CHECK(system->getCPUUsage(&cpu_usage));
		result["dsp"] = cpu_usage.dsp;
		result["stream"] = cpu_usage.stream;
		result["geometry"] = cpu_usage.geometry;
		result["update"] = cpu_usage.update;
		result["convolution1"] = cpu_usage.convolution1;
		result["convolution2"] = cpu_usage.convolution2;
		return result;
	}
}