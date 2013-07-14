#include <iostream>
#include "FSVision.h"
#include "ScanObjectFactory.h"
#include "FSSurfaceMesh.h"
#include "FSModel.h"

using namespace std;

void main(){
	ScanObjectFactory factory;

	int dpiVertical = 1;
	FSFloat lowerLimit = 0.2f;
	FSFloat th = 70;
	FSLaser* laser = factory.getLaser();;
	FSCamera* camera = factory.getCamera();  
	FSTurnTable* turntable = factory.getTurnTable();

	camera->test();

	FSPointCloud* pointCloud = new FSPointCloud(); 
	FSSurfaceMesh* surfaceMesh = new FSSurfaceMesh();
    FSModel* model = new FSModel(pointCloud, surfaceMesh);

	for(int i = 0; i < ScanObjectFactory::FRAME_NUM; i++){
		cout << "Process " << i << " of " << ScanObjectFactory::FRAME_NUM << endl;
		Mat laserFrame = factory.getLaserFrame();
		Mat noLaserFrame = factory.getNoLaserFrame();
		FSVision::putPointsFromFrameToCloud(noLaserFrame, 
									laserFrame, 
									pointCloud, 
									laser, 
									camera, 
									turntable, 
									dpiVertical, 
									lowerLimit, 
									th);

		factory.moveOneStep();
	}

	pointCloud->saveToPLYFile("C:/simon/study/opencv/DesktopScanner/output/xx.ply");
	surfaceMesh->saveToPLYFile("C:/simon/study/opencv/DesktopScanner/output/xxx.ply");
	cout << "Hello World, Desktop Scanner!" << endl;
}

