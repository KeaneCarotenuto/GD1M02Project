//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//


#define WIN32_LEAN_AND_MEAN

#include <windows.h>   // Include all the windows headers.
#include <windowsx.h>  // Include useful macros.

#include "utils.h"
#include "resource.h"

#define WINDOW_CLASS_NAME L"WINCLASS1"

HMENU g_hMenu;
HWND g_hDlgMatrix, g_hDlgTransformation, g_hDlgGaussian, g_hDlgQuaternion, g_hDlgSLERP;

void ReadMatrices(HWND _hwnd);
void WriteMatrices(HWND _hwnd);
void ClearMatrices(HWND _hwnd);

void AddMatrix(HWND _hwnd);
void SetToIdentity(HWND _hwnd, bool isA);

int matrixA[4][4], matrixB[4][4], matrixR[4][4];
int matrixAID[4][4] = {
	{IDC_EDIT_A11,IDC_EDIT_A12,IDC_EDIT_A13,IDC_EDIT_A14},
	{IDC_EDIT_A21,IDC_EDIT_A22,IDC_EDIT_A23,IDC_EDIT_A24},
	{IDC_EDIT_A31,IDC_EDIT_A32,IDC_EDIT_A33,IDC_EDIT_A34},
	{IDC_EDIT_A41,IDC_EDIT_A42,IDC_EDIT_A43,IDC_EDIT_A44}
};
int matrixBID[4][4] = {
	{IDC_EDIT_B11,IDC_EDIT_B12,IDC_EDIT_B13,IDC_EDIT_B14},
	{IDC_EDIT_B21,IDC_EDIT_B22,IDC_EDIT_B23,IDC_EDIT_B24},
	{IDC_EDIT_B31,IDC_EDIT_B32,IDC_EDIT_B33,IDC_EDIT_B34},
	{IDC_EDIT_B41,IDC_EDIT_B42,IDC_EDIT_B43,IDC_EDIT_B44}
};
int matrixRID[4][4] = {
	{IDC_EDIT_R11,IDC_EDIT_R12,IDC_EDIT_R13,IDC_EDIT_R14},
	{IDC_EDIT_R21,IDC_EDIT_R22,IDC_EDIT_R23,IDC_EDIT_R24},
	{IDC_EDIT_R31,IDC_EDIT_R32,IDC_EDIT_R33,IDC_EDIT_R34},
	{IDC_EDIT_R41,IDC_EDIT_R42,IDC_EDIT_R43,IDC_EDIT_R44}
};


void GameLoop()
{
	//One frame of game logic occurs here...
}

LRESULT CALLBACK WindowProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	// This is the main message handler of the system.
	PAINTSTRUCT ps; // Used in WM_PAINT.
	HDC hdc;        // Handle to a device context.

					// What is the message?
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
		case ID_CALCULATOR_MATRIX:
		{
			ShowWindow(g_hDlgMatrix, SW_SHOWNORMAL);
			break;
		}
		case ID_CALCULATOR_TRANSFORMATION:
		{
			ShowWindow(g_hDlgTransformation, SW_SHOWNORMAL);
			break;

		}
		//open the matrix dialog
		case ID_CALCULATOR_GAUSSIAN:
		{
			ShowWindow(g_hDlgGaussian, SW_SHOWNORMAL);
			break;
		}
		//open the gaussian dialog
		case ID_CALCULATOR_QUATERNION:
		{
			ShowWindow(g_hDlgQuaternion, SW_SHOWNORMAL);
			break;
		}
		//open the quaternion dialog
		case ID_CALCULATOR_SLERP:
		{
			ShowWindow(g_hDlgSLERP, SW_SHOWNORMAL);
			break;
		}
		default:
			break;
		}
		return(0);
	}
	break;

	case WM_DESTROY:
	{
		// Kill the application, this sends a WM_QUIT message.
		PostQuitMessage(0);

		// Return success.
		return (0);
	}
	break;

	default:break;
	} // End switch.

	  // Process any messages that we did not take care of...

	return (DefWindowProc(_hwnd, _msg, _wparam, _lparam));
}

BOOL CALLBACK MatrixDlgProc(HWND _hwnd,
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
		case IDC_EDIT_A11:
		{
			matrixA[0][0] = ReadFromEditBox(_hwnd, IDC_EDIT_A11);
			break;
		}

		case IDC_EDIT_B11:
		{
			matrixB[0][0] = ReadFromEditBox(_hwnd, IDC_EDIT_B11);
			break;
		}

		case IDOK:
		{
			AddMatrix(_hwnd);
			break;
		}
		case IDOK4:
		{
			SetToIdentity(_hwnd, true);
			break;
		}
		case IDOK8:
		{
			SetToIdentity(_hwnd, false);
			break;
		}

		case CLEARALL:
		{
			ClearMatrices(_hwnd);
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
		MessageBox(_hwnd, ToWideString(_value).c_str(), L"Default Value", MB_OK);
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
	}
	return FALSE;
}

BOOL CALLBACK TransformationDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{

	switch (_msg)
	{
	
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{

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


BOOL CALLBACK GaussianDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{

	switch (_msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{

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


BOOL CALLBACK QuaternionDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{

	switch (_msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{

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

BOOL CALLBACK SLERPDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{

	switch (_msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{

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

	//Laod the Menu
	g_hMenu = LoadMenu(_hInstance, MAKEINTRESOURCE(IDR_MENU1));

	// create the window
	hwnd = CreateWindowEx(NULL, // Extended style.
		WINDOW_CLASS_NAME,      // Class.
		L"Your Basic Window",   // Title.
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0,                    // Initial x,y.
		400, 100,                // Initial width, height.
		NULL,                   // Handle to parent.
		g_hMenu,                   // Handle to menu.
		_hInstance,             // Instance of this application.
		NULL);                  // Extra creation parameters.

	if (!(hwnd))
	{
		return (0);
	}

	//Create the modeless dialog boxes for the calculators
	//Matrix Calculator
	g_hDlgMatrix = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogMatrix), hwnd, (DLGPROC)MatrixDlgProc);
	g_hDlgTransformation = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogTransformations), hwnd, (DLGPROC)TransformationDlgProc);
	g_hDlgGaussian = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogGaussian), hwnd, (DLGPROC)GaussianDlgProc);
	g_hDlgQuaternion = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogQuaternion), hwnd, (DLGPROC)QuaternionDlgProc);
	g_hDlgSLERP = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogSLERP), hwnd, (DLGPROC)SLERPDlgProc);

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

			if ((g_hDlgMatrix == 0 && g_hDlgTransformation == 0 && g_hDlgGaussian == 0 && g_hDlgQuaternion == 0 && g_hDlgSLERP == 0) ||
				(!IsDialogMessage(g_hDlgMatrix, &msg) && !IsDialogMessage(g_hDlgTransformation, &msg) && !IsDialogMessage(g_hDlgGaussian, &msg) && !IsDialogMessage(g_hDlgQuaternion, &msg) && !IsDialogMessage(g_hDlgSLERP, &msg)))
			{
				// Translate any accelerator keys.
				TranslateMessage(&msg);
				// Send the message to the window proc.
				DispatchMessage(&msg);
			}
		}

		// Main game processing goes here.
		GameLoop(); //One frame of game logic occurs here...
	}

	// Return to Windows like this...
	return (static_cast<int>(msg.wParam));
}

void ReadMatrices(HWND _hwnd) {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			matrixA[y][x] = ReadFromEditBox(_hwnd, matrixAID[y][x]);
			matrixB[y][x] = ReadFromEditBox(_hwnd, matrixBID[y][x]);
			matrixR[y][x] = ReadFromEditBox(_hwnd, matrixRID[y][x]);
		}
	}
}

void WriteMatrices(HWND _hwnd) {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			WriteToEditBox(_hwnd, matrixAID[y][x], matrixA[y][x]);
			WriteToEditBox(_hwnd, matrixBID[y][x], matrixB[y][x]);
			WriteToEditBox(_hwnd, matrixRID[y][x], matrixR[y][x]);
		}
	}
}

void ClearMatrices(HWND _hwnd)
{
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			matrixA[y][x] = -INFINITY;
			matrixB[y][x] = -INFINITY;
			matrixR[y][x] = -INFINITY;

			
			WriteToEditBox(_hwnd, matrixAID[y][x], -INFINITY);
			WriteToEditBox(_hwnd, matrixBID[y][x], -INFINITY);
			WriteToEditBox(_hwnd, matrixRID[y][x], -INFINITY);
		}
	}
}

void AddMatrix(HWND _hwnd)
{
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			ReadMatrices(_hwnd);

			matrixR[y][x] = matrixA[y][x] + matrixB[y][x];

			WriteMatrices(_hwnd);
		}
	}
}

void SetToIdentity(HWND _hwnd, bool isA)
{
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			ReadMatrices(_hwnd);

			if (y == x) (isA ? matrixA : matrixB)[y][x] = 1;
			else (isA ? matrixA : matrixB)[y][x] = 0;

			WriteMatrices(_hwnd);
		}
	}
}