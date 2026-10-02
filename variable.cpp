#include "variable.h"
#include <iostream>

using std::cout;

void var::parents()
{
    int i;
    for(i = 0; i < n->last.size(); i++)
    {
        cout << "Var" << i << " " << n->last[i]->data << "\n";
    }
}

void var::link_to(var* adress)
{
    n->last.push_back(adress->n);
}

var new_var(float value, const char c, var& a, var& b)
{
    var ret = var(std::make_shared<node>(value, c));
    ret.link_to(&a);
    ret.link_to(&b);
    return ret;
}

void node::build_topo(std::vector<std::shared_ptr<node>>& topo, std::vector<node*>& visited)
{
    int i;
    std::shared_ptr<node> self = shared_from_this();

    for(i = 0; i < visited.size(); i++)
        if(visited[i] == this)
            return;
    
    gradient = 0;

    visited.push_back(this);
    
    for(i = 0; i < last.size(); i++)
        last[i]->build_topo(topo, visited);
    
    topo.push_back(self);
}

void var::backward()
{
    //记录每一个节点需要被访问几次
    std::vector<std::shared_ptr<node>> topo;
    std::vector<node*> visited;
    n->build_topo(topo, visited);

    //赋予梯度
    n->gradient = 1.0;

    //对于每一个节点进行反向传播
    int i;
    for(i = topo.size() - 1; i >= 0; i--)
        topo[i]->backward();
}

void node::backward()
{
    if(op == ' ')
        return;
    else if(op == '+')
    {
        last[0]->gradient += gradient;
        last[1]->gradient += gradient;
    }
    else if(op == '*')
    {
        last[0]->gradient += gradient * last[1]->data;
        last[1]->gradient += gradient * last[0]->data;
    }
    else if(op == '-')
    {
        last[0]->gradient += gradient;
        last[1]->gradient -= gradient;
    }
}

var var::copy()
{
    var ret = *this;
    ret.n = std::make_shared<node>(n->data, '0');
    return ret;
}

var operator+(var a, var b)
{
    return new_var(a.value() + b.value(), '+', a, b);
}

var operator*(var a, var b)
{
    return new_var(a.value() * b.value(), '*', a, b);
}

var operator-(var a, var b)
{
    return new_var(a.value() - b.value(), '-', a, b);
}