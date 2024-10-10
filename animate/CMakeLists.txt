cmake_minimum_required(VERSION 3.16)
project(Ejemplos)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD 17)
set(BASE_FOLDER ./)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets Core Gui)
find_package(Qt${QT_VERSION_MAJOR}  COMPONENTS Widgets REQUIRED )
find_package(Qt${QT_VERSION_MAJOR}  COMPONENTS  Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS  Core REQUIRED)

include_directories(${BASE_FOLDER}/include)
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_library(graficos SHARED src/tablerografico.cpp 
include/tablerografico.h )
target_link_libraries(graficos PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core PRIVATE Qt${QT_VERSION_MAJOR}::Gui )



set (TARGET1 animate)
add_executable(${TARGET1} ./src/animate.cpp)
target_include_directories(${TARGET1} PRIVATE ${BASE_FOLDER}/include)
target_link_libraries(${TARGET1} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core PRIVATE Qt${QT_VERSION_MAJOR}::Gui graficos)


include(GNUInstallDirs)
#install(TARGETS ${TARGET}
#    BUNDLE DESTINATION ./
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    
    
    
add_custom_target(mrproper 

            COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
            COMMAND ${CMAKE_COMMAND} -E remove_directory "CMakeFiles"
            COMMAND ${CMAKE_COMMAND} -E remove "CMakeCache.txt"
            COMMAND ${CMAKE_COMMAND} -E remove "CMakeDoxyfile.in"
            COMMAND ${CMAKE_COMMAND} -E remove "CMakeDoxygenDefaults.cmake"
            COMMAND ${CMAKE_COMMAND} -E remove "cmake_install.cmake"
            COMMAND ${CMAKE_COMMAND} -E remove_directory "doc_doxygen"
            COMMAND ${CMAKE_COMMAND} -E remove_directory "${TARGET1}_autogen"
            COMMAND ${CMAKE_COMMAND} -E remove_directory "${TARGET2}_autogen"
            COMMAND ${CMAKE_COMMAND} -E remove_directory "${TARGET3}_autogen"
            COMMAND ${CMAKE_COMMAND} -E remove_directory "${TARGET4}_autogen" 
            COMMAND ${CMAKE_COMMAND} -E remove_directory "graficos_autogen"
            COMMAND ${CMAKE_COMMAND} -E remove "libgraficos.so"                   
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}
)            


