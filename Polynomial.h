#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include<iostream>
#include<vector>
#include<fstream>
#include"term.h"
using namespace std;
//................................................................................................................//
void shift_to_left(vector<Term>& t, int in)
{

    for(int i=in;i<t.size()-1;i++)
    {
       t.at(i)=t.at(i+1) ;
    }
    t.pop_back();
}
void first_data(vector<Term>& t ,int ind)
{
    vector<Term> test=t;
    t.clear();

    for(int i=0;i<ind;i++)
    {
        t.push_back(test.at(i));
    }
    t.push_back(test.at(test.size()-1));
    for(int i=ind;i<test.size()-1;i++)
    {
            t.push_back(test.at(i));
    }
}
vector<Term>  sort_operation(vector<Term> &p)
{
    vector<Term> result=p;
    Term t;
    for(int i=0;i<result.size();i++)
    {
        for(int j=i+1;j<result.size();j++)
        {
            if(result.at(i).get_pow()==result.at(j).get_pow())
            {

                t= result.at(j)+result.at(i);
                shift_to_left(result,i);
                int ind=--j;
                shift_to_left(result,ind);
                result.push_back(t);
                first_data(result,i);
            }
        }
    }




    return result;
}


//................................................................................................................///
class Polynomial
{
private:
    vector<Term> poly;

public:
    Polynomial(vector<Term>& );
    Polynomial(){}
    void sort();
    bool empty(){
        if(poly.size()==0)
            return 1;
        else
            return 0;
                }
    int get_degree(){return poly.at(0).get_pow();}


    Polynomial operator+( Polynomial& );
    Polynomial operator+( Term& );
    Polynomial operator+( float& );
    friend Polynomial operator+( Polynomial&,Term &);
    friend Polynomial operator+(Polynomial &,float &);

    Polynomial operator-( Polynomial& );
    Polynomial operator-( Term& );
    Polynomial operator-( float& );
    friend Polynomial operator-( Polynomial&,Term &);
    friend Polynomial operator-(Polynomial &,float &);

    bool operator>(Polynomial& );
    bool operator>(Term& );
    bool operator>(float& );
    friend bool operator>(Polynomial&,Term&);
    friend bool operator>(Polynomial&,float&);
    bool operator<(Polynomial& );
    bool operator<(Term& );
    bool operator<(float& );
    friend bool operator<(Polynomial&,Term&);
    friend bool operator<(Polynomial&,float&);
    bool operator>=(Polynomial& );
    bool operator>=(Term& );
    bool operator>=(float& );
    friend bool operator>=(Polynomial&,Term&);
    friend bool operator>=(Polynomial&,float&);
    bool operator<=(Polynomial& );
    bool operator<=(Term& );
    bool operator<=(float& );
    friend bool operator<=(Polynomial&,Term&);
    friend bool operator<=(Polynomial&,float&);
    bool operator==(Polynomial& );
    bool operator==(Term& );
    bool operator==(float& );

    bool operator!=(Polynomial& );
    bool operator!=(Term& );
    bool operator!=(float& );

    Polynomial operator*(Polynomial& );
    Polynomial operator*( Term& );
    Polynomial operator*( float& );
    friend Polynomial operator*( Polynomial&,Term &);
    friend Polynomial operator*(Polynomial &,float &);

    void operator+=(Polynomial&);
    void operator+=(Term&);
    void operator+=(float&);
    friend void operator+=( Polynomial &,float &);
    friend void operator+=( Polynomial &,Term &);

    void operator-=(Polynomial&);
    void operator-=(Term&);
    void operator-=(float&);
    friend void operator-=( Polynomial &,float &);
    friend void operator-=( Polynomial &,Term &);

    void operator*=(Polynomial& );
    void operator*=( Term& );
    void operator*=( float& );
    friend void operator*=( Polynomial&,Term &);
    friend void operator*=(Polynomial &,float &);

    void operator=(Polynomial& );

    void operator++();
    void operator--();

    void operator~();

    float operator()(float );

    Term operator[](int ) const ;
    Term operator[](int );

    friend ostream& operator<<(ostream& ,Polynomial & );
    friend istream& operator>>(istream& ,Polynomial & );




    friend void write_to_file_binary(Polynomial &p,string file_name);
};

Polynomial::Polynomial(vector<Term> &p )

{
    poly=sort_operation(p);

    sort();

}

void Polynomial::sort()
{

    for(int i=0;i<poly.size();i++)
    {
        if(poly.at(i).get_coef()==0)
            shift_to_left(poly,i);
    }
    Term temp;
    for(int i=0;i<poly.size();i++)
    {
        for(int j=i+1;j<poly.size();j++)
        {
            if(poly.at(i).get_pow()<poly.at(j).get_pow())
            {
                temp=poly.at(i);
                poly.at(i)=poly.at(j);
                poly.at(j)=temp;
            }

        }
    }


}


//----------------------------------------------------------------------------------------------// operator +
Polynomial Polynomial::operator+( Polynomial &p)
{
    vector<Term> result,sum;
    for(int i=0;i<poly.size();i++)
    {
        sum.push_back(poly.at(i));
    }
    for(int i=0;i<p.poly.size();i++)
    {
        sum.push_back(p.poly.at(i));
    }
    result=sort_operation(sum);
    return Polynomial(result);
}

Polynomial Polynomial::operator+( Term &t)
{
    for(int i=0;i<poly.size();i++)
    {
            if(poly.at(i).get_pow()==t.get_pow())
            {
                poly.at(i)+=t;
            }
            else
                poly.push_back(t);
    }
    return Polynomial(poly);
}

Polynomial operator+( Polynomial& p, Term &t)
{
    for(int i=0;i<p.poly.size();i++)
    {
            if(p.poly.at(i).get_pow()==t.get_pow())
            {
                p.poly.at(i)+=t;
            }
            else
                p.poly.push_back(t);
    }
    return Polynomial(p.poly);
}

Polynomial Polynomial::operator+(float & n)
{
    for(int i=0;i<poly.size();i++)
    {
            if(poly.at(i).get_pow()==0)
            {
                poly.at(i)+=n;
            }
            else
            {
                Term t;
                t.set_pow(0);
                t.set_coef(n);
                poly.push_back(t);
            }

    }
    return Polynomial(poly);
}

Polynomial operator+(Polynomial &p ,float & n)
{
    for(int i=0;i<p.poly.size();i++)
    {
            if(p.poly.at(i).get_pow()==0)
            {
                p.poly.at(i)+=n;
            }
            else
            {
                Term t;
                t.set_pow(0);
                t.set_coef(n);
                p.poly.push_back(t);
            }

    }
    return Polynomial(p.poly);
}

//----------------------------------------------------------------------------------------------// operator -
Polynomial Polynomial::operator-( Polynomial &p)
{
    vector<Term> result,d;
    for(int i=0;i<poly.size();i++)
    {
        d.push_back(poly.at(i));
    }
    for(int i=0;i<p.poly.size();i++)
    {
        p.poly.at(i).set_coef(p.poly.at(i).get_coef()*-1);
        d.push_back(p.poly.at(i));
    }
    result=sort_operation(d);
    return Polynomial(result);
}

Polynomial Polynomial::operator-( Term &t)
{
    for(int i=0;i<poly.size();i++)
    {
            if(poly.at(i).get_pow()==t.get_pow())
            {
                poly.at(i)-=t;
            }
            else
                poly.push_back(t);
    }
    return Polynomial(poly);
}

Polynomial operator-( Polynomial& p, Term &t)
{
    for(int i=0;i<p.poly.size();i++)
    {
            if(p.poly.at(i).get_pow()==t.get_pow())
            {
                p.poly.at(i)-=t;
            }
            else
                p.poly.push_back(t);
    }
    return Polynomial(p.poly);
}

Polynomial Polynomial::operator-(float & n)
{
    for(int i=0;i<poly.size();i++)
    {
            if(poly.at(i).get_pow()==0)
            {
                poly.at(i)-=n;
            }
            else
            {
                Term t;
                t.set_pow(0);
                t.set_coef(n);
                poly.push_back(t);
            }

    }
    return Polynomial(poly);
}

Polynomial operator-(Polynomial &p ,float & n)
{
    for(int i=0;i<p.poly.size();i++)
    {
            if(p.poly.at(i).get_pow()==0)
            {
                p.poly.at(i)-=n;
            }
            else
            {
                Term t;
                t.set_pow(0);
                t.set_coef(n);
                p.poly.push_back(t);
            }

    }
    return Polynomial(p.poly);
}
//----------------------------------------------------------------------------------------------// operator < > >= <= == !=
bool Polynomial::operator>(Polynomial &p)
{
    for(int i=0;i<poly.size();i++)
    {
        for(int j=0;j<p.poly.size();j++)
        {
            if(poly.at(i)>p.poly.at(j))
                return 1;
            else
                return 0;
        }
    }
    return 0;
}

bool Polynomial::operator>(Term & t)
{
    for(int i=0;i<poly.size();i++)
    {
            if(poly.at(i)>t)
                return 1;
    }
    return 0;
}

bool Polynomial::operator>(float &n)
{
    for(int i=0;i<poly.size();i++)
    {
            if(poly.at(i)>n)
                return 1;
    }
    return 0;
}

bool operator>(Polynomial &p,Term& t)
{
    for(int i=0;i<p.poly.size();i++)
    {
            if(p.poly.at(i)>t)
                return 1;
    }
    return 0;
}

bool operator>(Polynomial &p,float &n)
{
    for(int i=0;i<p.poly.size();i++)
    {
            if(p.poly.at(i)>n)
                return 1;
    }
    return 0;
}


bool Polynomial::operator<(Polynomial &p)
{
    for(int i=0;i<poly.size();i++)
    {
        for(int j=0;j<p.poly.size();j++)
        {
            if(poly.at(i)<p.poly.at(j))
                return 1;
            else
                return 0;
        }
    }
    return 0;
}

bool Polynomial::operator<(Term & t)
{
    for(int i=0;i<poly.size();i++)
    {
            if(poly.at(i)<t)
                return 1;
    }
    return 0;
}

bool Polynomial::operator<(float &n)
{
    for(int i=0;i<poly.size();i++)
    {
            if(poly.at(i)<n)
                return 1;
    }
    return 0;
}

bool operator<(Polynomial &p,Term& t)
{
    for(int i=0;i<p.poly.size();i++)
    {
            if(p.poly.at(i)<t)
                return 1;
    }
    return 0;
}

bool operator<(Polynomial &p,float &n)
{
    for(int i=0;i<p.poly.size();i++)
    {
            if(p.poly.at(i)<n)
                return 1;
    }
    return 0;
}


bool Polynomial::operator>=(Polynomial &p)
{
    for(int i=0;i<poly.size();i++)
    {
        for(int j=0;j<p.poly.size();j++)
        {
            if(poly.at(i)>=p.poly.at(j))
                return 1;
            else
                return 0;
        }
    }
    return 0;
}

bool Polynomial::operator>=(Term & t)
{
    for(int i=0;i<poly.size();i++)
    {
            if(poly.at(i)>=t)
                return 1;
    }
    return 0;
}

bool Polynomial::operator>=(float &n)
{
    for(int i=0;i<poly.size();i++)
    {
            if(poly.at(i)>=n)
                return 1;
    }
    return 0;
}

bool operator>=(Polynomial &p,Term& t)
{
    for(int i=0;i<p.poly.size();i++)
    {
            if(p.poly.at(i)>=t)
                return 1;
    }
    return 0;
}

bool operator>=(Polynomial &p,float &n)
{
    for(int i=0;i<p.poly.size();i++)
    {
            if(p.poly.at(i)>=n)
                return 1;
    }
    return 0;
}


bool Polynomial::operator<=(Polynomial &p)
{
    for(int i=0;i<poly.size();i++)
    {
        for(int j=0;j<p.poly.size();j++)
        {
            if(poly.at(i)<=p.poly.at(j))
                return 1;
            else
                return 0;
        }
    }
    return 0;
}

bool Polynomial::operator<=(Term & t)
{
    for(int i=0;i<poly.size();i++)
    {
            if(poly.at(i)<=t)
                return 1;
    }
    return 0;
}

bool Polynomial::operator<=(float &n)
{
    for(int i=0;i<poly.size();i++)
    {
            if(poly.at(i)<=n)
                return 1;
    }
    return 0;
}

bool operator<=(Polynomial &p,Term& t)
{
    for(int i=0;i<p.poly.size();i++)
    {
            if(p.poly.at(i)<=t)
                return 1;
    }
    return 0;
}

bool operator<=(Polynomial &p,float &n)
{
    for(int i=0;i<p.poly.size();i++)
    {
            if(p.poly.at(i)<=n)
                return 1;
    }
    return 0;
}

bool Polynomial::operator==(Polynomial& p)
{
    int count=0;
    if(poly.size()!=p.poly.size())
        return 0;
    for(int i=0;i<poly.size();i++)
    {
        if(poly.at(i)==p.poly.at(i))
            count++;
    }
    if(count==poly.size())
        return 1;

    return 0;
}

bool Polynomial::operator==(Term & t)
{
    if(poly.size()==1)
    {
        if(poly.at(0)==t)
            return 1;
    }
    return 0;
}

bool Polynomial::operator==(float & n)
{
    if(poly.size()==1)
    {
        if(poly.at(0)==n)
            return 1;
    }
    return 0;
}


bool Polynomial::operator!=(Polynomial& p)
{
    if(!(*this==p))
        return 1;
    return 0;
}

bool Polynomial::operator!=(Term & t)
{
    if(!(*this==t))
        return 1;
    return 0;
}

bool Polynomial::operator!=(float & n)
{
    if(!(*this==n))
        return 1;
    return 0;
}
//----------------------------------------------------------------------------------------------//operator *
Polynomial Polynomial::operator*(Polynomial &p)
{
    vector<Term> mul;
    for(int i=0;i<poly.size();i++)
    {
        for(int j=0;j<p.poly.size();j++)
        {
            mul.push_back(poly.at(i)*p.poly.at(j));
        }
    }
    vector<Term> result;
    result=sort_operation(mul);
    return Polynomial(result);
}

Polynomial Polynomial::operator*(Term & t)
{
    vector<Term> mul;
    for(int i=0;i<poly.size();i++)
    {
            mul.push_back(poly.at(i)*t);

    }
    vector<Term> result;
    result=sort_operation(mul);
    return Polynomial(result);
}

Polynomial Polynomial::operator*(float& n)
{
    vector<Term> mul;
    for(int i=0;i<poly.size();i++)
    {
            mul.push_back(poly.at(i)*n);

    }
    vector<Term> result;
    result=sort_operation(mul);
    return Polynomial(result);
}

Polynomial operator*(Polynomial& p,Term & t)
{
    vector<Term> mul;
    for(int i=0;i<p.poly.size();i++)
    {
            mul.push_back(p.poly.at(i)*t);

    }
    vector<Term> result;
    result=sort_operation(mul);
    return Polynomial(result);
}

Polynomial operator*(Polynomial& p,float& n)
{
    vector<Term> mul;
    for(int i=0;i<p.poly.size();i++)
    {
            mul.push_back(p.poly.at(i)*n);

    }
    vector<Term> result;
    result=sort_operation(mul);
    return Polynomial(result);
}
//-----------------------------------------------------------------------------------------------//operator +=
void Polynomial::operator+=( Polynomial &p)
{
    vector<Term> result,sum;
    for(int i=0;i<poly.size();i++)
    {
        sum.push_back(poly.at(i));
    }
    for(int i=0;i<p.poly.size();i++)
    {
        sum.push_back(p.poly.at(i));
    }
    result=sort_operation(sum);
    poly.clear();
    poly=result;
    sort();

}

void Polynomial::operator+=( Term &t)
{
    for(int i=0;i<poly.size();i++)
    {
            if(poly.at(i).get_pow()==t.get_pow())
            {
                poly.at(i)+=t;
            }
            else
                poly.push_back(t);
    }
    sort();
}

void Polynomial::operator+=( float &n)
{
    for(int i=0;i<poly.size();i++)
    {
            if(poly.at(i).get_pow()==0)
            {
                poly.at(i).set_coef(poly.at(i).get_coef()+n);
            }
            else
            {
                Term t(n,0);
                poly.push_back(t);
            }

    }
    sort();
}

void operator+=(Polynomial &p, Term &t)
{
    for(int i=0;i<p.poly.size();i++)
    {
            if(p.poly.at(i).get_pow()==t.get_pow())
            {
               p. poly.at(i)+=t;
            }
            else
                p.poly.push_back(t);
    }
    p.sort();
}

void operator+=( Polynomial &p,float &n)
{
    for(int i=0;i<p.poly.size();i++)
    {
            if(p.poly.at(i).get_pow()==0)
            {
                p.poly.at(i).set_coef(p.poly.at(i).get_coef()+n);
            }
            else
            {
                Term t(n,0);
                p.poly.push_back(t);
            }

    }
    p.sort();
}
//-------------------------------------------------------------------------------------------------//operator -=
void Polynomial::operator-=( Polynomial &p)
{
    vector<Term> result,d;
    for(int i=0;i<poly.size();i++)
    {
        d.push_back(poly.at(i));
    }
    for(int i=0;i<p.poly.size();i++)
    {
        p.poly.at(i).set_coef(p.poly.at(i).get_coef()*-1);
        d.push_back(p.poly.at(i));
    }
    result=sort_operation(d);
    poly.clear();
    poly=result;
    sort();

}

void Polynomial::operator-=( Term &t)
{
    for(int i=0;i<poly.size();i++)
    {
            if(poly.at(i).get_pow()==t.get_pow())
            {
                poly.at(i)-=t;
            }
            else
            {
                t.set_coef(t.get_coef()*-1);
                poly.push_back(t);
            }
    }
    sort();
}

void Polynomial::operator-=( float &n)
{
    for(int i=0;i<poly.size();i++)
    {
            if(poly.at(i).get_pow()==0)
            {
                poly.at(i).set_coef(poly.at(i).get_coef()-n);
            }
            else
            {
                Term t(n,0);
                poly.push_back(t);
            }

    }
    sort();
}

void operator-=(Polynomial &p, Term &t)
{
    for(int i=0;i<p.poly.size();i++)
    {
            if(p.poly.at(i).get_pow()==t.get_pow())
            {
               p. poly.at(i)-=t;
            }
            else
            {
                t.set_coef(t.get_coef()*-1);
                p.poly.push_back(t);
            }
    }
    p.sort();
}

void operator-=( Polynomial &p,float &n)
{
    for(int i=0;i<p.poly.size();i++)
    {
            if(p.poly.at(i).get_pow()==0)
            {
                p.poly.at(i).set_coef(p.poly.at(i).get_coef()-n);
            }
            else
            {
                Term t(n,0);
                p.poly.push_back(t);
            }

    }
    p.sort();
}
//-----------------------------------------------------------------------------------------------//operator *=
void Polynomial::operator*=(Polynomial &p)
{
    vector<Term> mul;
    for(int i=0;i<poly.size();i++)
    {
        for(int j=0;j<p.poly.size();j++)
        {
            mul.push_back(poly.at(i)*p.poly.at(j));
        }
    }
    vector<Term> result;
    result=sort_operation(mul);
    poly.clear();
    poly=result;
    sort();
}

void Polynomial::operator*=(Term & t)
{
    vector<Term> mul;
    for(int i=0;i<poly.size();i++)
    {
            mul.push_back(poly.at(i)*t);

    }
    vector<Term> result;
    result=sort_operation(mul);
    poly.clear();
    poly=result;
    sort();
}

void Polynomial::operator*=(float& n)
{
    vector<Term> mul;
    for(int i=0;i<poly.size();i++)
    {
            mul.push_back(poly.at(i)*n);

    }
    vector<Term> result;
    result=sort_operation(mul);
    poly.clear();
    poly=result;
    sort();
}

void operator*=(Polynomial& p,Term & t)
{
    vector<Term> mul;
    for(int i=0;i<p.poly.size();i++)
    {
            mul.push_back(p.poly.at(i)*t);

    }
    vector<Term> result;
    result=sort_operation(mul);
    p.poly.clear();
    p.poly=result;
    p.sort();
}

void operator*=(Polynomial& p,float& n)
{
    vector<Term> mul;
    for(int i=0;i<p.poly.size();i++)
    {
            mul.push_back(p.poly.at(i)*n);

    }
    vector<Term> result;
    p.poly.clear();
    p.poly=result;
    p.sort();
}
//------------------------------------------------------------------------------------------------//operator =
void Polynomial::operator=(Polynomial& p)
{
    poly.clear();
    poly=p.poly;
}
//----------------------------------------------------------------------------------------------//operator ++ --

void Polynomial::operator++()
{
    bool flag=1;
    for(int i=0;i<poly.size();i++)
    {
        if(poly.at(i).get_pow()==0)
        {
            flag=0;
            poly.at(i)+=1;
        }
    }
    if(flag)
    {
        poly.push_back(Term(1,0));
    }
    sort();
}

void Polynomial::operator--()
{
    bool flag=1;
    for(int i=0;i<poly.size();i++)
    {
        if(poly.at(i).get_pow()==0)
        {
            flag=0;
            poly.at(i)-=1;
        }
    }
    if(flag)
    {
        poly.push_back(Term(-1,0));
    }
sort();
}
//-----------------------------------------------------------------------------------------------//operator ~
void Polynomial::operator~()
{

    int i=0;
    while(i<poly.size())
    {
            ~poly.at(i);
            i++;
    }
    sort();
}
//------------------------------------------------------------------------------------------------//operator ()
float Polynomial:: operator()(float num)
{
    int sum=0;
    for(int i=0;i<poly.size();i++)
    {
        sum+=(poly.at(i))(num);

    }
    return sum;
}

//------------------------------------------------------------------------------------------------// operator []
Term Polynomial::operator[](int ind) const
{
    return poly.at(ind);
}

Term Polynomial::operator[](int ind)
{
    return poly.at(ind);
}
//------------------------------------------------------------------------------------------------// operator <<  >>
ostream& operator<<(ostream& out,Polynomial & p)
{
    int i=0;;
    while (i<p.poly.size())
    {
        out<<p.poly.at(i);
        i++;
    }
    return out;
}

istream& operator>>(istream& in,Polynomial & p)
{

    string P,PE;
    vector<Term> POLY,result;
    vector<int> T;
    in>>P;
    for(int i=0;i<P.size();i++)
    {
        if(int(P[i])==43||int(P[i])==45)
        {
            T.push_back(i);
        }

    }

    if(T.size()==0)
    {
        Term t(P);
        POLY.push_back(t);
    }
    else
    {
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
    }

    result=sort_operation(POLY);
    p.poly=result;
    p.sort();
    return in;

}




////////////////////////////////////////////////////////////////////////////////////////////////////

void write_to_file_binary(Polynomial &p,string file_name)
{

    ofstream outputFile(file_name, ios::out | ios::binary|ios::trunc);
    if(!outputFile)
        cout<<"\nERROR NOT FOUND FILE!\n";
    else
        outputFile.write(reinterpret_cast<char *>(&p), sizeof(Polynomial));
}

void write_to_file_text(Polynomial &p,string file_name)
{

    ofstream outputFile(file_name, ios::out |ios::trunc);
    if(!outputFile)
        cout<<"\nERROR NOT FOUND FILE!\n";
    outputFile<<p;
}


#endif // POLYNOMIAL_H

