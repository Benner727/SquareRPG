workspace "SquareRPG"
	architecture "x86"
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

	includedirs
	{
		"C:/dev/SDL2_image-2.0.4/include",
		"C:/dev/SDL2_mixer-2.0.4/include",
		"C:/dev/SDL2_ttf-2.0.14/include",
		"C:/dev/SDL2-2.0.9/include"
	}
	
	links
	{
		"SDL2.lib",
		"SDL2main.lib",
		"SDL2_image.lib",
		"SDL2_ttf.lib",
		"SDL2_mixer.lib"
	}
	
	libdirs
	{
		"C:/dev/SDL2_image-2.0.4/lib/x86",
		"C:/dev/SDL2_mixer-2.0.4/lib/x86",
		"C:/dev/SDL2_ttf-2.0.14/lib/x86",
		"C:/dev/SDL2-2.0.9/lib/x86"
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
		defines "SQ_DEBUG"
		symbols "On"


	filter "configurations:Release"
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

	links
	{
		"Square"
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
		defines "SQ_DEBUG"
		symbols "On"


	filter "configurations:Release"
		defines "SQ_RELEASE"
		optimize "On"