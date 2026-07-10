#ifndef FMOD_AUDIO_BUS_LAYOUT_H
#define FMOD_AUDIO_BUS_LAYOUT_H

#include "mixer/fmod_audio_bus.h"
#include <godot_cpp/classes/audio_effect.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/vector.hpp>

namespace godot {
	class FmodAudioEffect;

	class FmodAudioBusLayout : public Resource {
		GDCLASS(FmodAudioBusLayout, Resource)

	private:
		struct AudioServerBusState {
			StringName name;
			StringName send;
			float volume_db = 0.0f;
			bool mute = false;
			bool solo = false;
			bool bypass = false;
			int effect_count = 0;
		};

		struct AudioEffectSlot {
			int bus_index = 0;
			int effect_index = 0;
			uint64_t instance_id = 0;
			bool enabled = false;
			Ref<AudioEffect> effect;
			Callable changed_callable;
		};

		HashMap<String, Ref<FmodAudioBus>> audio_buses_map;
		Vector<AudioServerBusState> audio_server_bus_states;
		Vector<AudioEffectSlot> audio_effect_slots;
		int next_audio_server_bus_index = 0;
		int next_audio_effect_slot_index = 0;
		bool audio_effects_dirty = false;

		void _clear_buses_except_master();
		Ref<FmodAudioBus> _ensure_master_bus();
		void _sync_bus_effects(Ref<FmodAudioBus> bus, int audio_server_bus_index);
		void _update_solo_mute();
		void _cache_audio_server_state();
		void _clear_audio_effect_observers();
		void _on_audio_effect_changed();
		bool _has_audio_server_bus_layout_changed(int p_bus_index) const;
		bool _has_audio_server_bus_state_changed(int p_bus_index) const;
		bool _has_audio_effect_instance_changed();

	protected:
		static void _bind_methods();

	public:
		// 总线管理
		void create_audio_bus(const String& name, Ref<FmodAudioBus> parent = Ref<FmodAudioBus>());
		Ref<FmodAudioBus> get_audio_bus(const String& name) const;
		bool has_audio_bus(const String& name) const;
		void remove_audio_bus(const String& name);

		void set_bus_volume(const String& name, const float volume_db);
		float get_bus_volume(const String& name) const;

		void set_bus_solo(const String& name, const bool solo);
		bool bus_is_solo(const String& name) const;

		void set_bus_mute(const String& name, const bool mute);
		bool bus_is_mute(const String& name) const;

		void set_bus_bypass(const String& name, const bool bypass);
		bool bus_is_bypass(const String& name) const;

		// 效果器管理
		void add_bus_effect(const String& bus_name, Ref<FmodAudioEffect> effect, const int index = 0);
		void remove_bus_effect(const String& bus_name, const int index);
		int get_bus_effect_count(const String& bus_name) const;
		Ref<FmodAudioEffect> get_bus_effect(const String& bus_name, const int index) const;

		// 与 Godot AudioServer 同步
		void sync_from_audio_server();
		bool sync_from_audio_server_if_changed();
		void sync_bus_state(const String& bus_name, int audio_server_bus_index) const;
		void clear();
	};
}

#endif // !FMOD_AUDIO_BUS_LAYOUT_H
