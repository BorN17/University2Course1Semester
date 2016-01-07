#pragma once
#include <cstdio>
#include <vector>

using namespace std;

class Polinom
{
private:
	int n; // power of polinom
	vector<int> kf; // koeficients
public:
	Polinom();
	Polinom(double x);
	Polinom(vector<double> x);
	int size();
	double getKf(int x);
	void print();
	void findRoots(vector<double> &result);
	void add(Polinom x);
	void multiply(Polinom x);
};

class Matrix // square matrix
{
private:
	int n; // size of matrix
	vector<vector<double> > el; // elements
public:
	Matrix();
	Matrix(int x);
	Matrix(vector<vector<double> > x);
	void fill();
	void print();
	Polinom getOwnPol(); 
	void makeJordan();
};
