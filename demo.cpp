#include<iostream>
#include "variable.h"
using namespace std;

int main()
{
    var a(3.6);
    var b(4.4);
    var c = a * (b + a);
    var d = a.copy();
    c.backward();
    cout << a.grad() << " " << b.grad() << endl;
    cout << d.grad();
}