//
//  FSLaser.cpp
//  FabScan3D
//
//  Created by Francis Engelmann on 6/30/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "FSLaser.h"

// ---------------------------------------------
#pragma mark -
#pragma mark Constructor and Destructor
// ---------------------------------------------

FSLaser::FSLaser()
{
}

FSLaser::~FSLaser()
{
  //printf("%s destructor\n",__PRETTY_FUNCTION__);
}

// ---------------------------------------------
#pragma mark -
#pragma mark Setters and Getters
// ---------------------------------------------

void FSLaser::setLaserPointPosition(FSPoint p){
  laserPointPosition = p;
}

FSPoint FSLaser::getLaserPointPosition(void){
  return laserPointPosition;
}


void FSLaser::turnOn(void)
{
  //To-Do
}

void FSLaser::turnOff(void)
{
  //To-Do
}
