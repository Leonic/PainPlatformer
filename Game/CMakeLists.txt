# CMakeList.txt : CMake project for Game, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_PATH_DEBUG}/bin" )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_PATH_RELEASE}/bin" )

add_compile_definitions(_GAME_)

set(PainNSuffering_Src
    src/main.cpp
    src/Game.cpp
    src/TextureManager.cpp
    src/EventHandler.cpp
)

set(PainNSuffering_Header
    src/Game.h
    src/TextureManager.h
    src/EventHandler.h
    src/EngineTypes.h
)

if (WIN32)
    # Workaround for RelWithDebInfo builds not installing all the libraries
    set(CMAKE_MAP_IMPORTED_CONFIG_MINSIZEREL Release)
    set(CMAKE_MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release)

    set(SDL2_LIBRARIES SDL2::SDL2 SDL2::SDL2main)
    set(SDL2_IMAGE_LIBRARIES SDL2::SDL2_image)
    set(SDL2_TTF_LIBRARIES SDL2::SDL2_ttf)
endif()

find_package(Python3 COMPONENTS Interpreter REQUIRED)
find_package(Git REQUIRED)

add_custom_target(EngineMetadata
        COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/src/EngineMetadata.py" "${GIT_EXECUTABLE}"
        COMMENT "Generating build Engine metadata..."
)

find_package(fmt CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(RapidJSON REQUIRED)
find_package(ZLIB REQUIRED)

# Add this because apparently find_package(SDL2 REQUIRED) doesn't work right on Arch?
if("${SDL2_LIBRARIES}" STREQUAL "")
    set(SDL2_LIBRARIES "SDL2::SDL2")
endif()

if("${SDL2_IMAGE_LIBRARIES}" STREQUAL "")
    set(SDL2IMAGE_LIBRARIES "SDL2::SDL2_image")
endif()

# Add this because apparently find_package(SDL2 REQUIRED) doesn't work right on Arch?
if("${SDL2_LIBRARIES}" STREQUAL "")
    set(SDL2_LIBRARIES "SDL2::SDL2")
endif()

if("${SDL2_IMAGE_LIBRARIES}" STREQUAL "")
    set(SDL2IMAGE_LIBRARIES "SDL2::SDL2_image")
endif()

set (PainNSuffering_Libs
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${ZLIB_LIBRARIES}
)

include_directories("${PROJECT_SOURCE_DIR}/Game/src")
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
include_directories(${RAPIDJSON_INCLUDE_DIRS})
include_directories(${ZLIB_INCLUDE_DIRS})

if (WIN32)

    set (PainNSuffering_Src
        ${PainNSuffering_Src}
        src/game.rc
    )

    set (PainNSuffering_Header
        ${PainNSuffering_Header}
        src/resource.h
    )

    add_executable (${GAME_NAME} WIN32 ${PainNSuffering_Src} ${PainNSuffering_Header})
elseif(UNIX)
    set(PainNSuffering_Libs 
        ${PainNSuffering_Libs}
        dl
    )

    add_executable (${GAME_NAME} ${PainNSuffering_Src} ${PainNSuffering_Header})
endif()

add_dependencies(${GAME_NAME} EngineMetadata)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(${GAME_NAME} PROPERTIES 
        OUTPUT_NAME "pain"
        VS_DEBUGGER_WORKING_DIRECTORY "${BIN_PATH_DEBUG}")
else()
# Copy assets for release
    set_target_properties(${GAME_NAME} PROPERTIES 
        OUTPUT_NAME "pain"
        VS_DEBUGGER_WORKING_DIRECTORY "${BIN_PATH_RELEASE}")
endif()

target_link_libraries(${GAME_NAME} PUBLIC ${PainNSuffering_Libs})

if (UNIX)
    install(TARGETS ${GAME_NAME} RUNTIME DESTINATION ./bin/${PROJECT_NAME})
elseif (WIN32)
    install(TARGETS ${GAME_NAME} RUNTIME DESTINATION ./)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/
            DESTINATION ./
            FILES_MATCHING PATTERN "*.dll"
            PATTERN ".cmake" EXCLUDE
            PATTERN "CMakeFiles" EXCLUDE
            PATTERN "include" EXCLUDE
            PATTERN "Testing" EXCLUDE
    )
endif()

install (DIRECTORY assets DESTINATION ./)
