#include <bits/stdc++.h>
using namespace std;
class Parent
{
private:

public:
    virtual void sayHello(){
        cout << "Parent: Hello" << endl;
    }
    Parent(/* args */);
    ~Parent();
};

Parent::Parent(/* args */)
{
}

Parent::~Parent()
{
}

class Child:public Parent
{
private:
    /* data */
public:
    void sayHello(){
        cout << "Child: Hello" << endl;
    }
    Child(/* args */);
    ~Child();
};

Child::Child(/* args */)
{
}

Child::~Child()
{
}
void func(Parent *c){
    c->sayHello();
}
void func_no_poly(Parent c){
    c.sayHello();
}

int main() {
    Parent par;
    par.sayHello();
    Child *chi=new Child();
    chi->sayHello();
    Parent *p=new Child();
    p->sayHello();

    func(&par);
    func(chi);
    vector<Parent> vp;
    vp.push_back(*chi);
    vp[0].sayHello();

    vector<Parent*> vpp;
    vpp.push_back(chi);
    vpp[0]->sayHello();
    

    return 0;
}
