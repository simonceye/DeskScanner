#pragma once

#include "FSHeaders.h"
#include "FSPointCloud.h"
#include "FSLaser.h"
#include "FSCamera.h"

class ScanObjectFactory{
public:
	static const int FRAME_NUM = 32;

private:
	static const char * FRAME_PATH;

	int steps;
	float stepAngle;
	char* framepaths[FRAME_NUM][2];
	Mat frames[FRAME_NUM][2];


	IplImage* noLaserFrame;
	IplImage* laserFrame;
	FSPointCloud* pointCloud; 
	FSLaser* laser;
	FSCamera* camera;  
	FSTurnTable* turntable;

	void buildScanFrames();
public:
	ScanObjectFactory();
	~ScanObjectFactory();

	void moveOneStep();
	void reset();
	void showScanFrames();

	FSLaser* getLaser(){
		return laser;
	}

	FSCamera* getCamera(){
		return camera;
	}

	FSTurnTable* getTurnTable(){
		return turntable;
	}

	Mat getNoLaserFrame();
	Mat getLaserFrame();
};