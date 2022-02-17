
cmake_minimum_required (VERSION 3.8)

project ("01_BASIC_NEURAL_NETWORK")

find_package(Torch REQUIRED)
add_executable (01_BASIC_NEURAL_NETWORK "01_BASIC_NEURAL_NETWORK.cpp" "01_BASIC_NEURAL_NETWORK.h")

target_link_libraries(01_BASIC_NEURAL_NETWORK "${TORCH_LIBRARIES}")

if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET 01_BASIC_NEURAL_NETWORK
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:01_BASIC_NEURAL_NETWORK>)
endif (MSVC)