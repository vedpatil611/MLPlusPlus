cmake_minimum_required(VERSION 3.5)

file(GLOB source_files
	"${PROJECT_SOURCE_DIR}/Dependencies/ImGui/src/ImGui/*.cpp"
)

add_library(ImGui "${source_files}")
target_include_directories(ImGui PRIVATE src/ImGui)
set_property(TARGET ImGui PROPERTY POSITION_INDEPENDENT_CODE ON)

