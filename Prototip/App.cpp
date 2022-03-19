#include "App.h"

std::wstring App::time() {
	tm *ptm{};
	time_t t = std::time(nullptr);
	ptm = std::gmtime(&t);
	int hour = ptm->tm_hour + 3;
	int min = ptm->tm_min;
	int sec = ptm->tm_sec;
	auto hour_s = std::to_wstring(hour);
	hour_s = (hour < 10) ? L"0" + hour_s : hour_s;
	auto min_s = std::to_wstring(min);
	min_s = (min < 10) ? L"0" + min_s : min_s;
	auto sec_s = std::to_wstring(sec);
	sec_s = (sec < 10) ? L"0" + sec_s : sec_s;
	return hour_s + L":" + min_s + L":" + sec_s;
}

int App::wm_timer(HWND m_hwnd) {
	static std::wstring old_time{};
	std::wstring t{ time() };
	if (old_time != t) {
		InvalidateRect(m_hwnd, NULL, TRUE); //делает окно недействительным
		UpdateWindow(m_hwnd); //обновление окна - сообщение в WM_PAINT
	}
	old_time = t;
	return 0;
}

int App::wm_paint(HWND m_hwnd) {
	PAINTSTRUCT ps;
	RECT rect;
	HDC hDC = BeginPaint(m_hwnd, &ps); //получаю контекст устройства
	GetClientRect(m_hwnd, &rect); //получаю ширину и высоту клиентской области
	HBRUSH brush = CreateSolidBrush(RGB(110, 245, 245)); //создаю кисть для фона - циан
	HBRUSH old_brush = (HBRUSH)SelectObject(hDC, brush); //устанавливаю кисть в контекст устройства
	FillRect(hDC, &rect, brush); //закрашиваю фон
	std::wstring t = time(); //получаю время

	HFONT hFont = CreateFont(90, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET, 0, 0, 0, 0, L"Arial Bold"); //создаю новый шрифт
	HFONT old_hFont = (HFONT)SelectObject(hDC, hFont); //устанавливаю шрифт в контекст устройства

	SetTextColor(hDC, RGB(222, 24, 97)); //устанавливаю цвет текста
	SetBkColor(hDC, RGB(110, 245, 245)); //устанавливаю цвет фона под текстом
	DrawText(hDC, t.c_str(), -1, &rect,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER); //вывод времени в окно

	SelectObject(hDC, old_hFont); //заменяю шрифт на стоковый и освобождаю созданный шрифт
	SelectObject(hDC, old_brush); //заменяю кисть на стоковую и освобождаю созданную кисть
	DeleteObject(hFont); //удаляю созданный шрифт
	DeleteObject(brush); //удаляю созданную кисть

	EndPaint(m_hwnd, &ps); //освобождаю контекст устройства
	return 0;
}