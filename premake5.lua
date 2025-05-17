-- premake5.lua
workspace("flo")
    architecture("x64")
    configurations({
        "Debug",
        "Release",
        "Dist"
    })
    location("build")
    cppdialect("C++20")

project("flo")
    location("build/flo")
    kind("SharedLib")
    language("C++")

    targetdir("build/bin/%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}/%{prj.name}")
    files({
        "src/**.h",
        "src/**.cpp",
    })

    filter("configurations:Debug")
        defines({"FLO_DEBUG"})
        symbols("On")

    filter("configurations:Release")
        defines({"FLO_RELEASE"})
        optimize("On")

    filter("configurations:Dist")
        defines({"FLO_DIST"})
        optimize("On")

project("sandbox")
    location("build/sandbox")
    kind("ConsoleApp")
    language("C++")

    targetdir("build/bin/%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}/%{prj.name}")
    files({
        "sandbox/**.h",
        "sandbox/**.cpp",
    })
    includedirs({
        "src"
    })
    links({
        "flo"
    })

    filter("configurations:Debug")
        defines({"FLO_DEBUG"})
        symbols("On")

    filter("configurations:Release")
        defines({"FLO_RELEASE"})
        optimize("On")

    filter("configurations:Dist")
        defines({"FLO_DIST"})
        optimize("On")
