cmake_minimum_required(VERSION 3.12)

# Compiler settings

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(STELLAR)




# SDL
find_package(SDL2 REQUIRED)
# SDL Image
# \\ find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)
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
    # SF  
    src/game.cpp
    # graphics
    src/graphics/renderer.cpp
    # gameobjs
    src/gameObjects/terrain/tile.cpp
    # map
    src/map/map.cpp
    # ui
    src/gameObjects/ui/text.cpp
    src/gameObjects/ui/inputpanel.cpp
    # utils
    src/utils/jsonReader.cpp
    #
    src/scene.cpp
    # main
    src/main.cpp
)


# Flags
target_compile_options(STELLAR PUBLIC -fpermissive -Wno-c++11-narrowing -g -O0)

target_link_libraries(STELLAR ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} sfml-graphics sfml-audio)
target_link_libraries(STELLAR ${LUA_LIBRARIES} ${LUA_DEPENDENCIES})
target_link_libraries(STELLAR ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} SDL2_image SDL2_ttf)
TARGET_LINK_LIBRARIES(STELLAR jsoncpp_lib)
