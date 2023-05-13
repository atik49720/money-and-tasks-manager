#include<iostream>
#include<fstream>
#include<ctime>
#include<string>
#include<iomanip>
#include<windows.h>
#include<conio.h>

using namespace std;

void alertBox(string Prompt)
{
    string Title="Alert !!";
    UINT BtnLst=MB_OK;
    // MessageBox(NULL,Prompt.c_str(),Title.c_str(),BtnLst);
}

string getDateTime()
{
    time_t rawtime;
    tm* timeinfo;
    char buffer [80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,80,"%Y-%m-%d %H:%M:%S",timeinfo);

    return buffer;
}

void activityLog(string str, string user)
{
    string dateTime = getDateTime();

    fstream f;
    f.open("activityLog.txt", ios::app);
    f <<endl<<dateTime<<"<=>"<<str<<"<=>"<<user;
    f.close();

}

void displayHeader(string dateTime)
{
    cout<<"Welcome to Money and Tasks Manager"<<endl;
    cout<<"Date & Time: "<<dateTime<<endl<<endl;
}

void displayWrongInput()
{
    system("cls");
    cout<<"Wrong Input!"<<endl<<endl;
}

void displayWrongInput(string message)
{
    system("cls");
    cout<<message<<endl<<endl;
}

string takePasswordFromUser()
{
    HANDLE hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
  
    // Create a restore point Mode
    // is know 503
    GetConsoleMode(hStdInput, &mode);
  
    // Enable echo input
    // set to 499
    SetConsoleMode(hStdInput, mode & (~ENABLE_ECHO_INPUT));

    // Take input
    string ipt;
    getline(cin, ipt);
  
    // Otherwise next cout will print
    // into the same line
    cout << endl;
  
    // Restore the mode
    SetConsoleMode(hStdInput, mode);
  
    return ipt;
}

string takePasswordFromUser2() {
    string pass = "";
    char c;
    while (true) {
        c = _getch();
        if (c == 13) { // if enter key is pressed
            cout << endl;
            break;
        }
        else if (c == 8) { // if backspace is pressed
            if (pass.length() > 0) {
                pass.erase(pass.length() - 1);
                cout << "\b \b";
            }
        }
        else {
            pass += c;
            cout << "*";
        }
    }
    return pass;
}

string userLogin(){
    string user, pass;
    cout<<"Username:"<<endl;
    getline(cin, user);
    cout<<"Password:"<<endl;
    pass = takePasswordFromUser2();

    ofstream tempLoggedInUser("temp.txt");
    tempLoggedInUser<<user;

    return user + " " + pass;
}

int authUser(string userInput)
{
    string userInfo;
    ifstream storedUserInfo("users.txt");
    while (getline (storedUserInfo, userInfo))
    {
        int temp = userInput.compare(userInfo);
        if(temp == 0)
        {
            system("cls");
            alertBox("User Verified Successfully.");
            return 1;
        }
    }
    storedUserInfo.close();
    alertBox("Wrong User or Password.");
    return 0;
}

string getLoggedInUser()
{
    string LoggedInUser, temp;
    ifstream tempLoggedInUser("temp.txt");
    while (getline (tempLoggedInUser, LoggedInUser))
    {
       temp = LoggedInUser;
    }
    tempLoggedInUser.close();

    return temp;
}

string setType()
{
    int op;
    string temp;
    cout<<"1. Income"<<endl<<"2. Expense"<<endl<<"3. Transfer"<<endl<<"4. Tasks"<<endl;
    cout<<"Select Your Option:"<<endl;
    cin>>op;
    switch(op)
    {
        case 1: temp = "Income"; break;
        case 2: temp = "Expense"; break;
        case 3: temp = "Transfer"; break;
        case 4: temp = "Tasks"; break;
        default: temp = "Wrong"; displayWrongInput();
    }

    return temp;
}

string setAccount()
{
    int op;
    string temp;
    cout<<"1. Cash"<<endl<<"2. Bank"<<endl<<"3. Card"<<endl;
    cout<<"Select Your Option:"<<endl;
    cin>>op;
    switch(op)
    {
        case 1: temp = "Cash"; break;
        case 2: temp = "Bank"; break;
        case 3: temp = "Card"; break;
        default: displayWrongInput();
    }

    return temp;
}

void deleteLine(const char *file_name, int n)
{
    char op;
    cout<<"Are You Sure? Y/N"<<endl;
    cin>>op;
    if(op == 'Y' || op == 'y')
    {  
        ifstream is(file_name);
        ofstream ofs;
        ofs.open("tempDB.txt", ofstream::out);
        char c;
        int line_no = 1;
        while (is.get(c))
        {
            if (c == '\n')
            line_no++;
            if (line_no != n)
                ofs << c;
        }
        ofs.close();
        is.close();
        remove(file_name);
        rename("tempDB.txt", file_name);

        system("cls");
        cout<<"Delete Record Successfully Done"<<endl<<endl;
        activityLog("Delete Record Successfully Done",getLoggedInUser());
    }
}

void updateLine(const string& filename, const string& newLine, int lineNum)
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

bool validateDate(int YYYY, int MM, int DD)
{
    if(YYYY>=1000 && YYYY <= 3000)
    {
        if(MM>=1 && MM<=12)
        {
            if(DD>=1 && DD<=31)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void splitString(string given_str, string tmpLoggedInUser, string tmpAddType)
{
string delim = "<=>";
size_t pos = 0;  
string token1;
int temp = 1, flag = 0;
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
        if(addType != tmpAddType)
        {
            return;
        }
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
            return;
        }
    }
    temp++;
    given_str.erase(0, pos + delim.length());
}
note = given_str;
if(tmpAddType == "Transfer" || tmpAddType == "Tasks" )
{
    cout<<ID<<" "<<DateTime<<" "<<inAccount<<" "<<toAccount<<" "<<amount<<" "<<note<<endl;
}
else
{
    cout<<ID<<" "<<DateTime<<" "<<inAccount<<" "<<amount<<" "<<note<<endl;
}
}

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
if(addType == "Tasks" && inAccount == tmpAccount)
{
    return 1;
}
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

int getLineNo(string tmpID, string tmpLoggedInUser)
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
        if(strID == tmpID && LoggedInUser == tmpLoggedInUser)
        {
            return Line;
        }
    }

    return 0;
}

string getUpdateLine(string tmpID, string tmpLoggedInUser)
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
            else if(temp == 7)
            {
                LoggedInUser = token1;
            }
            else
            {
                note = token1;
            }
            getLine.erase(0, pos + delim.length());
            temp++;
        }
        if(strID == tmpID && inAccount == "Pending" && LoggedInUser == tmpLoggedInUser)
        {
            inAccount = "Complete";
            return strID+"<=>"+DateTime+"<=>"+addType+"<=>"+inAccount+"<=>"+toAccount+"<=>"+amount+"<=>"+LoggedInUser+"<=>"+note;
        }
    }

    return "Wrong";
}

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

    return stoi(strID);
}

class softUser{
    public:
    void userAddAction(string dateTime, string LoggedInUser)
    {
        int op, temp2;
        int strID = getMaxID();
        strID++;
        string addType = "N/A";
        string inAccount = "N/A";
        string toAccount = "N/A";
        int amount = 0;
        string note = "N/A";
        system("cls");
        cout<<"Available Type for Adding:"<<endl;
        addType = setType();
        if(addType != "Wrong")
        {
            if(addType == "Income" || addType == "Expense" || addType == "Transfer")
            {
                cout<<"Account:"<<endl;
                inAccount = setAccount();
            }
            else
            {
                inAccount = "Pending";
            }
            if(addType == "Transfer")
            {
                cout<<"to Account:"<<endl;
                toAccount = setAccount();
                temp2 = getDashboardBalance(inAccount, LoggedInUser);
            }
            if(addType == "Tasks")
            {
                int YYYY, MM, DD;
                cout<<"Date: (YYYY MM DD)"<<endl;
                cin>>YYYY>>MM>>DD;
                if(validateDate(YYYY,MM,DD) == false)
                {
                    displayWrongInput();
                    return;
                }
                toAccount = to_string(YYYY)+"-"+to_string(MM)+"-"+to_string(DD);
            }
            int temp = inAccount.compare(toAccount);
            if(temp == 0)
            {
                displayWrongInput();
            }
            else
            {
                cout<<"Amount:"<<endl;
                cin>>amount;
                if(addType == "Transfer" && amount>temp2)
                {
                    displayWrongInput("Not enough balance for transfer.");
                    return;
                }
                if(amount>=0)
                {
                    cout<<"Note:"<<endl;
                    cin.ignore();
                    getline(cin, note);

                    ofstream foutput;
                    ifstream finput;
                    finput.open ("DB.txt");
                    foutput.open ("DB.txt",ios::app);
                    
                    if(finput.is_open())
                    foutput<<endl<<strID<<"<=>"<<dateTime<<"<=>"<<addType<<"<=>"<<inAccount<<"<=>"<<toAccount<<"<=>"<<amount<<"<=>"<<LoggedInUser<<"<=>"<<note;

                    system("cls");
                    cout<<"Add New "<<addType<<" Successfully Done"<<endl<<endl;
                    activityLog("Add New "+addType+" Successfully Done",getLoggedInUser());

                    finput.close();
                    foutput.close();
                }
                else
                {
                    displayWrongInput();
                }
            }
        
        }
    }
    
    void userDeleteAction(string LoggedInUser)
    {
        string ID;
        cout<<"Enter the Record ID No:"<<endl;
        cin.ignore();
        cin>>ID;
        int LineNo = getLineNo(ID, LoggedInUser);
        if(LineNo)
        {
            deleteLine("DB.txt",LineNo);
        }
        else
        {
            displayWrongInput();
        }
    }

    void userUpdateAction(string LoggedInUser, string action)
    {
        if(action == "markAsComplete")
        {
            string ID;
            cout<<"Enter the Record ID No:"<<endl;
            cin.ignore();
            cin>>ID;
            string newLine = getUpdateLine(ID, LoggedInUser);
            if(newLine == "Wrong")
            {
                displayWrongInput();
            }
            else
            {
                int LineNo = getLineNo(ID, LoggedInUser);
                if(LineNo)
                {
                    updateLine("DB.txt", newLine, LineNo);
                }
                system("cls");
                cout<<"Task Status Change Successfully Done"<<endl<<endl;
                activityLog("Task Status Change Successfully Done",getLoggedInUser());
            }
            
        }

    }

    void userViewAction(string LoggedInUser)
    {
        int op;
        string addType;
        system("cls");
        cout<<"Available Type for Viewing:"<<endl;
        addType = setType();
        if(addType != "Wrong")
        {
            system("cls");
            string getLine;
            ifstream MyRecordFile("DB.txt");
            cout<<"All "<<addType<<" of User: "<<LoggedInUser<<endl<<endl;
            if(addType == "Transfer")
            {
                cout<<"ID_No DateTime Account toAccount Amount Note"<<endl;
            }
            else if(addType == "Tasks")
            {
                cout<<"ID_No DateTime Status Task_Date Amount Note"<<endl;
            }
            else
            {
                cout<<"ID_No DateTime Account Amount Note"<<endl;
            }
            while (getline (MyRecordFile, getLine))
            {
                splitString(getLine, LoggedInUser, addType);
            }
            MyRecordFile.close();
            cout<<endl;
            cout<<"Action:"<<endl<<"1. Back to Dashboard"<<endl<<"2. Delete Record"<<endl;
            if(addType == "Tasks")
            {
                cout<<"3. Mark As Complete";
            }
            cout<<endl;
            cout<<"Select Your Option:"<<endl;
            cin>>op;
            switch(op)
            {
                case 1: system("cls"); break;
                case 2: userDeleteAction(LoggedInUser); break;
                if(addType=="Tasks")
                {
                    case 3: userUpdateAction(LoggedInUser, "markAsComplete");
                }
                default: break; displayWrongInput();
            }
        }
    }

    void userViewActivityLog(string LoggedInUser)
    {

    }

    int getDashboardBalance(string addType, string LoggedInUser)
    {
        int temp = 0;
        string getLine;
        ifstream MyRecordFile("DB.txt");
        while (getline (MyRecordFile, getLine))
        {
            temp+=splitString(getLine, LoggedInUser, addType, "Calculate");
        }
        MyRecordFile.close();
        return temp;
    }

    void userDashboard(string LoggedInUser)
    {
        displayHeader(getDateTime());
        cout<<"Hello, "<<LoggedInUser<<endl<<endl;

        cout<<"Your Balance:"<<endl;
        cout<<"Cash: "<<getDashboardBalance("Cash", LoggedInUser)<<" BDT"<<endl;
        cout<<"Bank: "<<getDashboardBalance("Bank", LoggedInUser)<<" BDT"<<endl;
        cout<<"Card: "<<getDashboardBalance("Card", LoggedInUser)<<" BDT"<<endl<<endl;

        cout<<"Your Tasks:"<<endl;
        cout<<"Pending: "<<getDashboardBalance("Pending", LoggedInUser)<<endl;
        cout<<"Complete: "<<getDashboardBalance("Complete", LoggedInUser)<<endl<<endl;

        cout<<"Action:"<<endl;
        cout<<"1. Add"<<endl;
        cout<<"2. View"<<endl;
        cout<<"3. Delete"<<endl;
        cout<<"4. Refresh"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"Select Your Option:"<<endl;
        char op;
        cin>>op;
        switch(op)
        {
            case '1': userAddAction(getDateTime(), LoggedInUser); userDashboard(LoggedInUser); break;
            case '2': userViewAction(LoggedInUser); userDashboard(LoggedInUser); break;
            case '3': userDeleteAction(LoggedInUser); userDashboard(LoggedInUser); break;
            case '4': system("cls"); userDashboard(LoggedInUser); break;
            case '5': break;
            default: displayWrongInput(); userDashboard(LoggedInUser); break;
        }
    }
};

int main()
{
    activityLog("Program Run Successfully Done", "Guest");
    displayHeader(getDateTime());
    for(int i = 1; i <= 5; i++)
    {
        if(i>1){cout<<"Remaining:"<<6-i<<endl;}
        if(authUser(userLogin()))
        {
            activityLog("User Logged In Successfully",getLoggedInUser());
            class softUser LoggedInUser;
            LoggedInUser.userDashboard(getLoggedInUser());
            break;
        }
        else
        {
            activityLog("Wrong User or Password Given", getLoggedInUser());
        }
    }
    system("cls");
    cout<<"Thank you for using this software."<<endl<<endl;
    activityLog("Program Close Successfully Done",getLoggedInUser());

    return 0;
}
