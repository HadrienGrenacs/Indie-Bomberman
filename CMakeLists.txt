cmake_minimum_required(VERSION 3.0)
PROJECT(bomberman)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

INCLUDE_DIRECTORIES(
   ${PROJECT_SOURCE_DIR}/include
   ${PROJECT_SOURCE_DIR}/src
)

FILE(GLOB SRCS src/*.cpp)
FILE(GLOB HDRS include/*.h)

if(UNIX)

ADD_EXECUTABLE(bomberman 
   ${SRCS}
   ${HDRS}
)

TARGET_LINK_LIBRARIES(bomberman
   ${PROJECT_SOURCE_DIR}/lib/Linux/libIrrlicht.a -lGL -lXxf86vm -lXext -lX11 -lXcursor -lsfml-audio
)

elseif(WIN32)

ADD_EXECUTABLE(bomberman 
   ${SRCS}
   ${HDRS}
)

TARGET_LINK_LIBRARIES(bomberman
   ${PROJECT_SOURCE_DIR}/lib/Win64-visualStudio/Irrlicht.lib -lGL -lXxf86vm -lXext -lX11 -lXcursor ${PROJECT_SOURCE_DIR}/lib/SFML/sfml-audio.lib
)
endif(UNIX)