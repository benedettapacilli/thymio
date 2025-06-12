#find_library(asebacppapi_LIBRARY NAMES asebacppapi HINTS /usr/local/lib)
#include_directories(${LIBXML2_INCLUDE_DIR})

if(ARGOS_BUILD_FOR_SIMULATOR)
   add_library(
        thymio_obstacle_avoidance MODULE
		   thymio_obstacle_avoidance.h
		   thymio_obstacle_avoidance.cpp
        )

   target_link_libraries(thymio_obstacle_avoidance
		   argos3core_${ARGOS_BUILD_FOR}
		   argos3plugin_${ARGOS_BUILD_FOR}_thymio
		   argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
		   ${LIBXML2_LIBRARIES}
		   )
endif(ARGOS_BUILD_FOR_SIMULATOR)