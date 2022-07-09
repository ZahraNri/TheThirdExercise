#include <iostream>
#include"term.h"
#include"Polynomial.h"
#include<conio.h>
#include<fstream>
using namespace std;
void scan(string& _string)
{
    char _char;
    cin>>_char;
    getline(cin,_string);
    _string=_char+_string;
}
Polynomial str_to_poly(string P)
{
    string PE;
    vector<Term> POLY,result;
    vector<int> T;

    for(int i=0;i<P.size();i++)
    {
        if(int(P[i])==43||int(P[i])==45)
        {
            T.push_back(i);
        }

    }
    if(P[0]=='+'||P[0]=='-')
    {
        for(int i=0;i<T.size();i++)
        {
            if(i==T.size()-1)
            {
                PE=P.substr(T.at(i),P.size());
                Term t(PE);
                POLY.push_back(t);
                i++;
            }
            else
            {
                PE=P.substr(T.at(i),T.at(i+1)-T.at(i));
                Term t(PE);
                POLY.push_back(t);
            }
        }
    }
    else
    {
        PE=P.substr(0,T.at(0));
        Term t(PE);
        POLY.push_back(t);
        for(int i=0;i<T.size();i++)
        {
            if(i==T.size()-1)
            {
                PE=P.substr(T.at(i),P.size());
                Term t(PE);
                POLY.push_back(t);
            }
            else
            {
                PE=P.substr(T.at(i),T.at(i+1)-T.at(i));
                Term t(PE);
                POLY.push_back(t);
            }
        }
    }
    result=sort_operation(POLY);

    return  Polynomial(result);
}

Polynomial load_from_text_file(string file_name)
{
    string p;
    vector<Term> T={Term(0,0)};
    Polynomial P(T);
    ifstream file;
    file.open(file_name,ios::in);
    if(file)
    {
            file>>p;
            return str_to_poly(p);
    }
    else
        cout<<"\nNOT FOUND\n";
    return P;
}

void load_from_binary_file(string file_name,Polynomial &POLY)
{

    ifstream file(file_name,ios::in|ios::binary);
    if(file)
    {

        file.read(reinterpret_cast<char *>(&POLY), sizeof(Polynomial));
    }
    else
        cout<<"\nNOT FOUND\n";


}

int  Polynomial_menu()
{
    int n;
    system("cls");
    cout<<"Polynomial Menu\n\n"
          "Current Polynomial= \n\n"<<
          "1-Add\n"
          "2-Subtract\n"
          "3-Multiply\n"
          "4-Derivative\n"
          "5-Find Degree\n"
          "6-Find Value for specific x\n"
          "7-Compare\n"
          "8-Save to text file\n"
          "9-Save to binary file\n"
          "10-back to MAIN MENU\n\n"
          "choos?  ";
    cin>>n;
    return n;
}

void Polynomial_operation(Polynomial& p)
{
    system("cls");
    while(1)
    {
        string n;
        system("cls");
        cout<<"Polynomial Menu\n\n"
              "Current Polynomial= ";
        if(p.empty())
            cout<<" 0\n\n";
        else
            cout<<p<<endl;

        cout<<"1-Add\n"
              "2-Subtract\n"
              "3-Multiply\n"
              "4-Derivative\n"
              "5-Find Degree\n"
              "6-Find Value for specific x\n"
              "7-Compare\n"
              "8-Save to text file\n"
              "9-Save to binary file\n"
              "10-back to MAIN MENU\n\n"
              "choos?  ";
        cin>>n;
        if(n=="1")
        {   system("cls");
            while(1)
            {

                Polynomial new_p;
                cout<<"Enter Polynomail  for Add Current Polynomial: ";
                cin>>new_p;
                p+=new_p;
                if(p.empty())
                    cout<<endl<<"Current Polynomial= 0\n\n";
                else
                    cout<<endl<<"Current Polynomial= "<<p<<endl;
                char ch;
                cout<<"\n\ncountinue? [Y or N] ";
                cin>>ch;
                if(ch=='N'||ch=='n')
                    break;
                else
                {
                    system("cls");
                    if(p.empty())
                        cout<<endl<<"Current Polynomial= 0\n\n";
                    else
                        cout<<endl<<"Current Polynomial= "<<p<<endl;
                }


            }
        }
        else
            if(n=="2")
            {
                system("cls");
                while(1)
                {

                    Polynomial new_p;
                    cout<<"Enter Polynomail  for Subtract Current Polynomial: ";
                    cin>>new_p;
                    p-=new_p;
                    if(p.empty())
                        cout<<endl<<"Current Polynomial= 0\n\n";
                    else
                        cout<<endl<<"Current Polynomial= "<<p<<endl;
                    char ch;
                    cout<<"\n\ncountinue? [Y or N] ";
                    cin>>ch;
                    if(ch=='N'||ch=='n')
                        break;
                    else
                    {
                        system("cls");
                        if(p.empty())
                            cout<<endl<<"Current Polynomial= 0\n\n";
                        else
                            cout<<endl<<"Current Polynomial= "<<p<<endl;
                    }


                }
            }
            else
                if(n=="3")
                {
                    system("cls");
                    while(1)
                    {

                        Polynomial new_p;
                        cout<<"Enter Polynomail  for Multiply Current Polynomial: ";
                        cin>>new_p;
                        p*=new_p;
                        if(p.empty())
                            cout<<endl<<"Current Polynomial= 0\n\n";
                        else
                            cout<<endl<<"Current Polynomial= "<<p<<endl;
                        char ch;
                        cout<<"\n\ncountinue? [Y or N] ";
                        cin>>ch;
                        if(ch=='N'||ch=='n')
                            break;
                        else
                        {
                            system("cls");
                            if(p.empty())
                                cout<<endl<<"Current Polynomial= 0\n\n";
                            else
                                cout<<endl<<"Current Polynomial= "<<p<<endl;
                        }


                    }

                }
                else
                    if(n=="4")
                    {
                        system("cls");
                        while(1)
                        {

                            cout<<"Derivative Current Polynomial\n ";
                            ~p;
                            if(p.empty())
                                cout<<endl<<"Current Polynomial= 0\n\n";
                            else
                                cout<<endl<<"Current Polynomial= "<<p<<endl;
                            char ch;
                            cout<<"\n\ncountinue? [Y or N] ";
                            cin>>ch;
                            if(ch=='N'||ch=='n')
                                break;
                            else
                            {
                                system("cls");
                                if(p.empty())
                                    cout<<endl<<"Current Polynomial= 0\n\n";
                                else
                                    cout<<endl<<"Current Polynomial= "<<p<<endl;
                            }


                        }
                    }
                    else
                        if(n=="5")
                        {
                            system("cls");
                            cout<<"Degree= "<<p.get_degree();
                            _sleep(2000);
                        }
                        else
                            if(n=="6")
                            {
                                system("cls");
                                while (1)
                                {

                                    float x;
                                    cout<<"Enter number for Value: ";
                                    cin>>x;
                                    cout<<"\n\nInput Value= "<<p(x);

                                    char ch;
                                    cout<<"\n\ncountinue? [Y or N] ";
                                    cin>>ch;
                                    if(ch=='N'||ch=='n')
                                        break;
                                    else
                                    {
                                        system("cls");
                                        if(p.empty())
                                            cout<<endl<<"Current Polynomial= 0\n\n";
                                        else
                                            cout<<endl<<"Current Polynomial= "<<p<<endl;
                                    }
                                }

                            }

                            else
                                if(n=="7")
                                {
                                    system("cls");
                                    while(1)
                                    {

                                        Polynomial new_p;
                                        cout<<"Enter Polynomail  for Comparing Current Polynomial: ";
                                        cin>>new_p;
                                        if(p.empty())
                                            cout<<endl<<"Current Polynomial= 0\n\n";
                                        else
                                            cout<<endl<<"Current Polynomial= "<<p<<endl;

                                        cout<<"\nOther Polynomil= "<<new_p<<endl;

                                        cout<<"\nComparing Current_Polynomial with Other_Polynomial \n";
                                        cout<<"Current_Polynomial > Other_Polynomial:";
                                        if(p>new_p)
                                            cout<<" True\n";
                                        else
                                            cout<<" False\n";
                                        cout<<"Current_Polynomial >= Other_Polynomial:";
                                        if(p>=new_p)
                                            cout<<" True\n";
                                        else
                                            cout<<" False\n";
                                        cout<<"Current_Polynomial < Other_Polynomial:";
                                        if(p<new_p)
                                            cout<<" True\n";
                                        else
                                            cout<<" False\n";
                                        cout<<"Current_Polynomial <= Other_Polynomial:";
                                        if(p<=new_p)
                                            cout<<" True\n";
                                        else
                                            cout<<" False\n";
                                        cout<<"Current_Polynomial == Other_Polynomial:";
                                        if(p==new_p)
                                            cout<<" True\n";
                                        else
                                            cout<<" False\n";
                                        char ch;
                                        cout<<"\n\ncountinue? [Y or N] ";
                                        cin>>ch;
                                        if(ch=='N'||ch=='n')
                                            break;
                                        else
                                        {
                                            system("cls");
                                            if(p.empty())
                                                cout<<endl<<"Current Polynomial= 0\n\n";
                                            else
                                                cout<<endl<<"Current Polynomial= "<<p<<endl;
                                        }


                                    }
                                }
                                else
                                    if(n=="8")
                                    {
                                        system("cls");
                                        string file;
                                        cout<<"Enter  file name: ";
                                        scan(file);
                                        write_to_file_text(p,file);
                                        cout<<"COPLECTED...";
                                        _sleep(2000);
                                    }
                                    else
                                        if(n=="9")
                                        {
                                            system("cls");
                                            string file;
                                            cout<<"Enter  file name: ";
                                            scan(file);
                                            write_to_file_binary(p,file);
                                            cout<<"COPLECTED...";
                                            _sleep(2000);
                                        }
                                        else
                                            if(n=="10")
                                            {
                                                break;
                                            }
                                            else
                                            {
                                                cout<<"\n\nERROR INVALID CHOOS ! ENTER AGAIN2.\n\n";
                                                _sleep(2000);

                                            }
    }

}
int main()
{
    Polynomial current_polynomial;
    string n;
    while(1)
    {
        system("cls");
        cout<<"Main Menu:\n"
              "1-New Polynomial\n"
              "2-load from text file\n"
              "3-load from binary file\n"
              "4-Quit\n\n"
              "choos?  ";
        cin>>n;

        if(n=="1")
        {
            Polynomial_operation(current_polynomial);
        }
        else
            if(n=="2")
            {
                system("cls");
                string address;
                cout<<"Enter address file:\n";
                cin.get();
                getline(cin,address);
                Polynomial p=load_from_text_file(address);
                current_polynomial=p;
                _sleep(2000);
                Polynomial_operation(current_polynomial);

            }
            else
                if(n=="3")
                {
                    system("cls");
                    string address;
                    cout<<"Enter address file:\n";
                   // cin>>address;
                    cin.get();
                    getline(cin,address);
                    Polynomial p;
                    load_from_binary_file(address,p);
                    current_polynomial=p;
                    _sleep(2000);
                    Polynomial_operation(current_polynomial);
                }
                else
                    if(n=="4")
                    {
                        cout<<"\n\nGOOD LUCK\n\n";
                        break;
                    }
                    else
                    {
                        cout<<"\n\nERROR INVALID CHOOS! ENTER AGAIN.\n\n";
                        _sleep(2000);
                        system("cls");
                    }

    }

    getch();
    return 0;
}
