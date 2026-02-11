#include "fmod_channel.h"
#include "fmod_channel_group.h"
#include "fmod_server.h"
#include "fmod_sound.h"
#include <godot_cpp/classes/project_settings.hpp>
#include <string>

namespace godot {
	FmodServer* FmodServer::singleton = nullptr;
	FMOD::System* FmodServer::fmod_system = nullptr;
	Ref<FmodChannelGroup> FmodServer::master_channel_group;

	void FmodServer::_bind_methods() {
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

		ClassDB::bind_static_method("FmodServer", D_METHOD("get_singleton"), &FmodServer::get_singleton);
		ClassDB::bind_static_method("FmodServer", D_METHOD("get_version"), &FmodServer::get_version);
		ClassDB::bind_static_method("FmodServer", D_METHOD("get_master_channel_group"), &FmodServer::get_master_channel_group);
		ClassDB::bind_static_method("FmodServer", D_METHOD("create_sound_from_file", "path", "mode"), &FmodServer::create_sound_from_file, DEFVAL(MODE_DEFAULT));
		ClassDB::bind_static_method("FmodServer", D_METHOD("create_sound_from_memory", "data", "mode"), &FmodServer::create_sound_from_memory, DEFVAL(MODE_DEFAULT));
		ClassDB::bind_static_method("FmodServer", D_METHOD("create_sound_from_res", "path", "mod"), &FmodServer::create_sound_from_res, DEFVAL(MODE_DEFAULT));
		ClassDB::bind_static_method("FmodServer", D_METHOD("create_channel_group", "name"), &FmodServer::create_channel_group);
		ClassDB::bind_static_method("FmodServer", D_METHOD("play_sound", "sound", "channel_group", "paused"), &FmodServer::play_sound);
		ClassDB::bind_static_method("FmodServer", D_METHOD("play_sound_use_master_channel_group", "sound", "paused"), &FmodServer::play_sound_use_master_channel_group);
	}

	FmodServer::FmodServer() {
		ERR_FAIL_COND(singleton != nullptr);
		singleton = this;

		ERR_FAIL_COND(fmod_system != nullptr);

		FMOD_CHECK(FMOD::System_Create(&fmod_system));
		
		FMOD_CHECK(fmod_system->init(32, FMOD_INIT_NORMAL, nullptr));
		master_channel_group.instantiate();
		if (master_channel_group.is_null()) {
			UtilityFunctions::push_error("Failed to init master channel group!");
			return;
		}
		FMOD_CHECK(fmod_system->getMasterChannelGroup(&master_channel_group->channel_group));
		UtilityFunctions::print("FMOD Completed.\nFMOD Version: ", get_version());
	}

	FmodServer::~FmodServer() {
		ERR_FAIL_COND(singleton != this);
		singleton = nullptr;
		
		FMOD_CHECK(fmod_system->release());
	}

	FmodServer* FmodServer::get_singleton() {
		return singleton;
	}

	bool FmodServer::_process(double p_delta) {
		FMOD_CHECK(fmod_system->update());
		return false;
	}

	int FmodServer::get_version() {
		return FMOD_VERSION;
	}

	Ref<FmodChannelGroup> FmodServer::get_master_channel_group() {
		return master_channel_group;
	}

	Ref<FmodSound> FmodServer::create_sound_from_file(const String p_path, unsigned int mode) {
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

		FMOD_RESULT err = fmod_system->createSound(
			path_cstr,
			mode,
			nullptr,							// 文件加载不需要 exinfo
			&fmod_sound->sound
		);

		if (err != FMOD_OK) {
			UtilityFunctions::push_error("Failed to create sound from file: ", FMOD_ErrorString(err));
			return Ref<FmodSound>();
		}
		
		return fmod_sound;
	}

	Ref<FmodSound> FmodServer::create_sound_from_memory(const PackedByteArray& data, unsigned int mode) {
		// 数据判空
		ERR_FAIL_COND_V(data.is_empty(), Ref<FmodSound>());

		// 实例化 FmodSound
		Ref<FmodSound> sound;
		sound.instantiate();
		sound->data = data;
		FMOD_CREATESOUNDEXINFO exinfo = {};
		exinfo.cbsize = sizeof(exinfo);
		exinfo.length = sound->data.size();

		// 从 FmodSystem 创建音频
		FMOD_RESULT result = fmod_system->createSound(
			(const char*)sound->data.ptr(),
			mode,
			&exinfo,
			&sound->sound
		);

		if (result != FMOD_OK) {
			UtilityFunctions::push_error("Memory sound failed: ", FMOD_ErrorString(result));
			sound->data.clear();
			return Ref<FmodSound>();
		}
		
		return sound;
	}

	Ref<FmodSound> FmodServer::create_sound_from_res(const String p_path, unsigned int mode) {
		// 打开文件
		Ref<FileAccess> file = FileAccess::open(p_path, FileAccess::READ);
		ERR_FAIL_COND_V(file.is_null(), Ref<FmodSound>());

		// 读取文件数据到内存
		PackedByteArray data = file->get_buffer(file->get_length());
		ERR_FAIL_COND_V(data.is_empty(), Ref<FmodSound>());

		// 用内存模式创建 FMOD Sound
		String extension = p_path.get_extension();
		return create_sound_from_memory(data, mode);
	}

	Ref<FmodChannelGroup> FmodServer::create_channel_group(const String& p_name) {
		Ref<FmodChannelGroup> channel_group;
		channel_group.instantiate();

		FMOD_CHECK(fmod_system->createChannelGroup(p_name.utf8().get_data(), &channel_group->channel_group));
		return channel_group;
	}

	Ref<FmodChannel> FmodServer::play_sound(Ref<FmodSound> sound, Ref<FmodChannelGroup> channel_group, bool paused) {
		ERR_FAIL_COND_V(!fmod_system, Ref<FmodChannel>());
		ERR_FAIL_COND_V(sound.is_null() || !sound->sound, Ref<FmodChannel>());

		// 确定 channel group
		FMOD::ChannelGroup* fmod_cg = master_channel_group->channel_group;
		if (channel_group.is_valid() && channel_group->channel_group) {
			fmod_cg = channel_group->channel_group;
		}
		ERR_FAIL_COND_V(!fmod_cg, Ref<FmodChannel>());

		// 创建 channel（不 instantiate，等 playSound 成功后再创建）
		FMOD::Channel* fmod_channel = nullptr;

		FMOD_RESULT result = fmod_system->playSound(sound->sound, fmod_cg, paused, &fmod_channel);

		// 关键：检查 result，不是用 FMOD_CHECK 宏！
		if (result != FMOD_OK) {
			UtilityFunctions::push_error("playSound failed: ", FMOD_ErrorString(result));
			return Ref<FmodChannel>();
		}

		// 关键：检查 fmod_channel 是否被填充
		if (!fmod_channel) {
			UtilityFunctions::push_error("playSound returned null channel");
			return Ref<FmodChannel>();
		}

		// 现在创建 Godot 包装对象
		Ref<FmodChannel> channel;
		channel.instantiate();
		channel->channel = fmod_channel;  // 赋值！

		return channel;
	}

	Ref<FmodChannel> FmodServer::play_sound_use_master_channel_group(Ref<FmodSound> sound, bool paused) {
		return play_sound(sound, master_channel_group, paused);
	}
}
