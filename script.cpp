/*
	Author: Abrar Anwar Qureshi
*/


#include "script.h"
#include "keyboard.h"
#include <windows.h>
#include <iostream>
#include <string> 

using namespace std;


/****************************************************************************************/
/****************************************** VARIABLES ***********************************/
/****************************************************************************************/


// notification text
std::string _notification_text;
DWORD _notification_text_draw_ticks_max;
bool _notification_text_gxt_entry;

// camera parameters
int _order_rot = 2; // rotation order

// The output file names  
std::string _dataset_live = "\\\\10.3.93.221\\gta_live\\images";
std::string _pose_file_text = "\\\\10.3.93.221\\gta_live\\pose.txt";

std::ofstream _ofile; // stream to write output files

GDIScreenCaptureWorker _screen_capture_worker; // variable for screen capture


/****************************************************************************************/
/******************************** IMPLEMENTATIONS OF FUNCTIONS **************************/
/****************************************************************************************/


void setNotificationText(std::string str, DWORD time /*= 1500*/, bool isGxtEntry /*= false*/)
{
	_notification_text = str;
	_notification_text_draw_ticks_max = GetTickCount() + time;
	_notification_text_gxt_entry = isGxtEntry;
}

void GDIInitScreenCapture()
{
	_screen_capture_worker.nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	_screen_capture_worker.nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	_screen_capture_worker.hDesktopWnd = GetDesktopWindow();
	_screen_capture_worker.hDesktopDC = GetDC(_screen_capture_worker.hDesktopWnd);
	_screen_capture_worker.hCaptureDC = CreateCompatibleDC(_screen_capture_worker.hDesktopDC);

	_screen_capture_worker.hCaptureBitmap = CreateCompatibleBitmap(_screen_capture_worker.hDesktopDC,
		_screen_capture_worker.nScreenWidth, _screen_capture_worker.nScreenHeight);

	SelectObject(_screen_capture_worker.hCaptureDC, _screen_capture_worker.hCaptureBitmap);
}

void GDIReleaseScreenCapture()
{
	ReleaseDC(_screen_capture_worker.hDesktopWnd, _screen_capture_worker.hDesktopDC);
	DeleteDC(_screen_capture_worker.hCaptureDC);
	DeleteObject(_screen_capture_worker.hCaptureBitmap);
}

bool GDITakeScreenshots(std::string file_name)
{
	BitBlt(_screen_capture_worker.hCaptureDC, 0, 0,
		_screen_capture_worker.nScreenWidth, _screen_capture_worker.nScreenHeight,
		_screen_capture_worker.hDesktopDC, 0, 0, SRCCOPY | CAPTUREBLT);

	CImage image;
	image.Attach(_screen_capture_worker.hCaptureBitmap);
	image.Save(file_name.c_str(), Gdiplus::ImageFormatJPEG);

	return true;
}

bool startMapping()
{
	return IsKeyJustUp(VK_F5);
}

bool endMapping()
{
	return IsKeyJustUp(VK_END);
}

Quaternion rotationRPY(float roll, float pitch, float yaw)
{
	Quaternion result;

	roll = roll * PI / 180;
	pitch = pitch * PI / 180;
	yaw = yaw * PI / 180;

	float halfYaw = yaw * 0.5f;
	float sinYaw = (float)(sin((double)(halfYaw)));
	float cosYaw = (float)(cos((double)(halfYaw)));
	float halfPitch = pitch * 0.5f;
	float sinPitch = (float)(sin((double)(halfPitch)));
	float cosPitch = (float)(cos((double)(halfPitch)));
	float halfRoll = roll * 0.5f;
	float sinRoll = (float)(sin((double)(halfRoll)));
	float cosRoll = (float)(cos((double)(halfRoll)));

	result.x = (cosRoll * sinPitch * cosYaw) + (sinRoll * cosPitch * sinYaw);
	result.y = (sinRoll * cosPitch * cosYaw) - (cosRoll * sinPitch * sinYaw);
	result.z = (cosRoll * cosPitch * sinYaw) - (sinRoll * sinPitch * cosYaw);
	result.w = (cosRoll * cosPitch * cosYaw) + (sinRoll * sinPitch * sinYaw);

	return result;
}

void liveMapping()
{
	setNotificationText("Live Mapping Started");

	GDIInitScreenCapture();
	_ofile.open(_pose_file_text.c_str(), std::ios_base::app); //  open pose file

	int i = 0;
	WAIT(100);

	while (TRUE)
	{
		std::string im_name;
		Vector3 gameplay_cam_coord = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 gameplay_cam_rot = CAM::GET_GAMEPLAY_CAM_ROT(_order_rot);
		//Quaternion gameplay_cam_rotq = rotationRPY(gameplay_cam_rot.y, gameplay_cam_rot.x, gameplay_cam_rot.z);

		im_name = _dataset_live + "/" + std::to_string(i) + ".jpg";

		GDITakeScreenshots(im_name); // capture screen

		_ofile << im_name << " ";
		_ofile << gameplay_cam_coord.x << " " << gameplay_cam_coord.y << " " << gameplay_cam_coord.z << " ";           //  save translation pose to file
		//_ofile << gameplay_cam_rotq.x << " " << gameplay_cam_rotq.y << " " << gameplay_cam_rotq.z << " " << gameplay_cam_rotq.w << " " << std::endl;    //  save quaternion rotation pose to file
		_ofile << gameplay_cam_rot.x << " " << gameplay_cam_rot.y << " " << gameplay_cam_rot.z << " " << std::endl;    //  save rpy rotation pose to file

		i++;

		if (endMapping())
		{
			setNotificationText("Live Mapping Ended");
			_ofile.close();
			GDIReleaseScreenCapture();
			WAIT(100);
			break;
		}

	}

	return;
}

void updateNotificationText()
{
	if (GetTickCount() < _notification_text_draw_ticks_max)
	{
		UI::SET_TEXT_FONT(0);
		UI::SET_TEXT_SCALE(0.55, 0.55);
		UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		UI::SET_TEXT_WRAP(0.0, 1.0);
		UI::SET_TEXT_CENTRE(1);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
		if (_notification_text_gxt_entry)
		{
			UI::_SET_TEXT_ENTRY((char*)_notification_text.c_str());
		}
		else
		{
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING((char*)_notification_text.c_str());
		}
		UI::_DRAW_TEXT(0.5, 0.5);
	}
}


int updateFeatures()
{
	updateNotificationText();
	return 0;
}

void main()
{
	HANDLE livMap = NULL;

	while (true)
	{

		if (startMapping())
		{
			livMap = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)liveMapping, NULL, 0, NULL);
		}

		updateFeatures();
		WAIT(10);

	}

}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}