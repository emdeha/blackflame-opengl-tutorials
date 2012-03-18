// Geometry.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Geometry.h"


// This is an example of an exported variable
GEOMETRY_API int nGeometry=0;

// This is an example of an exported function.
GEOMETRY_API int fnGeometry(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see Geometry.h for the class definition
CGeometry::CGeometry()
{
	return;
}
