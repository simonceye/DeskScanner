//
//  FSCamera.cpp
//  FabScan3D
//
//  Created by Francis Engelmann on 7/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "FSCamera.h"
#include <iostream>

using namespace std;
// ---------------------------------------------
#pragma mark -
#pragma mark Constructor and Destructor
// ---------------------------------------------

FSCamera::FSCamera()
{
  //this->resPath = resPath;
  display = 0;
  /*
  %TODO what happens when no camera is connected
  */
  camera.open(CV_CAP_ANY);
  //position = FSMakePoint(0.0f, 1.0f, 5.0f);
}

FSCamera::~FSCamera()
{
	camera.release();
}

Mat FSCamera::fetchQuickFrame()
{
  Mat frame;
  camera >> frame;

  return frame;
}

Mat FSCamera::fetchFrame()
{
  return fetchQuickFrame();
}

void FSCamera::setPosition(FSPoint p)
{
  position = p;
}

FSPoint FSCamera::getPosition(void)
{
  return position;
}