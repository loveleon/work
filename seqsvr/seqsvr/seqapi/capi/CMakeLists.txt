include_directories(. .. ../seqapi)
set (SRC_LIST
    capi.cpp
    capi.h
    ../seqapi.h
    ../seqapi.cc
)
add_library(capi STATIC ${SRC_LIST})
#target_link_libraries(capi seqapi)
