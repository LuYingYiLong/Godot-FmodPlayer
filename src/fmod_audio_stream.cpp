#include "fmod_audio_stream.h"

namespace godot {
	void FmodAudioStream::_bind_methods() { }

	FmodAudioStream::FmodAudioStream() { }

	FmodAudioStream::~FmodAudioStream() { }

	void FmodAudioStream::set_file_path(const String& p_path) {
		file_path = p_path;
		sound = FmodServer::get_main_system()->create_sound_from_file(p_path, FmodSystem::MODE_CREATESTREAM | FmodSystem::MODE_LOOP_NORMAL);
	}
}