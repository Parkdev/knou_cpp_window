#include <Windows.h> //����µ� �ֿ��Լ�
#define ID_OK_BTN 2000 // ��ư ��Ʈ���� ID�� ����

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // ������ ���ν��� Ÿ�� ����; ()�ȿ� �ִ� �Լ��� ����� �Ŵ�
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HINSTANCE g_hInst; //���ϵ� �����츦 ���鶧 ���

LPCTSTR lpszClass = L"HelloAPI";
LPCTSTR ChildClassName = L"ChildWin";

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) // �����Լ�
// hinstance�� handle + instance (������ �̸�ǥ��)
//hprevinstance ���� �ν��Ͻ� �ڵ�
//lpcmdline Ŀ�ǵ� ������ ���ڰ��� �޴� ������ (���߿� ���)
//ncmdshow �����찡 ȭ��� �������� ���� showwindow�� �Ű������� ���
{
	HWND hWnd;  // ������ �ڵ��� hWnd������ ����; �ϳ��ǰ�ü�� �ν��ϰ� ������� �̸������� ã�ư�
	MSG Message; // �޼���Ÿ��
	WNDCLASS  WndClass; /* "������ Ŭ����"��� ����ü �ϳ��� ����; ����*/
	g_hInst = hInstance;  // ���ϵ� �������Ҷ� ���

	/*������ Ŭ���� ����ü�� Ŀ����; �������� ����� ����*/
	WndClass.cbClsExtra = 0; //���࿵���̷�
	WndClass.cbWndExtra = 0; //���࿵��
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //  �������� ������
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // ���α׷����� ����ϴ� Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ���α׷����� ����ϴ� ������
	WndClass.hInstance = hInstance;				//���α׷��� ��ü �ڵ�;���� �츮�� �˼� ����.
	WndClass.lpfnWndProc = (WNDPROC)WndProc;	//��� ���ν��� ���� (�ݹ��Լ��� �����ΰ�?); (Ÿ��)�����̸�
	// �ݹ��Լ��� ������ ������ ����������Ѵ�.
	WndClass.lpszClassName = lpszClass;			//Ŭ���� �̸� ����(��ǥ�̸�); ������ HelloAPI��� ����������
	// Ŭ���� �Լ� ���� ������ ����������Ѵ�.
	WndClass.lpszMenuName = NULL;				//�޴�
	WndClass.style = CS_HREDRAW | CS_VREDRAW;	//Ŭ������ ��Ÿ��; ����,���� ��Ÿ��
	RegisterClass(&WndClass); /*�������Ϳ� !���, ���α׷��� �ü���� ��û*/
	OutputDebugString(L"���������� Ŭ���� ���\n"); //���α׷��� ������߿� �ش� ���ڿ��� �������� ����ȴ�.

	WndClass.lpfnWndProc = ChildWndProc; // ���ϵ� ������
	WndClass.lpszClassName = ChildClassName;
	RegisterClass(&WndClass);
	OutputDebugString(L"���ϵ�Ŭ���� ���\n");

	OutputDebugString(L"������������ ��������\n");
	hWnd = CreateWindow(
		lpszClass,								/*������ Ŭ���� �̸������� �� ��������� (ȭ�鿡 ����������); HelloAPI*/
		L"������ ���α׷���",					//������ Ÿ��Ʋ (Ÿ��Ʋ�ٿ� �������̸�)
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,		//������ ��Ÿ�� (��ø������; �ý��� �޴�, �ִ� �ּ� ��ư, Ÿ��Ʋ��, ��輱 (�츮�� ���� ���� ������ ���� ����) | ?? )
		200, 200,								//�����찡 ���϶�  x,y ��ǥ
		600, 600,								//�������� ���� ����
		(HWND)NULL,								//�θ� ������ �ڵ�
		(HMENU)NULL,							//�����찡 ������ �޴� �ڵ�
		hInstance,								//��ü �ڵ�
		NULL);									//������ ������

	OutputDebugString(L"������������ �����Ϸ�\n");
	ShowWindow(hWnd, nCmdShow);  /*������� �����츦 ���� ������*/
	//hWnd�� ������ ������ CreateWindow����
	//nCmdShow�� �⺻��
	//SW_HIDE,SW_MINIMIZE,SW_RESTORE,SW_SHOW,SW_SHOWNORMAL�� ���� ����
	OutputDebugString(L"������������ Show �Ϸ�\n");

	while (GetMessage(&Message, 0, 0, 0)) { // ��� �޼���(������)�� �����ͼ� ó���� ; !���� ; �ڼ��� ������ å����
		TranslateMessage(&Message); //Ű���� �Է½� WM_CHAR �޼����� ��ȯ 
		DispatchMessage(&Message); // �޼����� �ü���� �����Ͽ� �����Ѱ��� ��� (�ݹ��Լ�;������ ���ν���)
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(// ���������� �������ڸ� ���;������ ���ν���(=�ݹ��Լ�)
	HWND hWnd,				// ������ �ڵ�
	UINT iMessage,			// �޼���
	WPARAM wParam,			// �޼��� �Ƕ����1
	LPARAM lParam)			// �޼��� �Ƕ����2
/*�̺�Ʈ�� �Ͼ������ ������ ó���ϴ� �Լ�; �̸� �޼����� ����� ����*/
/*�ü���� ������ ������ ���α׷��� ���� �� case���� ����� ����*/
/*callback : �ü���� �ҷ��شٶ�� ��*/
{
	LPCTSTR text = L"���� ������ ����";
	switch (iMessage)
	{
		case WM_PAINT:  // �����쿡 ���𰡸� �׸���, �̵��Ҷ� // �����츦 �������ٷν���
		{
			PAINTSTRUCT ps; //������ Ŭ���̾�Ʈ ������ �׸��� ������ ������ �ִ� ����ü; dc�� ���Ѵ�.
			HDC hdc = BeginPaint(hWnd, &ps); // �̰���(ps��) ����� �Ұ��Դϴ�.��� �غ��ϴ� �۾�
			TextOut(hdc, 100, 100, text, lstrlen(text)); // ���ڴ� ��ǥ, text����, lstrlen(text);text������ ���̸�ŭ �����
			OutputDebugString(L"(����������)WndProc�� WM_PAINT �߻�ó��\n");
			// hdc ; dc(device context)�� �ڵ� ; ����� �ϱ����� �ڷᱸ��
			EndPaint(hWnd, &ps); // ��
			return 0;
		}
		case WM_CREATE:
		{	//���ϵ� �����찡 ������� �� ������ �ڵ鰪�� ����ȴ�.; ���ϵ� ������ ����
			OutputDebugString(L"WndProc���� child ������ ��������\n");
			HWND hChildWnd = CreateWindow(
				ChildClassName,
				L"���ϵ� ������",
				WS_OVERLAPPEDWINDOW | WS_CHILD,
				150,
				150,
				260,
				200,
				hWnd,
				(HMENU)1000,  // ���ϵ� ������ ID
				g_hInst, //��������,��ü�ڵ�??
				(LPVOID)NULL);
			//���ϵ� �����찡 ���������� �����Ǿ����� ������ �ڵ��� �˻�
			if (!hChildWnd) return -1;

			ShowWindow(hChildWnd, SW_SHOW); // ���ϵ������츦 ȭ�鿡 �����ش�.
			OutputDebugString(L"WndProc���� child ����������� Show �Ϸ�\n");

			//��ư����
			OutputDebugString(L"WndProc���� ��ư�������� ��������\n");
			hChildWnd = CreateWindow(
				L"button",				//Ŭ�����̸�;
				L"��������",			//Ÿ��Ʋ
				WS_CHILD | WS_VISIBLE,	//��Ÿ��
				20,						//x ��ǥ
				400,					//y ��ǥ
				100,					//��
				30,						//����
				hWnd,					//�θ� ������
				(HMENU)ID_OK_BTN,		//��Ʈ�� id (������ 2000���� ����)
				g_hInst,				//��ü �ڵ�
				(LPVOID)NULL);			//������ ������

			if (!hChildWnd) return -1;	//��ư�� ��������� ������ ����
			OutputDebugString(L"WndProc���� ��ư������ ���� �� Show �Ϸ�\n");
			return 0;
		}
		case WM_COMMAND: //��ư Ŭ��
		{
			OutputDebugString(L"WM_COMMAND �߻� \n");
			//WM_COMMAND �޼����� �߻���Ų ��Ʈ���� ID�� �˻�
			if (LOWORD(wParam) == ID_OK_BTN)
			{	//�޼��� �ڽ��� ����.
				MessageBox(hWnd, L"��ư�� Ŭ���Ǿ���", L"��������", MB_OK); // MB_OK�� Ȯ�ι�ư
				OutputDebugString(L"MessageBog [Ȯ��] ó���Ϸ� \n");
			}
			return 0;
		}
		case WM_DESTROY:
			OutputDebugString(L"WndProc���� WM_DESTROYó������\n");
			PostQuitMessage(0); // ���⼭ WM_QUIT�޼����� ������
			OutputDebugString(L"WndProc���� WM_DESTROYó���Ϸ�\n");
			return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam); // ������ ������������ ���̽����� �� �̰�����
}

LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	LPCTSTR text = L"���ϵ� ������ ����";
	switch (message)
	{
		case WM_PAINT:  
		{
			PAINTSTRUCT ps; //����Ʈ ���� ����ü
			HDC hdc = BeginPaint(hWnd, &ps); // DC �ڵ� ������
			TextOut(hdc, 10, 10, text, lstrlen(text)); // ���ڿ� ��� �Լ�
			EndPaint(hWnd, &ps); // �ڵ�����
			OutputDebugString(L"ChildWndProc���� WM_PAINT ó���Ϸ�\n");
			return 0;
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}