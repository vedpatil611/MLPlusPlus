workspace "MLPlusPlus"
	startproject "MLPlusPlus"

	architecture "x64"

	configurations {
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Dependencies/glfw"
include "Dependencies/GLAD"
include "Dependencies/ImGui"

IncludeDirs = {}
IncludeDirs["GLAD"] = "Dependencies/GLAD/include"
IncludeDirs["GLFW"] = "Dependencies/glfw/include"
IncludeDirs["GLM"] = "Dependencies/glm"
IncludeDirs["ImGui"] = "Dependencies/ImGui/src"
IncludeDirs["RapidCSV"] = "Dependencies/rapidcsv/src"

project "MLPlusPlus"
	location "MLPlusPlus"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

	includedirs {
		"%{prj.name}/src/",
		"%{IncludeDirs.GLAD}",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.GLM}",
		"%{IncludeDirs.ImGui}",
		"%{IncludeDirs.RapidCSV}"
	}

	links {
		"GLFW",
		"GLAD",
		"ImGui"
	}

	files { 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp",
	}

	filter "system:windows"
		defines {
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "system:linux"
		links {
			"dl",
			"pthread"
		}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "RELEASE" }
		optimize "On"
		buildoptions "/MD"
