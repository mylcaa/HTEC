#include <cassert>
#include <iostream>
#include <cstdint>
#include <cmath>
 
class FixedPoint2{
    private:
        int16_t base{};
        int8_t decimal{};
        int8_t sign;
    public:
        FixedPoint2(int16_t whole, int8_t fraction){

            base = (whole < 0 ? -whole : whole);
            decimal = (fraction < 0 ? -fraction : fraction);

            while(decimal > 99){
                decimal -= 100;
                base++;
            }

            if(whole < 0 || fraction < 0)
                sign = -1;
            else    
                sign = 1; 
        }

        FixedPoint2(double number): FixedPoint2(static_cast<int>(number), static_cast<int>(std::round(number*100)) - static_cast<int>(number)*100)
        {}

        operator double() const {
            return sign*(base + static_cast<double>(decimal)/100);
        }

        FixedPoint2& operator-(){
            sign = -sign;
            return *this;
        }

        friend bool operator==(const FixedPoint2& op1, const FixedPoint2& op2){
            return (op1.sign*op1.base == op2.sign*op2.base) && (op1.sign*op1.decimal == op2.sign*op2.decimal);
        }

        friend FixedPoint2 operator+(const FixedPoint2& op1, const FixedPoint2& op2){
            return FixedPoint2{static_cast<double>(op1) + static_cast<double>(op2)};
        }

        friend std::ostream& operator<<(std::ostream& out, FixedPoint2& fixed_pt){
            out << static_cast<double>(fixed_pt);
            return out;
        }

        friend std::istream& operator>>(std::istream& in, FixedPoint2& fixed_pt){
            double input = static_cast<double>(fixed_pt);
            in >> input;
            fixed_pt = FixedPoint2{input};
            return in;
        }
};


int main()
{
	assert(FixedPoint2{ 0.75 } == FixedPoint2{ 0.75 });    // Test equality true
	assert(!(FixedPoint2{ 0.75 } == FixedPoint2{ 0.76 })); // Test equality false

	// Test additional cases -- h/t to reader Sharjeel Safdar for these test cases
    assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 1.98 });    // both positive, no decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 2.25 });    // both positive, with decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -1.98 }); // both negative, no decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -2.25 }); // both negative, with decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -0.48 });  // second negative, no decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -0.75 });  // second negative, possible decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 0.48 });   // first negative, no decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 0.75 });   // first negative, possible decimal overflow
    
	FixedPoint2 a{ -0.48 };
	assert(static_cast<double>(a) == -0.48);
	assert(static_cast<double>(-a) == 0.48);

	std::cout << "Enter a number: "; // enter 5.678
	std::cin >> a;
	std::cout << "You entered: " << a << '\n';
	assert(static_cast<double>(a) == 5.68);

	return 0;
}