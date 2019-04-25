#include <Windows.h> //입출력등 주요함수

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // 윈도우 프로시저 타입 선언; ()안에 있는 함수를 사용할 거다
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst; //차일드 윈도우를 만들때 사용
LPCTSTR lpszClass = L"HelloAPI";
LPCTSTR ChildClassName = L"ChildWin";

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdParam,int nCmdShow) // 메인함수
// hinstance는 handle + instance (일종의 이름표다)
//hprevinstance 이전 인스턴스 핸들
//lpcmdline 커맨드 라인의 인자값을 받는 포인터 (나중에 배움)
//ncmdshow 윈도우가 화면상에 보여질때 상태 showwindow의 매개변수로 사용
{
	HWND hWnd;  // 윈도우 핸들을 hWnd변수로 설정; 하나의객체로 인식하고 윈도우는 이를가지고 찾아감
	MSG Message; // 메세지타입
	WNDCLASS  WndClass; /* "윈도우 클래스"라는 구조체 하나를 선언; 생성*/
	g_hInst = hInstance;  // 차일드 윈도우할때 사용

	/*윈도우 클래스 구조체를 커스텀; 윈도우의 모습을 설정*/
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //  윈도우의 바탕색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 프로그램에서 사용하는 커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 프로그램에서 사용하는 아이콘
	WndClass.hInstance = hInstance;				//프로그램의 객체 핸들;값은 우리가 알수 없다.
	WndClass.lpfnWndProc = (WNDPROC)WndProc;	//운도우 프로시저 지정 (콜백함수가 무엇인가?); (타입)변수이름
	// 콜백함수는 무조건 본인이 지정해줘야한다.
	WndClass.lpszClassName = lpszClass;			//클래스 이름 설정(대표이름); 위에서 HelloAPI라고 변수설정함
	// 클래스 함수 또한 본인이 지정해줘야한다.
	WndClass.lpszMenuName = NULL;				//메뉴
	WndClass.style = CS_HREDRAW | CS_VREDRAW;	//클래스의 스타일; 수직,수평 스타일
	RegisterClass(&WndClass); /*레지스터에 !등록, 프로그램이 운영체제에 요청*/

	WndClass.lpfnWndProc = ChildWndProc; // 차일드 윈도우
	WndClass.lpszClassName = ChildClassName;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(
		lpszClass,								/*윈도우 클래스 이름에대한 새 윈도우생성 (화면에 보이진않음); HelloAPI*/
		L"윈도우 프로그래밍",					//윈도우 타이틀 (타이틀바에 나오는이름)
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,		//윈도우 스타일 (중첩윈도우; 시스템 메뉴, 최대 최소 버튼, 타이틀바, 경계선 (우리가 흔히 보는 윈도우 설정 모음) | ?? )
		200, 200,								//윈도우가 보일때  x,y 좌표
		600, 600,								//윈도우의 폭과 높이
		(HWND)NULL,								//부모 윈도우 핸들
		(HMENU)NULL,							//윈도우가 가지는 메뉴 핸들
		hInstance,								//객체 핸들
		NULL);									//여분의 데이터

	ShowWindow(hWnd, nCmdShow);  /*만들어진 윈도우를 눈에 보여줌*/
	//hWnd는 위에서 설정한 CreateWindow변수
	//nCmdShow는 기본값
	//SW_HIDE,SW_MINIMIZE,SW_RESTORE,SW_SHOW,SW_SHOWNORMAL을 전부 포함

	while (GetMessage(&Message, 0, 0, 0)) { // 계속 메세지(윈도우)를 가져와서 처리함 ; !루프 ; 자세한 내용은 책참조
		TranslateMessage(&Message); //키보드 입력시 변환 
		DispatchMessage(&Message); // 적절한곳에 배달 (콜백함수;윈도우 프로시저)
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(// 메인윈도우 생성글자를 출력;윈도우 프로시져(=콜백함수)
	HWND hWnd,				// 윈도우 핸들
	UINT iMessage,			// 메세지
	WPARAM wParam,			// 메세지 피라미터1
	LPARAM lParam)			// 메세지 피라미터2
/*이벤트가 일어날때마다 반응을 처리하는 함수; 이를 메세지로 만들어 전달*/
/*운영체제가 반응을 인지해 프로그램에 전달 각 case마다 명령을 실행*/
/*callback : 운영체제가 불러준다라는 뜻*/
{
	LPCTSTR text = L"메인 윈도우 생성";
	switch (iMessage)
	{
	case WM_PAINT:  // 윈도우에 무언가를 그릴때, 이동할때 // 윈도우를 켰을때바라ㅗ실행
	{
		PAINTSTRUCT ps; //윈도우 클라이언트 영역에 그리는 정보를 가지고 있는 구조체; dc를 구한다.
		HDC hdc = BeginPaint(hWnd, &ps); // 이곳에(ps에) 출력을 할것입니다.라고 준비하는 작업
		TextOut(hdc, 100, 100, text, lstrlen(text)); // 숫자는 좌표, text변수, lstrlen(text);text변수의 길이만큼 잡아줌
		// hdc ; dc(device context)의 핸들 ; 출력을 하기위한 자료구조
		EndPaint(hWnd, &ps); // 끗
		return 0;
	}
	case WM_CREATE:
	{	//차일드 윈도우가 만들어진 후 윈도우 핸들값이 저장된다.
		HWND hChildWnd = CreateWindow(
			ChildClassName,
			L"차일드 윈도우",
			WS_OVERLAPPEDWINDOW | WS_CHILD,
			150,
			150,
			260,
			200,
			hWnd,
			(HMENU)2000,
			g_hInst,
			(LPVOID)NULL);
		//차일드 윈도우가 성공적으로 생성되었는지 윈도우 핸들을 검사
		if (!hChildWnd) return -1;

		ShowWindow(hChildWnd, SW_SHOW); // 차일드윈도우를 화면에 보여준다.
		RETURN 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam); // 위에서 설정되지않은 케이스들은 다 이곳으로
}

LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, message, wParam, lParam);
}