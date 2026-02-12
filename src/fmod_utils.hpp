#ifndef UTILS_TOOLKIT_H
#define UTILS_TOOLKIT_H

#include "fmod_system.h"
#include <fmod_errors.h>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#define FMOD_CHECK(result)									                    \
    do {													                    \
        FMOD_RESULT _r = (result);							                    \
        if (_r != FMOD_OK) {								                    \
            godot::UtilityFunctions::push_error(			                    \
                "FMOD Error at ", __FILE__, ":", __LINE__,                      \
                " - ", FMOD_ErrorString(_r)					                    \
            );												                    \
        }													                    \
    } while(0)

#define FMOD_CHECK_ERR(result) FmodSystem::_check_error(result)

#define FMOD_CALL_CHECK_V(fmod_call, retval)                                    \
    do {                                                                        \
        FMOD_RESULT _r = (fmod_call);                                           \
        if (_r != FMOD_OK) {                                                    \
            godot::UtilityFunctions::push_error(                                \
                "FMOD Error at ", __FUNCTION__, " ", __FILE__, ":", __LINE__,   \
                " - ", FMOD_ErrorString(_r)                                     \
            );                                                                  \
            return retval;                                                      \
        }                                                                       \
    } while(0)

namespace FmodUtils {
	template <typename T>
	static godot::Ref<T> load(const godot::String& p_path) {
		godot::ResourceLoader* loader = godot::ResourceLoader::get_singleton();
		if (loader == nullptr) return godot::Ref<T>();
		godot::Ref<Resource> res = loader->load(p_path);
		if (res.is_null()) return godot::Ref<T>();
		godot::Ref<T> result = godot::Object::cast_to<T>(res.ptr());
		return result;
	}
}

#endif // !UTILS_TOOLKIT_H
