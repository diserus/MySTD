#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <iostream>
#include <cmath>
namespace mystd
{
    template <typename T>
    class Node
    {
    public:
        T data;
        Node *prev;
        Node *next;

        Node(const T &value) : data(value), prev(nullptr), next(nullptr) {}
    };
    template <typename T>
    class list
    {
    public:
        typedef std::size_t size_type;
        typedef Node<T> *iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;

        list() : head(nullptr) {}

        list(const list &other) : head(nullptr)
        {
        }

        list(size_type n, const T &val = T()) : head(nullptr)
        {
        }

        list(iterator start, iterator end) : head(nullptr)
        {
        }

        ~list()
        {
            delete head;
        }

        void push_back(const T &value)
        {
            Node<T> *newNode = new Node<T>(value);
            if (empty())
                head = newNode;
            else
            {
                Node<T> *current = head;
                while (current->next != nullptr)
                {
                    current = current->next;
                }
                current->next = newNode;
                newNode->prev = current;
            }
            _size++;
        }
        bool empty()
        {
            return head == nullptr;
        }

        // Итераторы не работают
        iterator begin()
        {
            return head;
        }
        iterator end()
        {
            Node<T> *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            return current;
        }

    private:
        Node<T> *head;
        size_type _size;
    };
}
#endif
