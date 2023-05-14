#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void updateFileLine(const string& filename, const string& newLine, int lineNum)
{
    ifstream fileIn(filename);
    ofstream fileOut("tempDB.txt");

    string line;
    int currentLine = 0;

    while (getline(fileIn, line))
    {
        currentLine++;

        if (currentLine == lineNum)
        {
            fileOut << newLine << endl;
        }
        else
        {
            fileOut << line << endl;
        }
    }

    fileIn.close();
    fileOut.close();

    // Rename temp file to original filename
    remove(filename.c_str());
    rename("tempDB.txt", filename.c_str());
}


int main() {

    updateFileLine("test.txt", "ok",4);


    return 0;
}
