include "Premake/CSExtensions.lua"

project "Coral.Managed"
    filter { "action:vs* or system:windows" }
        language "C#"
        dotnetframework "net8.0"
        kind "SharedLib"
        clr "Unsafe"
        targetdir("../bin/%{cfg.buildcfg}")
        objdir("../bin/%{cfg.buildcfg}/int")

        -- Don't specify architecture here

        files {
            "Source/**.cs"
        }
