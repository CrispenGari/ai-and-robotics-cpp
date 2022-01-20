# CMakeList.txt : CMake project for CMakeProject2, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package(Torch REQUIRED)
# Add source to this project's executable.
add_executable (CMakeProject2 "CMakeProject2.cpp" "CMakeProject2.h")

target_link_libraries(CMakeProject2 "${TORCH_LIBRARIES}")

if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET CMakeProject2
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:CMakeProject2>)
endif (MSVC)

# TODO: Add tests and install targets if needed.
