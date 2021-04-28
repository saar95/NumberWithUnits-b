#include <iostream>
#include <map>
#include <string>


namespace ariel {
    class NumberWithUnits{

    private:
        std::string type;
        double amount;
    public:
        NumberWithUnits(double amount, const std::string type);
        static void read_units(std::ifstream& file_name);
        friend std::ostream& operator<<(std::ostream& os, const NumberWithUnits& num1);
        friend std::istream& operator>>(std::istream& is, NumberWithUnits& num1);
        friend NumberWithUnits operator+(const NumberWithUnits& num1,const NumberWithUnits& num2);
        friend NumberWithUnits operator-(const NumberWithUnits& num1,const NumberWithUnits& num2);
        friend NumberWithUnits operator*(const NumberWithUnits& num1, double multi);
        friend NumberWithUnits operator*(double multi, const NumberWithUnits& num1);
        const NumberWithUnits operator++(int);
        const NumberWithUnits operator--(int);
        bool operator<=(const NumberWithUnits& num1) const;
        bool operator==(const NumberWithUnits& num1) const;
        bool operator!=(const NumberWithUnits& num1) const;
        bool operator>(const NumberWithUnits& num1) const;
        bool operator>=(const NumberWithUnits& num1) const;
        bool operator<(const NumberWithUnits& num1) const;
        NumberWithUnits& operator++();
        NumberWithUnits& operator--();
        NumberWithUnits operator-();
        NumberWithUnits operator+();
        NumberWithUnits& operator+=(const NumberWithUnits& num1);
        NumberWithUnits& operator-=(const NumberWithUnits& num1);
    };
}
