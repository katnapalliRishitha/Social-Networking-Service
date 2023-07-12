#include <iostream>
using namespace std;
#include <utility>
#include <string>
#include <vector>
#include <unordered_map>
#define SIZE_OF_INPUT 5 

unordered_map<string,int> mapper;

typedef struct Person_tag{
  string name;
  pair<string,int> school;
  pair<string,int> college;
  string *hobbies;
}person;



class Graph{
public:
vector<vector<person>> adjList{SIZE_OF_INPUT};
void addEdge(person people1,person people2)
{
    adjList[mapper[people1.name]].push_back(people2);
}
void Take_input()
{
    person *people = new person[5];
    for(int i=0; i<5; i++){
      string name;
      pair<string,int> school;
      pair<string,int> college;
      string *hobbies;
      mapper[name] = i;
    }
    addEdge(people[0],people[1]);
    addEdge(people[0],people[2]);

    addEdge(people[1],people[0]);
    addEdge(people[1],people[2]);

    addEdge(people[2],people[0]);
    addEdge(people[2],people[1]);

    addEdge(people[3],people[4]);
    
    addEdge(people[4],people[3]);
}
//Addition of new user
//find  current and past mates on the network
};

int main()
{
   Graph linkedIn;
}