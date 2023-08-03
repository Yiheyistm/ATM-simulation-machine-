#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <windows.h>
#include <fstream>
using namespace std;

HANDLE con;

float cn;
int num;
string tName;
struct ATM{
    private:
 string name;
 float acc;
 float money;
 float pass;

 public:
int color(int);
 void new_user(bool,float);
 void deposit(float,int,float);
 void transfer(float);
 void exist_user();
 void menu(float,string);
 void menu1();
 bool user_checker(float);
 void getData(int accnt){
     int pin;
     acc=accnt;
      cout<<"Full Name:";
        cin.sync();
       getline(cin,name);
     nm:
     cout<< "Create Pin:";
    cin>>pass;
    if(pass<1000){color(12);cout<<"Pin must be at least 4 digit\n";color(14);goto nm;}
    cout<<"Confirm Pin:";
    cin>>pin;
    if(pin!=pass)
    {
        color(12);
        cout<<"\nPin does't match, please input again!!\n";
        sleep(3);
        color(14);
        goto nm;
    }
    cout<< "Deposit some amount of money:";
    cin>>money;
    sleep(2);
    tName=name;
   }
}atm;

int ATM::color(int q){
return SetConsoleTextAttribute(con,q);
}
void ATM::new_user(bool flag,float uAcc){
   fstream file;
  file.open("input.txt",ios::out | ios::app);
    if(flag){
     atm.getData(uAcc);
      file.write((char*)&atm, sizeof(atm));
     file.close();
     atm.color(10);
    cout<<"\nSuccessfully Registered";
    sleep(3);
    atm.color(14);
    system("cls");
    atm.menu(uAcc,tName);

      }

 else{ atm.color(12);cout<<"Account is Taken, Please Create Another Account Number\n";sleep(3);system("cls");atm.color(14);}
}
void ATM::deposit(float accnt,int a,float mon=0){
    bool flag2=true;
        fstream file,file2;
    file.open("input.txt",ios::in);
    file2.open("temp.txt", ios::app | ios::out);
    file.read((char*)&atm, sizeof(atm));
    if(!file&&!file2){
        file.close();
       file2.close();

    }
    else{

        while(!file.eof()){

        if( a==1 && atm.acc==accnt){
                float g;
           cout<<"How much money do you want deposit:";
           cin>>g;
             atm.money+=g;

                file2.write((char*)&atm, sizeof(atm));
                cout<<endl;
                color(10);
                cout<<"\tDeposit "<<g<<" birr is succeed\n";
                color(14);
            }
        else if(a==2 && atm.acc==accnt){
                float g;
                int count1=1;
                  cout<<endl<<endl;
                  re:
                cout<< "  How much money do you want to Withdraw:";
                  cin>>g;
                if(atm.money < g){color(12);
                 cout<<"  Insufficient Balance\n Please first check your balance\n"; sleep(3);color(14);
                 if(count1<3) { ++count1; goto re;}
                 else {file2.write((char*)&atm, sizeof(atm)); color(12);cout<<" You lost your 3 trial\n";}
                    }
                else{
                  atm.money-=g;
                file2.write((char*)&atm, sizeof(atm));
                cout<<endl;
                color(10);
                cout<<"\tPending.....\n\n";sleep(3);
                cout<<"\tYou withdraw "<<g<<" birr succssfully\n";
                cout<<"\tTake your money\n";
                color(14);
                }
            }
        else if(a==3 && atm.acc==accnt){

         cout<<"\tAccount Owner: "<<atm.name<<endl;
         cout<<"\tAccount Number: "<<atm.acc<<endl;
         cout<<"\tTOTAL BALANCE: "<<atm.money<<endl;
          file2.write((char*)&atm, sizeof(atm));
        }
      else if(a==4 && atm.acc==accnt){

            atm.money+=mon;
            file2.write((char*)&atm, sizeof(atm));
                    cout<<endl;
                    color(10);
                    cout<<"\tPending...\n\n";sleep(3);
                    cout<<"\t"<<mon<<" Birr transfer to ";color(14);cout<<atm.name;color(10);
                    cout<<" account"<<endl;
                    cout<<"\tTransfer is completed!!\n";
                    color(14);
                    sleep(3);
                  }
    else if(a==5 && atm.acc==accnt){
            float tMoney;int counter=1;
            bool flag=false;
               if(atm.money<mon){
                        g:
                         cout<<endl;
                        color(12);
                        cout<<"Insufficient Balance\nPlease first check you balance or\n"
                        "Input Again\n"; sleep(2);
                        color(14);
                    cout<<"How Much Money Do You Want Transfer:";
                    cin>>tMoney;
                    if(atm.money < tMoney && counter<2){counter++;goto g;}
                    else if(atm.money < tMoney && counter>=2){file2.write((char*)&atm, sizeof(atm)); color(12);cout<<" You lost your 3 trial\n";}
                    else{mon=tMoney; flag=true; cn=mon;}}
            if(atm.money>=mon || flag){
                    atm.money-=mon;
                    file2.write((char*)&atm, sizeof(atm));
                   cn=mon;
                   flag2=false;
                   }
            }
         else{file2.write((char*)&atm, sizeof(atm));}
        file.read((char*)&atm, sizeof(atm));

        }
               if(flag2) {char bh;
                cout<<endl;
                color(11);
                cout<<"\tPress Enter to continue\n";
                cin.sync();
                color(14);
                cin.get(bh);}
    }
  file.close();
  file2.close();
  remove("input.txt");
  rename("temp.txt","input.txt");


}
void ATM::transfer(float bn){
    cn=0;
     float ra,mo,k;
    bool flag=false;
    l:
    cout<<"Enter receiver account number:";
    cin>>ra;
     fstream file;
     file.open("input.txt", ios::in);
     file.read((char*)&atm, sizeof(atm));
     if(!file)file.close();
     else{
        while(!file.eof()){
                if(ra==atm.acc && ra!=bn){
                    cout<<"How much money do you want transfer:";
                cin>>mo;
                   flag=true;
 }

     file.read((char*)&atm, sizeof(atm));
        }
     }
    file.close();
    if(flag){atm.deposit(bn,5,mo);
            atm.deposit(ra,4,cn);}
    else{color(12);cout<<"Sorry Receiver Account Doesn't Found,\tPlease Input Correctly\n";
                   sleep(2);
                   color(14);
                   goto l;}
}

void ATM::exist_user(){
    float uAcc;
    string name1;
    bool flag=false,flag2=true;
    int pin,l=3;
         color(9);
    cout<<"\t\t**** LOGIN ****\n";
    color(14);
    cout<<endl;
    cout<<"Enter Your Account Number:";
    cin>>uAcc;
         pw:
            color(10);
        cout<<"Password:";
         cin>>pin;
        color(11);
        cout<<"Please Wait........\n";
        color(9);
        sleep(3);
    fstream file;
 file.open("input.txt", ios::in);
 file.read((char*)&atm, sizeof(atm));
 if(!file)file.close();
 else{
    while(!file.eof()){
        if(uAcc==atm.acc){
                flag2=false;

                 if(pin==atm.pass){
                 system("cls");
                  color(10);
                cout<<"\t\t**** Login is Succeed **** \n";
                cout<<endl;
                name1=atm.name;
                flag=true;


            }
            else{ l--;
                color(12);
                cout<<"  Incorrect Password, ";
                cout<<l<< " Trial Left\n";
            if(l==0){
            cout<<"You tried 3 incorrect password\n Backing to Home\n";
            sleep(3);color(14);break;}
             goto pw;
            }
        }
     file.read((char*)&atm, sizeof(atm));}

    }
file.close();
if(flag2){color(12);cout<<"Your Account is not found from our database\n Please Register First";sleep(4);color(14);system("cls");atm.menu1();}
if(flag){color(10);atm.menu(uAcc,name1);}
}
void ATM::menu(float user,string name2){
  k:
      color(10);
    cout<<"\n\t\tWellcome Back ";color(14);
   cout<<name2<<endl;
    color(9);
    cout<<endl;
    cout << "\t\t******** MENU *******\n"<<endl;
    color(14);
    cout<<"\t1. Deposit money\t\t"
    "4. Check Balance\n"
    "\t2. Withdraw money\t\t"
    "5. Home\n"
    "\t3. Transfer money\t\t"<<endl;
     cin>>num;

     switch(num){
     case 1: atm.deposit(user,1);system("cls");goto k;;break;
     case 2:atm.deposit(user,2);system("cls");goto k;break;
     case 3: atm.transfer(user);system("cls");goto k;break;
     case 4: atm.deposit(user,3);system("cls");goto k;break;
     case 5:system("cls");atm.menu1();break;
     default: (cout<< "Wrong Input, Please Try Again!!\n");
      sleep(3);
      system("cls");
      goto k;
     }

}
bool ATM::user_checker(float accnt){
     fstream file;
     file.open("input.txt", ios::in);
     file.read((char*)&atm, sizeof(atm));
     if(!file)file.close();
     else{
        while(!file.eof()){
         if (accnt==atm.acc) {return false;}
     file.read((char*)&atm, sizeof(atm));
        }
     }
    file.close();
    return true;

}
void ATM::menu1(){
    int input;
    g:
     atm.color(9);
    cout<<"\t\t****MENU****\n\n";
    atm.color(14);
    cout<<"\t1. New User\n"
    "\t2. Registered User\n"
    "\t3. exit\n"
    "\n Enter Your Option:\n";
    cin>>input;
     system("cls");
    switch(input){
    case 1: atm.color(14); float uAcc;
               cout<< "Account Number:";
                cin>>uAcc;
               atm.new_user(atm.user_checker(uAcc),uAcc); system("cls");goto g;break;
    case 2:atm.exist_user();break;
    case 3: cout<<"\n\n\n\t\t\t****GOOGBAY****\n\n";sleep(5);exit(0);
    default:(cout<<"Wrong Input\n");
    sleep(3);
    system("cls");
    menu1();
    }
}
int main()
{
  con = GetStdHandle(STD_OUTPUT_HANDLE);

   atm.menu1();
    system("pause>0");
}
