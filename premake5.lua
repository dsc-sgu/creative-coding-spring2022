newoption {
    trigger = "arch",
    value = "arch",
    description = "Set the architecture of the binary to be built.",
    allowed = {
        { "arm64", "Build for arm64" },
        { "amd64", "Build for amd64" },
    },
    default = "amd64",
}

workspace "creative-coding"
    configurations { "Debug", "Release" }

    kind "ConsoleApp"

    includedirs { "include/" }
    links { "raylib" }

    filter "system:linux"
    	architecture "x64"
        libdirs { "lib/linux-amd64" }
        links { "m", "dl", "pthread" }

    filter "system:windows"
    	architecture "x64"
        libdirs { "lib/windows-amd64" }
        defines { "_WIN32" }
        links { "winmm", "kernel32", "opengl32", "gdi32" }

    filter { "system:macosx", "options:arch=arm64" }
        libdirs { "lib/macos-arm64" }
    filter { "system:macosx", "options:arch=amd64" }
        libdirs { "lib/macos-amd64" }
    filter "system:macosx"
        links {
            "m", "CoreVideo.framework", "CoreAudio.framework",
            "IOKit.framework", "Cocoa.framework", "OpenGL.framework"
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "example-project"
    language "C++"
    cppdialect "C++17"
    location "src/%{prj.name}"
    files { "src/%{prj.name}/**.h", "src/%{prj.name}/**.hpp", "src/%{prj.name}/**.cpp" }

project "sierpinski-triangle"
    language "C++"
    cppdialect "C++17"
    location "src/%{prj.name}"
    files { "src/%{prj.name}/**.h", "src/%{prj.name}/**.hpp", "src/%{prj.name}/**.cpp" }

project "game-of-life"
    language "C++"
    cppdialect "C++17"
    location "src/%{prj.name}"
    files { "src/%{prj.name}/**.h", "src/%{prj.name}/**.hpp", "src/%{prj.name}/**.cpp" }

project "times-table"
    language "C++"
    cppdialect "C++17"
    location "src/%{prj.name}"
    files { "src/%{prj.name}/**.h", "src/%{prj.name}/**.hpp", "src/%{prj.name}/**.cpp" }

project "mandelbrot-set"
    language "C++"
    cppdialect "C++17"
    location "src/%{prj.name}"
    files { "src/%{prj.name}/**.h", "src/%{prj.name}/**.hpp", "src/%{prj.name}/**.cpp" }

project "l-systems"
    language "C++"
    cppdialect "C++17"
    location "src/%{prj.name}"
    files { "src/%{prj.name}/**.h", "src/%{prj.name}/**.hpp", "src/%{prj.name}/**.cpp" }

project "raycasting"
    language "C++"
    cppdialect "C++17"
    location "src/%{prj.name}"
    files { "src/%{prj.name}/**.h", "src/%{prj.name}/**.hpp", "src/%{prj.name}/**.cpp" }

project "raycasting-mapeditor"
    language "C++"
    cppdialect "C++17"
    location "src/%{prj.name}"
    files { "src/%{prj.name}/**.h", "src/%{prj.name}/**.hpp", "src/%{prj.name}/**.cpp" }