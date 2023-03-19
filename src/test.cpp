#include<iostream>
#include<fstream>
#include<ctime>
#include<string>
#include<iomanip> 
#include<windows.h>
#include<conio.h>

using namespace std;


int splitString(string given_str, string tmpLoggedInUser, string tmpAccount, string action)
{
string delim = "<=>";
size_t pos = 0;  
string token1;
int temp = 1;
string ID, DateTime, addType, inAccount, toAccount, amount, LoggedInUser, note;
while (( pos = given_str.find (delim)) != string::npos)
{
    token1 = given_str.substr(0, pos);
    if(temp == 1)
    {
        ID = token1;
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
        if(LoggedInUser != tmpLoggedInUser)
        {
            return 0;
        }
    }
    temp++;
    given_str.erase(0, pos + delim.length());
}
note = given_str;
if(addType == "Income" && inAccount == tmpAccount)
{
    return stoi(amount);
}
else if(addType == "Expense" && inAccount == tmpAccount)
{
    return stoi(amount)*(-1);
}
else if(addType == "Transfer" && inAccount == tmpAccount)
{
    return stoi(amount)*(-1);
}
else if(addType == "Transfer" && toAccount == tmpAccount)
{
    return stoi(amount);
}

return 0;
}


int getDashboardBalance(string addType, string LoggedInUser)
{
    int temp = 0;
    string action = "Calculate";
    string getLine;
    ifstream MyRecordFile("DB.txt");
    while (getline (MyRecordFile, getLine))
    {
        temp+=splitString(getLine, LoggedInUser, addType, action);
    }
    MyRecordFile.close();
    return temp;
}


int main()
{
    // cout<<splitString("1003<=>2023-03-17 11:23:18<=>Tansfer<=>Bank<=>Cash<=>234<=>atik<=>sdf", "atik", "Bank", "Ok");
    cout<<getDashboardBalance("Bank", "atik");
    
    return 0;
}