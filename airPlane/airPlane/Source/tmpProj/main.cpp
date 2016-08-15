/*
 * main.cpp
 *
 *  Created on: Aug 30, 2012
 *      Author: root
 */

#include "main.h"
void PrintBuildInfo() {
	FC2Version fc2Version;
	Utilities::GetLibraryVersion(&fc2Version);

	ostringstream version;
	version << "FlyCapture2 library version: " << fc2Version.major << "."
			<< fc2Version.minor << "." << fc2Version.type << "."
			<< fc2Version.build;
	cout << version.str() << endl;

	ostringstream timeStamp;
	timeStamp << "Application build date: " << __DATE__ << " " << __TIME__;
	cout << timeStamp.str() << endl << endl;
}

void PrintCameraInfo(CameraInfo* pCamInfo) {
	cout << endl;
	cout << "*** CAMERA INFORMATION ***" << endl;
	cout << "Serial number -" << pCamInfo->serialNumber << endl;
	cout << "Camera model - " << pCamInfo->modelName << endl;
	cout << "Camera vendor - " << pCamInfo->vendorName << endl;
	cout << "Sensor - " << pCamInfo->sensorInfo << endl;
	cout << "Resolution - " << pCamInfo->sensorResolution << endl;
	cout << "Firmware version - " << pCamInfo->firmwareVersion << endl;
	cout << "Firmware build time - " << pCamInfo->firmwareBuildTime << endl
			<< endl;

}

void PrintError(Error error) {
	error.PrintErrorTrace();
}
#if 1
int InitCamera(Camera *cam,PGRGuid guid){

	//const int k_numImages = 1;
	//static int imageCnt = 0;
	Error error;
	//Camera cam;

	// Connect to a camera
	error = cam->Connect(&guid);
	if (error != PGRERROR_OK) {
		PrintError(error);
		return -1;
	}

	// Get the camera information
	CameraInfo camInfo;
	error = cam->GetCameraInfo(&camInfo);
	if (error != PGRERROR_OK) {
		PrintError(error);
		return -1;
	}
	PrintCameraInfo(&camInfo);

	// Get the camera configuration
	FC2Config config;
	error = cam->GetConfiguration(&config);
	if (error != PGRERROR_OK) {
		PrintError(error);
		return -1;
	}

	// Set the number of driver buffers used to 10.
	config.numBuffers = 10;

	// Set the camera configuration
	error = cam->SetConfiguration(&config);
	if (error != PGRERROR_OK) {
		PrintError(error);
		return -1;
	}

	return 0;


}

#endif
int RunSingleCamera(Camera *cam,PGRGuid guid) {
	//const int k_numImages = 1;
	static int imageCnt = 0;
	Error error;
	//Camera cam;
#if 0
	// Connect to a camera
	error = cam->Connect(&guid);
	if (error != PGRERROR_OK) {
		PrintError(error);
		return -1;
	}

	// Get the camera information
	CameraInfo camInfo;
	error = cam.GetCameraInfo(&camInfo);
	if (error != PGRERROR_OK) {
		PrintError(error);
		return -1;
	}
	PrintCameraInfo(&camInfo);

	// Get the camera configuration
	FC2Config config;
	error = cam.GetConfiguration(&config);
	if (error != PGRERROR_OK) {
		PrintError(error);
		return -1;
	}

	// Set the number of driver buffers used to 10.
	config.numBuffers = 10;

	// Set the camera configuration
	error = cam.SetConfiguration(&config);
	if (error != PGRERROR_OK) {
		PrintError(error);
		return -1;
	}
#endif
	// Start capturing images
	error = cam->StartCapture();
	if (error != PGRERROR_OK) {
		PrintError(error);
		return -1;
	}

	Image rawImage;
	//for (int imageCnt = 0; imageCnt < k_numImages; imageCnt++) {
	// Retrieve an image
	error = cam->RetrieveBuffer(&rawImage);
	if (error != PGRERROR_OK) {
		PrintError(error);
		//continue;
	}
	++imageCnt;
	cout << "Grabbed image " << imageCnt << endl;

	// Create a converted image
	Image convertedImage;

	// Convert the raw image
	error = rawImage.Convert(PIXEL_FORMAT_RGB8, &convertedImage);
	if (error != PGRERROR_OK) {
		PrintError(error);
		return -1;
	}

	// Create a unique filename

	ostringstream filename;
	filename << imageCnt << ".jpeg";

	// Save the image. If a file format is not passed in, then the file
	// extension is parsed to attempt to determine the file format.
	error = convertedImage.Save(filename.str().c_str());
	if (error != PGRERROR_OK) {
		PrintError(error);
		return -1;
	}
	//}

	// Stop capturing images
	error = cam->StopCapture();
	if (error != PGRERROR_OK) {
		PrintError(error);
		return -1;
	}
#if 0
	// Disconnect the camera
	error = cam->Disconnect();
	if (error != PGRERROR_OK) {
		PrintError(error);
		return -1;
	}
#endif
	return 0;
}

int main(int argc, char *argv[]) {

	//1.init camera
	//init gpio
    jetsonGPIO redLED = gpio165 ;
    // Make the button and led available in user space
    gpioExport(redLED) ;
    gpioSetDirection(redLED,outputPin) ;


	PrintBuildInfo();
	Camera cam;
	Error error;
	// Since this application saves images in the current folder
	// we must ensure that we have permission to write to this folder.
	// If we do not have permission, fail right away.
	FILE* tempFile = fopen("test.txt", "w+");
	if (tempFile == NULL) {
		cout
				<< "Failed to create file in current folder.  Please check permissions."
				<< endl;
		return -1;
	}
	fclose(tempFile);
	remove("test.txt");

	BusManager busMgr;
	unsigned int numCameras;
	error = busMgr.GetNumOfCameras(&numCameras);
	if (error != PGRERROR_OK) {
		PrintError(error);
		return -1;
	}
	cout << "Number of cameras detected: " << numCameras << endl;

    if(numCameras <= 0){
    	while(1){
			gpioSetValue(redLED, off);
			sleep(1);
			gpioSetValue(redLED, on);
			sleep(1);
    	}
    }
	PGRGuid guid;
	error = busMgr.GetCameraFromIndex(0, &guid);
	if (error != PGRERROR_OK) {
		PrintError(error);
		return -1;
	}
	InitCamera(&cam,guid);
	//2.init gps
#if 1   //gps
	char ch;
	int k = 0;
	unsigned char buffer[1024] = {0};
	Serialcom *gpscom = new Serialcom();
	gpscom->setSerialName((char *) "/dev/ttyTHS1");
	if (-1 == gpscom->SerialcomOpen()) {
		cout << "open serialcom error" << endl;
		return 0;
	};
#endif
	//3.init  log
	//4.init inifile
	int interval  = read_profile_int("AIRPLANE", "INTERVAL", 5, "./INTERVAL.ini");

	int task_num  = read_profile_int("AIRPLANE", "TASKNUM", 500, "./INTERVAL.ini");
	//4.1 compare gps
	{
	}
	//4.2 select gps
	int index = 0;
	int tmp_index = 0;
	int tmp_task = 0;
	while (1) {
#if 1
		//get gps
		{
			bzero(buffer, 1024);
			k = 0;
			while (1) {
				if (gpscom->CheckSerialcomData() > 0) {
					gpscom->SerialcomRead(&ch, 1);
					buffer[k++] = ch;
					cout << ch;
					if (ch == '\n') {
						cout << endl;
						break;
					}
				}
			}
			cout << "=================================================="
			<< endl;
			if (memcmp(buffer, "$GPGGA", 6) == 0) {
				NMEA_GPGGA_Analysis(&gpsx, buffer);
			} else if (memcmp(buffer, "$GPRMC", 6) == 0) {
				NMEA_GPRMC_Analysis(&gpsx, buffer);
			}
			if(((gpsx.latitude == 0)||(gpsx.latitude == 0))&&(tmp_index != 0) ){
				++index;
				memcpy(&gpsx,&tmp_gpsx,sizeof(nmea_msg));
			}else{
				++tmp_index;
				index = 0;
				bzero(&tmp_gpsx,sizeof(nmea_msg));
				memcpy(&tmp_gpsx,&gpsx,sizeof(nmea_msg));
			}
			Gps_Msg_Show(index,&tmp_gpsx);
		}
#endif
		//save pic
		{
			RunSingleCamera(&cam,guid);
		}
		++tmp_task;
		if(tmp_task >= task_num ){
			std::cout<< "Task over!"<< std::endl;
			break;	
		}
		sleep(interval);
	}
	//free gps:
	{
	}
	//free camera;
	{
		cout << "Done! Press Enter to exit..." << endl;
		cin.ignore();
	}

	return 0;
}
