//Ejemplo clasico y muy simple
class Observer {
public:
   virtual void notify() = 0;
};

class Subject {
public:
   void addObserver( Observer* );
   void remObserver( Observer* );
private:
   void notifyAll();
};

void Subject::notifyAll() {
   for (all registered observers) { observer->notify(); }
}


// EJEMPLO 2




#include <iostream>
#include <list>
#include <thread>
#include <chrono>
 
class Observer; // Forward Decleration
 
class Subject 
{
 
    int _m_time;
    // List to observers, who will be notified when state change
    std::list<Observer*> _m_list;
public:
    Subject();
    ~Subject();
    void Attach(Observer*);
    void Detach(Observer*);
    void SetState(int);
    int GetState();
private:
    Subject(const Subject &other) = delete;  // Disallow copying
    void operator=(const Subject &) = delete;// Disallow copying
    void Notify();
};
 
class Observer
{
protected:
    Subject* _m_sub;
public:
 
    virtual void Update()=0;
};
     
//Constructor
Subject::Subject()
{ 
    _m_time = 0; 
}
//Destructor
Subject::~Subject() 
{ 
    _m_time = 0;
    if(!_m_list.empty())
    {
        _m_list.clear();
    }       
}
//Attach Function is used for registeration and observer will use this fucntion
void Subject::Attach(Observer* ob)
{
    _m_list.push_back(ob);
}
     
//Detach function is used for de-registeration
void Subject::Detach(Observer* ob)
{
    _m_list.remove(ob);
}
     
//Notify Function is notify to registered observer when state change
void Subject::Notify()
{
    std::list<Observer *>::iterator iterator = _m_list.begin();
    while (iterator != _m_list.end()) 
    {
        (*iterator)->Update();
        ++iterator;
    }
}
 
//Set state
void Subject::SetState(int t)
{
    _m_time = t;
    Notify();
}
 
int Subject::GetState()
{
    return _m_time;
}
 
 
class AnalogObserver : public Observer
{
public:
    AnalogObserver(Subject * sub)
    {
        _m_sub = sub;
        _m_sub->Attach(this);
    } 
    ~AnalogObserver() 
    {   
        _m_sub->Detach(this);
    }
    void Update()
    {
        PrintTime();
    }
    void PrintTime()
    { 
        std::cout<<"AnalogTimer got notification:"<<_m_sub->GetState()<<std::endl;
    }
};
 
class DigitalObserver : public Observer
{
public:
      DigitalObserver(Subject * sub)
    {
        _m_sub = sub; 
        _m_sub->Attach(this);
    }
        ~DigitalObserver() 
    {
        _m_sub->Detach(this);
    } 
        void Update()
        { 
        PrintTime();
    }
        void PrintTime()
        { 
        std::cout<<"DigitalTimer got notification:"<<_m_sub->GetState()<<std::endl;
    }
};
 
 
int main()
{
    std::cout<<"In Main"<<std::endl;   
    //Create the Subject
    Subject sub;
    //Create the Observers
    AnalogObserver analogObj(&sub);
    DigitalObserver digitalObj(&sub);
    //Change the Subject, Observer should be notified
    for(int i =1; i<5; i++)
    {
    sub.SetState(i);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    }   
    return 0;
}
