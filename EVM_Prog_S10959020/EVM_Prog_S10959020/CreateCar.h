#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#define N 10	
#define NK 1
// N*NK have to = POINTS_COUNT
//change map size to get more or less points
void createCar();
void createCar() {
	srand(5);	//change seeds to change map
	ofstream File("Car.txt");
	if (File.fail())
	{
		cout << "File open fail\n";
		exit(1);
	}
	for (int i = 0; i < N*NK; i++)
	{
		//coordinate size x,y
		int x = rand() % 50, y = rand() % 50;	//coordinate x = 0~49 y = 0~49
		if (i == N*NK - 1)
			File << x << " " << y;
		else
			File << x << " " << y << "\n";
	}
	File.close();
}