include "Premake/CSExtensions.lua"

project "Coral.Managed"
    filter { "action:vs* or system:windows" }
        language "C#"
        dotnetframework "net8.0"
        kind "SharedLib"
        clr "Unsafe"
        targetdir("../bin")
        objdir("../bin")

        -- Don't specify architecture here

        files {
            "Coral.Managed/Source/**.cs"
        }
