#include<iostream>
#include<fstream>
#include<ctime>
#include<windows.h>

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

void displayHeader(string dateTime)
{
    cout<<"Welcome to Money and Taks Manager"<<endl;
    cout<<"Date & Time: "<<dateTime<<endl<<endl;
}

void displayWrongInput()
{
    system("cls");
    cout<<"Wrong Input!"<<endl<<endl;\
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

string userLogin(){
    string user, pass;
    cout<<"Username:"<<endl;
    getline(cin, user);
    cout<<"Password:"<<endl;
    pass = takePasswordFromUser();

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
    alertBox("Wrong User and Password.");
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

class softUser{
    public:

    void userAddAction(string dateTime, string LoggedInUser)
    {
        int op;
        string addType = "N/A";
        string inAccount = "N/A";
        string toAccount = "N/A";
        int amount = 0;
        string note = "N/A";
        system("cls");
        cout<<"Available Type for Adding:"<<endl<<"1. Income"<<endl<<"2. Expense"<<endl<<"3. Transfer"<<endl<<"4. Tasks"<<endl;
        cout<<"Select Your Option:"<<endl;
        cin>>op;
        switch(op)
        {
            case 1: addType = "Income"; break;
            case 2: addType = "Expense"; break;
            case 3: addType = "Transfer"; break;
            case 4: addType = "Tasks"; break;
            default: displayWrongInput();
        }
        if(op>= 1 && op <=4)
        {
            if(op>=1 && op <=3)
            {
                cout<<"Account:"<<endl;
                inAccount = setAccount();
            }
            if(op == 3)
            {
                cout<<"to Account:"<<endl;
                toAccount = setAccount();
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
                if(amount>0)
                {
                    cout<<"Note:"<<endl;
                    cin.ignore();
                    getline(cin, note);

                    ofstream foutput;
                    ifstream finput;
                    finput.open ("DB.txt");
                    foutput.open ("DB.txt",ios::app);

                    if(finput.is_open())
                    foutput<<endl<<dateTime<<"<=>"<<addType<<"<=>"<<inAccount<<"<=>"<<toAccount<<"<=>"<<amount<<"<=>"<<LoggedInUser<<"<=>"<<note;

                    system("cls");
                    cout<<"Add New "<<addType<<" Successfully Done"<<endl<<endl;

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
    
    void userDashboard(string LoggedInUser)
    {
        displayHeader(getDateTime());
        cout<<"Hello, "<<LoggedInUser<<endl<<endl;

        cout<<"Your Balance:"<<endl;
        cout<<"Cash: 200 BDT"<<endl;
        cout<<"Bank: 200 BDT"<<endl;
        cout<<"Card: 200 BDT"<<endl<<endl;

        cout<<"Your Tasks:"<<endl;
        cout<<"Pending: 20"<<endl;
        cout<<"Complete: 20"<<endl<<endl;

        cout<<"Action:"<<endl;
        cout<<"1. Add"<<endl;
        cout<<"2. View"<<endl;
        cout<<"3. Edit"<<endl;
        cout<<"4. Delete"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"Select Your Option:"<<endl;
        int op;
        cin>>op;
        switch(op)
        {
            case 1: userAddAction(getDateTime(), getLoggedInUser()); userDashboard(getLoggedInUser()); break;
            case 2: ; break;
            case 3: ; break;
            case 4: ; break;
            case 5: ; break;
            default: displayWrongInput(); userDashboard(getLoggedInUser());
        }

    }

};

int main()
{
    displayHeader(getDateTime());
    for(int i = 1; i <= 5; i++)
    {
        if(i>1){cout<<"Remaining:"<<6-i<<endl;}
        if(authUser(userLogin()))
        {
            class softUser LoggedInUser;
            LoggedInUser.userDashboard(getLoggedInUser());
            break;
        }
    }
    cout<<"Thank you for using this software.";
    return 0;
}
