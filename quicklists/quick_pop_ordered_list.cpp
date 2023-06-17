#include <cstddef> // size_t
#include <iostream> // test
#include <pthread.h> // mutex 

template <typename T>
class QuickPopOrderedList
{
public:
    explicit QuickPopOrderedList(int (*cmpFunc)(const T lhs, const T rhs));
    ~QuickPopOrderedList();

    QuickPopOrderedList(const QuickPopOrderedList& other) = delete;
    QuickPopOrderedList& operator=(const QuickPopOrderedList& other) = delete;
    
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
QuickPopOrderedList<T>::QuickPopOrderedList(int (*cmpFunc)(const T lhs, const T rhs)) : 
m_head(NULL), m_cmpFunc(cmpFunc), m_size(0), m_lock({0}) {}

template <typename T>
QuickPopOrderedList<T>::~QuickPopOrderedList()
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
void QuickPopOrderedList<T>::Push(T data)
{
    pthread_mutex_lock(&m_lock);
    
    struct node *new_node = new struct node;
    struct node *iter = m_head;

    new_node->data = data;
    new_node->next = NULL;
    ++m_size;

    if (!iter)
    {
        m_head = new_node;
        pthread_mutex_unlock(&m_lock);
        return;
    }

    while ((m_cmpFunc(iter->data, data) < 0) && iter->next)
    {
        iter = iter->next;
    }

    if ((m_cmpFunc(iter->data, data) < 0) && !iter->next)
    {
        iter->next = new_node;
        pthread_mutex_unlock(&m_lock);
        return;
    }

    new_node->next = iter->next;
    iter->next = new_node;
    new_node->data = iter->data;
    iter->data = data;

    pthread_mutex_unlock(&m_lock);
}

template <typename T>
T QuickPopOrderedList<T>::Pop()
{
    pthread_mutex_lock(&m_lock);
    struct node *temp = m_head;
    T ret = m_head->data;

    --m_size;
    
    m_head = m_head->next;
    delete temp;

    pthread_mutex_unlock(&m_lock);
    
    return ret;
}

template <typename T>
size_t QuickPopOrderedList<T>::Size()
{
    return m_size;
}

int IntCompareFunc(const int a, const int b)
{
    return b - a;
}


int main()
{
    QuickPopOrderedList<int> list(IntCompareFunc);
    int x = 0;

    list.Push(5);
    list.Push(1);
    list.Push(3);
    list.Push(2);
    list.Push(8);
    list.Push(4);
    list.Push(6);
    list.Push(9);

    while (list.Size())
    {
        std::cout << list.Pop() << "\n";
    }

    return 0;
}
