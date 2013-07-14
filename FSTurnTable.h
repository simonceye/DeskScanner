//
//  FSTurnTable.h
//  Desktop Scanner 3D
//
//  Created by Simon Li on 16/6/13.
//

#ifndef FS_TURN_TABLE_H
#define FS_TURN_TABLE_H

#include "FSHeaders.h"
#include "FSObject.h"

class FSTurnTable : public FSObject {
  private:
    FSDirection direction;
    
  public:
    /* Constructor and Destructor */
    FSTurnTable();
    ~FSTurnTable();

    //void selectStepper(unsigned char id);
    
    void turnNumberOfDegrees(FSFloat degrees);
    void setDirection(FSDirection direction);
    void enable(void);
    void disable(void);
};

#endif
