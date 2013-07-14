#include "ScanObjectFactory.h"

const char * ScanObjectFactory::FRAME_PATH = "C:/simon/study/opencv/DesktopScanner/resource/";

ScanObjectFactory::ScanObjectFactory(){
	steps = 0;

	laser = new FSLaser();
	laser->setPosition(FSMakePoint(LASER_POS_X, LASER_POS_Y, LASER_POS_Z));
	laser->setLaserPointPosition(FSMakePoint(-3.23,0,0));

	camera = new FSCamera();
	camera->setPosition(FSMakePoint(CAM_POS_X, CAM_POS_Y, CAM_POS_Z));

	turntable = new FSTurnTable();
	turntable->setRotation(FSMakePoint(0, 0, 0));

	stepAngle = 11.25;

	framepaths[0][0] = "temp0.jpg";
	framepaths[0][1] = "temp1.jpg";
	framepaths[1][0] = "temp2.jpg";
	framepaths[1][1] = "temp3.jpg";
	framepaths[2][0] = "temp4.jpg";
	framepaths[2][1] = "temp5.jpg";
	framepaths[3][0] = "temp6.jpg";
	framepaths[3][1] = "temp7.jpg";
	framepaths[4][0] = "temp9.jpg";
	framepaths[4][1] = "temp10.jpg";

	framepaths[5][0] = "temp12.jpg";
	framepaths[5][1] = "temp13.jpg";
	framepaths[6][0] = "temp14.jpg";
	framepaths[6][1] = "temp15.jpg";
	framepaths[7][0] = "temp16.jpg";
	framepaths[7][1] = "temp17.jpg";
	framepaths[8][0] = "temp18.jpg";
	framepaths[8][1] = "temp19.jpg";
	framepaths[9][0] = "temp20.jpg";
	framepaths[9][1] = "temp21.jpg";

	framepaths[10][0] = "temp22.jpg";
	framepaths[10][1] = "temp23.jpg";
	framepaths[11][0] = "temp25.jpg";
	framepaths[11][1] = "temp26.jpg";
	framepaths[12][0] = "temp28.jpg";
	framepaths[12][1] = "temp27.jpg";
	framepaths[13][0] = "temp30.jpg";
	framepaths[13][1] = "temp31.jpg";
	framepaths[14][0] = "temp34.jpg";
	framepaths[14][1] = "temp33.jpg";

	framepaths[15][0] = "temp35.jpg";
	framepaths[15][1] = "temp36.jpg";
	framepaths[16][0] = "temp38.jpg";
	framepaths[16][1] = "temp37.jpg";
	framepaths[17][0] = "temp39.jpg";
	framepaths[17][1] = "temp40.jpg";
	framepaths[18][0] = "temp42.jpg";
	framepaths[18][1] = "temp41.jpg";
	framepaths[19][0] = "temp43.jpg";
	framepaths[19][1] = "temp44.jpg";
	
	framepaths[20][0] = "temp46.jpg";
	framepaths[20][1] = "temp45.jpg";
	framepaths[21][0] = "temp47.jpg";
	framepaths[21][1] = "temp48.jpg";
	framepaths[22][0] = "temp50.jpg";
	framepaths[22][1] = "temp49.jpg";
	framepaths[23][0] = "temp51.jpg";
	framepaths[23][1] = "temp52.jpg";
	framepaths[24][0] = "temp54.jpg";
	framepaths[24][1] = "temp53.jpg";

	framepaths[25][0] = "temp55.jpg";
	framepaths[25][1] = "temp56.jpg";
	framepaths[26][0] = "temp58.jpg";
	framepaths[26][1] = "temp57.jpg";
	framepaths[27][0] = "temp59.jpg";
	framepaths[27][1] = "temp60.jpg";
	framepaths[28][0] = "temp62.jpg";
	framepaths[28][1] = "temp61.jpg";
	framepaths[29][0] = "temp63.jpg";
	framepaths[29][1] = "temp64.jpg";
	
	framepaths[30][0] = "temp66.jpg";
	framepaths[30][1] = "temp65.jpg";
	framepaths[31][0] = "temp67.jpg";
	framepaths[31][1] = "temp68.jpg";

	/*
	framepaths[32][0] = "temp70.jpg";
	framepaths[32][1] = "temp69.jpg";
	framepaths[33][0] = "temp71.jpg";
	framepaths[33][1] = "temp72.jpg";
	framepaths[34][0] = "temp74.jpg";
	framepaths[34][1] = "temp73.jpg";

	framepaths[35][0] = "temp75.jpg";
	framepaths[35][1] = "temp76.jpg";
	framepaths[36][0] = "temp79.jpg";
	framepaths[36][1] = "temp78.jpg";
	*/

	buildScanFrames();
}

ScanObjectFactory::~ScanObjectFactory(){
	delete laser;
	delete camera;
	delete turntable;
}

void ScanObjectFactory::reset(){
	steps = 0;
	turntable->setRotation(FSMakePoint(0, steps * stepAngle, 0));
}

void ScanObjectFactory::moveOneStep(){
	steps++;
	turntable->setRotation(FSMakePoint(0, steps * stepAngle, 0));
}

Mat ScanObjectFactory::getNoLaserFrame(){
	return frames[steps][1];
}

Mat ScanObjectFactory::getLaserFrame(){
	return frames[steps][0];
}

void ScanObjectFactory::buildScanFrames(){
	for(int i =0; i< FRAME_NUM; i++){
		for(int j = 0; j <2; j++){
			char image_path[100];
			char index[8];	

			memset(image_path, 0, sizeof(image_path));
			strcat(image_path, FRAME_PATH);
			strcat(image_path, framepaths[i][j]);

			frames[i][j] = imread(image_path);
		}
	}
}

void ScanObjectFactory::showScanFrames(){
	cv::namedWindow("laserFrame");
	cv::namedWindow("noLaserFrame");

	for(int i = 0; i < ScanObjectFactory::FRAME_NUM; i++){
		Mat laserFrame = getLaserFrame();
		Mat noLaserFrame = getNoLaserFrame();
		moveOneStep();

		cv::imshow("laserFrame", laserFrame);
		cv::imshow("noLaserFrame", noLaserFrame);
		cv::waitKey(0);
	}

	reset();
}