#pragma once
#include<iostream>
#include<algorithm>
#include<vector>
#include "Q1_to_Q4.h" //class Point and POINTS_COUNT
using namespace std;
int *ass = new int[POINTS_COUNT];	//assignment col array

vector<vector<double>> findcost(Point *p1, Point *p2) {
	vector<vector<double>>cost;
	//can't reserve vector of vector size by (A,B)
	vector<double> temp_reserve(POINTS_COUNT);
	cost.resize(POINTS_COUNT, temp_reserve);
	//vector can't use [] if no reserved	
	cout << endl << "Cost Matrix : " << endl;
	for (int i = 0; i < POINTS_COUNT; i++)
	{
		for (int j = 0; j < POINTS_COUNT; j++)
		{
			cost[i][j] = sqrt((p1[i].x - p2[j].x)*(p1[i].x - p2[j].x) + (p1[i].y - p2[j].y)*(p1[i].y - p2[j].y));
			cout << cost[i][j] << " ";
		}
		cout << endl;
	}
	temp_reserve.clear(); temp_reserve.shrink_to_fit();	
	return cost;
}
void minusMin(vector<vector<double>> &c) {	
	double mini = 100;
	//step 1 sub each row's mini value
	for (unsigned int i = 0; i < c.size(); i++)
	{
		for (unsigned int j = 0; j < c[i].size(); j++) 
			if (c[i][j] < mini)
				mini = c[i][j];
		
		for (unsigned int j = 0; j < c.size(); j++)
			c[i][j] -= mini;
		
		mini = 100;
	}
	//step 2 : - each column mini value
	for (unsigned int i = 0; i < c.size(); i++)
	{
		for (unsigned int j = 0; j < c[i].size(); j++)
			if (c[j][i] < mini)
				mini = c[j][i];
		
		for (unsigned int j = 0; j < c[i].size(); j++)
			c[j][i] -= mini;
		
		mini = 100;
	}	
}
bool findAss(vector<vector<double>> &c)	//find assignment
{
	int *Assign = new int[c.size()]; 
	for (unsigned int i = 0; i < c.size(); i++) 
		Assign[i] = -1;
	unsigned int *rowZeros =new unsigned int[c.size()];
	bool *usedRow = new bool[c.size()];
	bool *usedCol = new bool[c.size()];
	for (unsigned int i = 0; i < c.size(); i++) {
		usedRow[i] = false; usedCol[i] = false; 
	}
	unsigned int nLine = 0;
	while (nLine<c.size()) {
		for (unsigned int i = 0; i<c.size(); i++) 
			rowZeros[i] = 0;
		for (unsigned int i = 0; i < c.size(); i++) {
			if (usedRow[i]) continue;
			for (unsigned int j = 0; j<c.size(); j++) {
				if (!usedCol[j] && c[i][j] == 0) rowZeros[i]++;
			}
		}
		unsigned int minZeros = c.size();
		int minRowId = -1;
		//find min zero row 
		for (unsigned int i = 0; i<c.size(); i++) {
			if (!usedRow[i] && rowZeros[i] < minZeros && rowZeros[i]>0) {
				minZeros = rowZeros[i];
				minRowId = i;
			}
		}
		if (minRowId == -1) break; //no minZero's rowID
		for (unsigned int j = 0; j<c.size(); j++) {
			if (c[minRowId][j] == 0 && !usedCol[j]) {
				usedRow[minRowId] = true;
				usedCol[j] = true;
				Assign[minRowId] = j;
				break;
			}
		}
		nLine++;
	}
	for (unsigned int i = 0; i<c.size(); i++)
		ass[i] = Assign[i];
	delete[]Assign;	delete[]rowZeros;
	delete[]usedRow; delete[]usedCol;

	for (unsigned int i = 0; i < c.size(); i++) 
		if (ass[i] == -1) return false; //some no assign
	return true;
}
int* draw_Minus(vector<vector<double>> &c)
{
	bool *markRow = new bool[c.size()];	bool *markcol = new bool[c.size()];
	bool *rowLine = new bool[c.size()];	bool *colLine = new bool[c.size()];
	for (unsigned int i = 0; i < c.size(); i++) {
		markRow[i] = false; markcol[i] = false; rowLine[i] = false; colLine[i] = false;
	}	
	for (unsigned int i = 0; i < c.size(); i++)
		if (ass[i] == -1)
			markRow[i] = 1;
	//repeat mark rows which have zero
	//and then mark those rows which have assignment zero
	while (true) {
		int previous = 0;
		for (unsigned int i = 0; i < c.size(); i++)
			previous += markRow[i] + markcol[i];
		for (unsigned int i = 0; i < c.size(); i++) {
			if (markRow[i]) {
				for (unsigned int j = 0; j < c.size(); j++) {
					if (c[i][j] == 0) markcol[j] = true;
				}
			}
		}
		for (unsigned int j = 0; j < c.size(); j++) {
			if (markcol[j]) {
				for (unsigned int i = 0; i < c.size(); i++) {
					if (ass[i] == j) markRow[i] = true;
				}
			}
		}
		int change = 0;
		for (unsigned int i = 0; i < c.size(); i++)
			change += markRow[i] + markcol[i];
		if (previous == change) break;
	}
	//draw lines
	for (unsigned int i = 0; i < c.size(); i++) {
		if (!markRow[i]) rowLine[i] = 1;
		if (markcol[i]) colLine[i] = 1;
	}
	//find min 
	double min = 100;
	for (unsigned int i = 0; i < c.size(); i++) {
		for (unsigned int j = 0; j < c.size(); j++) {
			if (!rowLine[i] && !colLine[j] && c[i][j] < min)
				min = c[i][j];
		}
	}
	//minus min to every non-lined element
	for (unsigned int i = 0; i < c.size(); i++) {
		if (markRow[i])
			for (unsigned int j = 0; j < c.size(); j++)
				c[i][j] -= min;
	}
	for (unsigned int i = 0; i < c.size(); i++) {
		if (markcol[i])
			for (unsigned int j = 0; j < c.size(); j++)
				if(c[j][i]<0)
					c[j][i] += min;
	}
	delete[]markRow;	delete[]markcol;
	delete[]rowLine; delete[]colLine;
	return ass;
}