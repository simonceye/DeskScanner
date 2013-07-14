//
//  FSVision.h
//  Desktop Scanner 3D
//
//  Created by Simon Li on 16/6/13.
//

#ifndef FS_VISION_H
#define FS_VISION_H

#include "FSHeaders.h"
#include "FSLaser.h"
#include "FSCamera.h"
#include "FSTurnTable.h"
#include "FSPointCloud.h"

class FSVision {
  private:
	static int findBrightestPointInRow(uchar* row, int rowWidth);

  public:

    static FSPoint convertCvPointToFSPoint(CvPoint cvPoint);
    static CvPoint convertFSPointToCvPoint(FSPoint fsPoint);

    static void subLaser(const Mat& frame, const Mat& laserFrame, vector<int> & laserLocations);
    static void putPointsFromFrameToCloud(const Mat& noLaserFrame, const Mat& laserFrame, FSPointCloud* pointCloud, FSLaser* laser, FSCamera* camera, FSTurnTable* turntable, int dpiVertical, FSFloat lowerLimit, FSFloat treshold);
};

#endif