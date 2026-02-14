#ifndef FMOD_CHANNEL_H
#define FMOD_CHANNEL_H

#include "fmod_system.h"
#include "fmod_channel_group.h"
#include "fmod_sound.h"
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace godot {
	class FmodChannel : public Object {
		GDCLASS(FmodChannel, Object)

	private:
		FmodChannelGroup* internal_channel_group = nullptr;

	protected:
		static void _bind_methods();

	public:
		FmodChannel();
		~FmodChannel();

		FMOD::Channel* channel = nullptr;

		void setup(FMOD::Channel* p_channel);

		void set_frequency(const double frequency);					// 设置播放频率或播放频率，作为 FMOD_CREATESAMPLE 开启的声音 (非FMOD_CREATESTREAM或FMOD_CREATECOMPRESSEDSAMPLE) 可以通过给出负频率来倒放播放
		double get_frequency() const;								// 获取播放频率或播放速率

		void set_priority(const int64_t priority);					// 设置虚拟语音排序的优先级
		int64_t get_priority() const;								// 获取用于虚拟语音排序的优先级
		
		void set_position(int position, FmodSystem::FmodTimeunit timeunit = FmodSystem::TIMEUNIT_MS);								// 设置当前播放位置
		int get_position(FmodSystem::FmodTimeunit timeunit = FmodSystem::TIMEUNIT_MS) const;										// 获取当前播放位置
		
		void set_channel_group(FmodChannelGroup* p_channel_group);	// 设置该对象输出的 ChannelGroup
		FmodChannelGroup* get_channel_group() const;				// 获取该对象输出的 ChannelGroup

		void set_loop_count(const int64_t loop_count);				// 设置循环次数后停止，0 代表“一次性播放”，1 代表“循环一次然后停止”，-1 代表“循环永远”
		int64_t get_loop_count() const;								// 读取停止前要循环的次数

		void set_loop_points(const int64_t start, const int64_t end, FmodSystem::FmodTimeunit timeunit = FmodSystem::TIMEUNIT_MS);	// 设置循环的起点和终点
		Dictionary get_loop_points(FmodSystem::FmodTimeunit timeunit = FmodSystem::TIMEUNIT_MS) const;								// 获取循环的起点和终点

		bool is_virtual() const;									// 检索虚拟语音系统是否正在模拟频道
		FmodSound* get_current_sound() const;						// 获取当前播放的声音
		int64_t get_index() const;									// 检索该对象在系统通道池中的索引

		bool is_playing() const;									// 检索播放状态
		void stop();												// 停止该频道 (或嵌套 ChannelGroups 中的所有频道) 的播放

		void set_paused(const bool paused);							// 设置暂停状态
		bool get_paused() const;									// 获取暂停状态

		void set_mode(FmodSystem::FmodMode mode);					// 设置播放模式，控制该对象的行为
		FmodSystem::FmodMode get_mode() const;						// 获取控制该对象行为的播放模式

		void set_pitch(const double pitch);							// 设置相对音高/播放速率
		double get_pitch() const;									// 获取相对音高/播放速率

		double get_audibility() const;								// 根据所有影响最终输出音量的衰减因子计算出可听度

		void set_volume_db(const double volume);					// 设置音量
		double get_volume_db() const;								// 获取音量
		
		void set_volume_ramp(const bool ramp);						// 设置音量变化是逐步增加还是瞬时变化
		bool get_volume_ramp() const;								// 检索音量变化是逐步减少还是瞬时变化

		void set_mute(const bool mute);								// 设置静音状态
		bool get_mute() const;										// 检索静音状态

		// 回调设置方法
		void set_callback();
		void clear_callback();
	};
}

extern "C" {
	FMOD_RESULT F_CALL fmod_channel_control_callback(
		FMOD_CHANNELCONTROL* channelcontrol,
		FMOD_CHANNELCONTROL_TYPE controltype,
		FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype,
		void* commanddata1,
		void* commanddata2
	);
}

#endif // !FMOD_CHANNEL_H
