find_library(libuuid REQUIRED)
set(LIBUUID_LIBRARIES uuid.so)

include_directories(${LIBUUID_INCLUDE_DIR})

HHVM_EXTENSION(uuid ext_uuid.cpp)
HHVM_SYSTEMLIB(uuid ext_uuid.php)

target_link_libraries(uuid ${LIBUUID_LIBRARIES})
