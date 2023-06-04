#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Point {
	double x, y;
};

struct CStudent {
	std::string ID;
	std::string Name;
	Point pt;
	float score[3];
};

void SortAverage(std::vector<CStudent>& v);
double Distance(Point pt1, Point pt2);