#pragma once
#include <iostream>
#include <cstdlib>
#include<cmath>
#include <vector>
#include"CreatStation.h"
#include <algorithm>
using namespace std;
#define POINTS_COUNT 10	
//change map size to get more or less points
class Point
{
public:
	Point();	
	~Point();
	int x;
	int y;
	bool marked = false;
private:

};
/*void closestBrute(Point *p);
void farestBrute(vector<Point> p);
vector<Point> convexhull(Point *p);
void area(vector<Point> p);*/
Point::Point()
{
}
Point::~Point()
{
}

void closestBrute(Point *p) {
	double dmin = POINTS_COUNT + 1;
	int imin, jmin;
	for (int i = 0; i < POINTS_COUNT - 1; i++)
	{
		for (int j = i + 1; j < POINTS_COUNT; j++)
		{
			double distance = sqrt((p[i].x - p[j].x)*(p[i].x - p[j].x) + (p[i].y - p[j].y)*(p[i].y - p[j].y));
			if (distance == 0) break; //same point
			if (distance < dmin)
			{
				dmin = distance;
				imin = i;
				jmin = j;
			}
		}
	}
	cout << "shortest distance (brute force): "
		<< dmin << endl
		<< "point1: ("
		<< p[imin].x << ',' << p[imin].y << ')' << endl
		<< "point2: ("
		<< p[jmin].x << ',' << p[jmin].y << ')' << endl;
}
void farestBrute(vector<Point> p) {
	double dmax = -1;
	int imax, jmax;
	for (unsigned int i = 0; i < p.size(); i++)
	{
		for (unsigned int j = i + 1; j < p.size(); j++)
		{
			double distance = sqrt((p[i].x - p[j].x)*(p[i].x - p[j].x) + (p[i].y - p[j].y)*(p[i].y - p[j].y));
			if (distance == 0) continue; //same point
			if (distance > dmax)
			{
				dmax = distance;
				imax = i;
				jmax = j;
			}
		}
	}
	cout <<endl<< "farest distance of convex hull(brute force): "
		<< dmax << endl
		<< "point1: ("
		<< p[imax].x << ',' << p[imax].y << ')' << endl
		<< "point2: ("
		<< p[jmax].x << ',' << p[jmax].y << ')' << endl;
}
vector<Point> convexhull(Point *p) {	
	vector<Point> extremep;		
	for (int i = 0; i < POINTS_COUNT - 1; i++)
	{
		for (int j = i + 1; j < POINTS_COUNT; j++)
		{			
			int pos = 0, neg = 0;			
			int a = p[j].y - p[i].y, b = p[i].x - p[j].x
				, c = p[i].x * p[j].y - p[i].y * p[j].x;	
			
			for (int k = 0; k < POINTS_COUNT; k++)
			{		
				int answer = a*p[k].x + b*p[k].y - c;
				if (answer == 0)
					continue;
				else if (answer< 0)
					neg++;
				else if (answer> 0)
					pos++;
				
			}
			if (neg == 0 || pos == 0) {	
				extremep.push_back(p[i]); extremep.push_back(p[j]);				
			}
		}			
	}
	int *pointCount = new int[extremep.size()];
	for (unsigned int i = 0; i<extremep.size(); i++) pointCount[i] = 0;	
	
	for (unsigned int i = 0; i < extremep.size() - 1; i++){				
		for (unsigned int j = i+1; j < extremep.size(); j++)
		{
			if (extremep[i].x == extremep[j].x &&extremep[i].y == extremep[j].y)			
				pointCount[i]++;
			
			if (pointCount[i] > 1)
				extremep.erase(extremep.begin() + i);
			
		}			
	}	
	vector<Point> result;
	result.push_back(extremep[0]); extremep[0].marked = true;
	int i = 1;	
	while (result.size()<(extremep.size()/2))	//find adjacency point and push to result vector
	{
		result.push_back(extremep[i]); 
		extremep[i].marked = true;		
		for (unsigned int j = 0; j < extremep.size(); j++)
		{
			if (!extremep[j].marked&&extremep[i].x==extremep[j].x &&extremep[i].y==extremep[j].y)
			{				
				if (j % 2 == 1) {					
					i = j - 1; 
					break;
				}
				else
				{
					i = j + 1;
					break;
				}
			}
		}
	}
	//erase repeat adjacency point 
	for (unsigned int i = 0; i < result.size()-1; i++)
	{
		for (unsigned int j = i+1; j < result.size(); j++)
		{
			if (result[i].x == result[j].x &&result[i].y == result[j].y)
			{
				result.erase(result.begin() + i);
			}
		}
	}
	
	for (unsigned int i = 0; i < result.size(); i++)
		cout << result[i].x << ' ' << result[i].y << endl;	
	delete[] pointCount;
	extremep.resize(0); extremep.shrink_to_fit();
	return result;
}
void area(vector<Point> p) {
	double sumltrb = 0, sumrtlb = 0;
	//sum for left top * right bottom and leftbot*righttop
	//determinant calculate area	
	p.push_back(p[0]);
	for (unsigned int i = 1; i < p.size(); i++)
	{
		sumltrb += p[i - 1].x*p[i].y;
		sumrtlb += p[i - 1].y*p[i].x;
	}
	cout << "area: "<< abs((sumrtlb - sumltrb)) / 2 << endl;
	p.pop_back();
}