workspace "SquareRPG"
	architecture "x86_64"
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
		"%{prj.name}/src"
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
		runtime "Release"
		symbols "On"
		buildoptions "/MDd"


	filter "configurations:Release"
		links { "SDL2main.lib" }
		defines "SQ_RELEASE"
		runtime "Release"
		optimize "On"
		buildoptions "/MD"

project "Sandbox"
	location "Sandbox"
	language "c++"
	kind "ConsoleApp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Square/src",
		"Sandbox/src"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"SQ_PLATFORM_WINDOWS"
		}
		
	postbuildcommands 
	{
		("{COPY} %{prj.location}/Assets %{cfg.targetdir}/Assets")
	}

	filter "configurations:Debug"
		defines "SQ_DEBUG"
		runtime "Debug"
		symbols "On"
		buildoptions "/MDd"	
		
		links 
		{ 
			"Square",
			"SDL2maind.lib"
		}

	filter "configurations:Release"
		defines "SQ_RELEASE"
		runtime "Release"
		optimize "On"
		buildoptions "/MD"	
		
		links 
		{ 
			"Square",
			"SDL2main.lib"
		}