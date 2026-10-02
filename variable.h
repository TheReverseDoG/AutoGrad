#pragma once
#include<vector>
#include<memory>

class node : public std::enable_shared_from_this<node>
{
    char op;
public:
    float data;
    float gradient;
    std::vector<std::shared_ptr<node>> last;
    
    node(float value, const char c) : op(c), data(value), gradient(0) {}
    void build_topo(std::vector<std::shared_ptr<node>>& topo, std::vector<node*>& visited);
    void backward();
};

class var
{
private:
    std::shared_ptr<node> n;
public:
    var(float x) : n(std::make_shared<node>(x, ' ')) {}
    var(std::shared_ptr<node> p) : n(p) {}

    float value()   {return n->data; }
    float grad()    {return n->gradient; }
    void link_to(var* adress);

    void parents();

    void backward();

    var copy();

    var& operator+=(var x)
    {
        n->data += x.n->data;
        return *this;
    }

    var& operator-=(var x)
    {
        n->data -= x.n->data;
        return *this;
    }

    var& operator*=(var x)
    {
        n->data *= x.n->data;
        return *this;
    }
    
};

var new_var(float value, const char c, var& a, var& b);

var operator+(var a, var b);
var operator*(var a, var b);
var operator-(var a, var b);

