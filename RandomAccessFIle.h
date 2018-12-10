#pragma once

#include <fstream>

using namespace std;

class RandomAccessFile {
	string m_fileName;
	mutable fstream m_file; //filepointer darf sich ändert trotz benutzung der const methode


public:
	struct IOException : public exception {
		IOException(const char* msg): exception(msg){}
	};

	RandomAccessFile(const string& filename);
	virtual ~RandomAccessFile() = default;

	streamsize length() const;
	operator bool() const { return m_file.good(); }
	bool truncate(streamsize s);

	template<class T> T read(streampos pos = -1) const;
	template<class T> void write(const T& data, streampos pos = -1);
};