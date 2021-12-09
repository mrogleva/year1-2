#include "FileOperator.hpp"

FileOperator::FileOperator(std::string filePath)
{
    file.open(filePath, std::ios::ate);
    if(!file)
    {
        throw std::runtime_error("Unable to open this file.");
    }
}

FileOperator::~FileOperator()
{
    file.close();
}

void FileOperator::saveToFile(std::string text)
{
    file << text << '\n';
}