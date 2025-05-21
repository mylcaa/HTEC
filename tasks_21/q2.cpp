#include<iostream>
#include<cstdint>

class Average{
    private:
        int32_t sumNums;
        int numNums;
    public:
        Average(int32_t sumNums = 0, int numNums = 0):
        sumNums{sumNums},
        numNums{numNums}
        {}

        Average(const Average& avg):
        sumNums{avg.sumNums},
        numNums{avg.numNums}
        {}

        Average& operator+=(int operand){
            numNums++;
            sumNums += operand;
            
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& out, const Average& avg);
};

std::ostream& operator<<(std::ostream& out, const Average& avg){
    
    if(avg.numNums)
        out << static_cast<float>(avg.sumNums)/avg.numNums;
    return out;
}

int main()
{
	Average avg{};
	std::cout << avg << '\n';

	avg += 4;
	std::cout << avg << '\n'; // 4 / 1 = 4

	avg += 8;
	std::cout << avg << '\n'; // (4 + 8) / 2 = 6

	avg += 24;
	std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

	avg += -10;
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

	(avg += 6) += 10; // 2 calls chained together
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

	Average copy{ avg };
	std::cout << copy << '\n';

	return 0;
}