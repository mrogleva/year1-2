#include <iostream>
#include <cstring>

// MEMORY LEAK при грешен вход за table
// How many letters would you like to encrypt?2
// a dd
// v
// free(): double free detected in tcache 2

const size_t MAX_STRING_SIZE = 100;
const size_t MAX_MSG_SIZE = 1000;

char*** createTable(size_t rows);
char* encrypt(char* original, char*** table, std::size_t rows, int* sizes);
// returns a pointer to the encrypted message

bool decrypt(char* encrypted, char*** table, std::size_t rows, int* sizes);
void copyString(char* from, char* to, std::size_t size); //TODO
int* tableFill(char*** table, size_t rows); //takes the console input and
    //returns a pointer to an array, which stores the sizes of each 
// criptic sequence, without the terminating character
void printTable(char*** table, size_t rows, int* sizes);
char** messagesInput(std::size_t cnt);
void printMessages(char** msgs, std::size_t cnt);
void clearTable(char*** table, std::size_t takenRows);
void lengthSort(int* values, int* tosort, unsigned size);
unsigned maxFrom(int* array, unsigned from, unsigned to);
char* myStrstr(char* haystack, std::size_t hSize, char* needle);

int main()
{
    std::cout<<"How many letters would you like to encrypt?";
    std::size_t rows;
    if(std::cin>>rows)
    {
        char*** table = createTable(rows);
        int* sizes = tableFill(table, rows);
        if(!sizes)
        {
            clearTable(table, rows);
            return 1;
        }

        std::cout<<"How many messages would you like to encrypt?"<<std::endl;
        std::size_t msgs;
        if(std::cin>>msgs)
        {
            char** messages = messagesInput(msgs);
            if(!messages)
            {
                clearTable(table, rows);
                delete[] sizes; ////////////////////
                return 1;
            }
            // printMessages(messages, msgs);
            for(std::size_t i = 0; i < msgs; ++i)
            {
                char* temp = encrypt(messages[i], table, rows, sizes);
                printMessages(&temp, 1);
                delete[] temp;
            }
        }
        else
        {
            std::cout<<"Please enter a positive number.";
            clearTable(table, rows);
            delete[] sizes; ////////////////////
            return 1;
        }
        
        std::cout<<"How many messages would you like to decrypt?"<<std::endl;
        std::size_t enc;
        if(std::cin>>enc)
        {
            char** encrypted = messagesInput(enc);
            if(!encrypted)
            {
                clearTable(table, rows);
                delete[] sizes; ////////////////////
                return 1;
            }
            // printMessages(encrypted, msgs);
            for(std::size_t i = 0; i < enc; ++i)
            {
                decrypt(encrypted[i], table, rows, sizes);
            }

            clearTable(table, rows);
            delete[] sizes;
        }
        else
        {
            std::cout<<"Please enter a positive number.";
            clearTable(table, rows);
            delete[] sizes; ////////////////////
            return 1;
        }
    }
    else
    {
        std::cout<<"Unable to create a table with "<<rows<<" rows.";
        return 1;
    }
    
    return 0; 
}

char*** createTable(size_t rows) 
{
    char*** table = new(std::nothrow) char**[rows];
    if (!table) return table;

    table[0] = new(std::nothrow) char*[rows*2]; //we need 2 coloumns
    // will have an additional array of the sizes of the criptic parts
    if (!table[0]) 
    {
        delete[] table;
        return nullptr;
    }

    for (size_t i = 1; i < rows; ++i)
    {
        table[i] = table[i-1] + 2;
    }

    return table;
}

char* encrypt(char* original, char*** table, std::size_t rows, int* sizes)
{
    std::size_t orSize = 0;
    while(original[orSize])
    {
        orSize += 1;
    }
    int* help = new(std::nothrow) int[orSize + 1]; //incl the terminating char
    if (!help) 
    {
        return nullptr;
    }
    for(std::size_t i = 0; i < orSize + 1; ++i)
    {
        help[i] = -1;
    }
    // will be used to store which row of the table should be used to 
    // encrypt each symbol. -1 if the symbol should stay the same
    std::size_t encSize = orSize;
    for(std::size_t i = 0; i<orSize; ++i) //to find the length of the encrypted msg
    {
        for(std::size_t j = 0; j<rows; ++j)
        {
            if(original[i] == table[j][0][0])
            {
                encSize += sizes[j] - 1;
                help[i] = j;
                break;
            }
        }
    }

    char* encrypted = new(std::nothrow) char[encSize + 1]; //incl the terminating char
    if (!encrypted) 
    {
        delete[] help;
        help = nullptr;
        return 0;
    }
    std::size_t index = 0;
    for(std::size_t i = 0; i < orSize + 1; ++i)
    {
        if(help[i] == -1)
        {
            encrypted[index] = original[i];
            index += 1;
        }
        if(help[i] != -1) 
        {
            for(std::size_t j = 0; j < sizes[help[i]]; ++j)
            {
                encrypted[index] = table[help[i]][1][j];
                index += 1;
            }
        }
    }
    
    delete[] help;
    help = nullptr;
    return encrypted;
}   

void clearTable(char*** table, std::size_t takenRows)
{
    // for(std::size_t i = 0; i<takenRows; ++i)
    // {
    //     delete table[i][0];
    //     delete[] table[i][1];
    // }
    delete[] table[0]; 
    delete[] table;
}

int* tableFill(char*** table, size_t rows)
{
    int* sizes = new(std::nothrow) int[rows];
    if(!sizes) return sizes;

    std::size_t filled = 0;
    for(std::size_t i = 0; i<rows; ++i)
    {
        char buffer[MAX_STRING_SIZE + 3];
        std::cin.ignore(10, '\n');
        std::cin.get(buffer, MAX_STRING_SIZE+3);
        std::size_t len = 0; 
        while(buffer[len])
        {
            len += 1;   
        }
        if(len > 2 && isalpha(buffer[0]) && buffer[1] == ' ')
        {
            if(i>0)
            {
                for(std::size_t j = 0; j < i; ++j)
                {
                    if(buffer[0] == table[j][0][0])
                    {
                        delete[] sizes;
                        std::cout<<"Every letter should have a unique encryption.";
                        return nullptr;
                    }
                }
            }
            
            char* tempChar = new(std::nothrow) char;
            if(!tempChar)
            {
                delete[] sizes;
                std::cout<<"Incorrect input.";
                return nullptr;
            }
            tempChar[0] = buffer[0];
            table[i][0] = tempChar;

            char* crypt = new(std::nothrow) char[len - 1]; //////////
            if(!crypt)
            {
                delete[] sizes;
                delete[] tempChar;
                return nullptr;
            }
            for(std::size_t j = 2; j < len + 1; ++j)/////////////
            {
                crypt[j-2] = buffer[j];
            }
            table[i][1] = crypt;
            sizes[i] = len - 2;
            filled += 1;
        }
        else
        {
            clearTable(table, filled);
            delete[] sizes;
            std::cout<<"Incorrect input.";
            return nullptr;
        }
    }
    return sizes;
}

void printTable(char*** table, size_t rows, int* sizes)
{
    for(std::size_t i = 0; i<rows; ++i)
    {
        std::cout<<table[i][0]<<" ";
        for(std::size_t j = 0; j<sizes[i]; ++j)
        {
            std::cout<<table[i][1][j];
        }
        std::cout<<std::endl;
    }
}

char** messagesInput(std::size_t cnt)
{
    char** messages = new(std::nothrow) char*[cnt];
    if(!messages)
    {
        std::cout<<"Memory error.";
        return nullptr;
    }
    char buffer[MAX_MSG_SIZE + 1];
    std::cout<<"Please enter the messages separated with a new line:"<<std::endl;
    for(std::size_t i = 0; i < cnt; ++i)
    {
        std::cin.ignore(10, '\n');
        std::cin.get(buffer, MAX_MSG_SIZE+1);
        std::size_t len = 0; 
        while(buffer[len])
        {
            len += 1;   
        }
        char* tempMsg = new(std::nothrow) char[len + 1];
        if(!tempMsg)
        {
            delete[] messages;
            return nullptr;
        }
        for(std::size_t j = 0; j < len + 1; ++j) //+1 is to copy the term char as well
        {
            tempMsg[j] = buffer[j];
        }
        messages[i] = tempMsg;
    }
    return messages;
}

void printMessages(char** msgs, std::size_t cnt)
{
    for(std::size_t i = 0; i < cnt; ++i)
    {
        std::size_t len = 0; 
        while(msgs[i][len])
        {
            len += 1;
        }
        for(std::size_t j = 0; j < len + 1; ++j)
        {
            std::cout<<msgs[i][j];
        }
        std::cout<<std::endl;
    }
}

bool decrypt(char* encrypted, char*** table, std::size_t rows, int* sizes)
{
    std::size_t encSize = 0;
    while(encrypted[encSize])
    {
        encSize += 1;
    }

    int* order = new(std::nothrow) int[rows]; //съхранява индексите на редовете в таблицата
    if(!order)
    {
        std::cout<<"Memory error.";
        return false;
    }
    for(std::size_t i = 0; i < rows; ++i)
    {
        order[i] = i;
    }
    lengthSort(sizes, order, rows);
    //по реда, указан в order, започваме да търсим съвпадения в копие и да ги махаме

    char tempOriginal[encSize + 1]; //оригиналният текст няма как да е по-дълъг
    for(std::size_t i = 0; i < encSize; ++i)
    {
        tempOriginal[i] = '\0';
    }
    char encCopy[encSize + 1];  //копие на низа, в което ще трием вече намерените изрази
    for(std::size_t i = 0; i < encSize; ++i)
    {
        encCopy[i] = encrypted[i];
    }

    char* found = encCopy; //указател, к' ще сочи началото на намерения израз
    for(std::size_t i = 0; i < rows; ++i)
    {
        while(found) 
        {
            found = myStrstr(encCopy, encSize, table[order[i]][1]);
            if(found)
            {
                for(std::size_t j = 0; j < sizes[order[i]]; ++j)
                {
                    found[j] = '\0';
                }
                tempOriginal[found - encCopy] = table[order[i]][0][0]; ///////
            }
        }
        found = encCopy;
    }
    for(std::size_t i = 0; i < encSize; ++i)
    {
        if(encCopy[i])
        {
            for(std::size_t j = 0; j < rows; ++j)
            {
                if(encCopy[i] == table[j][0][0])
                {
                    delete[] order;
                    std::cout<<"Bad string"<<std::endl;
                    return false;
                    //ако символ не е бил променен, а фигурира в 1 кол на таблицата,
                    //имаме противоречие 
                }
            }
        }
    }
    for(std::size_t i = 0; i < encSize; ++i)
    {
        if(encCopy[i])
        {
            tempOriginal[i] = encCopy[i]; 
            //събираме на едно място променените и запазените символи
        }
    }
    for(std::size_t i = 0; i < encSize; ++i)
    {
        if(tempOriginal[i])
        {
            std::cout<<tempOriginal[i];
        }
    }
    std::cout<<std::endl;
    delete[] order;
    return true;
}

unsigned maxFrom(int* array, unsigned from, unsigned to)
{
    unsigned max = from;
    for (unsigned i = from + 1; i < to; ++i) 
    {
        if (array[i] > array[max])
        {
            max = i;
        }
    }
    return max;
}

void lengthSort(int* values, int* tosort, unsigned size)
{
    for(unsigned i = 0; i < size-1; ++i) 
    {
        int m = maxFrom(values, i, size);
        int temp = tosort[i];
        tosort[i] = tosort[m];
        tosort[m] = temp;
    }
}

char* myStrstr(char* haystack, std::size_t hSize, char* needle)
{
    if(!needle || needle[0] == '\0')
    {
        return haystack;
    }
    std::size_t nSize = 0;
    while(needle[nSize])
    {
        nSize += 1;
    }
    if(nSize > hSize)
    {
        return nullptr;
    }
    
    std::size_t i = 0, j = 0, cnt = 0, move = 0;
    while(i < hSize && j < nSize)
    {
        if(haystack[i] == needle[j])
        {
            i += 1;
            j += 1;
            cnt += 1;
        }
        else
        {
            move += 1; //отместване
            i = move;
            j = 0;
            cnt = 0;
        }
    }
    if(cnt == nSize)
    {
        return &haystack[i-cnt];
    }
    else
    {
        return nullptr;
    }
}