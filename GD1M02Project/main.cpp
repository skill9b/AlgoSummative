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
// Author		: Jay Patel, Vivian Xu
// Mail			: ????????????? ,vivian.xu9501@mediadesign.school.nz
//


#define WIN32_LEAN_AND_MEAN

#include <windows.h>   // Include all the windows headers.
#include <windowsx.h>  // Include useful macros.

#include "utils.h"
#include "resource.h"

#define WINDOW_CLASS_NAME L"WINCLASS1"
#define BFSDFS_BUTTON_TEXT L"BFS & DFS"
#define ASTAR_BUTTON_TEXT L"A STAR"

HMENU g_hMenu;
HWND g_hDlgBFSDFS, g_hDlgAStar;		// Dialog handles
HWND BfsDfsButton, AStarButton;

LRESULT CALLBACK WindowProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	// This is the main message handler of the system.
	PAINTSTRUCT ps; // Used in WM_PAINT.
	HDC hdc;        // Handle to a device context.

	switch (_msg)
	{
		case WM_CREATE:
		{
			// Do initialization stuff here.

			// Return Success.
			return (0);
		}
		break;
		case WM_PAINT:
		{
			// Simply validate the window.
			hdc = BeginPaint(_hwnd, &ps);

			// You would do all your painting here...

			EndPaint(_hwnd, &ps);

			// Return Success.
			return (0);
		}
		break;
		case WM_COMMAND:
		{
			switch (LOWORD(_wparam))
			{
				case ID_EXIT:
				{
					PostQuitMessage(0);
					break;
				}
				case ID_BFSDFS:
				{
					ShowWindow(g_hDlgBFSDFS, SW_SHOWNORMAL);
					break;
				}
				case ID_ASTAR:
				{
					ShowWindow(g_hDlgAStar, SW_SHOWNORMAL);
					break;
				}
				case BFSDFS_BUTTON:
				{
					ShowWindow(g_hDlgBFSDFS, SW_SHOWNORMAL);
					break;
				}
				case ASTAR_BUTTON:
				{
					ShowWindow(g_hDlgAStar, SW_SHOWNORMAL);
					break;
				}
				default:
					break;
			}
		}
		return(0);
		break;
		case WM_DESTROY:
		{
			// Kill the application, this sends a WM_QUIT message.
			PostQuitMessage(0);

			// Return success.
			return (0);
		}
		break;

		default:
			break;
	} // End switch.
	  // Process any messages that we did not take care of...

	return (DefWindowProc(_hwnd, _msg, _wparam, _lparam));
}

BOOL CALLBACK BfsDfsDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	static float _value;
	switch (_msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{
		/*case IDC_EDIT_A11:
		{
			_value = ReadFromEditBox(_hwnd, IDC_EDIT_A11);
			break;
		}*/
		default:
			break;
		}
		return TRUE;
		break;
	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
	}
	return FALSE;
}

BOOL CALLBACK AStarDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{

	switch (_msg)
	{
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
	}
	return FALSE;
}


int WINAPI WinMain(HINSTANCE _hInstance,
	HINSTANCE _hPrevInstance,
	LPSTR _lpCmdLine,
	int _nCmdShow)
{
	WNDCLASSEX winclass; // This will hold the class we create.
	HWND hwnd;           // Generic window handle.
	MSG msg;             // Generic message.

						 // First fill in the window class structure.
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground =
		static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register the window class
	if (!RegisterClassEx(&winclass))
	{
		return (0);
	}

	//Load the Menu
	g_hMenu = LoadMenu(_hInstance, MAKEINTRESOURCE(IDR_MENU));

	// Create the window
	hwnd = CreateWindowEx(NULL, // Extended style.
		WINDOW_CLASS_NAME,      // Class.
		L"Your Basic Window",   // Title.
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		350, 200,                    // Initial x,y.
		400, 500,                // Initial width, height.
		NULL,                   // Handle to parent.
		g_hMenu,                   // Handle to menu.
		_hInstance,             // Instance of this application.
		NULL);                  // Extra creation parameters.

	if (!(hwnd))
	{
		return (0);
	}

	BfsDfsButton = CreateWindowEx(
		0,							// Extended possibilities for variation
		L"BUTTON",					// Class name
		BFSDFS_BUTTON_TEXT,			// Button text
		WS_CHILD | WS_VISIBLE,		// Child to the window, visible
		55,							// x co-ordinate
		55,							// y co-ordinate		
		80,							// Width
		18,							// Height
		hwnd,						// Button is child to our window
		(HMENU)BfsDfsButton,		
		NULL,						// Program instance handler
		NULL						// No Window creation data
	);

	AStarButton = CreateWindowEx(
		0,
		L"BUTTON",
		ASTAR_BUTTON_TEXT,
		WS_CHILD | WS_VISIBLE,
		55,
		75,
		80,
		18,
		hwnd,
		(HMENU)AStarButton,
		NULL,
		NULL
	);

	//Create the modeless dialog boxes for the calculators
	//Matrix Calculator
	g_hDlgBFSDFS = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogBFSDFS), hwnd, (DLGPROC)BfsDfsDlgProc);
	g_hDlgAStar = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogAStar), hwnd, (DLGPROC)AStarDlgProc);

	// Enter main event loop
	while (true)
	{
		// Test if there is a message in queue, if so get it.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Test if this is a quit.
			if (msg.message == WM_QUIT)
			{
				break;
			}

			if ((g_hDlgBFSDFS == 0 && g_hDlgAStar == 0) ||
				(!IsDialogMessage(g_hDlgBFSDFS, &msg) && !IsDialogMessage(g_hDlgAStar, &msg)))
			{
				// Translate any accelerator keys.
				TranslateMessage(&msg);
				// Send the message to the window proc.
				DispatchMessage(&msg);
			}
		}

	}

	// Return to Windows like this...
	return (static_cast<int>(msg.wParam));
}


