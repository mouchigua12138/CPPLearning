#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "CStudent.h"

void SortAverage(std::vector<CStudent>& v) {
	
	std::vector<float> vAverage;
	std::multimap<float, CStudent> mScoreStudent;
	std::multimap<float, CStudent>::iterator p;

	for (int i = 0; i < v.size(); i++) {
		float avg = (v[i].score[0] + v[i].score[1] + v[i].score[2]) / 3;
		vAverage.push_back(avg);
		mScoreStudent.insert(std::make_pair(avg, v[i]));
	}

	std::sort(vAverage.begin(), vAverage.end(), std::greater<float>());

	v.clear();

	for (int i = 0; i < vAverage.size(); i++) {
		for (p = mScoreStudent.begin(); p != mScoreStudent.end(); p++) {

			if (p->first == vAverage[i]) {
				v.push_back(p->second);
				break;
			}
		}
	}
}

double Distance(Point pt1, Point pt2) {
	double dx = pt1.x - pt2.x, dy = pt1.y - pt2.y;
	return sqrt(dx * dx + dy * dy);
}