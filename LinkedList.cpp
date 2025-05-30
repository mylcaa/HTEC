#include <iostream>
#include <memory>
#include <cassert>
#include <initializer_list>
#include <type_traits>

template<typename T>
class Node{
    public:
        T value{};
        std::shared_ptr<Node<T>> next{};
    public:
        Node(T value = 0, std::shared_ptr<Node<T>> next = nullptr) : 
        value{value}, 
        next{next}
        {}
};

template <typename T, typename = typename std::enable_if<std::is_floating_point<T>::value || 
std::is_integral<T>::value, T>::type>
class LinkedList{
    private:
        std::shared_ptr<Node<T>> head{};
        std::shared_ptr<Node<T>> tail{};
        int size{};
    public:

        LinkedList(const int size):                                            //init through size of list
        size{size}
        {
            assert(size >= 0 && "Error: size must be positive");
                
            std::shared_ptr<Node<T>> head_copy{};        

            for(int i = 0; i < size; ++i){
                std::shared_ptr<Node<T>> temp{new Node<T>{}};                  //make a node and connect it to a smart ptr
                
                if(i == 0){
                    head = temp;                                               //setup head_ptr on the first iteration
                    head_copy = head;                                          //and initialize helper ptr with first node
                }else{
                    (*head_copy).next = temp;                                  //else connect the current and previous node    
                    head_copy = temp;                                          //move the knitting ptr along the list
                }

                if(i == size-1){
                    tail = head_copy;                                          //if you're at the end of the list set the tail ptr
                }
            }
        }

        LinkedList(std::initializer_list<T> args):                             //init through initializer list
        size{static_cast<int>(args.size())}
        {   
            std::shared_ptr<Node<T>> head_copy{};                              //make a helper ptr to use in for loop

            for(size_t i = 0; i < args.size(); ++i){
                std::shared_ptr<Node<T>> temp{new Node<T>{args.begin()[i]}};   //make a node and connect it to a temp ptr

                if(i == 0){
                    head = temp;                                               //set head_ptr on the first iteration
                    head_copy = head;                                          //initialize helper ptr on the first iteration
                }else{
                    (*head_copy).next = temp;                                  //connect the current and previous node    
                    head_copy = temp;                                          //move the knitting ptr along the list
                }

                if(i == args.size()-1){
                    tail = head_copy;                                          //set tail_ptr on the last iteration
                }
            }
        }

        void push_back(T value){
            std::shared_ptr<Node<T>> temp{new Node<T>{value}};

            if(size != 0){
                (*tail).next = temp;
                tail = temp;
                size++;
            }else{
                head = temp;
                tail = temp;
            }
        }

        void insert(T value, const int position){
            assert(position <= size && "Position out of bounds");

            if(position == size){                                              //trivial case pos = end of list
                this->push_back(value);
                return;
            }

            std::shared_ptr<Node<T>> position_ptr{new Node<T>{value}};
            
            if(position == 0){                                                 //trivial case pos = beginning of list
                position_ptr->next = head;
                head = position_ptr;
                return;    
            }

            std::shared_ptr<Node<T>> trail = head;
            position_ptr->next = head->next;

            for(int i = 1; i < position; ++i){
                position_ptr->next = position_ptr->next->next;
                trail = trail->next;
            }
            trail->next = position_ptr;
        }

        void clear(){
            tail.reset();
            head.reset();
            size = 0;
        }

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

    LinkedList<int> l{1, 2, 3}; 

    return 0;
}

//limiting the type of LinkedList through template specialization of struct type_sifting
/*template<bool B, typename T>
struct enable_if {};
template<typename T>
struct enable_if<true, T> { typedef T type; };

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
};*/