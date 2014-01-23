include_directories(${CMAKE_SOURCE_DIR}/include ${LIBSNDFILE_INCLUDE_DIR})

add_executable(BiosignalProcessor BiosignalProcessor.c)			#Creates compilation target.
target_link_libraries(BiosignalProcessor ${LIBSNDFILE_LIBRARY})