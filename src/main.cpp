#include<iostream>
using namespace std;

int authUser(string user, string pass)
{
    if(user == pass)
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

int main()
{
    cout<<"Welcome to Money and Taks Manager"<<endl<<endl;

    string user, pass;
    cout<<"Username:"<<endl;
    getline(cin, user);
    cout<<"Password:"<<endl;
    getline(cin, pass);

    if(authUser(user, pass))
    {
        cout<<"Your Balance:"<<endl;
        cout<<"Cash: 200 BDT"<<endl;
        cout<<"Bank: 200 BDT"<<endl;
        cout<<"Card: 200 BDT"<<endl<<endl;

        cout<<"Your Tasks:"<<endl;
        cout<<"Pending: 20"<<endl;
        cout<<"Complete: 20"<<endl<<endl;

        cout<<"Action:"<<endl;
        cout<<"1. Add"<<endl;
        cout<<"2. Edit"<<endl;
        cout<<"3. Delete"<<endl;
    }
    return 0;
}