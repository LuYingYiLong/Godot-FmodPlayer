#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

env.Append(CCFLAGS=["/utf-8"])
env.Append(CXXFLAGS=["/utf-8"])
env.Append(CCFLAGS=["/wd4828"])
# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/", "src/thirdparty/fmod/inc"])
sources = Glob("src/*.cpp")
# if env["target"] in ["editor", "template_debug"]:
#     try:
#         doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
#         sources.append(doc_data)
#     except AttributeError:
#         print("Not including class reference as we're targeting a pre-4.3 baseline.")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "demo/bin/fmod_player.{}.{}.framework/fmod_player.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
elif env["platform"] == "ios":
    if env["ios_simulator"]:
        library = env.StaticLibrary(
            "demo/bin/fmod_player.{}.{}.simulator.a".format(env["platform"], env["target"]),
            source=sources,
        )
    else:
        library = env.StaticLibrary(
            "demo/bin/fmod_player.{}.{}.a".format(env["platform"], env["target"]),
            source=sources,
        )
else:
    env.Append(CXXFLAGS=['/utf-8'])
    env.Append(LIBPATH=["src/thirdparty/fmod/lib/x64"])
    env.Append(LIBS=["fmod_vc"])
    library = env.SharedLibrary(
        "demo/bin/fmod_player{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
