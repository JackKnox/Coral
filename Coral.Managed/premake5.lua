StrypeDirectory = os.getenv("STRYPE_DIR")

workspace "Coral.Managed"
	architecture "universal"
	startproject "Coral.Managed"

	configurations {
		"Debug",
		"Release"
	}

include "../Premake/CSExtensions.lua"

project "Coral.Managed"
    filter { "not action:vs*", "not system:windows" }
        kind "StaticLib"
    filter { "action:vs* or system:windows" }
        language "C#"
        dotnetframework "net8.0"
        kind "SharedLib"
        clr "Unsafe"
        dependson { "Coral.Generator" }

	    targetdir ("%{StrypeDirectory}/Strype/master/DotNet")
	    objdir ("%{StrypeDirectory}/Strype/master/DotNet/Intermediates")

        -- Don't specify architecture here. (see https://github.com/premake/premake-core/issues/1758)

        propertytags {
            { "AppendTargetFrameworkToOutputPath", "false" },
            { "Nullable", "enable" },
        }

        disablewarnings {
            "CS8500"
        }

        files {
            "Source/**.cs"
        }
