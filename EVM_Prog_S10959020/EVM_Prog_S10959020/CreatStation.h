#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#define M 10	
#define MK 1	//size of each station
// M*MK have to = POINTS_COUNT
//change map size to get more or less points
void createStation();
void createStation() {
	srand(10);	//change seeds to change map
	ofstream File("Station.txt");	
	vector<int> xarr(M), yarr(M);
	if (File.fail())
	{
		cout << "File open fail\n";
		exit(1);
	}	
	for (int j = 0; j < M; j++)
	{
		int x = rand() % 50, y = rand() % 50;	//coordinate x = 0~49 y = 0~49
		xarr[j] = x; yarr[j] = y;
	}
	xarr.insert(xarr.end(), xarr.begin(), xarr.end()); yarr.insert(yarr.end(), yarr.begin(), yarr.end());
	for (int i = 0; i < M*MK; i++)
	{			
		//coordinate size x,y				

		if (i == M*MK - 1)	//file end with space or endl might make error
			File << xarr[i] << " " << yarr[i];
		else
			File << xarr[i] << " " << yarr[i] << "\n";
	}
	xarr.clear(); yarr.clear();
	xarr.shrink_to_fit(); yarr.shrink_to_fit();
	File.close();	
}