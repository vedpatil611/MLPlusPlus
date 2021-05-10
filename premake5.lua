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
IncludeDirs["ImGui"] = "Dependencies/ImGui/src/ImGui"
IncludeDirs["ImFileBrowser"] = "Dependencies/imgui-filebrowser"
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
		"%{prj.name}/src/vendors",
		"%{IncludeDirs.GLAD}",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.GLM}",
		"%{IncludeDirs.ImGui}",
		"%{IncludeDirs.ImFileBrowser}",
		"%{IncludeDirs.ImGuiNodeEditor}",
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
		"%{prj.name}/src/Algorithms/**.h",
		"%{prj.name}/src/Algorithms/**.cpp",
		"%{prj.name}/src/Plotter/**.h",
		"%{prj.name}/src/Plotter/**.cpp",
		"%{prj.name}/src/UI/**.h",
		"%{prj.name}/src/UI/**.cpp",
		"%{prj.name}/src/Utils/**.h",
		"%{prj.name}/src/Utils/**.cpp",
		"%{prj.name}/src/vendors/imnodes/**.h",
		"%{prj.name}/src/vendors/imnodes/**.cpp",
		"%{prj.name}/Shaders/**.glsl",
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
