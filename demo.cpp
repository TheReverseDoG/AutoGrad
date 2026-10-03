#include<iostream>
#include "variable.h"
using namespace std;

int main()
{
    var a(3.6);
    var b(4.4);
    var c(2);
    var d = power(a, 2) + power(b, c);
    //var d = a.copy();
    d.backward();
    cout << a.grad() << " " << b.grad() << " " << c.grad() << endl;
    //cout << d.grad();
}