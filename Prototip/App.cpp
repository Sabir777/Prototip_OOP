#include "App.h"


int App::wm_timer(HWND m_hwnd) {
	/*
	static std::wstring old_time{};
	std::wstring t{ time() };
	if (old_time != t) {
		InvalidateRect(m_hwnd, NULL, TRUE); //делает окно недействительным
		UpdateWindow(m_hwnd); //обновление окна - сообщение в WM_PAINT
	}
	old_time = t;
	*/
	return 0;
}

int App::wm_paint(HWND m_hwnd) {
	
	PAINTSTRUCT ps;
	RECT rect;
	HDC hDC = BeginPaint(m_hwnd, &ps); //получаю контекст устройства
	const int number_of_lines{ 3 };
	GetClientRect(m_hwnd, &rect); //получаю ширину и высоту клиентской области

	//рисую фон
	HBRUSH brush = CreateSolidBrush(RGB(25, 25, 61)); //создаю кисть для фона
	HBRUSH old_brush = (HBRUSH)SelectObject(hDC, brush); //устанавливаю кисть в контекст устройства
	FillRect(hDC, &rect, brush); //закрашиваю фон

	//меняю цвет линий на более светлый
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(188, 32, 212)); //создаю карандаш
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen); // Выбираю свой Pen в DC, запоминаю старый Pen

	//рисую три вертикальные линии
	for (int i = 0; i < number_of_lines; ++i) {
		MoveToEx(hDC, 100 * (i + 1) + i, 0, NULL); //перемещаю положение начальной точки
		LineTo(hDC, 100 * (i + 1) + i, rect.bottom); //указываю конец линии
	}
	
	//рисую три горизонтальные линии
	for (int i = 0; i < number_of_lines; ++i) {
		MoveToEx(hDC, 0, 100 * (i + 1) + i, NULL); //перемещаю положение начальной точки
		LineTo(hDC, rect.right, 100 * (i + 1) + i); //указываю конец линии
	}
	
	//рисую квадратик
	SelectObject(hDC, CreateSolidBrush(RGB(84, 14, 35))); //создаю кисть для квадрата
	Rectangle(hDC, 0, 0, 100, 100); //рисую квадратик

	//рисую число в центре квадратика
	HFONT hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET, 0, 0, 0, 0, L"Arial Bold"); //создаю новый шрифт
	HFONT old_hFont = (HFONT)SelectObject(hDC, hFont); //устанавливаю шрифт в контекст устройства
	SetTextColor(hDC, RGB(250, 174, 22)); //устанавливаю цвет текста
	SetBkColor(hDC, RGB(84, 14, 35)); //устанавливаю цвет фона под текстом
	rect = RECT {0, 0, 100, 100};
	DrawText(hDC, L"11", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); //вывод времени в окно

	//восстанавливаю стоковые объекты, удаляю созданные объекты
	SelectObject(hDC, hOldPen); // Выбираю старый Pen в DC (освобождаю свой Pen из DC)
	DeleteObject(hPen); // Удаляю Pen
	SelectObject(hDC, old_brush); //заменяю кисть на стоковую и освобождаю созданную кисть
	DeleteObject(brush); //удаляю созданную кисть
	SelectObject(hDC, old_hFont); //заменяю шрифт на стоковый
	DeleteObject(hFont); //удаляю созданный шрифт

	EndPaint(m_hwnd, &ps); //освобождаю контекст устройства
	return 0;
}