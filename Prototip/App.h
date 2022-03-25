#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <Windows.h>
#include <ctime>
#include <string>

class App {
public:
	int wm_timer(HWND m_hwnd); //обрабатываю события таймера
	int wm_paint(HWND m_hwnd); //перерисовываю окно
};
