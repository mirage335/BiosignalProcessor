include_directories(${CMAKE_SOURCE_DIR}/include ${LIBSNDFILE_INCLUDE_DIR})
add_executable(OutputObjectName source.c)			#Creates compilation target.
target_link_libraries(OutputObjectName ${LIBSNDFILE_LIBRARY})