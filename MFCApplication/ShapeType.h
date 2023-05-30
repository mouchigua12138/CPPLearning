#pragma once


struct Point {
	double x, y;

	friend bool   operator == (Point const& x, Point const& y);
	friend double distance(Point const& x, Point const& y);
};

bool operator == (Point const& x, Point const& y);
double distance(Point const& x, Point const& y);

struct Line {

	Point* pt;
	int    size;

	Line() {
		this->pt = NULL;
		this->size = 0;
	}

	Line(int nLen) {
		this->pt = new Point[nLen];
		this->size = nLen;
	}

	void setPosition(Point pt, int nPosition) {
		if (nPosition >= this->size || nPosition < 0)return;
		this->pt[nPosition] = pt;
	}

	~Line() {
		if (!this->pt)delete[]this->pt;
	}
};

struct PolygonLine {
	Point* pt;
	int    size;

	PolygonLine() {
		this->pt = NULL;
		this->size = 0;
	}

	PolygonLine(int nLen) {
		this->pt = new Point[nLen];
		this->size = nLen;
	}

	void setPosition(Point pt, int nPosition) {
		if (nPosition >= this->size || nPosition < 0)return;
		this->pt[nPosition] = pt;
	}

	~PolygonLine() {
		if (!this->pt)delete[]this->pt;
	}
};
