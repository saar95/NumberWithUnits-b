#include <string>
#include <iostream>
#include "NumberWithUnits.hpp"
#include <cmath>
#include <fstream>
#include <sstream>
const double EPS = 0.001;
using namespace std;

namespace ariel {
        static map<string, map<string,double> > my_table;
        NumberWithUnits::NumberWithUnits(double amount, const string type){
            if(my_table.count(type)!=0){
                this->type = type;
                this->amount = amount;  
            }
                else
                    throw invalid_argument {"please use types from the txt file."};     
    }
        double convert(string from,string to,double amount){
            if (from==to) {
                return amount;
                }
                try{
                    return my_table.at(from).at(to)*amount;
                }
                catch(const exception& e)
                {
                    throw invalid_argument {"cannot covert between this 2 types."};
                }
            }
        void update(string type1,string type2){
            for(auto &pairs : my_table[type2]) {
                double amount = my_table[type1][type2] * pairs.second;
                my_table[pairs.first][type1] = 1/amount;
                my_table[type1][pairs.first] = amount;
                
            }
            for(auto &pairs : my_table[type1]) {
                double amount = my_table[type2][type1] * pairs.second;
                my_table[pairs.first][type2] = 1/amount;
                my_table[type2][pairs.first] = amount;
            }
            }
        void NumberWithUnits::read_units(ifstream& text_file){
            double amount1,amount2;
            string type1,type2,eq;
            while (text_file>>amount1>>type1>>eq>>amount2>>type2){
                my_table[type2][type1]=1/amount2;
                my_table[type1][type2]=amount2;
                update(type1,type2);
            }
        }
        ostream& operator <<(ostream& os,const NumberWithUnits& num1){
            return os<<num1.amount<<"["<<num1.type<<"]";
        } 
        istream& operator >>(istream& input,NumberWithUnits& num1){
            char temp1,temp2;
            double amount;
            string type;
            input>>amount>>temp1>>type;
            if(type.find(']')!=string::npos)//check if "]" is in the string
            {
                size_t index=type.find(']');
                type=type.substr(0,index);
            }
            else 
                input>>temp2;
            if(my_table.count(type)==0)
                throw invalid_argument {"please use types from the txt file."};
            else{
                num1.type=type;
                num1.amount=amount;
            }
            return input;
         }  
        bool NumberWithUnits :: operator <= (const NumberWithUnits& num1) const{
            if (this->amount <= convert(num1.type,this->type,num1.amount))
                return true;
            return false;
        }
        bool NumberWithUnits :: operator == (const NumberWithUnits& num1) const{
            if(abs(this->amount-convert(num1.type,this->type,num1.amount))<EPS)
                return true;
            return false;
        }
        bool NumberWithUnits :: operator != (const NumberWithUnits& num1) const{
            if (!(*this == num1))
                return true;
            return false;
        }
        NumberWithUnits& NumberWithUnits ::operator += (const NumberWithUnits& num1){// a=a+b
            this->amount=this->amount+convert(num1.type,this->type,num1.amount);
            return *this;
        } 
        NumberWithUnits& NumberWithUnits ::operator -= (const NumberWithUnits& num1){// a=a-b
            this->amount=this->amount-convert(num1.type,this->type,num1.amount);
            return *this;
        } 
        NumberWithUnits& NumberWithUnits :: operator -- (){
            this->amount=this->amount-1;
            return *this;
        }      
		const NumberWithUnits NumberWithUnits :: operator -- (int){
            double amount=this->amount;
            this->amount=amount-1;
            return NumberWithUnits{amount,this->type};
        }   
        ////////////////////////
        NumberWithUnits operator + (const NumberWithUnits& num1,const NumberWithUnits& num2){// x=(a+b) ->FRIND FUNCTION
            double amount=convert(num2.type,num1.type,num2.amount)+num1.amount;
            return NumberWithUnits{amount,num1.type};
        } 
        NumberWithUnits operator - (const NumberWithUnits& num1,const NumberWithUnits& num2){// x=(a-b) ->FRIND FUNCTION
            double amount=num1.amount-convert(num2.type,num1.type,num2.amount);
            return NumberWithUnits{amount,num1.type};
        } 
        NumberWithUnits NumberWithUnits ::operator + () {
            return NumberWithUnits{+this->amount,this->type};
        }   
        NumberWithUnits NumberWithUnits ::operator - () {
            return NumberWithUnits{-this->amount,this->type};
        }   
        bool NumberWithUnits :: operator > (const NumberWithUnits& num1) const{ 
            if (this->amount > convert(num1.type,this->type,num1.amount))
                return true;
            return false;
        }
        bool NumberWithUnits :: operator >= (const NumberWithUnits& num1) const{
            if (this->amount >= convert(num1.type,this->type,num1.amount))
                return true;
            return false;
        }
        bool NumberWithUnits :: operator < (const NumberWithUnits& num1) const{
            if (this->amount < convert(num1.type,this->type,num1.amount))
                return true;
            return false;
        }
        NumberWithUnits& NumberWithUnits :: operator ++ (){
            this->amount=this->amount+1;
            return *this;
        }      
		const NumberWithUnits NumberWithUnits :: operator ++ (int){
            double amount=this->amount;
            this->amount=amount+1;
            return NumberWithUnits{amount,this->type};
        }   
        NumberWithUnits operator * (const NumberWithUnits& num1,double multi) {
            return NumberWithUnits(num1.amount*multi,num1.type);
        }
        NumberWithUnits operator * (double multi,const NumberWithUnits& num1) {
            return NumberWithUnits(num1.amount*multi,num1.type);
        }
    }



        
    



