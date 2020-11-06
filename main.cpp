//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name	: main.cpp
// Description	: Contains functionality for the Calculator Window and the various calculators inside of it
// Author		: Keane Carotenuto & Jake Laird
// Mail			: keane.carotenuto@mds.ac.nz & jake.laird@mds.ac.nz
//

//check if radio button is checked
//SendDlgItemMessage(IDC_RADIO, BM_GETCHECK) == BST_CHECKED
//SendDlgItemMessage(hWndDlg, IDC_RADIO, BM_GETCHECK, 0, 0L ) == BST_CHECKED
//check if radio button is NOT checked
//SendDlgItemMessage(IDC_RADIO, BM_GETCHECK) == BST_UNCHECKED

#define WIN32_LEAN_AND_MEAN

#include <windows.h>   // Include all the windows headers.
#include <windowsx.h>  // Include useful macros.
#include <string.h>  // Include useful macros.
#include <math.h>

#include "utils.h"
#include "resource.h"

#define WINDOW_CLASS_NAME L"WINCLASS1"

HMENU g_hMenu;
HWND g_hDlgMatrix, g_hDlgTransformation, g_hDlgGaussian, g_hDlgQuaternion, g_hDlgSLERP;

//Matrix Calculator Function Declarations And Variable Initialisations
void ReadMatrices(HWND _hwnd);
void WriteMatrices(HWND _hwnd);
void ClearMatrices(HWND _hwnd);

void AddMatrix(HWND _hwnd);
void SubtractMatrix(HWND _hwnd);
void MultiplyMatrix(HWND _hwnd, bool dirAB);

void SetToIdentity(HWND _hwnd, bool isA);
void MultiplyBy(HWND _hwnd, bool isA);
void Transpose(HWND _hwnd, bool isA);
void Determinant(HWND _hwnd, bool isA);
float detFunc(float mat[4][4], float n);
void Inverse(HWND _hwnd, bool isA);

float matrixA[4][4], matrixB[4][4], matrixR[4][4];
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

//Quaternion Calculator Function Declarations And Variable Initialisations
void ReadQuaternions(HWND _hwnd);
void WriteQuaternions(HWND _hwnd);

void AddQuaternions(HWND _hwnd);
void SubtractQuaternions(HWND _hwnd, bool isA);
void MultiplyQuaternions(HWND _hwnd, bool isA);

void MagnitudeQuaternions(HWND _hwnd, bool isA);
void ConjugateQuaternions(HWND _hwnd, bool isA);
void DotProductQuaternions(HWND _hwnd);
void InverseQuaternions(HWND _hwnd, bool isA);
void ScaleQuaternions(HWND _hwnd, bool isA);

float quaternionA[4], quaternionB[4], quaternionR[4];
int quaternionAID[4] = {
	{IDC_EDIT1}, 
	{IDC_EDIT2},
	{IDC_EDIT3},
	{IDC_EDIT4}
};
int quaternionBID[4] = {
	{IDC_EDIT5},
	{IDC_EDIT6},
	{IDC_EDIT7},
	{IDC_EDIT8}
};
int quaternionRID[4] = {
	{IDC_EDIT10}, 
	{IDC_EDIT11},
	{IDC_EDIT12},
	{IDC_EDIT13}
};

//Gaussian Eliminator Function Declarations And Variable Initialisations
void ReadGaussian(HWND _hwnd);
void WriteGaussian(HWND _hwnd);

void MultiplyGaussianRow(HWND _hwnd);
void SwapGaussianRow(HWND _hwnd);
void AddMultipliedRow(HWND _hwnd);

void SolveReducedRow(HWND _hwnd);
void SortGaussian(const HWND& _hwnd);
void CheckEchelonForms(HWND _hwnd);

long double gaussianMatrix[3][4];
int gaussianMatrixID[3][4] = {
	{IDC_EDIT1, IDC_EDIT2, IDC_EDIT3, IDC_EDIT4},
	{IDC_EDIT5, IDC_EDIT6, IDC_EDIT7, IDC_EDIT8},
	{IDC_EDIT9, IDC_EDIT10, IDC_EDIT11, IDC_EDIT12}
};

//SLERP Calculator Function Declarations And Variable Initialisations

long double SLERPquaternionA[4];
long double SLERPquaternionB[4];
long double SLERPquaternionR[4];
long double SLERPt;

int SLERPquaternionAID[4] = {
	{IDC_EDIT1},
	{IDC_EDIT2},
	{IDC_EDIT3},
	{IDC_EDIT4}
};
int SLERPquaternionBID[4] = {
	{IDC_EDIT5},
	{IDC_EDIT6},
	{IDC_EDIT7},
	{IDC_EDIT8}
};
int SLERPquaternionRID[4] = {
	{IDC_EDIT10},
	{IDC_EDIT11},
	{IDC_EDIT12},
	{IDC_EDIT13}
};
int SLERPMatrixRID[4][4] = {
	{IDC_EDIT34,IDC_EDIT35,IDC_EDIT36,IDC_EDIT37},
	{IDC_EDIT38,IDC_EDIT39,IDC_EDIT40,IDC_EDIT41},
	{IDC_EDIT42,IDC_EDIT43,IDC_EDIT44,IDC_EDIT45},
	{IDC_EDIT46,IDC_EDIT47,IDC_EDIT48,IDC_EDIT49}
};

void ReadSlerpQuat(HWND _hwnd);
void WriteSlerpQuat(HWND _hwnd);

void Slerp(HWND _hwnd);

void SlerpNormalise(HWND _hwnd);
void SlerpMatrix(HWND _hwnd, bool isSlerp, bool isA);

//Transformation Matrices Function Declarations And Variable Initialisations
void ReadTransforms(HWND _hwnd);
void WriteTransforms(HWND _hwnd);
void ClearTransforms(HWND _hwnd);

void ScaleTransform(HWND _hwnd);
void TranslateTransform(HWND _hwnd);
void RotateTransform(HWND _hwnd);
void ProjectTransform(HWND _hwnd);

void MultiplyTransforms(HWND _hwnd, float matrix[4][4]);

float scaleData[3], translateData[3], rotateData[4], projectData[4];
float resultantMatrix[4][4] = {
	{1.f,0.f,0.f,0.f},
	{0.f,1.f,0.f,0.f},
	{0.f,0.f,1.f,0.f},
	{0.f,0.f,0.f,1.f}
};
int scaleDataID[3] = {
	{IDC_EDIT1},
	{IDC_EDIT2},
	{IDC_EDIT3}
};
int translateDataID[3] = {
	{IDC_EDIT4},
	{IDC_EDIT5},
	{IDC_EDIT6}
};
int rotateDataID[4] = {
	{IDC_EDIT13},
	{IDC_RADIO1},
	{IDC_RADIO2},
	{IDC_RADIO3}
};
int projectDataID[4] = {
	{IDC_EDIT15},
	{IDC_RADIO4},
	{IDC_RADIO5},
	{IDC_RADIO6}
};
int columnResultID[4][4] = {
	{IDC_EDIT8,IDC_EDIT9,IDC_EDIT10,IDC_EDIT11},
	{IDC_EDIT12,IDC_EDIT16,IDC_EDIT18,IDC_EDIT19},
	{IDC_EDIT20,IDC_EDIT21,IDC_EDIT22,IDC_EDIT23},
	{IDC_EDIT24,IDC_EDIT25,IDC_EDIT26,IDC_EDIT27}
};int rowResultID[4][4] = {
	{IDC_EDIT47,IDC_EDIT48,IDC_EDIT49,IDC_EDIT50},
	{IDC_EDIT51,IDC_EDIT52,IDC_EDIT53,IDC_EDIT54},
	{IDC_EDIT55,IDC_EDIT56,IDC_EDIT57,IDC_EDIT58},
	{IDC_EDIT59,IDC_EDIT60,IDC_EDIT61,IDC_EDIT62}
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

		case IDOK4:
		{
			SetToIdentity(_hwnd, true);
			break;
		}

		case IDOK6:
		{
			MultiplyBy(_hwnd, true);
			break;
		}

		case IDOK10:
		{
			MultiplyBy(_hwnd, false);
			break;
		}

		case IDOK8:
		{
			SetToIdentity(_hwnd, false);
			break;
		}

		case IDOK9:
		{
			Transpose(_hwnd, true);
			break;
		}

		case IDOK11:
		{
			Transpose(_hwnd, false);
			break;
		}

		case IDOK3:
		{
			Determinant(_hwnd, true);
			break;
		}
		case IDOK7:
		{
			Determinant(_hwnd, false);
			break;
		}

		case IDCANCEL2:
		{
			Inverse(_hwnd, true);
			break;
		}
		case IDCANCEL3:
		{
			Inverse(_hwnd, false);
			break;
		}

		case IDOK:
		{
			AddMatrix(_hwnd);
			break;
		}

		case IDCANCEL:
		{
			SubtractMatrix(_hwnd);
			break;
		}

		case IDOK2:
		{
			MultiplyMatrix(_hwnd, true);
			break;
		}
		case IDOK5:
		{
			MultiplyMatrix(_hwnd, false);
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
		case IDC_BUTTON4:
			ScaleTransform(_hwnd);
			break;

		case IDC_BUTTON15:
			TranslateTransform(_hwnd);
			break;

		case IDC_BUTTON16:
			RotateTransform(_hwnd);
			break;

		case IDC_BUTTON17:
			ProjectTransform(_hwnd);
			break;

		case IDC_COMBO1:
			ClearTransforms(_hwnd);
			break;

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
		case IDC_BUTTON1:
		{
			MultiplyGaussianRow(_hwnd);
			break;
		}

		case IDC_BUTTON2:
		{
			SwapGaussianRow(_hwnd);
			break;
		}

		case IDC_BUTTON3:
		{
			AddMultipliedRow(_hwnd);
			break;
		}

		case IDC_SOLVE:
		{
			MessageBox(_hwnd, L"Solving for Row  Echelon\n(Might not work too well with weird matricies...)", L"Solving:", MB_OK);
			SolveReducedRow(_hwnd);
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
		
		case IDC_BUTTON1:
		{
			AddQuaternions(_hwnd);
			break;
		}
		
		case IDC_BUTTON5:
		{
			SubtractQuaternions(_hwnd, true);
			break;
		}
		
		case IDC_BUTTON6:
		{
			SubtractQuaternions(_hwnd, false);
			break;
		}
		
		case IDC_BUTTON2:
		{
			MultiplyQuaternions(_hwnd, true);
			break;
		}
		
		case IDC_BUTTON7:
		{
			MultiplyQuaternions(_hwnd, false);
			break;
		}
		
		case IDC_BUTTON8:
		{
			DotProductQuaternions(_hwnd);
			break;
		}
		
		case IDC_BUTTON3:
		{
			ConjugateQuaternions(_hwnd, true);
			break;
		}
		
		case IDC_BUTTON9:
		{
			ConjugateQuaternions(_hwnd, false);
			break;
		}
		
		case IDC_BUTTON10:
		{
			MagnitudeQuaternions(_hwnd, true);
			break;
		}
		
		case IDC_BUTTON11:
		{
			MagnitudeQuaternions(_hwnd, false);
			break;
		}
		
		case IDC_BUTTON12:
		{
			InverseQuaternions(_hwnd, true);
			break;
		}
		
		case IDC_BUTTON13:
		{
			InverseQuaternions(_hwnd, false);
			break;
		}
		
		case IDC_BUTTON14:
		{
			ScaleQuaternions(_hwnd, true);
			break;
		}
		
		case IDC_BUTTON15:
		{
			ScaleQuaternions(_hwnd, false);
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
	return FALSE;
}

//void SlerpTest() {
//	quat q = *new quat();
//	quat a = *new quat(0.7071, 0, 0, 0.7071);
//	quat b = *new quat(1, 0, 0, 0);
//	double t = (double)1 / (double)3;
//	q = slerp(a, b, t);
//	std::wstringstream wss;
//	wss << q.w << ", " << q.x << ", " << q.y << ", " << q.z << "\n";
//
//	int msgboxID = MessageBox(
//		NULL,
//		wss.str().c_str(),
//		(LPCWSTR)L"Account Details",
//		MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
//	);
//}

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
		case IDC_BUTTON1:
			Slerp(_hwnd);
			break;

		case IDC_BUTTON2:
			SlerpMatrix(_hwnd, false, true);
			break;

		case IDC_BUTTON3:
			SlerpMatrix(_hwnd, false, false);
			break;

		case IDC_BUTTON4:
			SlerpMatrix(_hwnd, true, false);
			break;

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

/// <summary>
/// Reads all of the imputs in the window and assigns them to the matrices - Keane
/// </summary>
void ReadMatrices(HWND _hwnd) {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			matrixA[y][x] = ReadFromEditBox(_hwnd, matrixAID[y][x]);
			matrixB[y][x] = ReadFromEditBox(_hwnd, matrixBID[y][x]);
			matrixR[y][x] = ReadFromEditBox(_hwnd, matrixRID[y][x]);
		}
	}
}

/// <summary>
/// Writes from the matrices to the window - Keane
/// </summary>
void WriteMatrices(HWND _hwnd) {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			WriteToEditBox(_hwnd, matrixAID[y][x], matrixA[y][x]);
			WriteToEditBox(_hwnd, matrixBID[y][x], matrixB[y][x]);
			WriteToEditBox(_hwnd, matrixRID[y][x], matrixR[y][x]);
		}
	}
}

/// <summary>
/// Clears all Matrix input boxes - Keane
/// </summary>
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

/// <summary>
/// Adds Both matrices - Keane
/// </summary>
void AddMatrix(HWND _hwnd)
{
	ReadMatrices(_hwnd);
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {

			matrixR[y][x] = matrixA[y][x] + matrixB[y][x];

		}
	}
	WriteMatrices(_hwnd);
}

/// <summary>
/// Subtracts matricies B from A - Keane
/// </summary>
void SubtractMatrix(HWND _hwnd)
{
	ReadMatrices(_hwnd);
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {

			matrixR[y][x] = matrixA[y][x] - matrixB[y][x];

		}
	}
	WriteMatrices(_hwnd);
}

/// <summary>
/// Multiplies A * B if true, or B * A if false - Keane
/// </summary>
void MultiplyMatrix(HWND _hwnd, bool dirAB) 
{
	ReadMatrices(_hwnd);
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			float temp = 0;
			for (int w = 0; w < 4; w++){
				temp += (dirAB ? matrixA[y][w] * matrixB[w][x] : matrixB[y][w] * matrixA[w][x]);
			}
			matrixR[y][x] = temp;
		}
	}
	WriteMatrices(_hwnd);
}

/// <summary>
/// If true, Sets A to identity, otherwise sets B to identity - Jake
/// </summary>
void SetToIdentity(HWND _hwnd, bool isA)
{
	ReadMatrices(_hwnd);
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {

			if (y == x) (isA ? matrixA : matrixB)[y][x] = 1;
			else (isA ? matrixA : matrixB)[y][x] = 0;

		}
	}
	WriteMatrices(_hwnd);
}

/// <summary>
/// Scales Either A (if true) or B (if false) by amount - Keane
/// </summary>
void MultiplyBy(HWND _hwnd, bool isA)
{
	ReadMatrices(_hwnd);
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			
			(isA ? matrixA : matrixB)[y][x] *= ReadFromEditBox(_hwnd, (isA ? IDC_EDIT_AScaled : IDC_EDIT_BScaled));

		}
	}
	WriteMatrices(_hwnd);
}

/// <summary>
/// Transposes Either A (if true) or B - Keane
/// </summary>
void Transpose(HWND _hwnd, bool isA)
{
	ReadMatrices(_hwnd);
	WriteMatrices(_hwnd);
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {

			(isA ? matrixA : matrixB)[y][x] = ReadFromEditBox(_hwnd, (isA ? matrixAID : matrixBID)[x][y]);

		}
	}
	WriteMatrices(_hwnd);
}

/// <summary>
/// Calls the Real Determinant function with matrix A (if true) or B (if false) - Keane
/// </summary>
void Determinant(HWND _hwnd, bool isA)
{
	ReadMatrices(_hwnd);
	WriteToEditBox(_hwnd, (isA ? IDC_EDIT_DetA : IDC_EDIT_DetB), detFunc((isA ? matrixA : matrixB), 4));
	WriteMatrices(_hwnd);
}

/// <summary>
/// Calculates Determinant of A (if true) or B - Keane
/// </summary>
float detFunc(float mat[4][4], float n) {
	float det = 0;
	float tempMat[4][4];

	if (n == 2)return ((mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]));
		
	for (int i = 0; i < n; i++) {
		int tempY = 0;
		for (int y = 0; y < n; y++) {
			int tempX = 0;
			for (int x = 0; x < n; x++) {
				if (x == i || y == 0) continue;

				tempMat[tempY][tempX] = mat[y][x];
				tempX++;
			}
			if (y != 0) tempY++;
		}
		det = det + ((i % 2 == 0 ? 1 : -1) * mat[0][i] * detFunc(tempMat, n - 1));
	}
	return det;
}

/// <summary>
/// Returns the Inverse of A (if true) or B (if false) - Keane
/// </summary>
void Inverse(HWND _hwnd, bool isA) {
	ReadMatrices(_hwnd);

	float det = detFunc((isA ? matrixA : matrixB), 4);

	float toWriteMatrix[4][4];

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {

			float tempMat[4][4];

			int r = 0;
			for (int ty = 0; ty < 4; ty++) {
				int c = 0;
				for (int tx = 0; tx < 4; tx++) {
					if (ty == y || tx == x) continue;
					tempMat[r][c] = (isA ? matrixA : matrixB)[ty][tx];
					c++;
				}
				if (ty != y) {
					r++;
				}
			}

			toWriteMatrix[y][x] = detFunc(tempMat, 3);

		}
	}

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			(isA ? matrixA : matrixB)[y][x] = (y % 2 == 0 ? 1 : -1) * (x % 2 == 0 ? 1 : -1) * toWriteMatrix[y][x];
		}
	}

	WriteMatrices(_hwnd);
	Transpose(_hwnd, isA);

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {

			(isA ? matrixA : matrixB)[y][x] *= 1/det;

		}
	}

	WriteMatrices(_hwnd);
}

//Functions specifically for the Quaternion calculator

/// <summary>
/// Reads all of the imputs in the window and assigns them to the quaternions - Jake
/// </summary>
void ReadQuaternions(HWND _hwnd) {
	for (int y = 0; y < 4; y++) {
			quaternionA[y] = ReadFromEditBox(_hwnd, quaternionAID[y]);
			quaternionB[y] = ReadFromEditBox(_hwnd, quaternionBID[y]);
			quaternionR[y] = ReadFromEditBox(_hwnd, quaternionRID[y]);
	}
}

/// <summary>
/// Writes from the quaternions to the window
/// </summary>
void WriteQuaternions(HWND _hwnd) {
	for (int y = 0; y < 4; y++) {
			WriteToEditBox(_hwnd, quaternionAID[y], quaternionA[y]);
			WriteToEditBox(_hwnd, quaternionBID[y], quaternionB[y]);
			WriteToEditBox(_hwnd, quaternionRID[y], quaternionR[y]);
	}
}

/// <summary>
/// Handles the addition of Quaternions. Addition is commutative so this doesn't require an order operator - Jake
/// </summary>
void AddQuaternions(HWND _hwnd)
{
	ReadQuaternions(_hwnd);
	for (int y = 0; y < 4; y++) {
		quaternionR[y] = quaternionA[y] + quaternionB[y];
	}
	WriteQuaternions(_hwnd);
}

/// <summary>
/// Handles the subtraction of Quaternions. Computes A - B if true or B - A if false - Jake
/// </summary>
void SubtractQuaternions(HWND _hwnd, bool isA)
{
	ReadQuaternions(_hwnd);
	for (int y = 0; y < 4; y++) {
		quaternionR[y] = (isA ? (quaternionA[y] - quaternionB[y]) : (quaternionB[y] - quaternionA[y]));
	}
	WriteQuaternions(_hwnd);
}

/// <summary>
/// Handles the multiplication of Quaternions. Computes A*B if true or B*A if false - Jake
/// </summary>
void MultiplyQuaternions(HWND _hwnd, bool isA)
{
	ReadQuaternions(_hwnd);
	float tempMatrix[4][4]; // Using a temporary matrix to store the results of the multiplication

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++)
		{
			tempMatrix[y][x] = (isA ? (quaternionA[x] * quaternionB[y]) : (quaternionB[x] * quaternionA[y]));
		}
	}

	quaternionR[0] = (tempMatrix[0][3] + tempMatrix[2][1] + tempMatrix[3][0] - tempMatrix[1][2]); //This is the i component of the resultant quaternion
	quaternionR[1] = (tempMatrix[0][2] + tempMatrix[1][3] + tempMatrix[3][1] - tempMatrix[2][0]); //This is the j component of the resultant quaternion
	quaternionR[2] = (tempMatrix[1][0] + tempMatrix[2][3] + tempMatrix[3][2] - tempMatrix[0][1]); //This is the k component of the resultant quaternion
	quaternionR[3] = (tempMatrix[3][3] - tempMatrix[2][2] - tempMatrix[1][1] - tempMatrix[0][0]); //This is the real component of the resultant quaternion

	WriteQuaternions(_hwnd);
}

/// <summary>
/// Handles the dot product calculation of Quaternions - Jake
/// </summary>
void DotProductQuaternions(HWND _hwnd)
{
	ReadQuaternions(_hwnd);
	quaternionR[3] = 0;

	for (int y = 0; y < 4; y++) {
		if (y != 3)
		{
			quaternionR[y] = 0;
			quaternionR[3] += quaternionA[y] * quaternionB[y];
		}
		else
		{
			quaternionR[3] += quaternionA[y] * quaternionB[y];
		}	
	}
	WriteQuaternions(_hwnd);
}

/// <summary>
/// Handles the conjugation of Quaternions. Computes A* if true or B* if false - Jake
/// </summary>
void ConjugateQuaternions(HWND _hwnd, bool isA)
{
	ReadQuaternions(_hwnd);
	for (int y = 0; y < 4; y++) {
		if (y == 3)
		{
			quaternionR[y] = (isA ? quaternionA : quaternionB)[y];
		}
		else
		{
			quaternionR[y] = (isA ? quaternionA : quaternionB)[y] * -1;
		}
	}
	WriteQuaternions(_hwnd);
}

/// <summary>
/// Handles the magnitude calculation of Quaternions. Computes |A| if true or |B| if false - Jake
/// </summary>
void MagnitudeQuaternions(HWND _hwnd, bool isA)
{
	ReadQuaternions(_hwnd);
	quaternionR[3] = 0;

	for (int y = 0; y < 4; y++) {
		if (y != 3)
		{
			quaternionR[y] = 0;
		}
		
		quaternionR[3] += pow((isA ? quaternionA : quaternionB)[y], 2);
	}

	quaternionR[3] = sqrt(quaternionR[3]);

	WriteQuaternions(_hwnd);
}

/// <summary>
/// Handles the inverse calculation of Quaternions. Computes A inverse if true or B inverse if false - Jake
/// </summary>
void InverseQuaternions(HWND _hwnd, bool isA)
{
	ReadQuaternions(_hwnd);
	float tempQuaternion[4] = { 0.f };
	float tempMagnitude = 0.f;

	for (int y = 0; y < 4; y++) {
			quaternionR[y] = 0;
	}

	ConjugateQuaternions(_hwnd, isA);

	for (int y = 0; y < 4; y++) {
		tempQuaternion[y] = quaternionR[y]; // Stores the result of the conjugate function into a temporary quaternion
		quaternionR[y] = 0; // Resets the resultant quaternion value so that the next operation works as intended
	}

	MagnitudeQuaternions(_hwnd, isA);

	tempMagnitude = quaternionR[3]; // Stores the Result of the magnitude in this temporary variable
	quaternionR[3] = 0; // Resets the resultant quaternion value so that any future operations work as intended

	for (int y = 0; y < 4; y++) {
		quaternionR[y] = (tempQuaternion[y]/pow(tempMagnitude, 2));
	}

	WriteQuaternions(_hwnd);
}

/// <summary>
/// Handles the scaling of Quaternions. Scales A if true or B if false - Jake
/// </summary>
void ScaleQuaternions(HWND _hwnd, bool isA)
{
	ReadQuaternions(_hwnd);
	for (int y = 0; y < 4; y++) {
		quaternionR[y] = (isA ? quaternionA : quaternionB)[y] * ReadFromEditBox(_hwnd, IDC_EDIT9);
	}
	WriteQuaternions(_hwnd);
}

//Functions specifically for the Gaussian Eliminator

/// <summary>
/// Reads all of the imputs in the window and assigns them as a gaussian matrix
/// </summary>
void ReadGaussian(HWND _hwnd) {
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 4; x++) {
			gaussianMatrix[y][x] = ReadFromEditBox(_hwnd, gaussianMatrixID[y][x]);
		}
	}
}

/// <summary>
/// Writes from the gaussian matrix to the window
/// </summary>
void WriteGaussian(HWND _hwnd) {
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 4; x++) {
			WriteToEditBox(_hwnd, gaussianMatrixID[y][x], gaussianMatrix[y][x]);
		}
	}

	CheckEchelonForms(_hwnd);
}

/// <summary>
/// Multiplies a specified row in the gaussian matrix by a specified amount. It assumes the user is unfamiliar with the fact that arrays start at 0 in c++, hence the ReadFromEditBox() - 1 operation - Jake
/// </summary>
void MultiplyGaussianRow(HWND _hwnd) {
	
	ReadGaussian(_hwnd);
	
	int rowToMultiply = ReadFromEditBox(_hwnd, IDC_EDIT13) - 1;
	long double multiplyingBy = ReadFromEditBox(_hwnd, IDC_EDIT14);

	for (int x = 0; x < 4; x++) {
		gaussianMatrix[rowToMultiply][x] *= multiplyingBy;
	}

	WriteGaussian(_hwnd);
}

/// <summary>
/// Swaps a first specified row with a second specified row - Jake
/// </summary>
void SwapGaussianRow(HWND _hwnd) {

	ReadGaussian(_hwnd);

	int rowSwapProvider = ReadFromEditBox(_hwnd, IDC_EDIT16) - 1;
	int rowSwapRecipient = ReadFromEditBox(_hwnd, IDC_EDIT17) - 1;
	long double tempEquation[4] = { 0 };

	for (int x = 0; x < 4; x++) {
		tempEquation[x] = gaussianMatrix[rowSwapRecipient][x];
		gaussianMatrix[rowSwapRecipient][x] = gaussianMatrix[rowSwapProvider][x];
		gaussianMatrix[rowSwapProvider][x] = tempEquation[x];
	}

	WriteGaussian(_hwnd);
}

/// <summary>
/// First it multiplies a specified row by a specified number, then it adds the result of that operation to another specified row - Jake
/// </summary>
void AddMultipliedRow(HWND _hwnd) {

	ReadGaussian(_hwnd);

	long double multiplyingBy = ReadFromEditBox(_hwnd, IDC_EDIT19);
	int rowToMultiply = ReadFromEditBox(_hwnd, IDC_EDIT20) - 1;
	int rowToAddTo = ReadFromEditBox(_hwnd, IDC_EDIT22) - 1;
	
	long double tempEquation[4] = { 0 };
	
	for (int x = 0; x < 4; x++) {
		tempEquation[x] = gaussianMatrix[rowToMultiply][x] * multiplyingBy; // Storing in a temporary variable so as not to affect the actual row in the gaussian matrix
		gaussianMatrix[rowToAddTo][x] += tempEquation[x];
	}

	WriteGaussian(_hwnd);
}

void SolveReducedRow(HWND _hwnd)
{

	SortGaussian(_hwnd);

	WriteGaussian(_hwnd);
	MessageBox(_hwnd, L"Sorted", L"Pause", MB_OK);

	ReadGaussian(_hwnd);


	for (int y = 0; y < 3; y++) {
		if (gaussianMatrix[y][y] != 0) {
			long double multi = 1 / gaussianMatrix[y][y];
			for (int x = 0; x < 4; x++) {
				gaussianMatrix[y][x] *= multi;
			}
		}
	}

	WriteGaussian(_hwnd);
	MessageBox(_hwnd, L"Diag to 1", L"Pause", MB_OK);


	long double multi1 = -gaussianMatrix[1][0];
	for (int x = 0; x < 4; x++) {
		gaussianMatrix[1][x] += multi1 * gaussianMatrix[0][x];
	}

	WriteGaussian(_hwnd);
	MessageBox(_hwnd, L"second row started", L"Pause", MB_OK);

	if (gaussianMatrix[1][1] != 0) {
		long double multi1Final = 1 / gaussianMatrix[1][1];
		for (int x = 0; x < 4; x++) {
			gaussianMatrix[1][x] *= multi1Final;
		}
	}
	
	WriteGaussian(_hwnd);
	MessageBox(_hwnd, L"second row done", L"Pause", MB_OK);

	long double multi2 = -gaussianMatrix[2][0];
	for (int x = 0; x < 4; x++) {
		gaussianMatrix[2][x] += multi2 * gaussianMatrix[0][x];
	}

	WriteGaussian(_hwnd);
	MessageBox(_hwnd, L"third row started", L"Pause", MB_OK);

	long double multi22 = -gaussianMatrix[2][1];
	for (int x = 0; x < 4; x++) {
		gaussianMatrix[2][x] += multi22 * gaussianMatrix[1][x];
	}

	WriteGaussian(_hwnd);
	MessageBox(_hwnd, L"third row still going", L"Pause", MB_OK);

	
	if (gaussianMatrix[2][2] != 0) {
		long double multi2Final = 1 / gaussianMatrix[2][2];
		for (int x = 0; x < 4; x++) {
			gaussianMatrix[2][x] *= multi2Final;
		}
	}

	WriteGaussian(_hwnd);
	MessageBox(_hwnd, L"third row done", L"Pause", MB_OK);




	WriteGaussian(_hwnd);
}

void SortGaussian(const HWND& _hwnd)
{
	ReadGaussian(_hwnd);

	bool sorted = false;

	while (!sorted) {

		int nums[3] = { 0,0,0 };

		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 4; x++) {
				if (gaussianMatrix[y][x] != 0) break;
				nums[y] ++;
			}
		}

		if (nums[0] <= nums[1] && nums[1] <= nums[2]) {
			sorted = true;
			break;
		}

		ReadGaussian(_hwnd);

		int rowSwapProvider = rand() % 3;
		int rowSwapRecipient = rand() % 3;
		long double tempEquation[4] = { 0 };

		for (int x = 0; x < 4; x++) {
			tempEquation[x] = gaussianMatrix[rowSwapRecipient][x];
			gaussianMatrix[rowSwapRecipient][x] = gaussianMatrix[rowSwapProvider][x];
			gaussianMatrix[rowSwapProvider][x] = tempEquation[x];
		}

		WriteGaussian(_hwnd);
	}

	WriteGaussian(_hwnd);
}

/// <summary>
/// Checks to see if the gaussian matrix has been successfully converted into either Row Echelon Form or Reduced Row Echelon Form - Jake
/// </summary>
void CheckEchelonForms(HWND _hwnd)
{
	ReadGaussian(_hwnd);

	int matchConditionsCount = 0;

	for (int y = 0; y < 3; y++){
		for (int x = 0; x < 3; x++) {

			if (y == x)
			{
				if (gaussianMatrix[y][x] == 1)
				{
					matchConditionsCount++;
				}
			}
			else if (x < y)
			{
				if (gaussianMatrix[y][x] == 0 && gaussianMatrix[0][0] == 1 && gaussianMatrix[1][1] == 1 && gaussianMatrix[2][2] == 1)
				{
					matchConditionsCount++;
				}
			}
			else if (x > y)
			{
				if (gaussianMatrix[y][x] == 0 && gaussianMatrix[x][y] == 0)
				{
					matchConditionsCount++;
				}
			}
		}
	}

	if (matchConditionsCount == 9)
	{
		MessageBox(_hwnd, L"You've successfully eliminated until you got to the Reduced Row Echelon form! :D", L"Congratulations!", MB_OK);
	}
	else if (matchConditionsCount == 6)
	{
		MessageBox(_hwnd, L"You've successfully eliminated until you got to the Row Echelon form! :)", L"Well done!", MB_OK);
	}
}

//Functions specifically for the SLERP Calculator

/// <summary>
/// Reads the quaternion values from the program
/// </summary>
void ReadSlerpQuat(HWND _hwnd)
{
	for (int y = 0; y < 4; y++) {
		SLERPquaternionA[y] = ReadFromEditBox(_hwnd, SLERPquaternionAID[y]);
		SLERPquaternionB[y] = ReadFromEditBox(_hwnd, SLERPquaternionBID[y]);
		SLERPquaternionR[y] = ReadFromEditBox(_hwnd, SLERPquaternionRID[y]);
		SLERPt = ReadFromEditBox(_hwnd, IDC_EDIT9);
	}
}

/// <summary>
/// Writes Quaternions to the program
/// </summary>
void WriteSlerpQuat(HWND _hwnd)
{
	for (int y = 0; y < 4; y++) {
		WriteToEditBox(_hwnd, SLERPquaternionAID[y], SLERPquaternionA[y]);
		WriteToEditBox(_hwnd, SLERPquaternionBID[y], SLERPquaternionB[y]);
		WriteToEditBox(_hwnd, SLERPquaternionRID[y], SLERPquaternionR[y]);
	}
}

/// <summary>
/// Normalises both quaternions - Keane
/// </summary>
void SlerpNormalise(HWND _hwnd) {
	ReadSlerpQuat(_hwnd);

	double qaMag = sqrt(SLERPquaternionA[0] * SLERPquaternionA[0] +
						SLERPquaternionA[1] * SLERPquaternionA[1] +
						SLERPquaternionA[2] * SLERPquaternionA[2] +
						SLERPquaternionA[3] * SLERPquaternionA[3]);

	if (!qaMag) {
		qaMag = 1;
	}

	for (int x = 0; x < 4; x++) {
		SLERPquaternionA[x] *= 1 / qaMag;
	}

	double qbMag = sqrt(SLERPquaternionB[0] * SLERPquaternionB[0] +
						SLERPquaternionB[1] * SLERPquaternionB[1] +
						SLERPquaternionB[2] * SLERPquaternionB[2] +
						SLERPquaternionB[3] * SLERPquaternionB[3]);

	if (!qbMag) {
		qbMag = 1;
	}

	for (int x = 0; x < 4; x++) {
		SLERPquaternionB[x] *= 1 / qbMag;
	}

	WriteSlerpQuat(_hwnd);
}

/// <summary>
/// Calculates the interpolation between two quaternions - Keane
/// </summary>
void Slerp(HWND _hwnd) {

	SlerpNormalise(_hwnd);
	ReadSlerpQuat(_hwnd);
	
	//Find angle between two quats
	double angle = acos(SLERPquaternionA[0] * SLERPquaternionB[0] +
						SLERPquaternionA[1] * SLERPquaternionB[1] +
						SLERPquaternionA[2] * SLERPquaternionB[2] +
						SLERPquaternionA[3] * SLERPquaternionB[3]);

	//Calculate what to multiply each quat by
	double quatAMult = sin((1 - SLERPt) * angle) / sin(angle);
	double quatBMult = sin(SLERPt * angle) / sin(angle);
	
	//calculate Quaternion
	for (int x = 0; x < 4; x++) {
		SLERPquaternionR[x] = (SLERPquaternionA[x] * quatAMult + SLERPquaternionB[x] * quatBMult);
	}

	WriteSlerpQuat(_hwnd);
}

/// <summary>
/// Calculates and generates the matrices induced by each quaternion - Jake
/// </summary>
void SlerpMatrix(HWND _hwnd, bool isSlerp, bool isA) {

	Slerp(_hwnd);
	ReadSlerpQuat(_hwnd);

	double tempSlerpQuat[4] = { 0 };

	for (int y = 0; y < 4; y++) {
		tempSlerpQuat[y] = (isSlerp ? SLERPquaternionR : (isA ? SLERPquaternionA : SLERPquaternionB))[y];
	}

	double tempMatrix[4][4] = { 0 };
	tempMatrix[3][3] = 1;

	// 2*((real term)^2 + ((i term)^2)) - 1
	tempMatrix[0][0] = (2 * ((pow(tempSlerpQuat[3], 2)) + (pow(tempSlerpQuat[0], 2)))) - 1;

	// 2*((i term)*(j term) + (real term)(k term))
	tempMatrix[0][1] = 2 * ((tempSlerpQuat[0] * tempSlerpQuat[1]) + (tempSlerpQuat[3] * tempSlerpQuat[2]));	

	// 2*((i term)*(k term) - (real term)(j term))
	tempMatrix[0][2] = 2 * ((tempSlerpQuat[0] * tempSlerpQuat[2]) - (tempSlerpQuat[3] * tempSlerpQuat[1]));

	// 2*((i term)*(j term) - (real term)(k term))
	tempMatrix[1][0] = 2 * ((tempSlerpQuat[0] * tempSlerpQuat[1]) - (tempSlerpQuat[3] * tempSlerpQuat[2]));

	// 2*((real term)^2 + ((j term)^2)) - 1
	tempMatrix[1][1] = (2 * ((pow(tempSlerpQuat[3], 2)) + (pow(tempSlerpQuat[1], 2)))) - 1;

	// 2*((j term)*(k term) + (real term)(i term))
	tempMatrix[1][2] = 2 * ((tempSlerpQuat[1] * tempSlerpQuat[2]) + (tempSlerpQuat[3] * tempSlerpQuat[0]));

	// 2*((i term)*(k term) + (real term)(j term))
	tempMatrix[2][0] = 2 * ((tempSlerpQuat[0] * tempSlerpQuat[2]) + (tempSlerpQuat[3] * tempSlerpQuat[1]));

	// 2*((j term)*(k term) + (real term)(i term))
	tempMatrix[2][1] = 2 * ((tempSlerpQuat[1] * tempSlerpQuat[2]) + (tempSlerpQuat[3] * tempSlerpQuat[0]));

	// 2*((real term)^2 + ((k term)^2)) - 1
	tempMatrix[2][2] = (2 * ((pow(tempSlerpQuat[3], 2)) + (pow(tempSlerpQuat[2], 2)))) - 1;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			WriteToEditBox(_hwnd, SLERPMatrixRID[y][x], tempMatrix[y][x]);
		}
	}

	WriteSlerpQuat(_hwnd);
}

//Functions specifically for the Transformation Calculator

/// <summary>
/// Reads all of the imputs in the window and assigns them to their respective matrices
/// </summary>
void ReadTransforms(HWND _hwnd) {
	float temp = 0.f;
	for (int y = 0; y < 4; y++) {
		if (y < 3)
		{
			scaleData[y] = ReadFromEditBox(_hwnd, scaleDataID[y]);
			translateData[y] = ReadFromEditBox(_hwnd, translateDataID[y]);
		}

		if (y == 0)
		{
			temp = ReadFromEditBox(_hwnd, rotateDataID[y]);

			while (temp < 0.f || temp > 360.f)
			{
				if (temp < 0.f)
				{
					temp += 360.f;
				}
				else
				{
					if (temp > 360.f)
					{
						temp -= 360.f;
					}
				}
			}

			rotateData[y] = temp;
			projectData[y] = ReadFromEditBox(_hwnd, projectDataID[y]);
		}
		else
		{
			rotateData[y] = (SendDlgItemMessage(_hwnd, rotateDataID[y], BM_GETCHECK, 0, 0L) == BST_CHECKED);
			projectData[y] = (SendDlgItemMessage(_hwnd, projectDataID[y], BM_GETCHECK, 0, 0L) == BST_CHECKED);
		}
	}
}

/// <summary>
/// Writes to the window in both Column and Row major forms
/// </summary>
void WriteTransforms(HWND _hwnd) {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			WriteToEditBox(_hwnd, columnResultID[y][x], resultantMatrix[y][x]);
			WriteToEditBox(_hwnd, rowResultID[y][x], resultantMatrix[x][y]);
		}
	}
}

/// <summary>
/// Resets the resultant transform matrix
/// </summary>
void ClearTransforms(HWND _hwnd) {

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (x == y)
			{
				resultantMatrix[y][x] = 1.f;
			}
			else
			{
				resultantMatrix[y][x] = 0.f;
			}
		}
	}

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			WriteToEditBox(_hwnd, columnResultID[y][x], resultantMatrix[y][x]);
			WriteToEditBox(_hwnd, rowResultID[y][x], resultantMatrix[x][y]);
		}
	}
}


/// <summary>
/// Writes to the window in both Column and Row major forms
/// </summary>
void ScaleTransform(HWND _hwnd) {
	ReadTransforms(_hwnd);

	float scaleMatrix[4][4] = { 0.f };

	scaleMatrix[3][3] = 1.f;

	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (x == y)
			{
				if (scaleData[y] == NULL)
				{
					scaleMatrix[y][x] = 1.f;
				}
				else
				{
					scaleMatrix[y][x] = scaleData[y];
				}
			}
		}
	}

	MultiplyTransforms(_hwnd, scaleMatrix);
}

/// <summary>
/// Writes to the window in both Column and Row major forms
/// </summary>
void TranslateTransform(HWND _hwnd) {
	ReadTransforms(_hwnd);

	float translateMatrix[4][4] = { 0.f };

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (x == y)
			{
				translateMatrix[y][x] = 1.f;
			}

			if (x == 3 && y!= 3)
			{
				if (translateData[y] == NULL)
				{
					translateMatrix[y][x] = 0.f;
				}
				else
				{
					translateMatrix[y][x] = translateData[y];
				}
			}
		}
	}

	MultiplyTransforms(_hwnd, translateMatrix);
}

/// <summary>
/// Writes to the window in both Column and Row major forms
/// </summary>
void RotateTransform(HWND _hwnd) {
	ReadTransforms(_hwnd);

	float rotateMatrix[4][4] = { 0.f };

	// Yeah I know it's the first hundred digits of pi and that I don't need to be *that* exact but I like having this degree of accuracy, just give me this one :D
	float pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (x == y)
			{
				rotateMatrix[y][x] = 1.f;
			}
		}
	}

	float radiansConversion = rotateData[0] * (pi / 180); // Converting to radians

	float cosine = cos(radiansConversion); // Takes radians as input
	float sine = sin(radiansConversion); // Takes radians as input

	float miniRotate[2][2] = {
		{cosine, (sine * -1)},
		{sine, cosine}
	};

	if (rotateData[1]) // X radio button selected
	{
		for (int y = 0; y < 2; y++) {
			for (int x = 0; x < 2; x++) {
				rotateMatrix[y + 1][x + 1] = miniRotate[y][x];
			}
		}
	}
	else if (rotateData[2]) // Y radio button selected
	{
		rotateMatrix[0][0] = miniRotate[0][0];
		rotateMatrix[0][2] = miniRotate[1][0];
		rotateMatrix[2][0] = miniRotate[0][1];
		rotateMatrix[2][2] = miniRotate[1][1];
	}
	else
	{
		if (rotateData[3]) // Z radio button selected
		{
			for (int y = 0; y < 2; y++) {
				for (int x = 0; x < 2; x++) {
					rotateMatrix[y][x] = miniRotate[y][x];
				}
			}
		}
	}

	MultiplyTransforms(_hwnd, rotateMatrix);
}

/// <summary>
/// Writes to the window in both Column and Row major forms
/// </summary>
void ProjectTransform(HWND _hwnd) {
	ReadTransforms(_hwnd);

	float projectMatrix[4][4] = { 0.f };

	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (x == y)
			{
				projectMatrix[y][x] = 1.f;
			}
		}
	}

	if (projectData[1]) // X radio button selected
	{
		projectMatrix[3][0] = (1 / projectData[0]);
	}
	else if (projectData[2]) // Y radio button selected
	{
		projectMatrix[3][1] = (1 / projectData[0]);
	}
	else
	{
		if (projectData[3]) // Z radio button selected
		{
			projectMatrix[3][2] = (1 / projectData[0]);
		}
	}

	MultiplyTransforms(_hwnd, projectMatrix);
}

void MultiplyTransforms(HWND _hwnd, float matrix[4][4])
{
	float tempMatrix[4][4] = { 0.f };

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			for (int w = 0; w < 4; w++) {
				tempMatrix[y][x] += matrix[y][w] * resultantMatrix[w][x];
			}
		}
	}

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			resultantMatrix[y][x] = tempMatrix[y][x];
		}
	}

	WriteTransforms(_hwnd);
}

/*std::wstringstream wss;
wss << matrixA[ty][tx];

int msgboxID = MessageBox(
	NULL,
	wss.str().c_str(),
	(LPCWSTR)L"Account Details",
	MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
);*/
