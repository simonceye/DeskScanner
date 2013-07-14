//
//  FSVision.cpp
//  Desktop Scanner 3D
//
//  Created by Simon Li on 16/6/13.
//

#include "FSVision.h"


int FSVision::findBrightestPointInRow(uchar* row, int rowWidth)
{
	// init values we will use
	int laserSum, laserNum, laserCenter, maxPx;
	uchar maxPxVal;
	//int h = row;

	// for each row, find the location of the laser
	laserSum = 0;
	laserNum = 0;
	maxPx = 0;
	maxPxVal = 0;

	for (int w = 0; w < rowWidth; w++)
	{
		uchar curVal = row[w];
		if (curVal > maxPxVal)
		{
			// this point is the brightest we have seen so far and it exceeds our minimum value
			maxPxVal = curVal;
			maxPx = w;

			laserSum = w;
			laserNum = 1;

		} else if (curVal == maxPxVal)
		{
			// this point is exactly as bright as our current brightest pixel, so average them
			laserSum += w;
			laserNum ++;
		}
	}

	// we are done with this row -- select the most likely point.
	// TODO: subpixel interpolation

	if (maxPx >= 0 && maxPxVal > 100)
	{
		// compute the center point of the laser
		laserCenter = laserSum/laserNum;
	} else {
		// no value for this row
		laserCenter = 0;
	}
	return laserCenter;
}

/**
 * 
 * @param image with laser on, image with laser off, threshold value
 * @return one channel of binary resul, with 255 or 0
 */
void FSVision::subLaser(const Mat& frame, const Mat& laserFrame, vector<int>& laserLocations){
  //printf("%s \n",__PRETTY_FUNCTION__);
  Size sz(CAM_IMAGE_WIDTH, CAM_IMAGE_HEIGHT);

  Mat bwNoLaser(sz, CV_8UC1);
  Mat bwWithLaser(sz, CV_8UC1);
  Mat subImage(sz, CV_8UC1);

  cvtColor(frame, bwNoLaser, CV_RGB2GRAY);
  cvtColor(laserFrame, bwWithLaser, CV_RGB2GRAY);
  absdiff(bwNoLaser,bwWithLaser,subImage);

  for(int r = 0; r < CAM_IMAGE_HEIGHT; r++){
	  uchar* row = subImage.ptr<uchar>(r);
	  laserLocations[r] = findBrightestPointInRow(row, CAM_IMAGE_WIDTH);
	  //cout << laserLocations[r] << endl;
  }
}

//Image frame to world frame (turntable far-end edge as origin)
FSPoint FSVision::convertCvPointToFSPoint(CvPoint cvPoint)
{
  CvSize cvImageSize = cvSize(CAM_IMAGE_WIDTH, CAM_IMAGE_HEIGHT); //1600 1200 is the resolution of the image from the camera
  FSSize fsImageSize = FSMakeSize(FRAME_WIDTH, (FRAME_WIDTH*CAM_IMAGE_HEIGHT)/CAM_IMAGE_WIDTH, 0.0f);
  
  //here we define the origin of the cvImage, we place it in the middle of the frame and in the corner of the two perpendiculair planes
  CvPoint origin;
  origin.x = cvImageSize.width/2.0f;
  origin.y = cvImageSize.height*ORIGIN_Y;
  
  FSPoint fsPoint;
  
  //translate
  cvPoint.x -= origin.x;
  cvPoint.y -= origin.y;
  //scale
  fsPoint.x = cvPoint.x*fsImageSize.width/cvImageSize.width;
  fsPoint.y = -cvPoint.y*fsImageSize.height/cvImageSize.height;
  fsPoint.z=0.0f;
  
  return fsPoint;
}


//World frame(turntable far-end edge as origin) to Image frame
CvPoint FSVision::convertFSPointToCvPoint(FSPoint fsPoint)
{
  CvSize cvImageSize = cvSize(CAM_IMAGE_WIDTH, CAM_IMAGE_HEIGHT);
  FSSize fsImageSize = FSMakeSize(FRAME_WIDTH, (FRAME_WIDTH*CAM_IMAGE_HEIGHT)/CAM_IMAGE_WIDTH, 0.0f);
  CvPoint origin;
  origin.x = cvImageSize.width/2.0f;
  origin.y = cvImageSize.height*ORIGIN_Y;
  CvPoint cvPoint; 

  cvPoint.x = fsPoint.x*cvImageSize.width/fsImageSize.width;
  cvPoint.y = -fsPoint.y*cvImageSize.height/fsImageSize.height;

  //translate
  cvPoint.x += origin.x;
  cvPoint.y += origin.y;

  return cvPoint;
}

void FSVision::putPointsFromFrameToCloud(const Mat& noLaserFrame, const Mat& laserFrame, FSPointCloud* pointCloud, FSLaser* laser, FSCamera* camera, FSTurnTable* turntable, int dpiVertical, FSFloat lowerLimit, FSFloat treshold)
{
    //extract laser line from the two images
	vector<int> laserLocations(CAM_IMAGE_HEIGHT);
    FSVision::subLaser(laserFrame,noLaserFrame, laserLocations);

	//For test
	if(DEBUG){
		Mat clone = laserFrame.clone();
		for(int i = 0; i < CAM_IMAGE_HEIGHT-1; i++){
			if(laserLocations[i+1] > 0 && laserLocations[i] > 0)
				line(clone, Point(laserLocations[i], i), Point(laserLocations[i+1], i+1), CV_RGB(0,0,255),1);  
		}

		namedWindow("laserLine");
		imshow("laserLine", clone);
		waitKey(0);
	}

    //calculate position of laser in cv frame
    FSPoint fsLaserLinePosition = laser->getLaserPointPosition();
	CvPoint cvLaserLinePosition = FSVision::convertFSPointToCvPoint(fsLaserLinePosition);
    FSFloat laserPos = cvLaserLinePosition.x;

	//int height = laserLine.rows;
	//int width = laserLine.cols;

    for( int y = UPPER_ANALYZING_FRAME_LIMIT; y < CAM_IMAGE_HEIGHT - LOWER_ANALYZING_FRAME_LIMIT; y+=dpiVertical ){ 
		//no bear outside of these limits :) cuttin gof top and bottom of frame
		int x = laserLocations[y];

		//100 is the offset where we stop looking for a reflected laser, cos we might catch the non reflected
		if(x > (laserPos + ANALYZING_LASER_OFFSET)){
		  const Vec3b* noLaserRow = noLaserFrame.ptr<Vec3b>(y);

          CvPoint cvNewPoint; //position of the reflected laser line on the image plane
          cvNewPoint.x = x;
          cvNewPoint.y = y;

          FSPoint fsNewPoint = FSVision::convertCvPointToFSPoint(cvNewPoint); //convert to world coordinates
          
          FSLine2 l1 = computeLineFromPoints(camera->getPosition(), fsNewPoint);
          FSLine2 l2 = computeLineFromPoints(laser->getPosition(), laser->getLaserPointPosition());
  
          FSPoint i = computeIntersectionOfLines(l1, l2);
          
          fsNewPoint.x = i.x;
          fsNewPoint.z = i.z;
          
          //old stuff probably wrong
          //FSFloat angle = (laser->getRotation()).y;
          //fsNewPoint.z = (fsNewPoint.x - fsLaserLinePosition.x)/tan(angle*M_PI/180.0f);
          
          
          //At this point we know the depth=z. Now we need to consider the scaling depending on the depth.
          //First we move our point to a camera centered cartesion system.
          fsNewPoint.y -= (camera->getPosition()).y;
          fsNewPoint.y *= ((camera->getPosition()).z - fsNewPoint.z)/(camera->getPosition()).z;
          //Redo the translation to the box centered cartesion system.
          fsNewPoint.y += (camera->getPosition()).y;


          FSUChar r = noLaserRow[x][2];
          FSUChar g = noLaserRow[x][1];
          FSUChar b = noLaserRow[x][0];

          //printf("COLOR %u %u %u \n",r,g,b);
          fsNewPoint.color = FSMakeColor(r, g, b);
          
          //turning new point according to current angle of turntable
          //translate coordinate system to the middle of the turntable
          fsNewPoint.z -= TURNTABLE_POS_Z; //7cm radius of turntbale plus 5mm offset from back plane
          FSPoint alphaDelta = turntable->getRotation();

		  //printf("%s %f \n", __PRETTY_FUNCTION__, alphaDelta.y);
          FSFloat alphaOld = (float)atan(fsNewPoint.z/fsNewPoint.x);	
		  
          //printf("%s %f \n",__PRETTY_FUNCTION__,alphaOld);
          FSFloat alphaNew = alphaOld+alphaDelta.y*(M_PI/180.0f);

		  FSFloat hypotenuse = (float)sqrt(fsNewPoint.x*fsNewPoint.x + fsNewPoint.z*fsNewPoint.z);
          
          if(fsNewPoint.z < 0 && fsNewPoint.x < 0){
            alphaNew += M_PI;
          }else if(fsNewPoint.z > 0 && fsNewPoint.x < 0){
            alphaNew -= M_PI;
          }
          fsNewPoint.z = (float)sin(alphaNew)*hypotenuse;
          fsNewPoint.x = (float)cos(alphaNew)*hypotenuse;
          
          if(fsNewPoint.y>lowerLimit && hypotenuse < 7){ //eliminate points from the grounds, that are not part of the model
            pointCloud->addPoint(fsNewPoint);
          }
        }
    }
  //cvReleaseImage(&bwImage);
}