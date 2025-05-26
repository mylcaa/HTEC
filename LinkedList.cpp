#include <iostream>
#include <memory>
#include <cassert>
#include <initializer_list>

//limiting the type of LinkedList through template specialization of struct type_sifting
template<typename T>
struct type_sifting{
    static const bool value = false;
};

template<>
struct type_sifting<int>{
    static const bool value = true;
};

template<>
struct type_sifting<float>{
    static const bool value = true;
};

template<typename T>
struct Node{
    std::shared_ptr<Node<T>> next{};
    T value{};
}; 

template <typename T>
class LinkedList{
    static_assert(type_sifting<T>::value, "List type must be int or float");
    
    private:
        std::shared_ptr<Node<T>> head{};
    public:
        LinkedList(int size = 0)                               //init through size of list
        {
            assert(size >= 0 && "Error: size must be positive");
             
            std::shared_ptr<Node<T>> head_copy{};        
            
            for(int i = 0; i < size; ++i){
                std::shared_ptr<Node<T>> temp{new Node<T>{}}; //make a node and connect it to a smart ptr
                
                if(i == 0){
                    head = temp;                               //setup head_ptr on the first iteration
                    head_copy = head;                          //and initialize helper ptr with first node
                }else{
                    (*head_copy).next = temp;                  //else connect the current and previous node    
                    head_copy = temp;                          //move the knitting ptr along the list
                }
            }
        }

        LinkedList(std::initializer_list<T> args)              //init through initializer list
        {   
           std::shared_ptr<Node<T>> head_copy{};              //make a helper ptr to use in for loop

            for(size_t i = 0; i < args.size(); ++i){
                std::shared_ptr<Node<T>> temp{new Node<T>{}};  //make a node and connect it to a temp ptr

                if(i == 0){
                    head = temp;                               //setup head_ptr on the first iteration
                    head_copy = head;                          //and initialize helper ptr with first node
                }else{
                    (*head_copy).next = temp;                  //else connect the current and previous node    
                    head_copy = temp;                          //move the knitting ptr along the list
                }
                
                (*head_copy).value = args.begin()[i];
            }
        }

        //helper test function
        void printLinkedList(){
            std::shared_ptr<Node<T>> head_copy = head;

            while(head_copy != nullptr){
                std::cout << (*head_copy).value << " ";
                head_copy = (*head_copy).next;
            }
            std::cout << '\n';
        }

};


int main(){

    LinkedList<int> l{1, 4, 5, 7};
    l.printLinkedList();

    return 0;
}