#include<iostream>
#include<stdlib.h>
#include<ctime>
using namespace std;
class Bank;
class Account
{
    protected:
        int accountno;
        string accountholdername;
        double balance;
    public:
        Account()
        {

        }
        Account(int a, string n,double b)
        {
            accountno=a;
            accountholdername=n;
            balance=b;
        }

        virtual void deposit(double amount)
        {
            balance=balance+amount;
        }

        virtual void withdraw(double amount)
        {
            if(amount>balance)
                cout<<"Insufficient balance!"<<endl;
            else
                balance=balance-amount;
        }

        virtual void display()
        {
            cout<<"Details of account number: "<<accountno<<endl;
            cout<<"Account holder name: "<<accountholdername<<endl;
            cout<<"Balance: "<<balance<<endl;
        }
        friend class Bank;
};

class Savings: public Account
{
    double interestrate;

    public:
        Savings()
        {


        }
        Savings(int a, string n,double b,double i):Account(a,n,b)
        {
            interestrate=i;
        }
        void addinterest()
        {
            balance=balance + balance*interestrate;
        }
        void display()
        {
            Account::display();
            cout<<"Interest rate: "<<interestrate<<endl;
            cout<<"Account type: Savings"<<endl;
        }
};

class Current: public Account
{
    double withdrawalfee;

    public:
        Current()
        {

        }
        Current(int a, string n,double b,double wf): Account(a,n,b)
        {
            withdrawalfee=wf;;
        }
        void withdraw(double amount)
        {
            if(amount<=balance)
            {
                balance=balance-amount;
                balance=balance-withdrawalfee;
            }
            else
            {
                cout<<"Oops! Insufficient Funds in Account No.: "<<accountno<<endl;
            }
        }
        void display()
        {
            Account::display();
            cout<<"Withdrawal Fee: "<<withdrawalfee<<endl;
            cout<<"Account type: Current"<<endl;
        }
};

class Transaction
{
    int transactionid;
    int accountno;
    string transactiontype;
    double amount;
    time_t datetime;

    public:
        Transaction()
        {

        }
        Transaction(int t,int an, string type, double a)
        {
            transactionid=t;
            accountno=an;
            transactiontype=type;
            amount=a;
            datetime=time(0);
        }

        void displaytransaction()
        {
            cout<<"Transaction ID:"<<transactionid<<" "<<"Transaction type:"<<transactiontype<<" "<<"Amount:"<<amount<<" "<<"Date time:"<<ctime(&datetime)<<endl;
        }
        friend class Bank;
};

class Bank
{
    Savings s[10];
    Current c[10];
    Transaction t[50];
    int scount,ccount;
    int transcount;
    public:
        Bank()
        {
            scount=0;
            ccount=0;
            transcount=0;
        }

        void createAccount(string accountholder,string accounttype, double initialbalance,double interestorfee)
        {
            if(accounttype=="Savings")
            {
                Savings sa(scount+1,accountholder,initialbalance,interestorfee);
                s[scount++]=sa;
            }
            else
            {
                Current cd(ccount+101,accountholder,initialbalance,interestorfee);
                c[ccount++]=cd;
            }

        }

        void displayaccount(int accountno,string type)
        {
            int i;
            if(type=="Savings")
            {
                for(i=0;i<scount;i++)
                {
                    if(s[i].accountno==accountno)
                    {
                        s[i].display();
                    }
                }
            }
            else
            {
                for(i=0;i<ccount;i++)
                {
                    if(c[i].accountno==accountno)
                    {
                        c[i].display();
                    }
                }
            }

        }

        void performtransaction(int accountno, string accounttype,string transactiontype, double amount)
        {
            if(accounttype=="Savings")
            {
                if(transactiontype=="Deposit")
                {
                    s[accountno-1].deposit(amount);
                    Transaction tr(transcount+1,accountno,transactiontype,amount);
                    t[transcount++]=tr;
                }
                else if(transactiontype=="Withdraw")
                {
                    s[accountno-1].withdraw(amount);
                    Transaction tw(transcount+1, accountno,transactiontype,amount);
                    t[transcount++]=tw;

                }
            }
            else
            {
                if(transactiontype=="Deposit")
                {
                    c[accountno-101].deposit(amount);
                    Transaction tr(transcount+1,accountno,transactiontype,amount);
                    t[transcount++]=tr;
                }
                else if(transactiontype=="Withdraw")
                {
                    c[accountno-101].withdraw(amount);
                    Transaction tw(transcount+1, accountno,transactiontype,amount);
                    t[transcount++]=tw;

                }

            }

        }

        void displaytransactions(int accountno)
        {
            int i;
            cout<<"Displaying transactions of account number: "<<accountno<<endl;
            for(i=0;i<transcount;i++)
            {
                if(t[i].accountno==accountno)
                {
                    t[i].displaytransaction();
                }
            }
        }
};

int main()
{

    Savings s;
    Current c;
    Bank mybank;
    string name,type;
    double amount,depositamount,withdrawamount,t;
    int choice1,choice2,choice3,accountno;
    cout<<"___________________________"<<endl;
    cout<<"| Welcome to National Bank|"<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"How may I help you?"<<endl;
    while(1)
    {
        cout<<"1. Create account"<<endl;
        cout<<"2. Perform transaction"<<endl;
        cout<<"3. Display transactions"<<endl;
        cout<<"4. Display account details"<<endl;
        cout<<"5. Exit"<<endl;
        cin>>choice1;
        switch(choice1)
        {
            case 1:
                cout<<"Enter the name of the account holder: "<<endl;
                cin>>name;
                cout<<"Enter the type of account: "<<endl;
                cin>>type;
                cout<<"Enter the initial balance in the account: "<<endl;
                cin>>amount;
                if(type=="Savings")
                {
                    cout<<"Enter interest rate: "<<endl;
                    cin>>t;
                }
                else
                {
                    cout<<"Enter withdrawal fee: "<<endl;
                    cin>>t;
                }
                mybank.createAccount(name,type,amount,t);
                break;

            case 2:
            	cout<<"What kind of transaction you want to perform?"<<endl;
                cout<<"1. Deposit"<<endl;
                cout<<"2. Withdrawal"<<endl;
                cin>>choice2;
                switch(choice2)
                {
                    case 1:
                        cout<<"Enter account number: "<<endl;
                        cin>>accountno;
                        cout<<"Enter Type of account: "<<endl;
                        cin>>type;
                        cout<<"Enter the amount to be deposited: "<<endl;
                        cin>>depositamount;
                        mybank.performtransaction(accountno,type,"Deposit", depositamount);
                        break;

                    case 2:
                        cout<<"Enter account number: "<<endl;
                        cin>>accountno;
                        cout<<"Enter the amount to be withdrawn: "<<endl;
                        cin>>withdrawamount;
                        cout<<"Enter type of account: "<<endl;
                        cin>>type;
                        mybank.performtransaction(accountno,type,"Withdraw", withdrawamount);
                        break;
                }
                break;

                case 3:
                    cout<<"Enter account number: "<<endl;
                    cin>>accountno;
                    mybank.displaytransactions(accountno);
                    break;

                case 4:
                    cout<<"Enter account number: "<<endl;
                    cin>>accountno;
                    cout<<"Enter type of account :"<<endl;
                    cin>>type;
                    mybank.displayaccount(accountno,type);
                    break;

                case 5:
                	cout<<"Thank you for choosing us :)"<<endl;
                	cout<<"See you soon"<<endl;
                    exit(1);
                    break;
        }
    }
}
