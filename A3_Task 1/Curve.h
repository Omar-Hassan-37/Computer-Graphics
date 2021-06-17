#pragma once

#include "resource.h"

#include <Windows.h>
#include <algorithm>
#include <math.h>

class Quad_Curve
{
public:

	static int Round(double x)
	{
		return (int)(x - 0.5);
	}

	template <int r, int c>
	class Matrix
	{
		int rows, columns;
		double M[r * c];

	public:
		Matrix() : rows(r), columns(c) { memset((char*)M, 0, r * c * sizeof(double)); }
		int getRows() { return rows; }
		int getColumns() { return columns; }
		double& operator()(int row, int col) { return M[row * columns + col]; }
		double& operator[](int index) { return M[index]; }
	};

	template <int M, int N, int L>
	static Matrix<M, L> multiplyMatrices(Matrix<M, N>& A, Matrix<N, L>& B)
	{
		Matrix <M, L> result;
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < L; j++)
			{
				result(i, j) = 0;
				for (int k = 0; k < N; k++)
				{
					result(i, j) += A(i, k) * B(k, j);
				}
			}
		}
		return result;
	}

	typedef Matrix<3, 3> Matrix3;
	typedef Matrix<2, 3> Matrix23;
	typedef Matrix<2, 1> Vector2;
	typedef Matrix<3, 1> Vector3;

	static Matrix3 constructBezierMatrix()
	{
		Matrix3 H;
		H(0, 0) = 1; H(0, 1) = -2; H(0, 2) = 1;
		H(1, 0) = -2; H(1, 1) = 2; H(1, 2) = 0;
		H(2, 0) = 1; H(2, 1) = 0; H(2, 2) = 0;
		return H;
	}

	static void DrawBezier(HDC hdc, int x[], int y[])
	{
		Matrix3 H = constructBezierMatrix();
		Matrix23 G;
		G(0, 0) = x[0]; G(0, 1) = x[1]; G(0, 2) = x[2];
		G(1, 0) = y[0]; G(1, 1) = y[1]; G(1, 2) = y[2];

		Matrix23 Coeff = multiplyMatrices(G, H);

		for (double t = 0; t <= 1; t += 0.001)
		{
			Vector3 vt;
			vt[2] = 1; vt[1] = t; vt[0] = t * t;
			Vector2 p = multiplyMatrices(Coeff, vt);
			SetPixel(hdc, Round(p[0]), Round(p[1]), 0x00FF0000);
		}
	}
};