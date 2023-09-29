from glob import glob
from pathlib import Path

env = SConscript("godot-cpp/SConstruct")
env.Append(CPPDEFINES={"nnabla_static_lib": 1})

debug_or_release = "release" if env["target"] == "template_release" else "debug"

if env["platform"] == "windows":
    if debug_or_release == "release":
        folder_name ="Release"
    else:
        folder_name = "Debug"

    libraries = [
        "nnabla_cli",
        "nnabla_utils",
        "nnabla",
        "hdf5.lib",
        "hdf5_hl.lib",
        "archive.lib",
        "libprotobuf"
    ]

    env.Append(
        LIBPATH=[
            "thirdparty/nnabla/build.cmake/bin/{:s}".format(folder_name),
            "thirdparty/nnabla/third_party/inst_hdf5-hdf5-1_12_2/lib",
            "thirdparty/nnabla/third_party/inst_libarchive-3.7.2/lib",
            "thirdparty/nnabla/third_party/inst_protobuf-3.20.1/lib"
        ]
    )
    env.Append(LIBS=libraries)
else:
    env.Append(
        LIBPATH=[
            "thirdparty/nnabla/build.cmake/lib",
            "thirdparty/nnabla/third_party/hdf5-hdf5-1_12_2/build.cmake/bin",
            "thirdparty/nnabla/third_party/protobuf-3.19.6/build.cmake",
            "thirdparty/nnabla/third_party/zstd-1.5.5/build.cmake/lib",
        ]
    )

    env.Append(
        LIBS=[
            "nnabla_cli",
            "nnabla_utils",
            "hdf5_hl",
            "hdf5",
            "nnabla",
            "protobuf",
            "protoc",
            "zstd",
        ]
    )

env.Append(CPPPATH=["thirdparty/nnabla/include"])
env.Append(CPPPATH=["src/"])


sources = Glob("src/*.cpp")


(extension_path,) = glob("demo/addons/*/*.gdextension")

# Find the addon path (e.g. project/addons/example).
addon_path = Path(extension_path).parent

# Find the project name from the gdextension file (e.g. example).
project_name = Path(extension_path).stem

# TODO: Cache is disabled currently.
# scons_cache_path = os.environ.get("SCONS_CACHE")
# if scons_cache_path != None:
#     CacheDir(scons_cache_path)
#     print("Scons cache enabled... (path: '" + scons_cache_path + "')")

# Create the library target (e.g. libexample.linux.debug.x86_64.so).
debug_or_release = "release" if env["target"] == "template_release" else "debug"
if env["platform"] == "macos":
    library = env.SharedLibrary(
        "{0}/bin/lib{1}.{2}.{3}.framework/{1}.{2}.{3}".format(
            addon_path,
            project_name,
            env["platform"],
            debug_or_release,
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "{}/bin/lib{}.{}.{}.{}{}".format(
            addon_path,
            project_name,
            env["platform"],
            debug_or_release,
            env["arch"],
            env["SHLIBSUFFIX"],
        ),
        source=sources,
    )

Default(library)
