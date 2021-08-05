#ifndef CELL_H
#define CELL_H
#include <string>
#include <vector>

enum CellType {INTEGER, DOUBLE, STRING, FORMULA, NONE};

class Cell
{
private:
    char coloumn;
    std::size_t row;

    CellType type = NONE;

    int iNum;
    double dNum;
    std::string str;
    std::string formula;

public:

};

#endif