workspace "ChocoGL"
	architecture "x64"
	targetdir "build"
	

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "CoCo"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "ChocoGL/vendor/GLFW/include"
IncludeDir["Glad"] = "ChocoGL/vendor/Glad/include"
IncludeDir["ImGui"]= "ChocoGL/vendor/imgui"
IncludeDir["glm"]  = "ChocoGL/vendor/glm"

include "ChocoGL/vendor/GLFW"
include "ChocoGL/vendor/Glad"
include "ChocoGL/vendor/imgui"

project "ChocoGL"
	location "ChocoGL"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "clpch.h"
	pchsource "ChocoGL/src/clpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp" 
		
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/assimp/include",
		"%{prj.name}/vendor/stb/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"

		systemversion "latest"

		defines
		{
			"CL_PLATFORM_WINDOWS",
			"CL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		

	filter "configurations:Debug"
		defines "CL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CL_DIST"
		runtime "Release"
		optimize "on"

project "CoCo"
	location "CoCo"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	links
	{
		"ChocoGL"
	}
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp" 
	}

	includedirs
	{
		"%{prj.name}/src",
		"ChocoGL/vendor/spdlog/include",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/assimp/include",
		"%{prj.name}/vendor/stb/include",
		"ChocoGL/src",
		"ChocoGL/vendor",
		"%{IncludeDir.glm}"
	}

	postbuildcommands 
	{
		'{COPY} "../CoCo/assets" "%{cfg.targetdir}/assets"'
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"CL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CL_DEBUG"
		runtime "Debug"
		symbols "on"

		links
		{
			"ChocoGL/vendor/assimp/bin/Debug/assimp-vc141-mtd.lib"
		}
		postbuildcommands 
		{
			'{COPY} "../ChocoGL/vendor/assimp/bin/Debug/assimp-vc141-mtd.dll" "%{cfg.targetdir}"'
		}

	filter "configurations:Release"
		defines "CL_RELEASE"
		runtime "Release"
		optimize "on"
		links
		{
			"ChocoGL/vendor/assimp/bin/Debug/assimp-vc141-mtd.lib"
		}
		postbuildcommands 
		{
			'{COPY} "../ChocoGL/vendor/assimp/bin/Debug/assimp-vc141-mtd.dll" "%{cfg.targetdir}"'
		}

	filter "configurations:Dist"
		defines "CL_DIST"
		runtime "Release"
		optimize "on"
		
		links
		{	
			"ChocoGL/vendor/assimp/bin/Debug/assimp-vc141-mtd.lib"
		}
		postbuildcommands 
		{
			'{COPY} "../ChocoGL/vendor/assimp/bin/Debug/assimp-vc141-mtd.dll" "%{cfg.targetdir}"'
		}

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	links
	{
		"ChocoGL"
	}

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp" 
	}

	includedirs
	{
		"%{prj.name}/src",
		"ChocoGL/src",
		"ChocoGL/vendor",
		"%{IncludeDir.glm}"
	}


	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"CL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CL_DEBUG"
		runtime "Debug"
		symbols "on"

			links
		{
			"ChocoGL/vendor/assimp/bin/Debug/assimp-vc141-mtd.lib"
		}

	filter "configurations:Release"
		defines "CL_RELEASE"
		runtime "Release"
		optimize "on"
		links
		{
			"ChocoGL/vendor/assimp/bin/Debug/assimp-vc141-mtd.lib"
		}

	filter "configurations:Dist"
		defines "CL_DIST"
		runtime "Release"
		optimize "on"
		
		links
		{	
			"ChocoGL/vendor/assimp/bin/Debug/assimp-vc141-mtd.lib"
		}