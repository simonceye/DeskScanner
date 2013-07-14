//
//  FSCamera.h
//  Desktop Scanner 3D
//
//  Created by Simon Li on 16/6/13.
//

#ifndef FS_CAMERA_H
#define FS_CAMERA_H

#include "FSHeaders.h"
#include "FSObject.h"
#include <iostream>
//#include "FSChessboardCalibration.h"

class FSCamera : public FSObject {
  private:
    VideoCapture camera;
    //CvMat *intrinsic; 
    //CvMat *distortion;
    const char* resPath;

    FSPoint position;       //the position of the camera in cm
    FSSize imageResolution; //the resolution of the image given by the camera
    FSFloat sceneWidth;     //the real width of what the camera sees in cm

  public:
    /* resPath : path to distortion/intrinisics params */
    FSCamera();
    ~FSCamera();

    FSPoint getPosition(void);
    void setPosition(FSPoint p);
    
    virtual Mat fetchFrame(void);
    Mat fetchQuickFrame(void);

	void test(){
		std::cout << "Width: " << this->camera.get(CV_CAP_PROP_FRAME_WIDTH) << std::endl;
		std::cout << "Height: " << this->camera.get(CV_CAP_PROP_FRAME_HEIGHT) << std::endl;
		std::cout << "FPS: " << this->camera.get(CV_CAP_PROP_FPS) << std::endl;;

		//this->camera.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
		//this->camera.set(CV_CAP_PROP_FRAME_HEIGHT, 960);

		std::cout << "Width: " << this->camera.get(CV_CAP_PROP_FRAME_WIDTH) << std::endl;
		std::cout << "Height: " << this->camera.get(CV_CAP_PROP_FRAME_HEIGHT) << std::endl;
		std::cout << "FPS: " << this->camera.get(CV_CAP_PROP_FPS) << std::endl;;

		Mat frame;
		namedWindow("video", 1);
		for(;;)
		{
			this->camera >> frame;
			imshow("video", frame);
			if(waitKey(30) >= 0) 
				break;
		}
	}
};

#endif