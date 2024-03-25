#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "CreatStation.h"
#include "CreateCar.h"
#include "Q5.h"
#include "Q1_to_Q4.h"
using namespace std;
//#define POINTS_COUNT 10	
//change map size to get more or less points

int main() {
	createStation();
	createCar();	
	Point *points1 = new Point[POINTS_COUNT],*points2 = new Point[POINTS_COUNT];
	if (points1 == 0 || points2 == 0)		
		return 0;
	vector<Point> extremepoints1,extremepoints2;
	ifstream inStream1,inStream2;
	if (inStream1.fail())
	{
		cout << "Input file fail\n";
		exit(1);
	}
	inStream1.open("Station.txt");
	inStream2.open("Car.txt");
	
	int index=0;
	while (!inStream1.eof()&&!inStream2.eof())
	{
		inStream1 >> points1[index].x >> points1[index].y;
		inStream2 >> points2[index].x >> points2[index].y;
		index++;
	}

	closestBrute(points1); closestBrute(points2);
	cout << endl << "Station convex hull extremepoints: \n";
	extremepoints1 = convexhull(points1);
	
	cout << endl << "Car convex hull extremepoints: \n";
	extremepoints2 = convexhull(points2);
	farestBrute(extremepoints1); farestBrute(extremepoints2);
	area(extremepoints1); area(extremepoints2);
	
	vector<vector<double>> costMatrix ,costMatrix2;		
	costMatrix = findcost(points1, points2);
	//costMatrix.clear();
	//costMatrix = { { 2,10,9,7 },{ 15,4,14,8 },{ 13,14,16,11 },{ 4,15,13,9 } }; example in ppt
	int *assign = new int[costMatrix.size()];
	costMatrix2 = costMatrix;
	//cost is set to distance * 1
	minusMin(costMatrix); //minus row then minus column use min of each row or col	
	while (!findAss(costMatrix))	//while can't find assignment draw line and Minus non-drawed elements
	{
		assign = draw_Minus(costMatrix);
	}
	double cost = 0;
	cout << endl<<"Assignment: ";
	for (unsigned int i = 0; i < costMatrix.size(); i++) {	//compute the cost
		cost += costMatrix2[i][assign[i]];
		cout <<costMatrix2[i][assign[i]]<<' ';
	}
	cout <<endl <<"Total cost is: " << cost << endl; 	
	inStream1.close(); inStream2.close();
	costMatrix.clear(); costMatrix.shrink_to_fit();
	costMatrix2.clear(); costMatrix2.shrink_to_fit();
	delete[] points1;delete[] points2;	
	int endProg = 0;	
	system("PAUSE");
	return 0;
}