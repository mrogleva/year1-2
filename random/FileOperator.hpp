#ifndef FILE_OPERATOR_H
#define FILE_OPERATOR_H

#include <iostream>
#include <fstream>
#include <string>

class FileOperator
{
private:
    std::ofstream file;

public:
    FileOperator(std::string filePath);
    FileOperator(const FileOperator& other) = delete;
    ~FileOperator();

    void saveToFile(std::string text);

};

#endif