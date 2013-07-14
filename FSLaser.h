//
//  FSLaser.h
//  Desktop Scanner 3D
//
//  Created by Simon Li on 16/6/13.
//

#ifndef FS_LASER_H
#define FS_LASER_H

#include "FSHeaders.h"
#include "FSGeometry.h"
#include "FSObject.h"

class FSStepper;
class FSSerial2;

class FSLaser : public FSObject {
  private:
    FSPoint laserPointPosition;
    FSSerial2* serial;
    
  public:
    /* Constructor and Destructor */
    FSLaser();
    ~FSLaser();
    
    /* Getters and Setters */
    void setLaserPointPosition(FSPoint p);
    FSPoint getLaserPointPosition(void);
    
    /* Methods */
    void turnOn();
    void turnOff();
};

#endif