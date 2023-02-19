#include<iostream>
#include<fstream>
#include<ctime>
#include<windows.h>

using namespace std;

void Alert(string Prompt="", string Title="Alert !!",UINT BtnLst=MB_OK)
{
   // MessageBox(nullptr,Prompt.c_str(),Title.c_str(),BtnLst);
}

void displayHeader(string dateTime)
{
    cout<<"Welcome to Money and Taks Manager"<<endl;
    cout<<"Date & Time: "<<dateTime<<endl<<endl;
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

string userLogin(){
    string user, pass;
    cout<<"Username:"<<endl;
    getline(cin, user);
    cout<<"Password:"<<endl;
    getline(cin, pass);

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
            Alert("User Verified Successfully.");
            return 1;
        }
    }
    storedUserInfo.close();
    Alert("Wrong User and Password.");
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

class softUser{
    public:
    void userAddAction(string dateTime, string LoggedInUser)
    {
        int op;
        string addType;
        int amount;
        string note;
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
            default: cout<<"Wrong Input!"<<endl;
        }
        if(op>= 1 && op <=4)
        {
        cout<<"Amount:"<<endl;
        cin>>amount;
            if(amount>=0)
            {
                cout<<"Note:"<<endl;
                cin>>note;
                ofstream foutput; 
                ifstream finput;
                finput.open ("DB.txt");
                foutput.open ("DB.txt",ios::app); 
                
                if(finput.is_open())
                foutput<<endl<<dateTime<<" "<<addType<<" "<<amount<<" "<<LoggedInUser<<" "<<note;
                
                system("cls");
                cout<<"Add New "<<addType<<" Successfully"<<endl<<endl;
                
                finput.close();
                foutput.close();
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
        cout<<"Select Your Option:"<<endl;
        int op;
        cin>>op;
        switch(op)
        {
            case 1: userAddAction(getDateTime(), getLoggedInUser()); userDashboard(getLoggedInUser()); break;
            case 2: ; break;
            case 3: ; break;
            case 4: ; break;
            default: cout<<"Wrong Input!"<<endl;
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

    return 0;
}