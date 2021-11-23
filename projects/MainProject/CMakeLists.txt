#--------------------------------------------------------------------------
# MainProject project
#--------------------------------------------------------------------------

PROJECT(MainProject)
FILE(GLOB MainProject_header code/*.h)
FILE(GLOB MainProject_sources code/*.cc)
FILE(GLOB MainProject_sources2 code/*.cpp)

SET(files_MainProject ${MainProject_headers} ${MainProject_sources} ${MainProject_sources2})
SOURCE_GROUP("MainProject" FILES ${files_MainProject})

ADD_EXECUTABLE(MainProject ${files_MainProject})
TARGET_LINK_LIBRARIES(MainProject core render)
ADD_DEPENDENCIES(MainProject core render)
set_property(TARGET MainProject PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")