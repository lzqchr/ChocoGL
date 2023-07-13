workspace "ChocoGL"
	architecture"x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "ChocoGL/vendor/GLFW/include"
IncludeDir["Glad"] = "ChocoGL/vendor/Glad/include"

include "ChocoGL/vendor/GLFW"
include "ChocoGL/vendor/Glad"

project "ChocoGL"
	location "ChocoGL"
	kind"SharedLib"
	language"C++"

	
	targetdir("bin/"..outputdir.."/%{prj.name}")
	
	objdir("bin-int/"..outputdir.."/%{prj.name}")

	pchheader"clpch.h"
	pchsource"ChocoGL/src/clpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include;",
		"%{prj.name}/src;",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	
	links 
	{ 
		"GLFW",
		"Glad",
		"opengl32.lib"
	}


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion"latest"

	defines
	{
		"CL_PLATFORM_WINDOWS",
		"CL_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
	 }
	
	postbuildcommands
	{
		 ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		 
	}

	filter "configurations:Debug"
		defines"GL_Debug"
		buildoptions "/MDd"
		symbols"on"
	filter "configurations:Release"
		defines"GL_RELEASE"
		buildoptions "/MD"
		optimize"on"

	filter "configurations:Dist"
		defines"GL_DIST"
		buildoptions "/MD"
		optimize"on"

project "Sandbox"
	location "Sandbox"
	kind"ConsoleApp"
	language"C++"

	
	targetdir("bin/"..outputdir.."/%{prj.name}")

	objdir("bin-int/"..outputdir.."/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"ChocoGL/vendor/spdlog/include;",
		"ChocoGL/src"
	}

	links
	{
		"ChocoGL"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion"latest"

	defines
	{
		"CL_PLATFORM_WINDOWS"

	 }
	
	

	filter "configurations:Debug"
		defines"GL_Debug"
		buildoptions "/MDd"
		symbols"on"
	filter "configurations:Release"
		defines"GL_RELEASE"
		buildoptions "/MD"
		optimize"on"

	filter "configurations:Dist"
		defines"GL_DIST"
		buildoptions "/MD"
		optimize"on"

