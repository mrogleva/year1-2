#include <iostream>
#include <new>

void search(int** tiles,                  //List of all tiles
            int n,                        //Number of all tiles
            bool* freeTiles,              //List of used/unused tiles
            int element,                  //Current element to search with
            unsigned int& maxLength,      //The length of the max path
            unsigned int& currentLength,  //The length of the current path
            int* tilePath,                //List of the current path
            int* maxTilePath              //List of the max path
) {
    tilePath[currentLength] = element;
    ++currentLength;

    if (currentLength > maxLength) {  //If a longer path is found it is copied
        maxLength = currentLength;
        for (unsigned int i = 0; i < maxLength + 1; ++i) {
            maxTilePath[i] = tilePath[i];
        }
    }

    if (maxLength - 1 == n) {  //Case when all tiles are used
        return;
    }

    for (unsigned int i = 0; i < n; ++i) {  //Recursive searching
        if (freeTiles[i] == true && (tiles[i][0] == element || tiles[i][1] == element)) {
            freeTiles[i] = false;
            if (tiles[i][0] == element) {
                search(tiles, n, freeTiles, tiles[i][1], maxLength, currentLength, tilePath, maxTilePath);
            }
            if (tiles[i][1] == element) {
                search(tiles, n, freeTiles, tiles[i][0], maxLength, currentLength, tilePath, maxTilePath);
            }
            freeTiles[i] = true;
        }
    }
    --currentLength;
}

int main() {
    //Number of tiles input
    int n;
    do {
        if (n < 0) {
            std::cout << "The number of tiles should be a positive number!";
        }
        std::cout << "N=";
        std::cin >> n;
    } while (n < 0);
    if (!std::cin) {
        std::cout << "Error! Invalid input!\n";
        return 0;
    }
    int** tiles = new (std::nothrow) int*[n];
    if (!tiles) {
        std::cout << "Error! Bad memory allocation!\n";
        return 0;
    }

    for (unsigned int i = 0; i < n; ++i) {
        tiles[i] = new (std::nothrow) int[2];
        if (!tiles[i]) {
            for (unsigned int j = 0; j <= i; ++j)
                delete[] tiles[j];
            delete[] tiles;
            std::cout << "Error! Bad memory allocation!\n";
            return 0;
        }
    }

    //Domino tile input
    std::cout << "Input the domino tile numbers!\n";
    for (unsigned int i = 0; i < n; ++i) {
        std::cin >> tiles[i][0];
        std::cin >> tiles[i][1];
        for (unsigned int j = 0; j < i; ++j) {
            if ((tiles[i][0] == tiles[j][0] && tiles[i][1] == tiles[j][1]) ||
                (tiles[i][0] == tiles[j][1] && tiles[j][0] == tiles[i][1])) {
                std::cout << "Error! Invalid input! Identical tiles!\n";
                for (size_t i = 0; i < n; ++i)
                    delete[] tiles[i];
                delete[] tiles;
                tiles = nullptr;
                return 0;
            }
        }
        if (!std::cin) {
            std::cout << "Error! Invalid input!\n";
            for (size_t i = 0; i < n; ++i)
                delete[] tiles[i];
            delete[] tiles;
            tiles = nullptr;
            return 0;
        }
    }

    //Searching for a path
    //Dynamic memory for the arrays
    bool* freeTiles = new (std::nothrow) bool[n];  //List of used/unused tiles
    if (!freeTiles) {
        std::cout << "Error! Bad memory allocation!\n";
        return 0;
    }
    int* tilePath = new (std::nothrow) int[n + 1];  //List of current path
    if (!tilePath) {
        std::cout << "Error! Bad memory allocation!\n";
        delete[] freeTiles;
        return 0;
    }
    int* maxPathOfNumbers = new (std::nothrow) int[n + 1];  //List of longest path
    if (!maxPathOfNumbers) {
        delete[] tilePath;
        delete[] freeTiles;
        std::cout << "Error! Bad memory allocation!\n";
        return 0;
    }
    if (!freeTiles || !tilePath || !maxPathOfNumbers) {
        for (size_t i = 0; i < n; ++i)
            delete[] tiles[i];
        delete[] tiles;
        tiles = nullptr;
    }

    unsigned int maxLength = 0;
    unsigned int currentLength = 0;
    for (unsigned int i = 0; i < n; ++i) {
        freeTiles[i] = true;
    }

    //Choosing every tile as first and searching with function
    for (unsigned int i = 0; i < n; ++i) {
        freeTiles[i] = false;
        currentLength = 1;

        tilePath[0] = tiles[i][1];
        search(tiles, n, freeTiles, tiles[i][0], maxLength, currentLength, tilePath, maxPathOfNumbers);

        tilePath[0] = tiles[i][0];
        search(tiles, n, freeTiles, tiles[i][1], maxLength, currentLength, tilePath, maxPathOfNumbers);

        freeTiles[i] = true;
    }

    //Printing the answer
    for (int i = 0; i < maxLength - 1; ++i) {
        std::cout << maxPathOfNumbers[i] << "-" << maxPathOfNumbers[i + 1] << " ";
    }
    std::cout << '\n';

    delete[] maxPathOfNumbers;
    maxPathOfNumbers = nullptr;
    delete[] tilePath;
    tilePath = nullptr;
    delete[] freeTiles;
    freeTiles = nullptr;
    for (size_t i = 0; i < n; ++i)
        delete[] tiles[i];
    delete[] tiles;
    tiles = nullptr;

    return 0;
}