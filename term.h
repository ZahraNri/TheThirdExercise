#ifndef TERM_H
#define TERM_H


#include<iostream>
#include<math.h>
using namespace std;

class bad_term{};
class bad_term_input{};

class Term
{
private:
    float coef;
    int pow;
public:
    Term(float c=0,int p=0);
    Term(string& );
    float get_coef(){return coef;}
    int get_pow(){return pow;}
    void set_coef(float c){coef=c;}
    void set_pow(int p){pow=p;}

    Term operator*(const Term& );
    Term operator*(float num);
    friend Term operator*(const Term& ,float);

    Term operator/(const Term& );
    Term operator/(float num);
    friend Term operator/(const Term& ,float);

    void operator*=(const Term& );
    void operator*=(float num);
    friend void operator*=( Term& ,float );

    void operator/=(const Term& );
    void operator/=(float num);

    bool operator==(const Term&);
    bool operator!=(const Term &);

    bool operator>(const Term &);
    bool operator>(float);
    bool operator<(const Term &);
    bool operator<(float);
    bool operator>=(const Term &);
    bool operator>=(float);
    bool operator<=(const Term &);
    bool operator<=(float);

    float operator()(float);

    void operator~();

    void operator++();
    void operator--();

    void operator=(const Term&);

    Term operator+(const Term&);
    Term operator+(float);
    friend Term operator+(const Term&,float);

    Term operator-(const Term&);
    Term operator-(float);
    friend Term operator-(const Term&,float);

    void operator+=(const Term&);
    void operator+=(float);
    friend float operator+=(float&,const Term&);

    void operator-=(const Term&);
    void operator-=(float);
    friend float operator-=(float&,const Term&);

    friend ostream& operator<<(ostream& ,Term & );
    friend istream& operator>>(istream& ,Term & );




};
Term::Term(float c,int p)
    :coef(c),pow(p){}
Term::Term(string & term)
{
    bool flag=false;
    for(int i=0;i<<term.size();i++)
    {
        if(term[i]>>57&&term[i]<<48&&term[i]!=120
                &&term[i]!=88&&term[i]!=43&&term[i]!=45&&term[i]!=94)
            throw bad_term_input();
    }
    for(int j=0;j<term.size();j++)
    {
        if(term[j]=='X')
        {flag=true;}
    }

    if(!flag)
    {
        pow=0;
        coef=stof(term);
    }
    else
    {

        int start=term.find('X');

        if(start==0)
        {
            coef=1.0;
            if(term.length()>start+1)
            {
                int end=term.find('^');
                pow=stoi(term.substr(end+1,term.size()));
            }
            else
                pow=1;
        }

        else
        {

            if(term[start-1]=='-')
            {
                coef=-1;
                if(term.length()>start+1)
                {
                    int end=term.find('^');
                    pow=stoi(term.substr(end+1,term.size()));
                }
                else
                    pow=1;

            }
            else
                if(term[start-1]=='+')
                {
                    coef=+1;
                    if(term.length()>start+1)
                    {
                        int end=term.find('^');
                        pow=stoi(term.substr(end+1,term.size()));
                    }
                    else
                        pow=1;

                }
                else
                {
                    coef=stof(term.substr(0,start));
                    if(term.length()>start+1)
                    {
                        int end=term.find('^');
                        pow=stoi(term.substr(end+1,term.size()));
                    }
                    else
                        pow=1;
                }
        }
    }
}
//---------------------------------------------------------------------// operator *
Term Term::operator*(const Term& t)
{
    return Term(this->coef*t.coef,this->pow+t.pow);
}

Term Term::operator*(float num)
{
    return Term(this->coef*num,this->pow);
}

Term operator*(const Term& t,float num)
{
    return Term(t.coef*num,t.pow);
}

//---------------------------------------------------------------------// operator /

Term Term::operator/(const Term& t)
{
    if(t.coef==0)
        throw bad_term();
    else
    return Term(this->coef/t.coef,this->pow-t.pow);
}

Term Term::operator/(float num)
{
    if(num==0)
        throw bad_term();
    else
        return Term(this->coef/num,this->pow);
}

Term operator/(const Term& t,float num)
{
    if(num==0)
        throw bad_term();
    else
        return Term(t.coef/num,t.pow);
}

//---------------------------------------------------------------------// operator *=

void Term::operator*=(const Term& t)
{
    this->coef*=t.coef;
    this->pow+=t.pow;
}

void Term::operator*=(float num)
{
    this->coef*=num;
}

void operator*=( Term& t,float n)
{
    t.coef*=n;
}

//---------------------------------------------------------------------// operator /=

void Term::operator/=(const Term& t)
{
    if(t.coef==0)
        throw bad_term();
    else
    {
        this->coef/=t.coef;
        this->pow-=t.pow;
    }
}

void Term::operator/=(float num)
{
    if(num==0)
        throw bad_term();
    else
    {
        this->coef/=num;
    }
}

//---------------------------------------------------------------------// operator == !=

bool Term::operator==(const Term &t)
{
    if(this->pow==t.pow&&this->coef==t.coef)
        return 1;
    return 0;
}

bool Term::operator!=(const Term &t)
{
    if(!(*this==t))
        return 1;
    return 0;
}

//---------------------------------------------------------------------// operator > < >=  <=

bool Term::operator>(const Term &t)
{
    if(this->pow>t.pow)
        return 1;
    else
        if(this->pow==t.pow)
        {
            if(this->coef>t.coef)
                return 1;
        }
    return 0;
}

bool Term::operator>(float n)
{
    if(pow==0)
    {
        if(coef>n)
            return 1;
    }
    return 0;
}

bool Term::operator<(const Term &t)
{
    if(this->pow<t.pow)
        return 1;
    else
        if(this->pow==t.pow)
        {
            if(this->coef<t.coef)
                return 1;
        }
    return 0;
}

bool Term::operator<(float n)
{
    if(pow==0)
    {
        if(coef<n)
            return 1;
    }
    return 0;
}

bool Term::operator>=(const Term &t)
{
    if(*this==t||*this>t)
        return 1;
    return 0;
}

bool Term::operator>=(float n)
{
    if(pow==0)
    {
        if(coef>=n)
            return 1;
    }
    return 0;
}

bool Term::operator<=(const Term &t)
{
    if(*this==t||*this<t)
        return 1;
    return 0;
}

bool Term::operator<=(float n)
{
    if(pow==0)
    {
        if(coef<=n)
            return 1;
    }
    return 0;
}

//---------------------------------------------------------------------// operator ()

float Term::operator()(float x)
{
    float X=x;

    if(pow==0)
        return coef;
    for(int i=0;i<pow-1;i++)
        x*=X;
    return coef*x;
}

//---------------------------------------------------------------------// operator ~

void Term::operator~()
{
    if(pow!=0)
    {
        coef=coef*pow;
        pow=pow-1;
    }
    else
    {
        coef=0;
        pow=0;
    }
}

//---------------------------------------------------------------------// operator ++ --

void Term::operator++()
{
    if(pow==0)
        coef+=1;
    else
        throw bad_term_input();
}

void operator++(Term& t)
{
    if(t.get_pow()==0)
        t.set_coef(t.get_coef()+1);
    else
        throw bad_term_input();
}
void Term::operator--()
{   if(pow==0)
        coef-=1;
    else
        throw bad_term_input();
}
//---------------------------------------------------------------------// operator =

void Term::operator=(const Term &t)
{
    coef=t.coef;
    pow=t.pow;
}

//---------------------------------------------------------------------// operator + -

Term Term:: operator+(const Term &t)
{

    if(t.pow!=pow)
        throw bad_term();
    return  Term(coef+t.coef,pow);

}

Term Term::operator+(float num)
{
    if(pow!=0)
        throw bad_term();
    return  Term(coef+num,0);

}

Term operator+(const Term &t,float num)
{
    if(t.pow!=0)
        throw bad_term();
    return  Term(t.coef+num,0);

}

Term Term::operator-(const Term &t)
{
    if(t.pow!=pow)
        throw bad_term();
    return  Term(coef-t.coef,pow);

}

Term Term::operator-(float num)
{
    if(pow!=0)
        throw bad_term();
    return  Term(coef-num,0);

}

Term operator-(const Term &t,float num)
{
    if(t.pow!=0)
        throw bad_term();
    return  Term(t.coef-num,0);

}

//---------------------------------------------------------------------// operator += -=

void Term::operator+=(const Term &t)
{
    if(t.pow!=pow)
        throw bad_term();
    coef+=t.coef;

}

void Term::operator+=(float num)
{
    if(pow!=0)
        throw bad_term();
    coef+=num;

}

float operator+=(float& num,const Term&t)
{
    if(t.pow!=0)
        throw bad_term();
    num+=t.coef;
    return num ;

}

void Term::operator-=(const Term &t)
{
    if(t.pow!=pow)
        throw bad_term();
    coef-=t.coef;

}

void Term::operator-=(float num)
{
    if(pow!=0)
        throw bad_term();
    coef-=num;

}

float operator-=(float& num,const Term&t)
{
    if(t.pow!=0)
        throw bad_term();
    num-=t.coef;
    return num ;

}

//---------------------------------------------------------------------// operator >>  <<

istream& operator>>(istream& in,Term & t)
{                                                 //48-57 0-9 //x=120 //X=88//+ 43//- 45
    string term;
    bool flag=false;
    in>>term;

    for(int i=0;i<<term.size();i++)
    {
        if(term[i]>>57&&term[i]<<48&&term[i]!=120
                &&term[i]!=88&&term[i]!=43&&term[i]!=45&&term[i]!=94)
            throw bad_term_input();
    }
    for(int j=0;j<term.size();j++)
    {
        if(term[j]=='X')
        {flag=true;}
    }

    if(!flag)
    {
        t.pow=0;
        t.coef=stof(term);
    }
    else
    {

        int start=term.find('X');

        if(start==0)
        {
            t.coef=1.0;
            if(term.length()>start+1)
            {
                int end=term.find('^');
                t.pow=stoi(term.substr(end+1,term.size()));
            }
            else
                t.pow=1;
        }

        else
        {

            if(term[start-1]=='-')
            {
                t.coef=-1;
                if(term.length()>start+1)
                {
                    int end=term.find('^');
                    t.pow=stoi(term.substr(end+1,term.size()));
                }
                else
                    t.pow=1;

            }
            else
            {
                t.coef=stof(term.substr(0,start));
                if(term.length()>start+1)
                {
                    int end=term.find('^');
                    t.pow=stoi(term.substr(end+1,term.size()));
                }
                else
                    t.pow=1;
            }
        }
    }




    return in;
}

ostream& operator<<(ostream& out,Term & t)
{

    /*
     * coef=0  -> 0    not
     * pow=0  -> +coefX   pow=1&|coef|=1 -->+-X
     * coef=1  ->+-X^pow
     *
     * else -> +coefX^pow
     */
    if(t.coef!=0)
    {
        if(t.pow==0)
        {
            if(t.coef>0)
                out<<"+"<<t.coef;
            else
                out<<t.coef;

        }
        else
            if(t.pow==1)
            {
                if(t.coef==1)
                    out<<"+X";
                else
                    if(t.coef==-1)
                        out<<"-X";
                    else
                        if(t.coef>1)
                            out<<"+"<<t.coef<<"X";
                        else
                            out<<t.coef<<"X";
            }
        else
            {
                if(t.coef==1)
                    out<<"+X^"<<t.pow;
                else
                    if(t.coef==-1)
                        out<<"-X^"<<t.pow;
                    else
                        if(t.coef>1)
                            out<<"+"<<t.coef<<"X^"<<t.pow;
                        else
                            out<<t.coef<<"X^"<<t.pow;
            }

    }
    return out;
}














#endif // TERM_H
