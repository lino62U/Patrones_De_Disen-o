#include <iostream>
#include <string.h>
 
using namespace std;
class Expression
{
    public:
        char name[20];
 
        Expression (char* n)
        {
            strcpy (name, n);
        }
 
        virtual bool interpret (char *exp)
        {
            return (!strcmp (name, exp));
        }
 
};
 
class Employee: public Expression
{
    public:
        Employee (char *name): Expression (name)
        {
        }
};
 
class Manager: public Expression
{
    public:
        Expression* exp1;
        Manager (char *mgr): Expression (mgr)
        {
        }
 
        void addEmployee (char *emp)
        {
            exp1 = new Employee (emp);
        }
 
        bool interpret (char *exp)
        {
            return (!strcmp (exp, exp1->name));
        }
};
 
class Interpreter
{
    public:
        virtual bool interpret (Expression *exp1, Expression  *exp2) = 0;
};
 
class isEmployee: public Interpreter
{
    public:
        bool interpret (Expression *exp1, Expression  *exp2) 
        {
            return (exp1 -> interpret (exp2 -> name));
        }
};
 
class isManager: public Interpreter
{
    public:
        bool interpret (Expression *exp1, Expression  *exp2) 
        {
            return (exp2 -> interpret (exp1 -> name));
        }
};
 
int main ()
{
    Employee e1 ("Ram");
    Employee e2 ("Mohan");
    Manager m ("John");
    m.addEmployee ("Ram");
 
    isEmployee isEmp;
    isManager isMgr;
 
    cout << "Ram is Employee of John: " << (isEmp.interpret (&m, &e1) ? "True" : "False") << endl;
    cout << "Mohan is Employee of John: " << (isEmp.interpret (&m, &e2) ? "True" : "False") << endl;
    cout << "John is manager of Ram: " << (isMgr.interpret (&e1, &m) ? "True" : "False") << endl;
    cout << "John is manager of Mohan: " << (isMgr.interpret (&e2, &m) ? "True" : "False") << endl;
}
