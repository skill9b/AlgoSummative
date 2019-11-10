//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#pragma once

#if !defined(__UTILS_H__)
#define __UTILS_H__

// Library Includes
#include <Windows.h>
#include <strstream>
#include <sstream>
#include <string>
#include "resource.h"
#include "Pathfinding.h"


int g_sourceDestinationGrid[10][10] = { {IDC_CHECK1, IDC_CHECK2, IDC_CHECK3, IDC_CHECK4, IDC_CHECK5, IDC_CHECK6, IDC_CHECK7, IDC_CHECK8, IDC_CHECK9, IDC_CHECK10},
										{IDC_CHECK11, IDC_CHECK12, IDC_CHECK13, IDC_CHECK14, IDC_CHECK15, IDC_CHECK16, IDC_CHECK17, IDC_CHECK18, IDC_CHECK19, IDC_CHECK20},
										{IDC_CHECK21, IDC_CHECK22, IDC_CHECK23, IDC_CHECK24, IDC_CHECK25, IDC_CHECK26, IDC_CHECK27, IDC_CHECK28, IDC_CHECK29, IDC_CHECK30},
										{IDC_CHECK31, IDC_CHECK32, IDC_CHECK33, IDC_CHECK34, IDC_CHECK35, IDC_CHECK36, IDC_CHECK37, IDC_CHECK38, IDC_CHECK39, IDC_CHECK40},
										{IDC_CHECK41, IDC_CHECK42, IDC_CHECK43, IDC_CHECK44, IDC_CHECK45, IDC_CHECK46, IDC_CHECK47, IDC_CHECK48, IDC_CHECK49, IDC_CHECK50},
										{IDC_CHECK51, IDC_CHECK52, IDC_CHECK53, IDC_CHECK54, IDC_CHECK55, IDC_CHECK56, IDC_CHECK57, IDC_CHECK58, IDC_CHECK59, IDC_CHECK60},
										{IDC_CHECK61, IDC_CHECK62, IDC_CHECK63, IDC_CHECK64, IDC_CHECK65, IDC_CHECK66, IDC_CHECK67, IDC_CHECK68, IDC_CHECK69, IDC_CHECK70},
										{IDC_CHECK71, IDC_CHECK72, IDC_CHECK73, IDC_CHECK74, IDC_CHECK75, IDC_CHECK76, IDC_CHECK77, IDC_CHECK78, IDC_CHECK79, IDC_CHECK80},
										{IDC_CHECK81, IDC_CHECK82, IDC_CHECK83, IDC_CHECK84, IDC_CHECK85, IDC_CHECK86, IDC_CHECK87, IDC_CHECK88, IDC_CHECK89, IDC_CHECK90},
										{IDC_CHECK91, IDC_CHECK92, IDC_CHECK93, IDC_CHECK94, IDC_CHECK95, IDC_CHECK96, IDC_CHECK97, IDC_CHECK98, IDC_CHECK99, IDC_CHECK100} };

int g_obstacleGrid[10][10] = { {IDC_CHECK101, IDC_CHECK102, IDC_CHECK103, IDC_CHECK104, IDC_CHECK105, IDC_CHECK106, IDC_CHECK107, IDC_CHECK108, IDC_CHECK109, IDC_CHECK110 },
							   {IDC_CHECK111, IDC_CHECK112, IDC_CHECK113, IDC_CHECK114, IDC_CHECK115, IDC_CHECK116, IDC_CHECK117, IDC_CHECK118, IDC_CHECK119, IDC_CHECK120},
							   {IDC_CHECK121, IDC_CHECK122, IDC_CHECK123, IDC_CHECK124, IDC_CHECK125, IDC_CHECK126, IDC_CHECK127, IDC_CHECK128, IDC_CHECK129, IDC_CHECK130},
							   {IDC_CHECK131, IDC_CHECK132, IDC_CHECK133, IDC_CHECK134, IDC_CHECK135, IDC_CHECK136, IDC_CHECK137, IDC_CHECK138, IDC_CHECK139, IDC_CHECK140},
							   {IDC_CHECK141, IDC_CHECK142, IDC_CHECK143, IDC_CHECK144, IDC_CHECK145, IDC_CHECK146, IDC_CHECK147, IDC_CHECK148, IDC_CHECK149, IDC_CHECK150},
							   {IDC_CHECK151, IDC_CHECK152, IDC_CHECK153, IDC_CHECK154, IDC_CHECK155, IDC_CHECK156, IDC_CHECK157, IDC_CHECK158, IDC_CHECK159, IDC_CHECK160},
							   {IDC_CHECK161, IDC_CHECK162, IDC_CHECK163, IDC_CHECK164, IDC_CHECK165, IDC_CHECK166, IDC_CHECK167, IDC_CHECK168, IDC_CHECK169, IDC_CHECK170},
							   {IDC_CHECK171, IDC_CHECK172, IDC_CHECK173, IDC_CHECK174, IDC_CHECK175, IDC_CHECK176, IDC_CHECK177, IDC_CHECK178, IDC_CHECK179, IDC_CHECK180},
							   {IDC_CHECK181, IDC_CHECK182, IDC_CHECK183, IDC_CHECK184, IDC_CHECK185, IDC_CHECK186, IDC_CHECK187, IDC_CHECK188, IDC_CHECK189, IDC_CHECK190},
							   {IDC_CHECK191, IDC_CHECK192, IDC_CHECK193, IDC_CHECK194, IDC_CHECK195, IDC_CHECK196, IDC_CHECK197, IDC_CHECK198, IDC_CHECK199, IDC_CHECK200} };


// Local Includes

// Types

// Constants

// Prototypes

#define VALIDATE(a) if (!a) return (false)


template<typename T> std::string ToString(const T& _value)
{
	std::strstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
}

template<typename T> std::wstring ToWideString(const T& _value)
{
	std::wstringstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
}

int StringToWString(std::wstring& ws, const std::string& s)
{
	std::wstring wsTmp(s.begin(), s.end());

	ws = wsTmp;

	return 0;
}

//Converts wchar_t array to std::string
std::string ToNarrow(const wchar_t* s, char dfault = '?', const std::locale& loc = std::locale())
{
	std::ostringstream stm;

	while (*s != L'\0') {
		stm << std::use_facet< std::ctype<wchar_t> >(loc).narrow(*s++, dfault);
	}
	return stm.str();
}

//Change return value to string
std::string ReadFromEditBox(HWND _hDlg, int _iResourceID)
{
	wchar_t _pcValue[10];
	std::string _return;
	//char _pcValue[3];
	ZeroMemory(_pcValue, 10);
	GetDlgItemText(_hDlg, _iResourceID, _pcValue, 10);

	_return = ToNarrow(_pcValue);

	//Gets rid of the 2nd character
	//_pcValue[1] = _pcValue[2];
	//_return.erase(2);

	return(_return);

}

void WriteToEditBox(HWND _hDlg, int _iResourceID, float _fValue)
{
	std::wstring _strValue = ToWideString(_fValue);
	SetDlgItemText(_hDlg, _iResourceID, _strValue.c_str());
}

void WriteToEditBoxString(HWND _hDlg, int _iResourceID, std::string _strInput)
{
	std::wstring _strValue;
	StringToWString(_strValue, _strInput);
	SetDlgItemText(_hDlg, _iResourceID, _strValue.c_str());
}

float ReadFromEditBoxFloat(HWND _hDlg, int _iResourceID)
{
	wchar_t _pcValue[10];
	ZeroMemory(_pcValue, 10);
	GetDlgItemText(_hDlg, _iResourceID, _pcValue, 10);
	if (_pcValue[0] == 0)
	{
		return 0.0f;
	}
	else
	{
		return static_cast<float>(_wtof(_pcValue));
	}
}

void CheckSourceDestinationGrid(HWND _hDlg, int _iSourceDest[4]) {
	int g_counter = 0;
	bool bSourceSet = false;

	// loop through every check box:
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			// if (SendDlgItemMessage(_hDlg, g_sourceDestinationGrid[i], BM_GETCHECK, 0, 0))
			if (IsDlgButtonChecked(_hDlg, g_sourceDestinationGrid[i][j]) == BST_CHECKED)
			{
				CheckDlgButton(_hDlg, g_obstacleGrid[i][j], BST_INDETERMINATE); 
				g_counter++;
			}
		}
	}

	if (g_counter == 2) {
		// Set everything but the checked boxes to indeterminate & set sourceXY and goalXY
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (IsDlgButtonChecked(_hDlg, g_sourceDestinationGrid[i][j]) == BST_CHECKED)
				{
					if (bSourceSet == false) {
						_iSourceDest[0] = i;
						_iSourceDest[1] = j;
						bSourceSet = true;
					}
					else
					{
						_iSourceDest[2] = i;
						_iSourceDest[3] = j;
					}
					continue;
				}
				else
				{
					// if unchecked
					CheckDlgButton(_hDlg, g_sourceDestinationGrid[i][j], BST_INDETERMINATE);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (IsDlgButtonChecked(_hDlg, g_sourceDestinationGrid[i][j]) == BST_CHECKED)
				{
					_iSourceDest[0] = -1;
					_iSourceDest[1] = -1;
					_iSourceDest[2] = -1;
					_iSourceDest[3] = -1;
					bSourceSet = false;
				}
				else
				{
					// if unchecked
					CheckDlgButton(_hDlg, g_sourceDestinationGrid[i][j], BST_UNCHECKED);
					CheckDlgButton(_hDlg, g_obstacleGrid[i][j], BST_UNCHECKED);
				}
			}
		}
	}
}


void ReadObstacleGrid(HWND _hDlg, Pathfinding* path) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (IsDlgButtonChecked(_hDlg, g_obstacleGrid[i][j]) == BST_CHECKED)
			{
				path->AddObstacle(i, j);
			}
		}
	}
}

//Backup
/*template<typename T>
std::string ToString(const T& _value)
{
	std::strstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
}

template<typename T>
std::wstring ToWideString(const T& _value)
{
	std::wstringstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
}

float ReadFromEditBox(HWND _hDlg, int _iResourceID)
{
	wchar_t _pcValue[10];
	ZeroMemory(_pcValue, 10);
	GetDlgItemText(_hDlg, _iResourceID, _pcValue, 10);
	if (_pcValue[0] == 0)
	{
		return 0.0f;
	}
	else
	{
		return static_cast<float>(_wtof(_pcValue));
	}
}

void WriteToEditBox(HWND _hDlg, int _iResourceID, float _fValue)
{
	std::wstring _strValue = ToWideString(_fValue);
	SetDlgItemText(_hDlg, _iResourceID, _strValue.c_str());
}*/




#endif    // __UTILS_H__


