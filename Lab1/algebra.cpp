#pragma once
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include "algebra.h"
#include <iostream>

using namespace std;

Polinom::Polinom()
{
	n = 0;
	kf.clear();
	kf.push_back(0.0);
}

Polinom::Polinom(vector<double> x)
{
	n = x.size() - 1;
	kf.clear();
	kf.resize(n + 1);
	for (int i = 0; i <= n; i++)
		kf[i] = x[i];
}

Polinom::Polinom(double x)
{
	n = 0;
	kf.clear();
	kf.push_back(x);
}

int Polinom::size()
{
	return n;
}

double Polinom::getKf(int x)
{
	if (x > n)
		return 0.0;
	return kf[x];
}

void Polinom::print()
{
	cout << kf[0];
	for (int i = 1; i <= n; i++)
		cout << " + " << kf[i] << "*x^" << i;
	cout << "\n";
}

void Polinom::findRoots(vector<double> &result)
{
	result.clear();
	if (n == 1)
	{
		result[0] = -kf[0] / kf[1];
	}
	if (n == 2)
	{
		double a = kf[2]; 
		double b = kf[1];
		double c = kf[0];
		double d = b * b - 4 * a * c;
		if (d >= 0)
			result[0] = (-b + sqrt(d)) / 2 / a, result[1] = (-b - sqrt(d)) / 2 / a;
	}
}

void Polinom::add(Polinom x)
{
	n = max(n, x.size());
	kf.resize(n + 1);
	for (int i = 0; i <= n; i++)
		kf[i] += x.getKf(i);
}

void Polinom::multiply(Polinom x)
{
	n += x.size();
	kf.resize(n + 1);
	vector<double> result;
	for (int power = 0; power <= n; power++)
	{
		double res = 0;
		for (int i = 0; i <= n; i++)
			res += kf[i] * x.getKf(n - i);
		result.push_back(res);
	}
	for (int i = 0; i <= n; i++)
		kf[i] = result[i];
}

Matrix::Matrix()
{
	n = 0;
	el.clear();
}

Matrix::Matrix(int x)
{
	n = x;
	el.clear();
}

Matrix::Matrix(vector<vector<double> > x)
{
	n = x.size();
	el.resize(n);
	for (int i = 0; i < n; i++)
	{
		el[i].resize(n);
		for (int j = 0; j < n; j++)
			el[i][j] = x[i][j];
	}
}

void Matrix::fill()
{
	FILE *File;
	freopen_s(&File, "input.txt", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> el[i][j];
}

void Matrix::print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << el[i][j];
		cout << "\n";
	}
}

Polinom Matrix::getOwnPol()
{
	if (n == 1)
	{
		vector<double> result;
		result.resize(2);
		result[0] = el[0][0] * 1.0;
		result[1] = -1.0;
		return Polinom(result);
	}
	else
	{
		Polinom result;
		for (int i = 0; i < n; i++)
		{
			Polinom minusOne(-1.0);
			vector<vector<double> > lessPower;
			lessPower.clear();
			lessPower.resize(n - 1);
			for (int j = 1; j < n; j++)
			{
				lessPower[j - 1].clear();
				lessPower[j - 1].resize(n - 1);
				for (int k = 0; k < i; k++)
					lessPower[j - 1][k] = el[j][k];
				for (int k = i + 1; k < n; k++)
					lessPower[j - 1][k - 1] = el[j][k];
			}
			Matrix lessPowerMatrix(lessPower);
			Polinom additive = lessPowerMatrix.getOwnPol();
			if (i == 0)
			{
				vector<double> first;
				first.clear();
				first.resize(2);
				first[0] = el[0][0];
				first[1] = -1.0;
				additive.multiply(Polinom(first));
			}
			else
				additive.multiply(Polinom(el[0][i]));
			if (i % 2)
				additive.multiply(minusOne);
			result.add(additive);
		}
		return result;
	}
}

void Matrix::makeJordan()
{
	Polinom ownPolinom = getOwnPol();
	vector<double> ownNumbers; 
	ownPolinom.findRoots(ownNumbers);
	for (int i = 0; i < n; i++)
		el[i][i] = ownNumbers[i];
	for (int i = 1; i < n; i++)
		el[i][i - 1] = 1;
}
