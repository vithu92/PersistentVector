#include "RandomAccessFIle.h"
#include "RandomAccessFIle.hpp"
#include <iostream>
#include "Main.h"


int main() {
	RandomAccessFile raf1("test.bin");

	//sequentielles schreiben
	raf1.write(1.0);
	raf1.write(2.0);
	raf1.write(3.0);

	// random access
	raf1.write(2.5, sizeof(double));

	cout << raf1.read<double>(0) << endl;
	cout << raf1.read<double>(1 *sizeof(double)) << endl;
	cout << raf1.read<double>(2 *sizeof(double)) << endl;


}