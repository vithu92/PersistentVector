#include "RandomAccessFIle.h"


RandomAccessFile::RandomAccessFile(const string & filename) : m_fileName(filename)
{

	m_file.open(m_fileName.c_str(), ios::in | ios::out | ios::binary);

	if (!m_file) {
		//file doesn't exist
		m_file.clear(); //clear flags

		//create file and try to open again
		m_file.open(m_fileName.c_str(), ios::in | ios::out | ios::binary | ios::trunc);
		//dieser trunc sorgt dass falls diese File exisitert, wird diese Datei zurückgesetzt und falls nicht existiert, wird eine leere Datei erstellt
		if (!m_file) m_file.setf(ios::failbit);
	}
}

// return length in bytes
streamsize RandomAccessFile::length() const
{
	streampos curPos = m_file.tellg(); 
	
	m_file.seekg(0, ios::end); //seekg hat diverse Modi - hier wird die relative position gesucht.  => Zum Ende springen
	streampos length = m_file.tellg(); // Distanz zum Anfang ermitteln


	m_file.seekg(curPos);

	return length;
}

bool RandomAccessFile::truncate(streamsize length) {
	if (length < 0) return false;

	const streamsize buffSize = 128;
	char buffer[buffSize];
	const char *fileName = "tmp.tmp";

	// create temp file
	ofstream tmp(fileName, ios::out | ios::trunc | ios::binary);

	// copy first length bytes
	m_file.seekg(0);
	if (!m_file) return false;
	streamsize n;
	while (length) {
		n = __min(buffSize, length);
		m_file.read(buffer, n);
		tmp.write(buffer, n);
		length -= n;
	}

	// close both files
	m_file.close();
	tmp.close();

	// delete this file and rename tmp
	if (remove(m_fileName.c_str())) return false;
	if (rename(fileName, m_fileName.c_str())) return false;

	// open this file
	m_file.open(m_fileName.c_str(), ios::in | ios::out | ios::binary);

	return m_file.good();
}

