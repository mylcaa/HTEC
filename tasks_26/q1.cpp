#include<iostream>

template<typename T>
class Pair1{
    private:
        T op1;
        T op2;
    public:
        Pair1(T op1, T op2): 
        op1{op1}, 
        op2{op2} 
        {}

        T first() const {return op1;}
        T second() const {return op2;}

};

template<typename T, typename U>
class Pair{
    private:
        T op1;
        U op2;
    public:
        Pair(T op1, U op2): 
        op1{op1}, 
        op2{op2} 
        {}

        T first() const {return op1;}
        U second() const {return op2;}

};

template<typename T>
class StringValuePair{
    private:
        std::string op1;
        T op2;
    public:
        StringValuePair(std::string op1, T op2): 
        op1{op1}, 
        op2{op2} 
        {}

        std::string first() const {return op1;}
        T second() const {return op2;}

};


int main()
{
    //1# test <typename T>
    Pair1<int> p1 { 5, 8 };
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair1<double> p2 { 2.3, 4.5 };
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    //2# test <typename T, typename U>
	Pair<int, double> p3 { 5, 6.7 };
	std::cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';

	const Pair<double, int> p4 { 2.3, 4 };
	std::cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';

    //3# test <typename T>
	StringValuePair<int> svp { "Hello", 5 };
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

	return 0;
}