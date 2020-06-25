#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <iomanip>
#include <string.h>

#include <io.h>
#include <fcntl.h>
#include <string>
#include <windows.h>
#include <mmsystem.h>

#pragma once
#pragma comment(lib, "winmm.lib")


void gotoXY(int x, int y);

void changColor(int k);

void resizeConsole(int width, int height);

void setFontSize(int FontSize);

