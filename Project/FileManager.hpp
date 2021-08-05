#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <vector>

class FileManager
{
private:
	bool openedFile = false;
	std::size_t fileSize = 0;
	std::fstream* file;
};

#endif