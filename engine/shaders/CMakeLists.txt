#--------------------------------------------------------------------------
# shaders
#--------------------------------------------------------------------------

FILE(GLOB shaders *.glsl)

SOURCE_GROUP("display" FILES ${files_shaders_display})


SET(files_shaders
	${shaders}
	${files_shaders_pch})

SET(files_pch ../config.h ../config.cc)
SOURCE_GROUP("pch" FILES ${files_pch})
ADD_LIBRARY(shaders STATIC ${files_shaders} ${files_pch})
TARGET_PCH(shaders ../)	
ADD_DEPENDENCIES(shaders glew glfw)
TARGET_LINK_LIBRARIES(shaders PUBLIC engine exts glew glfw imgui ${OPENGL_LIBS})
