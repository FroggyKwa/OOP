#include <iostream>


namespace GenericLists
{
    using namespace std;

    template<typename T>
    class List
    {
    public:
        virtual void add(T element)
        {};

        virtual void put(T element, int position)
        {};

        virtual void remove(int position)
        {};

        virtual int find(T element)
        {};

        virtual T get(int index)
        {};

        virtual void print()
        {};
    };

    template<typename T>
    class ArrayList
    {
    private:
        T *arr;
        const int DEFAULT_ARRAYLIST_SIZE = 5;
        int size;
        int capacity;
    public:
        ArrayList()
        {
            arr = new T[DEFAULT_ARRAYLIST_SIZE];
            size = 0;
            capacity = DEFAULT_ARRAYLIST_SIZE;
        }

        explicit ArrayList(int n)
        {
            arr = new T[n];
            size = 0;
            capacity = n;
        }

        void extend_arraylist()
        {
            if (size == capacity)
            {
                capacity = capacity + DEFAULT_ARRAYLIST_SIZE;
                T *new_arr = new T[capacity];
                for (int i = 0; i < size; new_arr[i] = arr[i++]);
                arr = new_arr;
            }
        }

        void add(T elem)
        {
            extend_arraylist();
            arr[size] = elem;
            size++;
        }

        void put(T elem, int index)
        {
            if (index > size - 1 || index < 0)
            {
                cerr << "Index out of array range";
            } else
            {
                arr[index] = elem;
            }
        }

        void remove(int index)
        {
            if (index > size - 1 || index < 0)
            {
                cerr << "Index out of array range";
            } else
            {
                T *new_arr = new T[capacity];
                for (int i = 0; i < size; i++)
                {
                    if (i == index)
                        i++;
                    new_arr[i] = arr[i];
                }
                arr = new_arr;
                size--;
            }
        }

        int find(T elem)
        {
            for (int i = 0; i < size; i++)
            {
                if (arr[i] == elem)
                {
                    return i;
                }
            }
            return -1;
        }

        T get(int index)
        {
            if (index < 0 || index > size - 1)
                cerr << "Index out of array range";
            return arr[index];
        }

        void print()
        {
            for (int i = 0; i < size; ++i)
            {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
    };

    template<typename T>
    class LinkedList : public List<T>
    {
    private:
        template<typename TT>
        class Node
        {
        public:
            Node<TT> *prev = nullptr;
            Node<TT> *next = nullptr;
            TT value;

            explicit Node(TT value_t)
            {
                value = value_t;
            }
        };

        Node<T> *head;
        Node<T> *tail;
        int size;
    public:
        explicit LinkedList()
        {
            head = nullptr;
            size = 0;
        }

        void add(T elem)
        {
            Node<T> *new_node = new Node<T>(elem);
            if (head == nullptr)
            {
                head = new_node;
            } else
            {
                tail->next = new_node;
                new_node->prev = tail;
            }
            tail = new_node;
            size++;
        }

        void put(T elem, int index)
        {
            Node<T> *new_node = new Node<T>(elem);
            if (index > size - 1 || index < 0)
                cerr << "Index out of array range";
            if (size == 0)
            {
                head = new_node;
                tail = new_node;
            } else if (index == 0)
            {
                new_node->next = head;
                head->prev = new_node;
                head = new_node;
            } else if (index == size)
            {
                tail->next = new_node;
                new_node->prev = tail;
                tail = new_node;
            } else
            {
                Node<T> *cur_node = head;
                for (int i = 0; i < index; i++)
                {
                    cur_node = cur_node->next;
                }
                new_node->prev = cur_node->prev;
                cur_node->prev->next = new_node;
                new_node->next = cur_node;
                cur_node->prev = new_node;
            }
        }

        void remove(int index)
        {
            if (index > size - 1 || index < 0)
                cerr << "Index out of array range";
            Node<T> *node = head;
            for (int i = 0; i < index; i++)
                node = node->next;
            if (index == size - 1)
                node->prev->next = node->next;
            else if (index == 0)
            {
                head = node->next;
                head->prev = nullptr;
            }
            else
            {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
        }

        int find(T elem)
        {
            Node<T> *node = head;
            for (int i = 0; i < size - 1; i++)
            {
                if (node->value == elem)
                    return i;
                node = node->next;
            }
            return -1;
        }

        T get(int index)
        {
            if (index > size - 1 || index < 0)
            {
                cerr << "Index out of array range";
            }
            Node<T> *node = head;
            for (int i = 0; i < index; i++)
            {
                node = node->next;
            }
            return node->value;
        }

        void print() override
        {
            for (Node<T>* i = head; i != nullptr; i = i->next)
                cout << i->value << " ";
            cout << endl;
        }
    };
}

using namespace GenericLists;

int main(int argc, char *argv[])
{
    auto ll = new LinkedList<int>();
    ll->add(2);
    ll->add(3);
    ll->add(5);
    ll->remove(1);
    cout << "Index in list of value 2 is " <<  ll->find(2) << endl;
    cout << "List items are: ";
    ll->print();
    cout << "The 1'st element is " << ll->get(1) << endl;
    return 0;
}