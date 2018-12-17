#include "RandomAccessFIle.h"
#include "RandomAccessFIle.hpp"
#include <iostream>
#include "Main.h"
#include "PersistentVector.hpp"
#include <algorithm>


#pragma
struct Point {
	double x, y, z;
	int color;
	double d;

	friend ostream& operator<<(ostream& os, const Point& p) {
		return os << "(" << p.x << ',' << p.y << ',' << p.z << ")" << p.color;
	}
};

int main() {
	RandomAccessFile raf1("test.bin");

	//sequentielles schreiben
	raf1.write(1.0);
	raf1.write(2.0);
	raf1.write(3.0);

	// random access
	raf1.write(2.5, sizeof(double));

	cout << raf1.read<double>(0) << endl; //man muss hier den Datentyp angeben, sonst kann man nicht lesen. 
	cout << raf1.read<double>(1*sizeof(double)) << endl;
	cout << raf1.read<double>() << endl; //Sequenzielles Lesen ab der letzten Position
	

	PersistentVector<double> pv1("pv1.bin");
	if (pv1.size() == 0) {
		pv1.assign(10, 3.14);
	}

	cout << pv1.front() << endl;
	cout << pv1.back() << endl;
	cout << "capacity = " << pv1.capacity() << endl;
	

	//Aufgabe! Anfangsiterator und Entiterator
	sort(pv1.begin(), pv1.end());
	
	
	/*PersistentVector<Point> pv2("pv2.bin");
	Point p{ 1.1, 2.2, 3.3, 4 };
	if (pv2.size() == 0) {
		pv2.assign(10, p);
	}

	cout << pv2[0] << endl;
	cout << pv2[pv1.size() - 1] << endl;
	cout << "capacity = " << pv1.capacity() << endl;
	cout << "sizeof(Point) = " << sizeof(Point) << endl;*/

}