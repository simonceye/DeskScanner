//
//  FSHeaders.h
//  Desktop Scanner 3D
//
//  Created by Simon Li on 16/6/13.
//
// ---------------------------------------------
#pragma mark -
#pragma mark C++ Headers
// ---------------------------------------------

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

// ---------------------------------------------
#pragma mark -
#pragma mark OpenGL Headers
// ---------------------------------------------

/**
#ifdef __APPLE__
  #include <GLUT/glut.h>
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
  #include <OpenGL/glext.h>
#else
  #include <GL/glut.h>
  #include <GL/gl.h>
  #include <GL/glu.h>
  #include <GL/glext.h>
#endif
**/

// ---------------------------------------------
#pragma mark -
#pragma mark OpenCV Headers
// ---------------------------------------------

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc_c.h>
using namespace cv;


// ---------------------------------------------
#pragma mark -
#pragma mark FabScan Headers
// ---------------------------------------------

#include "FSDefines.h"
#include "FSGeometry.h"
