#include "fmod_channel.h"

namespace godot {
	void FmodChannel::_bind_methods() {
		ClassDB::bind_method(D_METHOD("set_frequency", "frequency"), &FmodChannel::set_frequency);
		ClassDB::bind_method(D_METHOD("get_frequency"), &FmodChannel::get_frequency);
		ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "frequency"), "set_frequency", "get_frequency");

		ClassDB::bind_method(D_METHOD("set_priority", "priority"), &FmodChannel::set_priority);
		ClassDB::bind_method(D_METHOD("get_priority"), &FmodChannel::get_priority);
		ADD_PROPERTY(PropertyInfo(Variant::INT, "priority"), "set_priority", "get_priority");

		ClassDB::bind_method(D_METHOD("set_position", "position", "timeunit"), &FmodChannel::set_position, DEFVAL(FmodSystem::TIMEUNIT_MS));
		ClassDB::bind_method(D_METHOD("get_position", "timeunit"), &FmodChannel::get_position, DEFVAL(FmodSystem::TIMEUNIT_MS));
		ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "position"), "set_position", "get_position");

		ClassDB::bind_method(D_METHOD("set_channel_group", "channel_group"), &FmodChannel::set_channel_group);
		ClassDB::bind_method(D_METHOD("get_channel_group"), &FmodChannel::get_channel_group);
		ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "channel_group", PROPERTY_HINT_OBJECT_ID, "FmodChannelGroup"), "set_channel_group", "get_channel_group");

		ClassDB::bind_method(D_METHOD("set_loop_count", "loop_count"), &FmodChannel::set_loop_count);
		ClassDB::bind_method(D_METHOD("get_loop_count"), &FmodChannel::get_loop_count);
		ADD_PROPERTY(PropertyInfo(Variant::INT, "loop_count"), "set_loop_count", "get_loop_count");

		ClassDB::bind_method(D_METHOD("set_loop_points", "start", "end", "timeunit"), &FmodChannel::set_loop_points, DEFVAL(FmodSystem::TIMEUNIT_MS));
		ClassDB::bind_method(D_METHOD("get_loop_points"), &FmodChannel::get_loop_points);

		ClassDB::bind_method(D_METHOD("is_virtual"), &FmodChannel::is_virtual);
		ClassDB::bind_method(D_METHOD("get_current_sound"), &FmodChannel::get_current_sound);
		ClassDB::bind_method(D_METHOD("get_index"), &FmodChannel::get_index);

		ClassDB::bind_method(D_METHOD("is_playing"), &FmodChannel::is_playing);
		ClassDB::bind_method(D_METHOD("stop"), &FmodChannel::stop);

		ClassDB::bind_method(D_METHOD("set_paused", "paused"), &FmodChannel::set_paused);
		ClassDB::bind_method(D_METHOD("get_paused"), &FmodChannel::get_paused);
		ADD_PROPERTY(PropertyInfo(Variant::BOOL, "pasued"), "set_paused", "get_paused");

		ClassDB::bind_method(D_METHOD("set_mode", "mode"), &FmodChannel::set_mode);
		ClassDB::bind_method(D_METHOD("get_mode"), &FmodChannel::get_mode);

		ClassDB::bind_method(D_METHOD("set_pitch", "pitch"), &FmodChannel::set_pitch);
		ClassDB::bind_method(D_METHOD("get_pitch"), &FmodChannel::get_pitch);
		ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "pitch"), "set_pitch", "get_pitch");

		ClassDB::bind_method(D_METHOD("get_audibility"), &FmodChannel::get_audibility);

		ClassDB::bind_method(D_METHOD("set_volume_db", "volume"), &FmodChannel::set_volume_db);
		ClassDB::bind_method(D_METHOD("get_volume_db"), &FmodChannel::get_volume_db);
		ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "volume_db", PROPERTY_HINT_RANGE, "-80,24,0.1,suffix:dB"), "set_volume_db", "get_volume_db");

		ClassDB::bind_method(D_METHOD("set_volume_ramp", "volume_ramp"), &FmodChannel::set_volume_ramp);
		ClassDB::bind_method(D_METHOD("get_volume_ramp"), &FmodChannel::get_volume_ramp);
		ADD_PROPERTY(PropertyInfo(Variant::BOOL, "volume_ramp"), "set_volume_ramp", "get_volume_ramp");

		ClassDB::bind_method(D_METHOD("set_mute", "mute"), &FmodChannel::set_mute);
		ClassDB::bind_method(D_METHOD("get_mute"), &FmodChannel::get_mute);
		ADD_PROPERTY(PropertyInfo(Variant::BOOL, "mute"), "set_mute", "get_mute");

		ClassDB::bind_method(D_METHOD("set_callback"), &FmodChannel::set_callback);
		ClassDB::bind_method(D_METHOD("clear_callback"), &FmodChannel::clear_callback);

		ADD_SIGNAL(MethodInfo("ended"));
	}

	FmodChannel::FmodChannel() {
	
	}

	FmodChannel::~FmodChannel() {
		if (channel) {
			channel->setCallback(nullptr);
			channel->setUserData(nullptr);
			channel->stop();
			channel = nullptr;
		}
		if (internal_channel_group) {
			memdelete(internal_channel_group);
			internal_channel_group = nullptr;
		}
	}

	void FmodChannel::setup(FMOD::Channel* p_channel) {
		channel = p_channel;

		// 设置用户数据
		FMOD_RESULT result = channel->setUserData(this);
		if (result != FMOD_OK) {
			UtilityFunctions::push_error("Failed to set user data: ", FMOD_ErrorString(result));
		}

		// 设置回调
		result = channel->setCallback(fmod_channel_control_callback);
		if (result != FMOD_OK) {
			UtilityFunctions::push_error("Failed to set callback: ", FMOD_ErrorString(result));
		}
	}

	void FmodChannel::set_frequency(const double frequency) {
		ERR_FAIL_COND(!channel);
		FMOD_ERR_CHECK(channel->setFrequency((float)frequency));
	}

	double FmodChannel::get_frequency() const {
		ERR_FAIL_COND_V(!channel, 0.0);
		float frequency = 0.0;
		FMOD_ERR_CHECK(channel->getFrequency(&frequency));
		return (double)frequency;
	}

	void FmodChannel::set_priority(const int64_t priority) {
		ERR_FAIL_COND(!channel);
		FMOD_ERR_CHECK(channel->setPriority((int)priority));
	}

	int64_t FmodChannel::get_priority() const {
		ERR_FAIL_COND_V(!channel, 0);
		int priority = 0;
		FMOD_ERR_CHECK(channel->getPriority(&priority));
		return (int64_t)priority;
	}

	void FmodChannel::set_position(int position, FmodSystem::FmodTimeunit timeunit) {
		ERR_FAIL_COND(!channel);
		FMOD_ERR_CHECK(channel->setPosition(position, timeunit));
	}

	int FmodChannel::get_position(FmodSystem::FmodTimeunit timeunit) const {
		ERR_FAIL_COND_V(!channel, 0.0);
		unsigned int position = 0;
		FMOD_ERR_CHECK(channel->getPosition(&position, timeunit));
		return position;
	}

	void FmodChannel::set_channel_group(FmodChannelGroup* p_channel_group) {
		ERR_FAIL_COND(!channel);
		internal_channel_group = p_channel_group;
		FMOD_ERR_CHECK(channel->setChannelGroup(internal_channel_group->channel_group));
	}

	FmodChannelGroup* FmodChannel::get_channel_group() const {
		ERR_FAIL_COND_V(!channel, nullptr);
		return internal_channel_group;
	}

	void FmodChannel::set_loop_count(const int64_t loop_count) {
		ERR_FAIL_COND(!channel);
		FMOD_ERR_CHECK(channel->setLoopCount((int)loop_count));
	}

	int64_t FmodChannel::get_loop_count() const {
		ERR_FAIL_COND_V(!channel, 0);
		int loop_count = 0;
		FMOD_ERR_CHECK(channel->getLoopCount(&loop_count));
		return (int64_t)loop_count;
	}

	void FmodChannel::set_loop_points(const int64_t start, const int64_t end, FmodSystem::FmodTimeunit timeunit) {
		ERR_FAIL_COND(!channel);
		FMOD_TIMEUNIT fmod_timeunit = static_cast<FMOD_TIMEUNIT>((int)timeunit);
		FMOD_ERR_CHECK(channel->setLoopPoints((unsigned int)start, fmod_timeunit, (unsigned int)end, fmod_timeunit));
	}

	Dictionary FmodChannel::get_loop_points(FmodSystem::FmodTimeunit timeunit) const {
		ERR_FAIL_COND_V(!channel, Dictionary());
		FMOD_TIMEUNIT fmod_timeunit = static_cast<FMOD_TIMEUNIT>((int)timeunit);
		unsigned int start, end;
		FMOD_ERR_CHECK(channel->getLoopPoints(&start, fmod_timeunit, &end, fmod_timeunit));
		Dictionary result;
		result["start"] = start;
		result["end"] = end;
		return result;
	}

	bool FmodChannel::is_virtual() const {
		ERR_FAIL_COND_V(!channel, false);
		bool isvirtual = false;
		FMOD_ERR_CHECK(channel->isVirtual(&isvirtual));
		return isvirtual;
	}

	FmodSound* FmodChannel::get_current_sound() const {
		ERR_FAIL_COND_V(!channel, nullptr);
		FmodSound* sound = memnew(FmodSound);
		FMOD_ERR_CHECK(channel->getCurrentSound(&sound->sound));
		return sound;
	}

	int64_t FmodChannel::get_index() const {
		ERR_FAIL_COND_V(!channel, -1);
		int index = -1;
		FMOD_ERR_CHECK(channel->getIndex(&index));
		return index;
	}

	bool FmodChannel::is_playing() const {
		ERR_FAIL_COND_V(!channel, false);
		bool isplaying = false;
		FMOD_ERR_CHECK(channel->isPlaying(&isplaying));
		return isplaying;
	}

	void FmodChannel::stop() {
		ERR_FAIL_COND(!channel);
		FMOD_ERR_CHECK(channel->stop());
	}

	void FmodChannel::set_paused(bool paused) {
		ERR_FAIL_COND(!channel);
		FMOD_ERR_CHECK(channel->setPaused(paused));
	}

	bool FmodChannel::get_paused() const {
		ERR_FAIL_COND_V(!channel, true);
		bool paused = true;
		FMOD_ERR_CHECK(channel->getPaused(&paused));
		return paused;
	}

	void FmodChannel::set_mode(FmodSystem::FmodMode mode) {
		ERR_FAIL_COND(!channel);
		FMOD_MODE fmod_mode = static_cast<FMOD_MODE>((int)mode);
		FMOD_ERR_CHECK(channel->setMode(fmod_mode));
	}

	FmodSystem::FmodMode FmodChannel::get_mode() const {
		ERR_FAIL_COND_V(!channel, FmodSystem::MODE_DEFAULT);
		FMOD_MODE fmod_mode;
		FMOD_ERR_CHECK(channel->getMode(&fmod_mode));
		FmodSystem::FmodMode mode = static_cast<FmodSystem::FmodMode>((int)fmod_mode);
		return mode;
	}

	void FmodChannel::set_pitch(double pitch) {
		ERR_FAIL_COND(!channel);
		FMOD_ERR_CHECK(channel->setPitch((double)pitch));
	}

	double FmodChannel::get_pitch() const {
		ERR_FAIL_COND_V(!channel, 0.0);
		float pitch;
		FMOD_ERR_CHECK(channel->getPitch(&pitch));
		return (double)pitch;
	}
	
	double FmodChannel::get_audibility() const {
		ERR_FAIL_COND_V(!channel, 0.0);
		float audibility = 0.0;
		FMOD_ERR_CHECK(channel->getAudibility(&audibility));
		return audibility;
	}

	void FmodChannel::set_volume_db(double volume) {
		ERR_FAIL_COND(!channel);
		FMOD_ERR_CHECK(channel->setVolume(FmodUtils::dbfs_to_sample(volume)));
	}

	double FmodChannel::get_volume_db() const {
		ERR_FAIL_COND_V(!channel, 0.0);
		float volume;
		FMOD_ERR_CHECK(channel->getVolume(&volume));
		return FmodUtils::sample_to_dbfs(volume);
	}

	void FmodChannel::set_volume_ramp(const bool ramp) {
		ERR_FAIL_COND(!channel);
		FMOD_ERR_CHECK(channel->setVolumeRamp(ramp));
	}

	bool FmodChannel::get_volume_ramp() const {
		ERR_FAIL_COND_V(!channel, false);
		bool ramp = false;
		FMOD_ERR_CHECK(channel->getVolumeRamp(&ramp));
		return ramp;
	}

	void FmodChannel::set_mute(const bool mute) {
		ERR_FAIL_COND(!channel);
		FMOD_ERR_CHECK(channel->setMute(mute));
	}

	bool FmodChannel::get_mute() const {
		ERR_FAIL_COND_V(!channel, false);
		bool mute = false;
		FMOD_ERR_CHECK(channel->getMute(&mute));
		return mute;
	}

	// 设置回调
	void FmodChannel::set_callback() {
		ERR_FAIL_COND_MSG(!channel, "Channel is null");

		// 设置用户数据为 this，这样回调函数可以访问这个 Godot 对象
		FMOD_RESULT result = channel->setUserData(this);
		if (result != FMOD_OK) {
			UtilityFunctions::push_error("Failed to set user data: ", FMOD_ErrorString(result));
			return;
		}

		// 设置回调函数
		result = channel->setCallback(fmod_channel_control_callback);
		if (result != FMOD_OK) {
			UtilityFunctions::push_error("Failed to set callback: ", FMOD_ErrorString(result));
			return;
		}
	}

	// 清除回调
	void FmodChannel::clear_callback() {
		if (channel) {
			channel->setCallback(nullptr);
			channel->setUserData(nullptr);
			UtilityFunctions::print("Callback cleared");
		}
	}
}

// 回调函数实现
FMOD_RESULT F_CALL fmod_channel_control_callback(
	FMOD_CHANNELCONTROL* channelcontrol,
	FMOD_CHANNELCONTROL_TYPE controltype,
	FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype,
	void* commanddata1,
	void* commanddata2
) {
	// 获取用户数据
	void* userdata = nullptr;
	FMOD_RESULT result;

	if (controltype == FMOD_CHANNELCONTROL_CHANNEL) {
		result = ((FMOD::Channel*)channelcontrol)->getUserData(&userdata);
	}
	else {
		result = ((FMOD::ChannelGroup*)channelcontrol)->getUserData(&userdata);
	}

	if (result != FMOD_OK || !userdata) {
		return FMOD_OK;
	}
	// 转换为 FmodChannel 对象
	godot::FmodChannel* channel = static_cast<godot::FmodChannel*>(userdata);

	// 在这里处理所有回调类型
	switch (callbacktype) {
	case FMOD_CHANNELCONTROL_CALLBACK_END:
		channel->emit_signal("ended");
		break;
	}
	return FMOD_OK;
}
