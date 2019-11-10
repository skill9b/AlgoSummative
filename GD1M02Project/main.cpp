//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: main.cpp
// Description	: This programs runs dialogues for BFS, DFS and the A* algorithm.
// Author		: Jay Patel, Vivian Xu
// Mail			: jay.pat8646@mediadesign.school.nz ,vivian.xu9501@mediadesign.school.nz
//


#define WIN32_LEAN_AND_MEAN

#include <windows.h>   // Include all the windows headers.
#include <windowsx.h>  // Include useful macros.
#include <string>
#include <sstream>

#include "utils.h"
#include "resource.h"
#include "cGraph.h"
#include "Pathfinding.h"
#include "Node.h"

#define WINDOW_CLASS_NAME L"WINCLASS1"
#define BFSDFS_BUTTON_TEXT L"BFS & DFS"
#define ASTAR_BUTTON_TEXT L"A STAR"

HMENU g_hMenu;
HWND g_hDlgBFSDFS, g_hDlgAStar;		// Dialog handles
HWND BfsDfsButton, AStarButton;

int iSourceDest[4] = { -1, -1, -1, -1 };
bool bPathCalculated = false;


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

			RECT instructionRect = { 80,20,500,50};
			LPRECT pInstructionRect = &instructionRect;

			// Instruction text
			DrawText(
				hdc,
				L"Select one of the following:",
				28,
				pInstructionRect,
				DT_CENTER
			);

			EndPaint(_hwnd, &ps);

			// Return Success.
			return (0);
		}
		break;
		case WM_COMMAND:
		{
			switch (LOWORD(_wparam))
			{
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
	cGraph* Graph = new cGraph(int(ReadFromEditBoxFloat(_hwnd, IDC_EDIT1))); //Makes graph with amount of nodes read from first edit box

	int iAmountOfEdges = (int(ReadFromEditBoxFloat(_hwnd, IDC_EDIT22))); //Amount of loop

	int iEdges[20] = { IDC_EDIT2, IDC_EDIT3, IDC_EDIT4, IDC_EDIT5, IDC_EDIT6, IDC_EDIT7, IDC_EDIT8, IDC_EDIT9, IDC_EDIT10, IDC_EDIT11,
					   IDC_EDIT12, IDC_EDIT13, IDC_EDIT14, IDC_EDIT15, IDC_EDIT16, IDC_EDIT17, IDC_EDIT18, IDC_EDIT19, IDC_EDIT20, IDC_EDIT21 };

	std::string strBFSOutput;
	std::string strDFSOutput;

	static float _value;
	switch (_msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{
		case IDC_BUTTON6:	// BFS
		{
			strBFSOutput = "";
			std::string strEdges;
			int iFirst = 0, iSecond = 0;
			int iCheck = (int(ReadFromEditBoxFloat(_hwnd, IDC_EDIT1)));
			Graph->resetVertices(int(ReadFromEditBoxFloat(_hwnd, IDC_EDIT1)));

			if ((iCheck == 0))
			{
				MessageBox(_hwnd, ToWideString("Invalid amount of nodes").c_str(), L"Alert", MB_OK);
				break;
			}
			
			iAmountOfEdges = (int(ReadFromEditBoxFloat(_hwnd, IDC_EDIT22))); //Amount of loop
			if ((iAmountOfEdges >= 21) || (iAmountOfEdges <= 0)) //If user inputs more than 20 for amount of edges 
			{
				MessageBox(_hwnd, ToWideString("Invalid amount of edges").c_str(), L"Alert", MB_OK);
			//for (int i = 0; i < 20; i++)
				//{
				//	WriteToEditBoxString(_hwnd, iEdges[i], "ERROR");
				//}
				//WriteToEditBoxString(_hwnd, IDC_EDIT22, "ERROR");
				break;
			}

			
			//Check boxes to make sure they have correct formatting "1,2" number colon number here
			int iColons = 0;
			for (int i = 0; i < iAmountOfEdges; i++)
			{
				strEdges = ReadFromEditBox(_hwnd, iEdges[i]);
				
				for (int i = 0; i < strEdges.size(); i++) //Use j
				{
					if (strEdges[i] == 44)
					{
						iColons++;
					}
				}
				
			}
			if (iColons == 0)
			{
				MessageBox(_hwnd, ToWideString("Mising colon/s").c_str(), L"Alert", MB_OK);
				break;
			}

			//Reading edges into graph
			for (int i = 0; i < iAmountOfEdges; i++)
			{
				//if (i < iAmountOfEdges)
				//{
					strEdges = ReadFromEditBox(_hwnd, iEdges[i]);
					stringstream ss1(strEdges);

					//iFirst = std::atoi(&strEdges[0]);
					//iSecond = std::atoi(&strEdges[2]);

					std::string value;

					int iCount = 0;
					while (getline(ss1, value, ','))
					{
						if (iCount == 0)
						{
							iFirst = std::stoi(value);
							iCount++;
						}
						else if (iCount == 1)
						{
							iSecond = std::stoi(value);
							iCount++;
						}
					}
					Graph->addEdge(iFirst, iSecond);
				//}
				//else
				//{
				//	WriteToEditBoxString(_hwnd, iEdges[i], " ");
				//}
			}
			strBFSOutput = Graph->BFS(0);
			WriteToEditBoxString(_hwnd, IDC_EDIT24, strBFSOutput);
			Graph->clearStrings();
			break;
		}

		case IDC_BUTTON7: //DFS button
		{
			strDFSOutput = "";
			Graph->resetVertices(int(ReadFromEditBoxFloat(_hwnd, IDC_EDIT1)));
			int iCheck = (int(ReadFromEditBoxFloat(_hwnd, IDC_EDIT1)));
			std::string strEdges;
			int iFirst, iSecond;

			if ((iCheck == 0))
			{
				MessageBox(_hwnd, ToWideString("Invalid amount of nodes").c_str(), L"Alert", MB_OK);
				break;
			}

			iAmountOfEdges = (int(ReadFromEditBoxFloat(_hwnd, IDC_EDIT22))); //Amount of loop
			if ((iAmountOfEdges >= 21) || (iAmountOfEdges <= 0)) //If user inputs more than 20 for amount of edges 
			{
			MessageBox(_hwnd, ToWideString("Invalid amount of edges").c_str(), L"Alert", MB_OK);
			//for (int i = 0; i < 20; i++)
				//{
				//	WriteToEditBoxString(_hwnd, iEdges[i], "ERROR");
				//}
				//WriteToEditBoxString(_hwnd, IDC_EDIT22, "ERROR");
			break;
			}

			//Check boxes to make sure they have correct formatting "1,2" number colon number here
			int iColons = 0;
			for (int i = 0; i < iAmountOfEdges; i++)
			{
				strEdges = ReadFromEditBox(_hwnd, iEdges[i]);

				for (int i = 0; i < strEdges.size(); i++)
				{
					if (strEdges[i] == 44)
					{
						iColons++;
					}
				}

			}
			if (iColons == 0)
			{
				MessageBox(_hwnd, ToWideString("Missing colon/s").c_str(), L"Alert", MB_OK);
				break;
			}


			for (int i = 0; i < 20; i++)
			{
				if (i < iAmountOfEdges)
				{
					strEdges = ReadFromEditBox(_hwnd, iEdges[i]);
					stringstream ss1(strEdges);

					iFirst = std::atoi(&strEdges[0]);
					iSecond = std::atoi(&strEdges[2]);

					std::string value;

					int iCount = 0;
					while (getline(ss1, value, ','))
					{
						if (iCount == 0)
						{
							iFirst = std::stoi(value);
							iCount++;
						}
						else if (iCount == 1)
						{
							iSecond = std::stoi(value);
							iCount++;
						}
					}
					Graph->addEdge(iFirst, iSecond);
				}
				else
				{
					WriteToEditBoxString(_hwnd, iEdges[i], " ");
				}
			}



			strDFSOutput = Graph->DFS(0);
			WriteToEditBoxString(_hwnd, IDC_EDIT25, strDFSOutput);
			Graph->clearStrings();
			break;
		}
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
	Graph->clearStrings();
	return FALSE;
}

BOOL CALLBACK AStarDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	if (bPathCalculated == false) {
		// Constantly check Source & Destination grid and update Obstacle grid until path calculated
		CheckSourceDestinationGrid(_hwnd, iSourceDest);
	}

	switch (_msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{
			case IDC_BUTTON1:	// Compute A* Path
			{
				Pathfinding* path = new Pathfinding(iSourceDest[0], iSourceDest[1], iSourceDest[2], iSourceDest[3]);

				ReadObstacleGrid(_hwnd, path);

				path->FindPath();
				Node* endNode = path->GetEndNode();
					

				// Display grid output...
				if (endNode == nullptr)
				{
					MessageBox(_hwnd, ToWideString("There is no valid path!").c_str(), L"Alert", MB_OK);
				}
				else
				{
					bPathCalculated = true;

					Node* currentNode = endNode;
					std::set<Node*>* obstacleList = path->GetObstacleList();
					std::set<Node*>::iterator it = obstacleList->begin();

					// Set all Obstacle boxes as grey
					while (it != obstacleList->end()) {
						CheckDlgButton(_hwnd, g_obstacleGrid[(*it)->GetX()][(*it)->GetY()], BST_INDETERMINATE);
						it++;
					}

					// Set Source and Destination as ticked
					 CheckDlgButton(_hwnd, g_obstacleGrid[iSourceDest[0]][iSourceDest[1]], BST_CHECKED);
					 CheckDlgButton(_hwnd, g_obstacleGrid[iSourceDest[2]][iSourceDest[3]], BST_CHECKED);

					// Check all path boxes 
					while (currentNode->GetPreviousNode() != nullptr) {
						CheckDlgButton(_hwnd, g_obstacleGrid[currentNode->GetX()][currentNode->GetY()], BST_CHECKED);
						currentNode = currentNode->GetPreviousNode();
					}

				}
				break;
			}
			case IDC_BUTTON2:	// Clears all grids, resets A* algorithm
			{
				bPathCalculated = false;

				for (int i = 0; i < 4; i++) {
					iSourceDest[i] = 0;
				}

				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						CheckDlgButton(_hwnd, g_sourceDestinationGrid[i][j], BST_UNCHECKED);
						CheckDlgButton(_hwnd, g_obstacleGrid[i][j], BST_UNCHECKED);
					}
				}
				break;
			}

		}
		break;
	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);

		// Clears all data
		bPathCalculated = false;

		for (int i = 0; i < 4; i++) {
			iSourceDest[i] = 0;
		}

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				CheckDlgButton(_hwnd, g_sourceDestinationGrid[i][j], BST_UNCHECKED);
				CheckDlgButton(_hwnd, g_obstacleGrid[i][j], BST_UNCHECKED);
			}
		}
		break;

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
		static_cast<HBRUSH>(GetStockObject( LTGRAY_BRUSH ));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register the window class
	if (!RegisterClassEx(&winclass))
	{
		return (0);
	}

	// Create the window
	hwnd = CreateWindowEx(NULL, // Extended style.
		WINDOW_CLASS_NAME,      // Class.
		L"AlgoSummative Final Project || Jay & Vivian ",   // Title.
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		420, 200,                    // Initial x,y.
		600, 200,                // Initial width, height.
		NULL,                   // Handle to parent.
		g_hMenu,                   // Handle to menu.
		_hInstance,             // Instance of this application.
		NULL);                  // Extra creation parameters.

	if (!(hwnd))
	{
		return (0);
	}

	BfsDfsButton = CreateWindowEx(
		0,                            // Extended possibilities for variation
		L"BUTTON",                    // Class name
		BFSDFS_BUTTON_TEXT,            // Button text
		WS_CHILD | WS_VISIBLE,        // Child to the window, visible
		240,                            // x co-ordinate
		50,                            // y co-ordinate        
		100,                            // Width
		30,                            // Height
		hwnd,                        // Button is child to our window
		(HMENU)BFSDFS_BUTTON,
		NULL,                        // Program instance handler
		NULL                        // No Window creation data
	);

	AStarButton = CreateWindowEx(
		0,
		L"BUTTON",
		ASTAR_BUTTON_TEXT,
		WS_CHILD | WS_VISIBLE,
		240,
		85,
		100,
		30,
		hwnd,
		(HMENU)ASTAR_BUTTON,
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

/*
for (int i = 0; i < 20; i++)
{
	if (i < iAmountOfEdges)
	{
		strEdges = ReadFromEditBox(_hwnd, iEdges[i]);
		iFirst = std::atoi(&strEdges[0]);
		iSecond = std::atoi(&strEdges[2]);
		Graph->addEdge(iFirst, iSecond);
	}
	else
	{
		WriteToEditBoxString(_hwnd, iEdges[i], "");
	}
}*/

