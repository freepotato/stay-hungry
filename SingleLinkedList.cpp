#include <iostream>

// single-linked list 单链表实现;
// 节点 Node: data, next;
// 链表 LinkedList();
// 链表 public 方法:
//  void append, void printList, bool search, void remove


// 定义节点
template <typename T>
struct Node
{
    T data;
    Node* next;
    Node(const T& value): data(value), next(nullptr){}
};

// 定义链表
template <typename T>
class LinkedList
{
private:
    // 头、尾指针
    Node<T>* head;
    Node<T>* tail;
public:
    LinkedList(): head(nullptr){};

    void append(const T& value)
    {
        Node<T>* NewNode = new Node<T>(value);
        if (!head){
            head = NewNode;
            tail = head;
        }else{
            tail->next = NewNode;
            tail = NewNode; 
        }
    }

    void remove(const T& value)
    {
        // 空链表
        if(!head){
            std::cout << "ERROR: Empty list." << std::endl;
            return;
        }

        Node<T>* prev = head;
        Node<T>* current = head;
        while (current != nullptr){
            if (current->data == value){
                if (current == head){
                    head = current->next;
                }else{
                    prev->next = current->next;
                }
                delete current;
                break;
            }
            prev = current;
            current = current->next;
        }
    }

    void printList()
    {
        Node<T>* current = head;
        while (current){
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    bool search(const T& value)
    {
        Node<T>* current = head;
        while(current){
            if(current->data == value){
                return true;
            }
            current = current->next;
        }
        return false;
    }
    ~LinkedList()
    {
        Node<T>* current = head;
        while(current){
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
};
