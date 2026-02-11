#include "fmod_channel.h"
#include "fmod_channel_group.h"
#include "fmod_server.h"
#include "fmod_sound.h"
#include <godot_cpp/classes/project_settings.hpp>
#include <string>

namespace godot {
	FmodServer* FmodServer::singleton = nullptr;
	Ref<FmodSystem> FmodServer::main_system;

	void FmodServer::_bind_methods() {
		ClassDB::bind_static_method("FmodServer", D_METHOD("get_singleton"), &FmodServer::get_singleton);
		ClassDB::bind_static_method("FmodServer", D_METHOD("get_main_system"), &FmodServer::get_main_system);
		ClassDB::bind_static_method("FmodServer", D_METHOD("get_master_channel_group"), &FmodServer::get_master_channel_group);
		
	}

	FmodServer::FmodServer() {
		ERR_FAIL_COND(singleton != nullptr);
		singleton = this;

		main_system.instantiate();
		if (main_system.is_null()) {
			UtilityFunctions::push_error("Failed to init main syst!");
			return;
		}
		UtilityFunctions::print("FMOD Completed.\nFMOD Version: ", main_system->get_version());

		// 注册自定义监视器
		Performance* perf = Performance::get_singleton();
		if (perf) {
			perf->add_custom_monitor("FMOD/DSP", callable_mp(this, &FmodServer::_get_dsp));
			perf->add_custom_monitor("FMOD/Stream", callable_mp(this, &FmodServer::_get_stream));
			perf->add_custom_monitor("FMOD/Geometry", callable_mp(this, &FmodServer::_get_geometry));
			perf->add_custom_monitor("FMOD/Update", callable_mp(this, &FmodServer::_get_update));
			perf->add_custom_monitor("FMOD/Convolution1", callable_mp(this, &FmodServer::_get_convolution1));
			perf->add_custom_monitor("FMOD/Convolution2", callable_mp(this, &FmodServer::_get_convolution2));
		}
	}

	FmodServer::~FmodServer() {
		ERR_FAIL_COND(singleton != this);
		singleton = nullptr;

		// 注销自定义监视器
		Performance* perf = Performance::get_singleton();
		if (perf) {
			perf->remove_custom_monitor("FMOD/DSP");
			perf->remove_custom_monitor("FMOD/Stream");
			perf->remove_custom_monitor("FMOD/Geometry");
			perf->remove_custom_monitor("FMOD/Update");
			perf->remove_custom_monitor("FMOD/Convolution1");
			perf->remove_custom_monitor("FMOD/Convolution2");
		}
	}

	FmodServer* FmodServer::get_singleton() {
		return singleton;
	}

	bool FmodServer::_process(double p_delta) {
		main_system->update();
		return false;
	}

	Ref<FmodSystem> FmodServer::get_main_system() {
		return main_system;
	}

	Ref<FmodChannelGroup> FmodServer::get_master_channel_group() {
		return main_system->get_master_channel_group();
	}

	double FmodServer::_get_dsp() const {
		double dsp = main_system->get_cpu_usage().get("dsp", 0.0);
		return dsp;
	}

	double FmodServer::_get_stream() const {
		double stream = main_system->get_cpu_usage().get("stream", 0.0);
		return stream;
	}

	double FmodServer::_get_geometry() const {
		double geometry = main_system->get_cpu_usage().get("geometry", 0.0);
		return geometry;
	}

	double FmodServer::_get_update() const {
		double update = main_system->get_cpu_usage().get("update", 0.0);
		return update;
	}

	double FmodServer::_get_convolution1() const {
		double convolution1 = main_system->get_cpu_usage().get("convolution1", 0.0);
		return convolution1;
	}

	double FmodServer::_get_convolution2() const {
		double convolution2 = main_system->get_cpu_usage().get("convolution2", 0.0);
		return convolution2;
	}
}
