cmake_minimum_required(VERSION 3.12)

project(STELLAR)

# Compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# SDL
find_package(SDL2 REQUIRED)
# SDL Image
find_package(SDL2_image REQUIRED)

# LUA
find_package(Lua REQUIRED)
# JSONCPP
find_package(jsoncpp REQUIRED)
# SFML (nah)
find_package(SFML REQUIRED COMPONENTS graphics window system audio)

# Include directories
include_directories(src)
include_directories(${SFML_INCLUDE_DIR})    
include_directories(${SDL2_INCLUDE_DIR})
include_directories(/usr/local/include ${LUA_INCLUDE_DIR})
include_directories(${JSONCPP_INCLUDE_DIR})
include_directories(${SDL_INCLUDE_DIR})

# Compiler executable
add_executable(STELLAR
    # Sprite
    src/graphics/sprite.h
    src/graphics/sprite.cpp
    # scripting
    src/scripting/scriptmanager.cpp
    # engine
    src/transform.cpp
    src/gameobject.cpp
    src/scene.cpp
    # nunticle  
    src/game.cpp
    # graphics
    src/graphics/renderer.cpp
    # ui
    src/gameObjects/ui/text.cpp
    # utils
    src/utils/jsonReader.cpp
    # main
    src/main.cpp
)


# Flags
target_compile_options(STELLAR PUBLIC -fpermissive -g -O0)

target_link_libraries(STELLAR ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} sfml-graphics sfml-audio)
target_link_libraries(STELLAR ${LUA_LIBRARIES} ${LUA_DEPENDENCIES})
target_link_libraries(STELLAR ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} SDL2_image)
TARGET_LINK_LIBRARIES(STELLAR jsoncpp_lib)