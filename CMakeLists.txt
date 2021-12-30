cmake_minimum_required(VERSION 3.5)

project(MLPlusPlus VERSION 0.1)

add_subdirectory(Dependencies/glad)
add_subdirectory(Dependencies/glfw)
add_subdirectory(Dependencies/ImGui)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(WIN32)
	target_compile_definitions(MLPlusPlus PUBLIC OS_WINDOWS)
endif(WIN32)

if(UNIX)
	target_compile_definitions(MLPlusPlus PUBLIC OS_LINUX)
endif(UNIX)

set(self_include_dir "${PROJECT_SOURCE_DIR}/MLPlusPlus/src")
set(glfw_include_dir "${PROJECT_SOURCE_DIR}/Dependencies/glfw/include")
set(glad_include_dir "${PROJECT_SOURCE_DIR}/Dependencies/glad/include")
set(imgui_include_dir "${PROJECT_SOURCE_DIR}/Dependencies/ImGui/src/ImGui")
set(imgui_filebrowser_include_dir "${PROJECT_SOURCE_DIR}/Dependencies/imgui-filebrowser")
set(rapidcsv_include_dir "${PROJECT_SOURCE_DIR}/Dependencies/rapidcsv/src")

file(GLOB source_files
  "${PROJECT_SOURCE_DIR}/MLPlusPlus/src/*.cpp"
  "${PROJECT_SOURCE_DIR}/MLPlusPlus/src/Algorithms/*.cpp"
  "${PROJECT_SOURCE_DIR}/MLPlusPlus/src/DataTypes/*.cpp"
  "${PROJECT_SOURCE_DIR}/MLPlusPlus/src/NodeEditor/*.cpp"
  "${PROJECT_SOURCE_DIR}/MLPlusPlus/src/Plotter/*.cpp"
  "${PROJECT_SOURCE_DIR}/MLPlusPlus/src/UI/*.cpp"
  "${PROJECT_SOURCE_DIR}/MLPlusPlus/src/Utils/*.cpp"
  "${PROJECT_SOURCE_DIR}/MLPlusPlus/src/vendors/imnodes/*.cpp"
  "${PROJECT_SOURCE_DIR}/MLPlusPlus/src/vendors/implot/*.cpp"
)

file(GLOB include_files 
  "${self_include_dir}"
  "${glad_include_dir}"
  "${glfw_include_dir}"
  "${imgui_include_dir}"
  "${imgui_filebrowser_include_dir}"
  "${rapidcsv_include_dir}"
)

add_executable(MLPlusPlus "${source_files}")
target_include_directories(MLPlusPlus PUBLIC "${include_files}")

target_link_directories(MLPlusPlus PRIVATE Dependencies/GLFW/src)
target_link_libraries(MLPlusPlus PRIVATE glfw dl glad pthread ImGui)

# install(TARGETS MLPlusPlus DESTINATION lib)
