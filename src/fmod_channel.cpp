#include "fmod_channel.h"

namespace godot {
	void FmodChannel::_bind_methods() {
		ClassDB::bind_method(D_METHOD("set_paused", "paused"), &FmodChannel::set_paused);
		ClassDB::bind_method(D_METHOD("get_paused"), &FmodChannel::get_paused);
		ClassDB::bind_method(D_METHOD("set_volume", "volume"), &FmodChannel::set_volume);
		ClassDB::bind_method(D_METHOD("get_volume"), &FmodChannel::get_volume);
		ClassDB::bind_method(D_METHOD("set_pitch", "pitch"), &FmodChannel::set_pitch);
		ClassDB::bind_method(D_METHOD("get_pitch"), &FmodChannel::get_pitch);
		ClassDB::bind_method(D_METHOD("set_position", "position", "timeunit"), &FmodChannel::set_position, DEFVAL(FmodSystem::TIMEUNIT_MS));
		ClassDB::bind_method(D_METHOD("get_position", "timeunit"), &FmodChannel::get_position, DEFVAL(FmodSystem::TIMEUNIT_MS));
		ClassDB::bind_method(D_METHOD("set_callback"), &FmodChannel::set_callback);
		ClassDB::bind_method(D_METHOD("clear_callback"), &FmodChannel::clear_callback);

		ADD_PROPERTY(PropertyInfo(Variant::BOOL, "pasued"), "set_paused", "get_paused");
		ADD_PROPERTY(PropertyInfo(Variant::BOOL, "volume"), "set_volume", "get_volume");
		ADD_PROPERTY(PropertyInfo(Variant::BOOL, "pitch"), "set_pitch", "get_pitch");

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
	}

	void FmodChannel::setup(FMOD::Channel* p_channel) {
		channel = p_channel;
		
		if (!get_paused()) {
			exref = reference();
			if (!exref) UtilityFunctions::push_error("Reference failed");
		}

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

	void FmodChannel::set_paused(bool paused) {
		FMOD_CHECK(channel->setPaused(paused));

		if (paused && exref) exref = false;
		else if (!paused && !exref) exref = true;
	}

	bool FmodChannel::get_paused() const {
		bool paused;
		FMOD_CHECK(channel->getPaused(&paused));
		return paused;
	}

	void FmodChannel::set_volume(float volume) {
		FMOD_CHECK(channel->setVolume(volume));
	}

	float FmodChannel::get_volume() const {
		float volume;
		FMOD_CHECK(channel->getVolume(&volume));
		return volume;
	}
	
	void FmodChannel::set_pitch(float pitch) {
		FMOD_CHECK(channel->setPitch(pitch));
	}

	float FmodChannel::get_pitch() const {
		float pitch;
		FMOD_CHECK(channel->getPitch(&pitch));
		return pitch;
	}
		
	void FmodChannel::set_position(int position, FmodSystem::Timeunit timeunit) {
		FMOD_CHECK(channel->setPosition(position, timeunit));
	}

	int FmodChannel::get_position(FmodSystem::Timeunit timeunit) const {
		unsigned int position;
		FMOD_CHECK(channel->getPosition(&position, timeunit));
		return position;
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
	godot::Ref<godot::FmodChannel> channel = static_cast<godot::FmodChannel*>(userdata);

	// 在这里处理所有回调类型
	switch (callbacktype) {
	case FMOD_CHANNELCONTROL_CALLBACK_END:
		channel->emit_signal("ended");
		if (channel->exref) {
			FMOD_MODE mode;
			channel->channel->getMode(&mode);
			if (mode == godot::FmodSystem::MODE_LOOP_NORMAL || mode == godot::FmodSystem::MODE_LOOP_BIDI)
			channel->unreference();
		}
		break;

		return FMOD_OK;
	}
}
