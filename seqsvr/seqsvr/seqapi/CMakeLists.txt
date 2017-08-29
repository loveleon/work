include_directories(. .. ../../../nebula ../../seqsvr)
set (SRC_LIST
    seqapi.cc
    seqapi.h
    seqapi_command_handler.cc
    seqapi_command_handler.h
    ../../seqsvr/proto/cc/seqsvr.pb.h
    ../../seqsvr/proto/cc/seqsvr.pb.cc
    ../../seqsvr/base/message_handler_util.h
    ../../../nebula/nebula/base/readline_gets.cc
    ../../../nebula/nebula/base/readline_gets.h
    )

#set (SEQSVR_HEADER_DIRS
#    ../../../nebula/nebula/
#    ../../../nebula/
#    ../../seqsvr/proto/cc
#    ../../seqsvr/base
#)

set(SEQSVR_HEADER_DIRS
# be careful "../seqsvr/" is different with "../seqsvr"
    ../../seqsvr
    ../../seqsvr/base
    ../../seqsvr/proto
#    ../../seqsvr/seqapi/
    ../../../nebula/nebula
    )
foreach(dir ${SEQSVR_HEADER_DIRS})
    file(GLOB_RECURSE  headers ${dir}/*.h )
    set(SEQSVR_HEADERS
        ${SEQSVR_HEADERS}
        ${headers})
endforeach()

#add_library(seqapi SHARED ${SRC_LIST})
#add_library(seqapi MODULE ${SRC_LIST})
#add_library(seqapi STATIC ${SRC_LIST})
add_executable(seqapi ${SRC_LIST})
target_link_libraries(seqapi net base protobuf readline)
add_subdirectory(capi)

install(TARGETS seqapi DESTINATION lib)
foreach(dir ${SEQSVR_HEADER_DIRS})
    install(DIRECTORY ${dir} DESTINATION include
            FILES_MATCHING PATTERN "*.h")
endforeach()