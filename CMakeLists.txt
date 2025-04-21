cmake_minimum_required(VERSION 3.30)

project(roto_2_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(WINDEPLOYQT_EXECUTABLE "E:/Qt/6.7.3/msvc2022_64/bin/windeployqt.exe")

find_package(Qt6 COMPONENTS Core Widgets Gui REQUIRED)

add_executable(roto_2_cpp
        src/main.cpp
        src/window/SketchWindow.h
        src/window/SketchWindow.cpp
        src/window/CanvasWidget.cpp
        src/window/CanvasWidget.h
        src/utils/CurveUtils.cpp
        src/utils/CurveUtils.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Gui
)

# 添加自定义命令，在构建完成后自动运行 windeployqt
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${WINDEPLOYQT_EXECUTABLE}
        --verbose 0
        --no-compiler-runtime
        --no-opengl-sw
        \"$<TARGET_FILE:roto_2_cpp>\"
        COMMENT "正在部署 Qt 依赖项..."
)