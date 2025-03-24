#include <iostream>
#include <iomanip>
#define MAX 3
using namespace std;

struct Record{
    string student_name;
    int quiz_one, quiz_two, quiz_three;
};

Record recs[MAX];
int last = -1;

void menu_srcn();
void inz();
float average(int lst);
int add();
int del(string name);
int upt();
int dis();
int type();


int main(){
    inz();
    menu_srcn();

    return 0;
}

void inz(){
    last = -1;
}

int type(){
    int option;

    cout<<"1.ADD RECORD\n2.UPDATE RECORD\n3.DELETE RECORD\n4.DISPLAY\n5.EXIT"<<endl;
    cout<<"SELECT YOUR CHOICE: ";
    cin>> option;

    return option;
}

void menu_srcn(){

    int want = 0;
    string name;

    while(!want){
        switch(type()){
        case 1:
            system("cls");
            add();
            break;
        case 2:
            system("cls");
            upt();
            break;
        case 3:
            system("cls");
            cout<<"Enter name: ";
            cin>>name;
            del(name);
            break;
        case 4:
            system("cls");
            dis();
            break;
        case 5:
            want = 1;
            exit(1);
            break;
        default:
            cout<<"Its invalid input..."<<endl;
            system("pause");
        }
    }
}

int add(){
    Record addRec;

    if(last >= MAX - 1){
        cout<<"Record is full."<<endl;
        system("pause");
        return -1;
    }


        cout<<"Enter your name: ";
        cin>>addRec.student_name;
        cout<<"Enter quiz 1: ";
        cin >>addRec.quiz_one;
        cout<<"\n";
        cout<<"Enter quiz 2: ";
        cin >>addRec.quiz_two;
        cout<<"\n";
        cout<<"Enter quiz 3: ";
        cin >>addRec.quiz_three;

    recs[++last] = addRec;
    cout<<"added successfully"<<endl;
    system("cls");
    return 0;
}

int del( string name){
    int verfy = -1;

    if(last < 0){
        cout<<"No available record."<<endl;
        system("pause");
        return -1;
    }

    for(int i = 0; i <= last; i++){
        if(recs[i].student_name == name){
            verfy = i;
            break;
        }
    }

    if(verfy == -1){
        cout<<"no record found."<<endl;
        return -1;
    }

    for(int i = verfy; i < last; i++){
        recs[i] = recs[i+1];
    }
    --last;
    cout<<"Deleted successfully"<<endl;

    return 0;
}

int upt(){

    string name, fnd_name;
    int quiz_1, quiz_2, quiz_3, found = 0;

    if(last < 0){
        cout<<"No available record."<<endl;
        system("pause");
        return -1;
    }

        cout<<"Enter name to update: ";
        cin>>fnd_name;

        for(int i = 0; i <= last; i++){
            if(recs[i].student_name == fnd_name){
                cout<<"New name: ";
                cin>>name;
                cout<<"New quiz 1: ";
                cin>> quiz_1;
                cout<<"New quiz 2: ";
                cin>> quiz_2;
                cout<<"New quiz 3: ";
                cin>> quiz_3;
                recs[i].student_name = name;
                recs[i].quiz_one = quiz_1;
                recs[i].quiz_two = quiz_2;
                recs[i].quiz_three = quiz_3;
                found = 1;
                return 0;
            }
        }
        if(!found){
            cout<<"Record doesn't found"<<endl;
            return -1;
        }
    return 0;
}

float average(int lst){
    if(lst < 0 || lst > last)
    return 0;

    return (recs[lst].quiz_one + recs[lst].quiz_two + recs[lst].quiz_three) / 3.00;
}

int dis(){
    if(last < 0){
        cout<<"No available record."<<endl;
        return -1;
    } else {
        cout<<setw(10)<<right<<"NAME"
        <<setw(10)<<right<<"QUIZ 1"
        <<setw(10)<<right<<"QUIZ 2"
        <<setw(10)<<right<<"QUIZ 3"
        <<setw(10)<<right<<"AVERAGE"
        <<setw(10)<<right<<"REMARKS"<<endl;

        for(int i = 0; i <= last; i++){
            float ave = average(i);
            cout<<i+1<<".)"<<setw(15)<<left<<recs[i].student_name
            <<setw(10)<<left<<recs[i].quiz_one
            <<setw(10)<<left<<recs[i].quiz_two
            <<setw(10)<<left<<recs[i].quiz_three
            <<setw(10)<<left<<fixed<<setprecision(2)<<ave
            <<setw(10)<<left<<(ave >= 75 ? "PASSED":"FAILED")<<endl;
        }
        return 0;
    }
}
