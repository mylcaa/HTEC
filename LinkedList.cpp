#include <iostream>
#include <memory>

template <typename T>
class LinkedList{
    private:
        std::shared_ptr<LinkedList<T>> next{};
        T value{};
    public:
        LinkedList(std::shared_ptr<LinkedList<T>> smart_ptr = nullptr, T vvalue = 0)
        {
            next = smart_ptr;
            value = vvalue;
            std::cout << "created: " << value << '\n';
        }

        ~LinkedList(){
            std::cout << value << " destroyed\n";  
        }

        void setValue(T vvalue){value = vvalue;}
        void setPtr(std::shared_ptr<LinkedList<T>> smart_ptr){next = smart_ptr;}

        T getValue() const {return value;}
        std::shared_ptr<LinkedList<T>> getPtr() const {return next;}

};

//helper test function 
template<typename T>
void printLinkedList(std::shared_ptr<LinkedList<T>> head){

    while(head != nullptr){
        std::cout << (*head).getValue() << " ";
        head = (*head).getPtr();
    }
    std::cout << '\n';
}

int main(){

    std::shared_ptr<LinkedList<int>> head{new LinkedList<int>{nullptr, 0}};
    std::shared_ptr<LinkedList<int>> head_copy = head;

    for(int i = 1; i < 10; ++i){
        //make node and connect it to a smart ptr
        std::shared_ptr<LinkedList<int>> temp{new LinkedList<int>{nullptr, i}};
        //give that smart ptr to the previous node's ptr => connect the current and previous node
        (*head_copy).setPtr(temp);
        head_copy = temp;
    }

    printLinkedList(head);

    return 0;
}