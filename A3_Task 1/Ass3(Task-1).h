#pragma once

#include "resource.h"

#include <Windows.h>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;

class Ass3_Task_1 {

public:

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

	static void setP(HDC& hdc, int& x, int& y, COLORREF& c)
	{
		SetPixel(hdc, x, y, c);
	}

	static void drawLine1(HDC& hdc, int x1, int x2, int y1, int y2, COLORREF c)
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

			SetPixel(hdc, x, y1, c);
			while (x < x2)
			{
				x++;
				double y = y1 + (x - (double)x1) * (double)dy / dx;
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
				double x = x1 + (y - (double)y1) * (double)dy / dx;
				SetPixel(hdc, round(x), y, c);
			}

		}
	}

	static int getRaduis(int x1, int x2, int y1, int y2) {
		return (int)sqrt(pow((double)x2 - x1, 2) + pow((double)y2 - y1, 2));
	}

	static int Round(double x)
	{
		return (int)(x - 0.5);
	}


	static union InCode
	{
		unsigned All : 1;
		struct { unsigned inside : 1; };
	};


	static InCode GetInCode(double x, double y, int xc, int yc, int r)
	{
		InCode in;
		in.inside = 0;
		int checkx = abs(xc - x);
		int checky = abs(yc - y);;
		if ((checkx <= r) && (checky <= r))
		{
			in.inside = 1;
		}
		else 
		{
			in.inside = 0;
		}

		return in;
	}


	static void CohenSuth2(HDC hdc, int xs, int ys, int xe, int ye, int xc, int yc, int r)
	{
		bool flag = false;
		//int checkx, checky;
		double newX, newY;
		int dx = abs(xe - xs);
		int dy = abs(ye - ys);
		//double m = dy / (float)dx;
		double x1 = xs, y1 = ys, x2 = xe, y2 = ye;
		int x, y;
		//int c = y1 - (m * x1);
		InCode in1 = GetInCode(x1, y1, xc, yc, r);
		InCode in2 = GetInCode(x2, y2, xc, yc, r);
		if ((in1.inside == 1) && (in2.inside == 0))
		{
			newX = x2;
			newY = y2;
			while (in2.inside == 0)
			{
				if (dx >= dy)
				{
					if (x1 <= x2)
					{
						newX--;
					}
					else
					{
						newX++;
					}
					newY = round(y1 + (newX - x1) * (y2 - y1) / (x2 - x1));
				}
				else
				{
					if (y1 <= y2)
					{
						newY--;
					}
					else
					{
						newY++;
					}
					newX = round(x1 + (newY - y1) * (x2 - x1) / (y2 - y1));
				}
				in2 = GetInCode(newX, newY, xc, yc, r);
			}
			x = newX;
			y = newY;
			drawLine1(hdc, x1, x, y1, y, 0x00FF0000);
			//MoveToEx(hdc, x1, y1, NULL);
			//LineTo(hdc, x, y);
		}

		else if ((in1.inside == 0) && (in2.inside == 1))
		{
			newX = x1;
			newY = y1;
			while (!in1.inside)
			{
				if (dx >= dy)
				{
					if (x1 < x2)
					{
						newX++;
					}
					else
					{
						newX--;
					}
					newY = round(y2 + (newX - x2) * (y1 - y2) / (x1 - x2));
					in1 = GetInCode(newX, newY, xc, yc, r);
				}
				else
				{
					if (y1 < y2)
					{
						newY++;
					}
					else
					{
						newY--;
					}
					newX = round(x2 + (newY - y2) * (x1 - x2) / (y1 - y2));
					in1 = GetInCode(newX, newY, xc, yc, r);
				}
			}
			x = newX;
			y = newY;
			drawLine1(hdc, x2, x, y2, y, 0x00FF0000);
		}

		/*else if ((in1.inside == 0) && (in2.inside == 0))
		{
			newX = x2;
			newY = y2;
			while (!in2.inside)
			{
				if (dx >= dy)
				{
					if (x1 < x2)
					{
						newX--;
					}
					else
					{
						newX++;
					}
					newY = round(y1 + (newX - x1) * (y2 - y1) / (x2 - x1));
					in2 = GetInCode(newX, newY, xc, yc, r);
				}
				else
				{
					if (y1 < y2)
					{
						newY--;
					}
					else
					{
						newY++;
					}
					newX = round(x1 + (newY - y1) * (x2 - x1) / (y2 - y1));
					in2 = GetInCode(newX, newY, xc, yc, r);
				}
			}
			x2 = newX;
			y2 = newY;

			newX = x1;
			newY = y1;
			while (!in1.inside)
			{
				if (dx >= dy)
				{
					if (x1 < x2)
					{
						newX++;
					}
					else
					{
						newX--;
					}
					newY = round(y2 + (newX - x2) * (y1 - y2) / (x1 - x2));
					in1 = GetInCode(newX, newY, xc, yc, r);
				}
				else
				{
					if (y1 < y2)
					{
						newY++;
					}
					else
					{
						newY--;
					}
					newX = round(x2 + (newY - y2) * (x1 - x2) / (y1 - y2));
					in1 = GetInCode(newX, newY, xc, yc, r);
				}
			}
			x1 = newX;
			y2 = newY;
			drawLine1(hdc, x1, x2, y1, y2, 0x00FF0000);
		}*/

		else if (in1.All && in2.All)
		{
			drawLine1(hdc, x1, x2, y1, y2, 0x00FF0000);
			flag = true;
		}
		if (!flag)
		{
			drawLine1(hdc, x, xe, y, ye, 0x000000FF);
			//MoveToEx(hdc, x, y, NULL);
			//LineTo(hdc, xe, ye);
		}
	}


};