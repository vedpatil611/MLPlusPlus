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
		"%{IncludeDirs.ImGui}",
		"%{IncludeDirs.ImFileBrowser}",
		"%{IncludeDirs.ImGuiNodeEditor}",
		"%{IncludeDirs.RapidCSV}"
	}

    defines {
        "IMGUI_IMPL_OPENGL_LOADER_GLAD"
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
		"%{prj.name}/src/NodeEditor/**.h",
		"%{prj.name}/src/NodeEditor/**.cpp",
		"%{prj.name}/src/Plotter/**.h",
		"%{prj.name}/src/Plotter/**.cpp",
		"%{prj.name}/src/UI/**.h",
		"%{prj.name}/src/UI/**.cpp",
		"%{prj.name}/src/Utils/**.h",
		"%{prj.name}/src/Utils/**.cpp",
		"%{prj.name}/src/vendors/imnodes/**.h",
		"%{prj.name}/src/vendors/imnodes/**.cpp",
		"%{prj.name}/src/vendors/implot/**.h",
		"%{prj.name}/src/vendors/implot/**.cpp",
	}

	filter "system:windows"
		defines {
            "OS_WINDOWS",
			"_CRT_SECURE_NO_WARNINGS"
		}
		undefines {
			"_DEBUG"
		}

	filter "system:linux or unix"
		defines {
            "OS_LINUX",
        }
        links {
			"dl",
			"pthread"
		}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "RELEASE", "NDEBUG" }
		optimize "On"
