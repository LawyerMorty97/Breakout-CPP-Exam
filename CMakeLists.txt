cmake_minimum_required(VERSION 3.13)
project(Breakout_Exam)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

set(CMAKE_CXX_STANDARD 17)

if(${APPLE})
    message("Preparing macOS project")
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(OpenGL REQUIRED)

    include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lSDL2 -lSDL_ttf -lSDL_image")

    set(INC_DIR "${PROJECT_SOURCE_DIR}/include") #Include Directory
    set(LIB_DIR "${PROJECT_SOURCE_DIR}/library") #Library Directory
    find_package(OpenGL REQUIRED)

    if(${WIN32})
        message("Preparing Win32 project")
        set(SDL2_LIB "${LIB_DIR}/libSDL2.dll.a;${LIB_DIR}/libSDL2main.a")
        set(SDL2_TTF_LIB "${LIB_DIR}/libSDL2_ttf.dll.a")
        set(SDL2_IMAGE_LIB "${LIB_DIR}/libSDL2_image.dll.a")
    else()
        message("Preparing Linux project")
        set(SDL2_LIB "${LIB_DIR}/libSDL2.a;${LIB_DIR}/libSDL2main.a")
        set(SDL2_TTF_LIB "${LIB_DIR}/libSDL2_ttf.a")
        set(SDL2_IMAGE_LIB "${LIB_DIR}/libSDL2_image.a")
    endif()

    include_directories(${INC_DIR} ${OPENGL_INCLUDE_DIR})
endif()

add_executable(${PROJECT_NAME} main.cpp src/Core.cpp src/Components/Image.cpp src/Utils.cpp src/Managers/InputManager.cpp
        src/Managers/ImageManager.cpp src/Components/Screen.cpp src/Components/IGame.h src/Gameparts/Info.cpp src/Components/Font.cpp
        src/Components/Text.cpp src/Components/IComponent.h src/Components/IPosition.h src/Gameparts/Board.cpp
        src/Managers/GameManager.cpp src/Gameparts/Brick.cpp src/Gameparts/Ball.cpp)

if(${APPLE})
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${OPENGL_LIBRARIES})
else()
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIB} ${SDL2_TTF_LIB} ${SDL2_IMAGE_LIB} ${OPENGL_LIBRARIES})
endif()