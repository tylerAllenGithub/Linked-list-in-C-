//*******************************************************************************************
//CS 211 - Lab 9
//Complete the program Lab09(Program).cpp and implement the routines that are not implemented
//*******************************************************************************************



#include <iostream>
#include<string>
#include <fstream>
using namespace std;

class Node;
typedef Node* NodePtr;

class LL;
class Node
{
  friend class LL;
private:
  int stID;
  string stName;
  string stEmail;
  int stAge;
  NodePtr nextStudent;
};

class LL
{
private:
  NodePtr  top;
  void destroy (NodePtr&);

public:
  LL();
  LL(const LL& source);
  ~LL();
  void insertDataFromFile();
  void print ();
  bool search (int id);
  void insertAfterFirst (int id, string name, string email, int age);
  void insertBeforeFirst (int id, string name, string email, int age);
  void insertAfterLast (int id, string name, string email, int age);
  void insertBeforeLast (int id, string name, string email, int age);
  void remove (int id);
  void copy (NodePtr top1, NodePtr& top2);
};
//--------------------------------------------
//--------------------------------------------
// the default constructor
LL::LL()
{
  top=NULL;
}
//--------------------------------------------
//--------------------------------------------
// the copy constructor
LL::LL(const LL& source)
{
  top=NULL;
   copy(source.top, top);
}

//--------------------------------------------
//--------------------------------------------
// the destructor
LL::~LL()
{
  destroy(top);
}
void LL::insertDataFromFile()
{
   ifstream fin;
  fin.open("Transaction.txt");
  long id;
  string name;
  string email;
  int age;
  fin>>id;
  fin>>name;
  fin>>email;
  fin>>age;

  while(fin)
    {
      insertAfterLast(id,name, email,age);
      fin>>id;
      fin>>name;
      fin>>email;
      fin>>age;
    }
    fin.close();
}

// print the linked list
void LL::print()
{
  cout<<"Linked List: "<<endl;
  NodePtr p = top;
  while(p!=NULL)
    {
      cout<<"ID: "<<p->stID<<endl;
      cout<<"Name: "<<p->stName<<endl;
      cout<<"Email: "<<p->stEmail<<endl;
      cout<<"Age: "<<p->stAge<<endl;
      cout<<endl;
      p=p->nextStudent;
    }
}
//--------------------------------------------
//--------------------------------------------
// search for a particular student id in the list
bool LL::search (int id)
{
  NodePtr curr;
  bool found;
  curr = top;
  found = false;
  while ((curr != NULL) && (!found))
    if (curr -> stID == id)
      found = true;
    else
      curr = curr -> nextStudent;
  return (found);
}
void LL::insertAfterFirst (int id, string name, string email, int age)
{
  if(top==NULL)
    {
      insertBeforeFirst(id, name, email, age);
      return;
    }
  NodePtr newNode;
  NodePtr p=top, temp;
      newNode = new Node;
      newNode->stID=id;
      newNode->stName=name;
      newNode->stEmail=email;
      newNode->stAge=age;
      temp=p->nextStudent;
      p->nextStudent=newNode;
      newNode->nextStudent=temp;
}
void LL::insertBeforeFirst (int id, string name, string email, int age)
{
  NodePtr newNode;
  NodePtr p=top;
  newNode=new Node;
  newNode->stID=id;
  newNode->stName=name;
  newNode->stEmail=email;
  newNode->stAge=age;
  top=newNode;
  newNode->nextStudent=p;
}
void LL::insertAfterLast (int id, string name, string email, int age)
{
  if(top==NULL)
    {
      insertBeforeFirst(id, name, email, age);
      return;
    }
  NodePtr newNode, p;
  p=top;
  newNode= new Node;
  newNode->stID=id;
  newNode->stName=name;
  newNode->stEmail=email;
  newNode->stAge=age;

  while(p->nextStudent!=NULL)
    {
      p=p->nextStudent;
    }
  p->nextStudent=newNode;
  //newNode->nextStudent=NULL;
}
void LL::insertBeforeLast (int id, string name, string email, int age)
{
  NodePtr p=top;
  NodePtr prev;
  if(p==NULL||p->nextStudent==NULL)
    {
      insertBeforeFirst(id, name, email, age);
      return;
    }
  NodePtr newNode;
  newNode= new Node;
  newNode->stID=id;
  newNode->stName=name;
  newNode->stEmail=email;
  newNode->stAge=age;

  while(p->nextStudent!=NULL)
    {
         prev=p;
      p=p->nextStudent;
    }
  prev->nextStudent=newNode;
  newNode->nextStudent=p;
}
void LL::remove (int id)
{
  if (search(id)==false)
    {
      return;
    }
  if(top->nextStudent==NULL)
    {
      destroy(top);
      return;
    }
  NodePtr p=top;
  NodePtr q=top;

  while(p!=NULL)
    {
      if(p->stID==id)
        {
          q->nextStudent=p->nextStudent;
          delete(p);
        }
      else
        {
          q=p;
          p=p->nextStudent;
        }
    }

}
void LL::copy (NodePtr atop, NodePtr& btop)
{
  NodePtr aCurr, bCurr;
   destroy(btop);
  if(atop!=NULL)
    {
      btop=new Node;
      btop->stID=atop->stID;
      btop->stName=atop->stName;
      btop->stEmail=atop->stEmail;
      btop->stAge=atop->stAge;
      aCurr=atop;
      bCurr=btop;
      while(aCurr->nextStudent!=NULL)
        {
          bCurr->nextStudent=new Node;
          aCurr=aCurr->nextStudent;
          bCurr=bCurr->nextStudent;
          bCurr->stID=aCurr->stID;
          bCurr->stName=aCurr->stName;
          bCurr->stEmail=aCurr->stEmail;
          bCurr->stAge=aCurr->stAge;
        }
      bCurr->nextStudent=NULL;
    }
}
void LL::destroy(NodePtr& top)
{
  NodePtr p=top;
NodePtr temp;

  while(p!=NULL)
    {
      temp=p;
      p=temp->nextStudent;
      delete(temp);
}
  top=NULL;

}
int main ()
{
  LL list1;
  list1.insertDataFromFile();
  list1.print();
  list1.insertAfterFirst (54321, "Jim", "jim@csusm.edu", 25);
  list1.insertBeforeFirst (54123, "Joe", "joe@csusm.edu", 35);
  list1.insertAfterLast (63421, "Adam", "adam@csusm.edu", 20);
  list1.insertBeforeLast (66641, "Nancy", "nancy@csusm.edu", 27);
  list1.print();
  bool  found = list1.search (12321);
  if (found)
    cout << "the record was found" << endl;
  else
    cout << "the record was not found" << endl;
  list1.remove (54321);
  list1.print();

  LL list2(list1);
  list2.print();
  return 0;

}
