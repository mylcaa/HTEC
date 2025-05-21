#include <iostream>
#include <cassert>

class IntArray{
    private:
        int size{0};
        int* array{nullptr};
    
    public:
        IntArray(int size): size{size}{
            assert(size > 0);
            array = new int[size]{};
        }

        IntArray(const IntArray& ref): size{ref.size}{
            array = new int[size]{};

            for(int i = 0; i < size; ++i)
                array[i] = ref.array[i];
        }

        ~IntArray(){
            delete[] array;
        }

        int& operator[](const int position){
            assert(position >= 0 && position < size);

            return array[position];
        }

        IntArray& operator=(const IntArray& r_val){

            if(this == &r_val)
                return *this;

            if(size < r_val.size){
                delete[] array;
                array = new int[r_val.size]{};
                size = r_val.size;
            }
                
            for(int i = 0; i < r_val.size; ++i)
                array[i] = r_val.array[i];

            return *this;
        }

        friend std::ostream& operator<<(std::ostream& out, const IntArray& int_array){
            
            for(int i = 0; i < int_array.size; ++i)
                out << int_array.array[i] << " ";
            out << '\n';

            return out;
        }
         
};

IntArray fillArray()
{
	IntArray a(5);

	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;

	return a;
}

int main()
{
	IntArray a{ fillArray() };

	std::cout << a << '\n';

	auto& ref{ a }; // we're using this reference to avoid compiler self-assignment errors
	a = ref;

	IntArray b(1);
	b = a;

	a[4] = 7;

	std::cout << b << '\n';

	return 0;
}