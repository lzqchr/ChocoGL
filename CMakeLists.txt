cmake_minimum_required(VERSION 3.20)

cmake_policy(SET CMP0091 NEW)

set(CHOCOGL_PHYSX_LIBS
    PhysX_static_64
    PhysXCharacterKinematic_static_64
    PhysXCommon_static_64
    PhysXCooking_static_64
    PhysXExtensions_static_64
    PhysXFoundation_static_64
    PhysXPvdSDK_static_64
)

set(CHOCOGL_HAS_RELEASE_PHYSX ON)
foreach(physx_lib IN LISTS CHOCOGL_PHYSX_LIBS)
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/PhysX/lib/Release/${physx_lib}.lib")
        set(CHOCOGL_HAS_RELEASE_PHYSX OFF)
    endif()
endforeach()

if(CHOCOGL_HAS_RELEASE_PHYSX)
    set(CMAKE_CONFIGURATION_TYPES Debug Release Dist CACHE STRING "" FORCE)
else()
    set(CMAKE_CONFIGURATION_TYPES Debug CACHE STRING "" FORCE)
endif()

project(ChocoGL LANGUAGES C CXX)

if(NOT WIN32)
    message(FATAL_ERROR "ChocoGL's current CMake build mirrors the original Premake Windows configuration.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

get_property(CHOCOGL_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(NOT CHOCOGL_HAS_RELEASE_PHYSX)
    message(STATUS "PhysX Release libraries were not found; CMake presets expose Debug builds only.")
    if(NOT CHOCOGL_MULTI_CONFIG AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(FATAL_ERROR "This checkout only contains Debug PhysX libraries. Configure Debug, or add matching Release PhysX libraries under ChocoGL/vendor/PhysX/lib/Release.")
    endif()
endif()

if(MSVC)
    set(CMAKE_C_FLAGS_DIST "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "Flags used by the C compiler during Dist builds." FORCE)
    set(CMAKE_CXX_FLAGS_DIST "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "Flags used by the CXX compiler during Dist builds." FORCE)
    set(CMAKE_EXE_LINKER_FLAGS_DIST "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" CACHE STRING "Flags used by the linker during Dist builds." FORCE)
    set(CMAKE_STATIC_LINKER_FLAGS_DIST "${CMAKE_STATIC_LINKER_FLAGS_RELEASE}" CACHE STRING "Flags used by the static linker during Dist builds." FORCE)
endif()

set(CHOCOGL_OUTPUT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CHOCOGL_INTERMEDIATE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/bin-int")
set(CHOCOGL_CONFIG_OUTPUT_DIR "${CHOCOGL_OUTPUT_ROOT}/$<CONFIG>-windows-x86_64")

option(CHOCOGL_BUILD_CSHARP "Build ChocoGL C# script assemblies through MSBuild/dotnet." ON)

function(chocogl_require_path path message_text)
    if(NOT EXISTS "${path}")
        message(FATAL_ERROR "${message_text}: ${path}")
    endif()
endfunction()

function(chocogl_set_output_dirs target_name)
    set_target_properties(${target_name} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CHOCOGL_CONFIG_OUTPUT_DIR}/${target_name}"
        LIBRARY_OUTPUT_DIRECTORY "${CHOCOGL_CONFIG_OUTPUT_DIR}/${target_name}"
        RUNTIME_OUTPUT_DIRECTORY "${CHOCOGL_CONFIG_OUTPUT_DIR}/${target_name}"
        PDB_OUTPUT_DIRECTORY "${CHOCOGL_CONFIG_OUTPUT_DIR}/${target_name}"
    )
endfunction()

function(chocogl_pick_config_file out_var debug_path release_path dist_path)
    set(_debug "${debug_path}")
    set(_release "${release_path}")
    set(_dist "${dist_path}")

    if(NOT EXISTS "${_debug}")
        message(FATAL_ERROR "Missing required Debug prebuilt file: ${_debug}")
    endif()

    if(NOT EXISTS "${_release}")
        set(_release "${_debug}")
    endif()

    if(NOT EXISTS "${_dist}")
        set(_dist "${_release}")
    endif()

    set(${out_var}
        "$<$<CONFIG:Debug>:${_debug}>$<$<CONFIG:Release>:${_release}>$<$<CONFIG:Dist>:${_dist}>$<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>,$<CONFIG:Dist>>>:${_release}>"
        PARENT_SCOPE
    )
endfunction()

chocogl_require_path("${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/GLFW/include/GLFW/glfw3.h" "GLFW submodule is missing. Run git submodule update --init --recursive")
chocogl_require_path("${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/Glad/include/glad/glad.h" "Glad vendor files are missing")
chocogl_require_path("${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/imgui/imgui.h" "ImGui submodule is missing. Run git submodule update --init --recursive")
chocogl_require_path("${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/Box2D/include/Box2D/Box2D.h" "Box2D submodule is missing. Run git submodule update --init --recursive")
chocogl_require_path("${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/glm/glm/glm.hpp" "glm submodule is missing. Run git submodule update --init --recursive")
chocogl_require_path("${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/FastNoise/FastNoise.cpp" "FastNoise submodule is missing. Run git submodule update --init --recursive")
chocogl_require_path("${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/spdlog/spdlog.h" "spdlog submodule is missing. Run git submodule update --init --recursive")
chocogl_require_path("${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/entt/include/entt/entt.hpp" "entt vendor files are missing")
chocogl_require_path("${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/yaml-cpp/include/yaml-cpp/yaml.h" "yaml-cpp vendor files are missing")
chocogl_require_path("${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/mono/include/mono/jit/jit.h" "mono vendor files are missing")
chocogl_require_path("${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/PhysX/include/PhysX/PxPhysicsAPI.h" "PhysX vendor files are missing")
chocogl_require_path("${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/assimp/include/assimp/Importer.hpp" "assimp vendor files are missing")

add_library(Glad STATIC
    ChocoGL/vendor/Glad/include/glad/glad.h
    ChocoGL/vendor/Glad/include/KHR/khrplatform.h
    ChocoGL/vendor/Glad/src/glad.c
)
target_include_directories(Glad PUBLIC ChocoGL/vendor/Glad/include)
chocogl_set_output_dirs(Glad)

add_library(GLFW STATIC
    ChocoGL/vendor/GLFW/include/GLFW/glfw3.h
    ChocoGL/vendor/GLFW/include/GLFW/glfw3native.h
    ChocoGL/vendor/GLFW/src/context.c
    ChocoGL/vendor/GLFW/src/init.c
    ChocoGL/vendor/GLFW/src/input.c
    ChocoGL/vendor/GLFW/src/monitor.c
    ChocoGL/vendor/GLFW/src/vulkan.c
    ChocoGL/vendor/GLFW/src/window.c
    ChocoGL/vendor/GLFW/src/win32_init.c
    ChocoGL/vendor/GLFW/src/win32_joystick.c
    ChocoGL/vendor/GLFW/src/win32_monitor.c
    ChocoGL/vendor/GLFW/src/win32_time.c
    ChocoGL/vendor/GLFW/src/win32_thread.c
    ChocoGL/vendor/GLFW/src/win32_window.c
    ChocoGL/vendor/GLFW/src/wgl_context.c
    ChocoGL/vendor/GLFW/src/egl_context.c
    ChocoGL/vendor/GLFW/src/osmesa_context.c
)
target_include_directories(GLFW PUBLIC ChocoGL/vendor/GLFW/include)
target_compile_definitions(GLFW PRIVATE _GLFW_WIN32 _CRT_SECURE_NO_WARNINGS)
chocogl_set_output_dirs(GLFW)

add_library(ImGui STATIC
    ChocoGL/vendor/imgui/imconfig.h
    ChocoGL/vendor/imgui/imgui.h
    ChocoGL/vendor/imgui/imgui.cpp
    ChocoGL/vendor/imgui/imgui_draw.cpp
    ChocoGL/vendor/imgui/imgui_internal.h
    ChocoGL/vendor/imgui/imgui_widgets.cpp
    ChocoGL/vendor/imgui/imstb_rectpack.h
    ChocoGL/vendor/imgui/imstb_textedit.h
    ChocoGL/vendor/imgui/imstb_truetype.h
    ChocoGL/vendor/imgui/imgui_demo.cpp
)
target_include_directories(ImGui PUBLIC ChocoGL/vendor/imgui)
target_compile_features(ImGui PUBLIC cxx_std_17)
chocogl_set_output_dirs(ImGui)

file(GLOB_RECURSE BOX2D_SOURCES CONFIGURE_DEPENDS
    ChocoGL/vendor/Box2D/src/*.cpp
    ChocoGL/vendor/Box2D/src/*.h
    ChocoGL/vendor/Box2D/include/*.h
)
add_library(Box2D STATIC ${BOX2D_SOURCES})
target_include_directories(Box2D PUBLIC ChocoGL/vendor/Box2D/include PRIVATE ChocoGL/vendor/Box2D/src)
target_compile_features(Box2D PUBLIC cxx_std_11)
chocogl_set_output_dirs(Box2D)

file(GLOB_RECURSE CHOCOGL_ENGINE_SOURCES CONFIGURE_DEPENDS
    ChocoGL/src/*.h
    ChocoGL/src/*.hpp
    ChocoGL/src/*.c
    ChocoGL/src/*.cpp
)

file(GLOB_RECURSE CHOCOGL_YAML_SOURCES CONFIGURE_DEPENDS
    ChocoGL/vendor/yaml-cpp/src/*.h
    ChocoGL/vendor/yaml-cpp/src/*.cpp
    ChocoGL/vendor/yaml-cpp/include/*.h
)

set(CHOCOGL_THIRD_PARTY_SOURCES
    ChocoGL/vendor/FastNoise/FastNoise.cpp
    ${CHOCOGL_YAML_SOURCES}
)

add_library(ChocoGL STATIC
    ${CHOCOGL_ENGINE_SOURCES}
    ${CHOCOGL_THIRD_PARTY_SOURCES}
)
target_compile_features(ChocoGL PUBLIC cxx_std_17)
target_compile_definitions(ChocoGL
    PRIVATE
        _CRT_SECURE_NO_WARNINGS
        CL_BUILD_DLL
        GLFW_INCLUDE_NONE
        PX_PHYSX_STATIC_LIB
    PUBLIC
        CL_PLATFORM_WINDOWS
        "$<$<CONFIG:Debug>:CL_DEBUG>"
        "$<$<CONFIG:Release>:CL_RELEASE>"
        "$<$<CONFIG:Dist>:CL_DIST>"
)
target_include_directories(ChocoGL
    PUBLIC
        ChocoGL/src
        ChocoGL/vendor
        ChocoGL/vendor/assimp/include
        ChocoGL/vendor/stb/include
        ChocoGL/vendor/GLFW/include
        ChocoGL/vendor/Glad/include
        ChocoGL/vendor/imgui
        ChocoGL/vendor/Box2D/include
        ChocoGL/vendor/glm
        ChocoGL/vendor/entt/include
        ChocoGL/vendor/mono/include
        ChocoGL/vendor/FastNoise
        ChocoGL/vendor/PhysX/include
        ChocoGL/vendor/yaml-cpp/include
)
target_precompile_headers(ChocoGL PRIVATE ChocoGL/src/clpch.h)
set_source_files_properties(${CHOCOGL_THIRD_PARTY_SOURCES} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

chocogl_pick_config_file(CHOCOGL_MONO_LIB
    "${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/mono/lib/Debug/mono-2.0-sgen.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/mono/lib/Release/mono-2.0-sgen.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/mono/lib/Release/mono-2.0-sgen.lib"
)
chocogl_pick_config_file(CHOCOGL_MONO_DLL
    "${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/mono/bin/Debug/mono-2.0-sgen.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/mono/bin/Release/mono-2.0-sgen.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/mono/bin/Release/mono-2.0-sgen.dll"
)

foreach(physx_lib IN LISTS CHOCOGL_PHYSX_LIBS)
    chocogl_pick_config_file(CHOCOGL_${physx_lib}_LIB
        "${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/PhysX/lib/Debug/${physx_lib}.lib"
        "${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/PhysX/lib/Release/${physx_lib}.lib"
        "${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/PhysX/lib/Dist/${physx_lib}.lib"
    )
    list(APPEND CHOCOGL_PHYSX_LINK_LIBS "${CHOCOGL_${physx_lib}_LIB}")
endforeach()

target_link_libraries(ChocoGL
    PUBLIC
        GLFW
        Glad
        ImGui
        Box2D
        opengl32
        "${CHOCOGL_MONO_LIB}"
        ${CHOCOGL_PHYSX_LINK_LIBS}
)
chocogl_set_output_dirs(ChocoGL)

file(GLOB_RECURSE COCO_SOURCES CONFIGURE_DEPENDS
    CoCo/src/*.h
    CoCo/src/*.hpp
    CoCo/src/*.c
    CoCo/src/*.cpp
)

add_executable(CoCo ${COCO_SOURCES})
target_compile_features(CoCo PRIVATE cxx_std_17)
target_compile_definitions(CoCo
    PRIVATE
        CL_PLATFORM_WINDOWS
        "$<$<CONFIG:Debug>:CL_DEBUG>"
        "$<$<CONFIG:Release>:CL_RELEASE>"
        "$<$<CONFIG:Dist>:CL_DIST>"
)
target_include_directories(CoCo
    PRIVATE
        CoCo/src
        ChocoGL/src
        ChocoGL/vendor
        ChocoGL/vendor/entt/include
        ChocoGL/vendor/glm
)

chocogl_pick_config_file(CHOCOGL_ASSIMP_LIB
    "${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/assimp/bin/Debug/assimp-vc141-mtd.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/assimp/bin/Release/assimp-vc141-mt.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/assimp/bin/Release/assimp-vc141-mt.lib"
)
chocogl_pick_config_file(CHOCOGL_ASSIMP_DLL
    "${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/assimp/bin/Debug/assimp-vc141-mtd.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/assimp/bin/Release/assimp-vc141-mt.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/ChocoGL/vendor/assimp/bin/Release/assimp-vc141-mt.dll"
)

target_link_libraries(CoCo PRIVATE ChocoGL "${CHOCOGL_ASSIMP_LIB}")
chocogl_set_output_dirs(CoCo)

add_custom_command(TARGET CoCo POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/CoCo/assets"
        "$<TARGET_FILE_DIR:CoCo>/assets"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
        "${CHOCOGL_ASSIMP_DLL}"
        "$<TARGET_FILE_DIR:CoCo>"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
        "${CHOCOGL_MONO_DLL}"
        "$<TARGET_FILE_DIR:CoCo>"
    VERBATIM
)

if(CHOCOGL_BUILD_CSHARP)
    if(CMAKE_VS_MSBUILD_COMMAND)
        set(CHOCOGL_CSHARP_TOOL "${CMAKE_VS_MSBUILD_COMMAND}")
        set(CHOCOGL_CSHARP_TOOL_KIND msbuild)
    else()
        find_program(CHOCOGL_CSHARP_TOOL MSBuild.exe)
        if(CHOCOGL_CSHARP_TOOL)
            set(CHOCOGL_CSHARP_TOOL_KIND msbuild)
        else()
            find_program(CHOCOGL_CSHARP_TOOL dotnet)
            if(CHOCOGL_CSHARP_TOOL)
                set(CHOCOGL_CSHARP_TOOL_KIND dotnet)
            endif()
        endif()
    endif()

    if(CHOCOGL_CSHARP_TOOL)
        set(CHOCOGL_SCRIPT_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CoCo/assets/scripts")
        set(CHOCOGL_CS_INTERMEDIATE_DIR "${CHOCOGL_INTERMEDIATE_ROOT}/$<CONFIG>-windows-x86_64")

        function(chocogl_add_csharp_project target_name project_file)
            if(CHOCOGL_CSHARP_TOOL_KIND STREQUAL "msbuild")
                add_custom_target(${target_name} ALL
                    COMMAND "${CMAKE_COMMAND}" -E make_directory "${CHOCOGL_SCRIPT_OUTPUT_DIR}"
                    COMMAND "${CHOCOGL_CSHARP_TOOL}"
                        "${CMAKE_CURRENT_SOURCE_DIR}/${project_file}"
                        /nologo
                        /p:Configuration=$<CONFIG>
                        /p:Platform=x64
                        /p:OutputPath=${CHOCOGL_SCRIPT_OUTPUT_DIR}/
                        /p:BaseIntermediateOutputPath=${CHOCOGL_CS_INTERMEDIATE_DIR}/${target_name}/
                        /p:IntermediateOutputPath=${CHOCOGL_CS_INTERMEDIATE_DIR}/${target_name}/
                    VERBATIM
                )
            else()
                add_custom_target(${target_name} ALL
                    COMMAND "${CMAKE_COMMAND}" -E make_directory "${CHOCOGL_SCRIPT_OUTPUT_DIR}"
                    COMMAND "${CHOCOGL_CSHARP_TOOL}"
                        build
                        "${CMAKE_CURRENT_SOURCE_DIR}/${project_file}"
                        --configuration $<CONFIG>
                        /p:Platform=x64
                        /p:OutputPath=${CHOCOGL_SCRIPT_OUTPUT_DIR}/
                        /p:BaseIntermediateOutputPath=${CHOCOGL_CS_INTERMEDIATE_DIR}/${target_name}/
                        /p:IntermediateOutputPath=${CHOCOGL_CS_INTERMEDIATE_DIR}/${target_name}/
                    VERBATIM
                )
            endif()
        endfunction()

        chocogl_add_csharp_project(ChocoGL-ScriptCore-CS ChocoGL-ScriptCore/ChocoGL-ScriptCore.csproj)
        chocogl_add_csharp_project(ExampleApp-CS ExampleApp/ExampleApp.csproj)
        add_dependencies(ExampleApp-CS ChocoGL-ScriptCore-CS)
        add_dependencies(CoCo ExampleApp-CS)
    else()
        message(WARNING "CHOCOGL_BUILD_CSHARP is ON, but neither MSBuild nor dotnet was found. C# script assemblies will not be built.")
    endif()
endif()

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT CoCo)
