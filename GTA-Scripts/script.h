/*
	Author: Abrar Anwar Qureshi
*/
#pragma once
#include "..\dependencies\inc\natives.h"
#include "..\dependencies\inc\types.h"
#include "..\dependencies\inc\enums.h"
#include "..\dependencies\inc\main.h"
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <atlstr.h>
#include <atlimage.h>

#pragma comment(lib, "gdiplus.lib")

#define WIDEN2(x) L ## x
#define WIDEN(x) WIDEN2(x)
#define __WFILE__ WIDEN(__FILE__)
#define HRCHECK(__expr) {hr=(__expr);if(FAILED(hr)){wprintf(L"FAILURE 0x%08X (%i)\n\tline: %u file: '%s'\n\texpr: '" WIDEN(#__expr) L"'\n",hr, hr, __LINE__,__WFILE__);goto cleanup;}}
#define RELEASE(__p) {if(__p!=nullptr){__p->Release();__p=nullptr;}}

#define PI 3.14159265359
#define DIRECTX 1
#define GDI 2


/*********************************************************************/
/******************************** STRUCTS **************************/
/*********************************************************************/

struct Quaternion {
	float x = -1, y = -1, z = -1, w = -1;
};

// an element in trajectory
struct Point {
	Vector3 player_coord;
	Vector3 cam_rot;
	Vector3 cam_coord;
};

// struct stores all necessary variables for GDI method
struct GDIScreenCaptureWorker
{
	int nScreenWidth;
	int nScreenHeight;
	HWND hDesktopWnd;
	HDC hDesktopDC;
	HDC hCaptureDC;
	HBITMAP hCaptureBitmap;

};

/*********************************************************************/
/******************************** FUNCTIONS **************************/
/*********************************************************************/

/******************************** Functions for screen capture ********************************/
void GDIInitScreenCapture(); // initialize screen capture object
void GDIReleaseScreenCapture(); // release screen capture object
bool GDITakeScreenshots(std::string file_name); // capture screen

/******************************** Functions for listening keyboard ********************************/
bool startMapping(); // listen if users open main menu
bool endMapping(); // listen if user stops mapping

/********************************Function for live dataset mapping**********************************/
void liveMapping();  // takes screenshots for live mapping purposes

/******************************** Functions that deal with camera ********************************/
Quaternion rotationRPY(float roll, float pitch, float yaw); // get rotation in quaternion from roll, ptich, yaw

/******************************** Functions that display notifications ********************************/
void setNotificationText(std::string str, DWORD time = 1500, bool isGxtEntry = false); // set notification text
void updateNotificationText(); // set text style, position, font

/******************************** Functions to manipulate file stream ********************************/
bool isFileExist(std::string file_text); // check if file exists

/******************************** Other functions ****************************************************/
int updateFeatures(); // Update neccessary features within game, should be called in every frames
void ScriptMain(); // Main functions