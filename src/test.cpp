#include<iostream>
#include<fstream>
#include<ctime>
#include<string>
#include<iomanip> 
#include<windows.h>
#include<conio.h>

using namespace std;

int getMaxID()
{
    string delim = "<=>";
    size_t pos = 0;  
    string token1;
    int Line = 0;
    string strID, DateTime, addType, inAccount, toAccount, amount, LoggedInUser, note;
    string getLine;
    ifstream MyRecordFile("DB.txt");
    while (getline (MyRecordFile, getLine))
    {
        Line++; 
        int temp = 1;
        while (( pos = getLine.find (delim)) != string::npos)
        {  
            token1 = getLine.substr(0, pos);
            if(temp == 1)
            {
                strID = token1;
            }
            else if(temp == 2)
            {
                DateTime = token1;
            }
            else if(temp == 3)
            {
                addType = token1;
            }
            else if(temp == 4)
            {
                inAccount = token1;
            }
            else if(temp == 5)
            {
                toAccount = token1;
            }
            else if(temp == 6)
            {
                amount = token1;
            }
            else
            {
                LoggedInUser = token1;
            }
            getLine.erase(0, pos + delim.length());
            temp++;
        }
    }
    MyRecordFile.close();

    return stoi(strID);
}

int main()
{
    int strID = getMaxID();
    strID++;
    cout<<strID<<endl;

    return 0;
}