//*******************************************************************************************
//CS 211 - Lab 10
//Complete the program Lab10(Program).cpp and implement the routines that are not implemented
//*******************************************************************************************


/* Use the comments given in each routine to complete the following program */


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
  NodePtr prevStudent;
};

class LL
{
private:
  NodePtr top;
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
  NodePtr getTop() const;
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

//--------------------------------------------
//--------------------------------------------
// Read a transaction file and insert the data into it
// after reading a set of data you can call any of the
// insert functions to insert the node into the linked list
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
//--------------------------------------------
//--------------------------------------------
// creates a node and insert the node on the top of the
// linked list but after the first node. For example if the
// list constains 1 --> 20 -->13 --> 4 --> 5 --> 6
// after inserting 10, we should get:
// list constains 1 --> 10 --> 20 -->13 --> 4 --> 5 --> 6

void LL::insertAfterFirst (int id, string name, string email, int age)
{
  if(top==NULL)
    {
      insertBeforeFirst(id, name, email, age);
      return;
    }
  if(search(id))
    {
      cout<<"This id already exists."<<endl;
      return;
    }
  if(top->nextStudent==NULL)
    {
      insertAfterLast(id, name, email, age);
    }
  NodePtr newNode;
  NodePtr p=top, temp;
  newNode = new Node;
  newNode->stID=id;
  newNode->stName=name;
  newNode->stEmail=email;
  newNode->stAge=age;
  newNode->prevStudent=p;
  temp=p->nextStudent;
  p->nextStudent=newNode;
  newNode->nextStudent=temp;
}
void LL::insertBeforeFirst (int id, string name, string email, int age)
{
  if(search(id))
    {
     cout<<"This id already exists."<<endl;
     return;
    }
  NodePtr p= new Node;
  p->stID=id;
  p->stName=name;
  p->stEmail=email;
  p->stAge=age;
  if(top==NULL)
    {
     top=p;
     return;
    }
  p->nextStudent=top;
  top->prevStudent=p;
  top=p;
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
  newNode->prevStudent=p;
}
void LL::insertBeforeLast (int id, string name, string email, int age)
{
  NodePtr p=top;
  NodePtr q;
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

  while(p->nextStudent->nextStudent!=NULL)
    {
      p=p->nextStudent;
    }
  newNode->nextStudent=p->nextStudent;
  p->nextStudent=newNode;
  newNode->prevStudent=p;
}
//--------------------------------------------
//--------------------------------------------
// removes a node from the list based on the given student id
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
  //--------------------------------------------
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
  //--------------------------------------------
  // deallocate the nodes in a linked list
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

  //--------------------------------------------
  NodePtr LL::getTop() const
  {
    return top;
  }

  //-----------------------------------------
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
