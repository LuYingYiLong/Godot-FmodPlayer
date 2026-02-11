#ifndef FMOD_SERVER_H
#define FMOD_SERVER_H

#include <godot_cpp/classes/main_loop.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/performance.hpp>
#include "fmod_system.h"

namespace godot {
	class FmodServer : public MainLoop {
		GDCLASS(FmodServer, MainLoop)
		static FmodServer* singleton;

	private:
		double _get_dsp() const;
		double _get_stream() const;
		double _get_geometry() const;
		double _get_update() const;
		double _get_convolution1() const;
		double _get_convolution2() const;

	protected:
		static void _bind_methods();

	public:
		FmodServer();
		~FmodServer();

		static Ref<FmodSystem> main_system;

		static FmodServer* get_singleton();

		bool _process(double p_delta) override;

		static Ref<FmodSystem> get_main_system();
		static Ref<FmodChannelGroup> get_master_channel_group();
	};
}



#endif // !FMOD_SERVER_H
