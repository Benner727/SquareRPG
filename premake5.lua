workspace "SquareRPG"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Square"
	location "Square"
	kind "SharedLib"
	language "c++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines
	{
		"SQ_PLATFORM_WINDOWS",
		"SQ_BUILD_DLL"
	}
	
	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
	}

	filter "configurations:Debug"
		links { "SDL2maind.lib" }
		defines "SQ_DEBUG"
		symbols "On"


	filter "configurations:Release"
		links { "SDL2main.lib" }
		defines "SQ_RELEASE"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"	
	language "c++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Square/src"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines
	{
		"SQ_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		links { "Square", "SDL2maind.lib" }
		defines "SQ_DEBUG"
		symbols "On"


	filter "configurations:Release"
		links { "Square", "SDL2main.lib" }
		defines "SQ_RELEASE"
		optimize "On"