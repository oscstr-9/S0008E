#--------------------------------------------------------------------------
# core
#--------------------------------------------------------------------------

SET(files_core
	app.h
	app.cc
	MatrixMath.h
	VectorMath.h
	MathLine.h
	MathLine.cpp
	MathPlane.h
	MathPlane.cpp
	Quad.h
	Quad.cpp
	PerlinNoise.h
	PerlinNoise.cpp)
SOURCE_GROUP("core" FILES ${files_core})
	
SET(files_pch ../config.h ../config.cc)
SOURCE_GROUP("pch" FILES ${files_pch})
ADD_LIBRARY(core STATIC ${files_core} ${files_pch})
TARGET_PCH(core ../)
ADD_DEPENDENCIES(core glew)
TARGET_LINK_LIBRARIES(core PUBLIC engine exts glew)
