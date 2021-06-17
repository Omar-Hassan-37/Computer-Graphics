#pragma once
#include <Windows.h>
#include <algorithm>
#include <math.h>
class CG
{
public:
	static void setP(HDC& hdc, int& x, int& y, COLORREF& c)
	{
		SetPixel(hdc, x, y, c);
	}
	static void drawLine1(HDC& hdc, int x1,int x2,int y1, int y2, COLORREF c)
	{
		int dx = x2 - x1;
		int dy = y2 - y1;
		if (abs(dx) >= abs(dy))
		{
			if (x2 < x1) {
				std::swap(x1, x2);
				std::swap(y1, y2);
			}
			int x = x1;
			
			SetPixel(hdc, x, y1,c);
			while (x < x2)
			{
				x++;
				double y = y1 + (double)dy / dx * (x - (double)x1);
				SetPixel(hdc, x, round(y), c);
			}
		}
		else
		{
			if (y2 < y1)
			{
				std::swap(y2, y1);
				std::swap(x2, x1);
			}
			
			int y = y1;
			SetPixel(hdc, x1, y, c);
			while (y < y2)
			{
				y++;
				double x = x1 + (double)dy / dx * (y - (double)y1);
				SetPixel(hdc, round(x), y, c);
			}

		}
	}
	static void drawLine2(HDC& hdc, int x1, int x2, int y1, int y2, COLORREF c)
	{

	}

	static void Draw8Points(HDC hdc, int xc, int yc, int a, int b, COLORREF color) {
		SetPixel(hdc, xc + a, yc + b, color);
		SetPixel(hdc, xc - a, yc + b, color);
		SetPixel(hdc, xc - a, yc - b, color);

		SetPixel(hdc, xc + a, yc - b, color);
		SetPixel(hdc, xc + b, yc + a, color);
		SetPixel(hdc, xc - b, yc + a, color);
		SetPixel(hdc, xc - b, yc - a, color);
		SetPixel(hdc, xc + b, yc - a, color);
	}

	static void Draw8PointsFill(HDC hdc, int xc, int yc, int a, int b, COLORREF color) {
		SetPixel(hdc, xc + a, yc + b, color);
		SetPixel(hdc, xc - a, yc + b, color);
		SetPixel(hdc, xc - a, yc - b, color);
		SetPixel(hdc, xc + a, yc - b, color);
		SetPixel(hdc, xc + b, yc + a, color);
		SetPixel(hdc, xc - b, yc + a, color);
		SetPixel(hdc, xc - b, yc - a, color);
		SetPixel(hdc, xc + b, yc - a, color);
		drawLine1(hdc, xc + a, xc - a, yc + b, yc - b, color);
	}



	static void CirclePolar(HDC hdc, int xc, int yc, int R, COLORREF color) {
		int x = R, y = 0;

		double theta = 0, dTheta = 1.0 / R;
		Draw8Points(hdc, xc, yc, x, y, color);
		while (x > y) {
			theta += dTheta;
			x = round(R * cos(theta));
			y = round(R * sin(theta));
			Draw8Points(hdc, xc, yc, x, y, color);
		}
	}

	static void CirclePolarFill(HDC hdc, int xc, int yc, int R, COLORREF color) {
		int x = R, y = 0;
		double theta = 0, dTheta = 1.0 / R;
		Draw8Points(hdc, xc, yc, x, y, color);
		while (x > y) {
			theta += dTheta;
			x = round(R * cos(theta));
			y = round(R * sin(theta));
			Draw8PointsFill(hdc, xc, yc, x, y, color);
		}
	}

	static int myDistance(int x1, int x2, int y1, int y2) {
		return (int) sqrt(pow((double)x2 - x1, 2) + pow((double)y2 - y1, 2));
	}


};

