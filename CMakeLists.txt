
cmake_minimum_required (VERSION 3.17.0)

project (project_co_server)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY .)

SET(CMAKE_CXX_COMPILER /opt/rh/devtoolset-10/root/usr/bin/g++)

include_directories(${PROJECT_SOURCE_DIR})

ADD_DEFINITIONS(-D BOOST_ASIO_HAS_STD_COROUTINE -D BOOST_ASIO_HAS_CO_AWAIT)


aux_source_directory(${PROJECT_SOURCE_DIR}/logic SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/logic/database SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/logic/protocol SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/logic/servlet SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/log SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/net SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/redis SRC_LIST)

set(CMAKE_CXX_FLAGS "-std=c++2a -g -O0 -fcoroutines -fPIC -Wall -m64 -Wparentheses -Wconversion-null -Wreturn-type -DBOOST_BIND_GLOBAL_PLACEHOLDERS ${CMAKE_CXX_FLAGS}")

add_subdirectory(logic/protocol)
add_subdirectory(logic/database)

add_executable(co_spawn_server main.cpp ${SRC_LIST})
#add_executable(update_game update_game.cpp ${SRC_LIST})
#add_executable(test_websocket test_websocket.cpp ${SRC_LIST})

#set(exes server update_game test_websocket)
set(exes co_spawn_server)
FOREACH(exe ${exes})
    target_link_libraries(${exe} -lcrypto)
    #target_link_libraries(${exe} -ldl)
    target_link_libraries(${exe} -lglog)
    target_link_libraries(${exe} -lhiredis)
    #target_link_libraries(${exe} -llibgo)
    target_link_libraries(${exe} -lpthread)
    target_link_libraries(${exe} -lprotobuf)
    target_link_libraries(${exe} -lssl)
ENDFOREACH(exe)
