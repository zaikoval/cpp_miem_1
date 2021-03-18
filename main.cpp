#include "mainwindow.h"
#include <stdexcept>
#include <stack>

#include <QApplication>

template <typename T>
class queue
{
    std::stack<T> s1;
    std::stack<T> s2;
public:
    void push(T n)
    {
        s1.push(n);
    }
    void pop()
    {
        while(!s1.empty())
        {
            s2.push(s1.top());
            s1.pop();
        }
        s2.pop();
        while(!s2.empty())
        {
            s1.push(s2.top());
            s2.pop();
        }
    }
    void print()
    {
        while(!s1.empty())
        {
            s2.push(s1.top());
            s1.pop();
        }
        while(!s2.empty())
        {
            std::cout <<s2.top()<<' ';
            s1.push(s2.top());
            s2.pop();
        }
    }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

