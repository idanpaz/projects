#include <cstddef> // size_t
#include <iostream> // test
#include <pthread.h> // mutex 

template <typename T>
class QuickPushOrderedList
{
public:
    explicit QuickPushOrderedList(int (*cmpFunc)(const T lhs, const T rhs));
    ~QuickPushOrderedList();

    QuickPushOrderedList(const QuickPushOrderedList& other) = delete;
    QuickPushOrderedList& operator=(const QuickPushOrderedList& other) = delete;
    
    void Push(T data); // might throw bad_alloc
    T Pop();
    size_t Size();

protected:

private:
    struct node
    {
        T data;
        struct node *next;
    } *m_head;

    int (*m_cmpFunc)(const T lhs, const T rhs);
    size_t m_size;
    pthread_mutex_t m_lock;
};

template <typename T>
QuickPushOrderedList<T>::QuickPushOrderedList(int (*cmpFunc)(const T lhs, const T rhs)) : 
m_head(NULL), m_cmpFunc(cmpFunc), m_size(0), m_lock({0}) {}

template <typename T>
QuickPushOrderedList<T>::~QuickPushOrderedList()
{
    struct node *temp = NULL;

    while (m_head != NULL)
    {
        temp = m_head;
        m_head = m_head->next;
        delete temp;
    }
}

template <typename T>
void QuickPushOrderedList<T>::Push(T data)
{
    pthread_mutex_lock(&m_lock);

    struct node *new_node = new struct node;
    
    new_node->data = data;
    new_node->next = m_head;
    m_head = new_node;

    ++m_size;

    pthread_mutex_unlock(&m_lock);
}

template <typename T>
T QuickPushOrderedList<T>::Pop()
{
    pthread_mutex_lock(&m_lock);

    struct node *retNode = m_head;
    struct node *temp = m_head->next;
    T ret;

    while (temp != NULL)
    {
        if (m_cmpFunc(retNode->data, temp->data) > 0)
        {
            retNode = temp;
        }

        temp = temp->next;
    }

    ret = retNode->data;
    temp = retNode->next;

    if (temp)
    {
        retNode->data = temp->data;
        retNode->next = temp->next;

        if (temp == m_head)
        {
            m_head = temp->next;
        }

        delete temp; temp = NULL;
    }

    else
    {
        temp = m_head;
        while (temp && temp->next != retNode)
        {
            temp = temp->next;
        }

        if (temp)
        {
            if (retNode == m_head)
            {
                m_head = retNode->next;
            }

            delete retNode; retNode = NULL;
            temp->next = NULL;
        }
    }

    --m_size;

    pthread_mutex_unlock(&m_lock);
    
    return ret;
}

template <typename T>
size_t QuickPushOrderedList<T>::Size()
{
    return m_size;
}

int IntCompareFunc(const int a, const int b)
{
    return b - a;
}

int main()
{
    QuickPushOrderedList<int> list(IntCompareFunc);

    list.Push(5);
    list.Push(1);
    list.Push(3);
    list.Push(2);
    list.Push(8);
    list.Push(4);
    list.Push(6);
    list.Push(9);
    list.Push(7);

    while (list.Size())
    {
        std::cout << list.Pop() << "\n";
    }

    
    return 0;
}
