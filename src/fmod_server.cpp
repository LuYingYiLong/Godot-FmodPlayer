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

		ClassDB::bind_static_method("FmodServer", D_METHOD("get_singleton"), &FmodServer::get_singleton);
		ClassDB::bind_static_method("FmodServer", D_METHOD("get_version"), &FmodServer::get_version);
		ClassDB::bind_static_method("FmodServer", D_METHOD("get_master_channel_group"), &FmodServer::get_master_channel_group);
		ClassDB::bind_static_method("FmodServer", D_METHOD("create_sound", "path"), &FmodServer::create_sound);
		ClassDB::bind_static_method("FmodServer", D_METHOD("create_channel_group", "name"), &FmodServer::create_channel_group);
		ClassDB::bind_static_method("FmodServer", D_METHOD("play_sound", "sound", "channel_group", "paused"), &FmodServer::play_sound);
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

	Ref<FmodSound> FmodServer::create_sound(const String& p_path) {
		// 1. 保留字符串对象，防止悬空指针
		CharString path_utf8 = ProjectSettings::get_singleton()->globalize_path(p_path).utf8();
		const char* path_cstr = path_utf8.get_data();

		// 2. 清零 exinfo
		FMOD_CREATESOUNDEXINFO exinfo = {};  // C++11 零初始化
		exinfo.cbsize = sizeof(exinfo);

		Ref<FmodSound> fmod_sound;
		fmod_sound.instantiate();

		// 3. 从文件创建，不需要 exinfo.length（那是内存加载用的）
		FMOD_RESULT err = fmod_system->createSound(
			path_cstr,
			FMOD_DEFAULT,
			nullptr,  // 文件加载不需要 exinfo
			&fmod_sound->sound
		);

		if (err != FMOD_OK) {
			UtilityFunctions::push_error("Failed to create sound: ", FMOD_ErrorString(err));
			return Ref<FmodSound>();
		}
		return fmod_sound;
	}

	Ref<FmodChannelGroup> FmodServer::create_channel_group(const String& p_name) {
		Ref<FmodChannelGroup> channel_group;
		channel_group.instantiate();

		FMOD_CHECK(fmod_system->createChannelGroup(p_name.utf8().get_data(), &channel_group->channel_group));
		return channel_group;
	}

	Ref<FmodChannel> FmodServer::play_sound(Ref<FmodSound> sound, Ref<FmodChannelGroup> channel_group, bool paused) {
	//	Ref<FmodChannel> channel;
	//	channel.instantiate();
	//	Ref<FmodChannelGroup> target_cg = channel_group;

	//	if (sound.is_null()) {
	//		UtilityFunctions::push_error("Sound is null");
	//		return Ref<FmodChannel>();
	//	}

	//	if (target_cg.is_null()) {
	//		target_cg = master_channel_group;
	//	}

	//	FMOD_CHECK(fmod_system->playSound(sound->sound, target_cg->channel_group, paused, &channel->channel));

	//	return channel;
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
}
