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
IncludeDir["entt"] = "ChocoGL/vendor/entt/include"
IncludeDir["FastNoise"] = "ChocoGL/vendor/FastNoise"
IncludeDir["mono"] = "ChocoGL/vendor/mono/include"
IncludeDir["Box2D"] = "ChocoGL/vendor/Box2D/include"

LibraryDir = {}
LibraryDir["mono"] = "vendor/mono/lib/Debug/mono-2.0-sgen.lib"

group "Dependencies"

include "ChocoGL/vendor/GLFW"
include "ChocoGL/vendor/Glad"
include "ChocoGL/vendor/imgui"
include "ChocoGL/vendor/Box2D"

group ""

group "Core"
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
		"%{prj.name}/src/**.cpp" ,
		"%{prj.name}/src/**.cpp",

		"%{prj.name}/vendor/FastNoise/**.cpp",

		"%{prj.name}/vendor/yaml-cpp/src/**.cpp",
		"%{prj.name}/vendor/yaml-cpp/src/**.h",
		"%{prj.name}/vendor/yaml-cpp/include/**.h"
		
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
		"%{IncludeDir.Box2D}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.mono}",
		"%{IncludeDir.FastNoise}",
		"%{prj.name}/vendor/yaml-cpp/include"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"Box2D",
		"opengl32.lib",
		"%{LibraryDir.mono}"
	}
	filter "files:ChocoGL/vendor/FastNoise/**.cpp or files:ChocoGL/vendor/yaml-cpp/src/**.cpp"
   	flags { "NoPCH" }

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
		symbols "on"

	filter "configurations:Release"
		defines "CL_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "CL_DIST"
		optimize "on"

project "ChocoGL-ScriptCore"
	location "ChocoGL-ScriptCore"
	kind "SharedLib"
	language "C#"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.cs", 
	}

project "ExampleApp"
	location "ExampleApp"
	kind "SharedLib"
	language "C#"

	targetdir ("CoCo/assets/scripts")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.cs", 
	}

	links
	{
		"ChocoGL-ScriptCore"
	}
group ""

group "Tools"
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
		"ChocoGL/src",
		"ChocoGL/vendor",
		"%{IncludeDir.entt}",
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
		symbols "on"

		links
		{
			"ChocoGL/vendor/assimp/bin/Debug/assimp-vc141-mtd.lib"
		}
		postbuildcommands 
		{
			'{COPY} "../ChocoGL/vendor/assimp/bin/Debug/assimp-vc141-mtd.dll" "%{cfg.targetdir}"',
			'{COPY} "../ChocoGL/vendor/mono/bin/Debug/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
		}

	filter "configurations:Release"
		defines "CL_RELEASE"
		optimize "on"
		links
		{
			"ChocoGL/vendor/assimp/bin/Debug/assimp-vc141-mtd.lib"
		}
		postbuildcommands 
		{
			'{COPY} "../ChocoGL/vendor/assimp/bin/Debug/assimp-vc141-mtd.dll" "%{cfg.targetdir}"',
			'{COPY} "../ChocoGL/vendor/mono/bin/Debug/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
		}

	filter "configurations:Dist"
		defines "CL_DIST"
		optimize "on"
		
		links
		{	
			"ChocoGL/vendor/assimp/bin/Debug/assimp-vc141-mtd.lib"
		}
		postbuildcommands 
		{
			'{COPY} "../ChocoGL/vendor/assimp/bin/Debug/assimp-vc141-mtd.dll" "%{cfg.targetdir}"',
			'{COPY} "../ChocoGL/vendor/mono/bin/Debug/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
		}
group ""

project "ExampleApp"
	location "ExampleApp"
	kind "SharedLib"
	language "C#"

	targetdir ("CoCo/assets/scripts")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.cs", 
	}

	links
	{
		"ChocoGL-ScriptCore"
	}

project "ChocoGL-ScriptCore"
	location "ChocoGL-ScriptCore"
	kind "SharedLib"
	language "C#"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.cs", 
	}
	
--[[project "Sandbox"
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
]]
