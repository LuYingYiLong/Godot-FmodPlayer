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

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/", "src/thirdparty/fmod/inc"])
sources = Glob("src/*.cpp")

# if env["target"] in ["editor", "template_debug"]:
#     try:
#         doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
#         sources.append(doc_data)
#     except AttributeError:
#         print("Not including class reference as we're targeting a pre-4.3 baseline.")

# 如果在 Windows 上编译 Android，SCons 可能会错误地保留 MinGW 的链接库。
# 我们需要手动清洗 LIBS 列表。
if env["platform"] == "android":
    windows_libs_blacklist = [
        "mingw32", "gcc", "gcc_s", "moldname", "mingwex", "msvcrt", 
        "advapi32", "shell32", "user32", "kernel32", "stdc++"
    ]
    # 过滤掉黑名单中的库
    if "LIBS" in env:
        clean_libs = [lib for lib in env["LIBS"] if str(lib) not in windows_libs_blacklist]
        env.Replace(LIBS=clean_libs)

if env["platform"] == "android":
    env.Append(CXXFLAGS=['-std=c++17'])
    # 根据架构选择 Android 库路径
    arch = env["arch"]
    if arch == "arm64":
        fmod_lib_path = "src/thirdparty/fmod/lib/android/arm64-v8a"
    elif arch == "arm32":
        fmod_lib_path = "src/thirdparty/fmod/lib/android/armeabi-v7a"
    elif arch == "x86_64":
        fmod_lib_path = "src/thirdparty/fmod/lib/android/x86_64"
    else:
        fmod_lib_path = "src/thirdparty/fmod/lib/android/arm64-v8a"
    env.Append(LIBPATH=[fmod_lib_path])
    # Android 库名（SCons 会自动加 lib 前缀和 .so 后缀）
    if env["target"] == "template_release":
        env.Append(LIBS=["libfmod"])      # 链接 libfmod.so
    else:
        env.Append(LIBS=["libfmodL"])     # 链接 libfmodL.so (Debug)
    # 调试/发布配置
    if env["target"] == "template_release":
        env.Append(CXXFLAGS=['-O3'])
        env['LINKFLAGS'] = []
    else:  # template_debug 或 editor
        env.Append(CXXFLAGS=['-g', '-O0'])
        env['LINKFLAGS'] = ['-g']
    
    # Android 库输出路径
    library = env.SharedLibrary(
        "addons/bin/fmod_player{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )
elif env["platform"] == "macos":
    library = env.SharedLibrary(
        "addons/bin/fmod_player.{}.{}.framework/fmod_player.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
elif env["platform"] == "ios":
    if env["ios_simulator"]:
        library = env.StaticLibrary(
            "addons/bin/fmod_player.{}.{}.simulator.a".format(env["platform"], env["target"]),
            source=sources,
        )
    else:
        library = env.StaticLibrary(
            "addons/bin/fmod_player.{}.{}.a".format(env["platform"], env["target"]),
            source=sources,
        )
else:
    env.Append(CCFLAGS=["/utf-8"])
    env.Append(CXXFLAGS=["/utf-8"])
    env.Append(CCFLAGS=["/wd4828"])
    env.Append(LIBPATH=["src/thirdparty/fmod/lib/x64"])
    env.Append(LIBS=["fmod_vc"])
    library = env.SharedLibrary(
        "addons/bin/fmod_player{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
