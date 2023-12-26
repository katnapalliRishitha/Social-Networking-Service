#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <string>
#include <vector>
#include <iterator>
#include <unordered_map>
#include <list>
#define SIZE_OF_INPUT 14
using namespace std;
unordered_map<string,int> mapper;

typedef struct Person_tag
{
  string name;
  pair<string, int> school;
  pair<string, int> college;
  vector<string> hobbies;
} person;

int numbering = 0;

class Graph
{
public:
  vector<pair<person,list<person> > > adjList;
  Graph()
  {
    for(int i=0; i<SIZE_OF_INPUT; i++)
    {
      pair<person,list<person> > p;
      adjList.push_back(p);
    }
  }
  void addEdge(person people1, person people2)
  {
    adjList[mapper[people1.name]].first = people1;
    adjList[mapper[people1.name]].second.push_front(people2);
  }
  void Take_input()
  {
    person *people = new person[SIZE_OF_INPUT];
    for (int i = 0; i < SIZE_OF_INPUT; i++)
    {
      //Take input statements from file
      string name;
      pair<string, int> school;
      pair<string, int> college;
      vector<string> hobbies;
      mapper[name] = numbering++;
    }
    addEdge(people[0], people[1]);
    addEdge(people[0], people[2]);

    addEdge(people[1], people[0]);
    addEdge(people[1], people[2]);

    addEdge(people[2], people[0]);
    addEdge(people[2], people[1]);

    addEdge(people[3], people[4]);

    addEdge(people[4], people[3]);
  }
  void print_details(person *p){
    cout<<"Name : "<<p->name<<endl;
    cout<<"School Name  : "<<p->school.first<<endl;
    cout<<"School passout Year  : "<<p->school.second<<endl;
    cout<<"College  Name  : "<<p->college.first<<endl;
    cout<<"College Graduating year  : "<<p->college.second<<endl;
    cout<<"Hobbies : "<<endl;
    for(int i=0; i < p->hobbies.size();i++)
    {
      cout<<p->hobbies[i]<<" ";
    }
    cout<<endl<<endl;
  }
  //1.Addition of new user
  //find  current and past mates on the network
  void dfs(vector<bool> &visited,int sv,person* newUser)
  {
    visited[sv] = true;
    list<person>:: iterator it;
    for(it = adjList[sv].second.begin() ; it != adjList[sv].second.end(); it++)
    {
      if(!visited[mapper[it->name]])
      {
        dfs(visited,mapper[it->name],newUser);
      }
    }
    bool Equal = false;
    if(adjList[sv].first.school == newUser->school || adjList[sv].first.college == newUser->college)
    {
      Equal = true;
    }
    for(int i=0; i<adjList[sv].first.hobbies.size() && !Equal; i++)
    {
      for(int j=0; j<newUser->hobbies.size() && !Equal; j++)
      {
        if(newUser->hobbies[j] == adjList[sv].first.hobbies[i])
        {
          Equal = true;
        }
      }
    }
    if(Equal)
    {
      addEdge(*newUser,adjList[sv].first);
      addEdge(adjList[sv].first,*newUser);
    }
  }
  int isEmpty()
  {
    int ret_val = -1;
    for(int i=0; i<numbering && ret_val == -1; i++)
    {
      if(adjList[i].first.name == "")
      {
        ret_val = i;
      }
    }
    return ret_val;
  }
  void AddUserToNetwork()
  {
    person *newPerson = new person();
    cin >> newPerson->name;
    cin >> newPerson->school.first;
    cin >> newPerson->school.second;
    cin >> newPerson->college.first;
    cin >> newPerson->college.second;
    string hobby;
    cin >> hobby;
    while(hobby != "")
    {
      newPerson->hobbies.push_back(hobby);
      cin >> hobby;
    }
    int index = isEmpty();
    if(index != -1)
    {
      mapper[newPerson->name] = index;
    }
    else
    {
      mapper[newPerson->name] = numbering++;
      pair<person,list<person> > p;
      adjList.push_back(p);
    }
    vector<bool> visited(numbering,false);   
    for(int i=0; i<numbering; i++)
    {
      if(!visited[i])
      {
        dfs(visited,i,newPerson);
      }
    }
  }

  //2.Find current and past school mates on the network.
  void find_mates()
  {
    string name;
    cin>>name;
    vector<bool> visited(numbering,false);
    visited[mapper[name]] = true;
    list<person>:: iterator it;
    for(int index = 0; index < numbering; index++)
    {
      for(it=adjList[index].second.begin();it!= adjList[index].second.end();it++)
      {
        if(!visited[mapper[it->name]] && ((adjList[index].first.college.first==it->college.first && adjList[index].first.college.second==it->college.second) || (adjList[index].first.school.first==it->school.first && adjList[index].first.school.second==it->school.second)))
        {
          person p = *it;
          print_details(&p);
        }
        visited[mapper[it->name]]=true;
      }
    }  
  }

  //!!! Get connected to your friend !!!
  void connectHelper(int sv,int currvetex,vector<bool> &visited)
  {
    visited[currvetex] = true;
    list<person>::iterator it;
    for(it=adjList[currvetex].second.begin(); it != adjList[currvetex].second.end(); it++)
    {
      if(!visited[mapper[it->name]])
      {
        connectHelper(sv,mapper[it->name],visited);
      }
    }
    bool areConnected = false;
    if((adjList[sv].first.college.first == adjList[currvetex].first.college.first) || (adjList[sv].first.school.first == adjList[currvetex].first.school.first))
    {
      areConnected = true;
    }
    for(int i=0; i<adjList[sv].first.hobbies.size() && !areConnected; i++)
    {
      for(int j=0; j<adjList[currvetex].first.hobbies.size() && !areConnected; j++)
      {
        if(adjList[sv].first.hobbies[i] == adjList[currvetex].first.hobbies[j])
        {
          areConnected = true;
        }
      }
    }
    if(areConnected)
    {
      addEdge(adjList[sv].first,adjList[currvetex].first);
      addEdge(adjList[currvetex].first,adjList[sv].first);
    }
  }
  
  void connectWithAFriend()
  {
    string name;
    cout<<"Enter name of the person you want to suggest friends : "<<endl;
    cin>>name;
    int indexOfPerson = -1;
    if(mapper.count(name) > 0)
    {
      indexOfPerson = mapper[name];
      vector<bool> visited(numbering,false);
      list<person>::iterator it;
      visited[indexOfPerson] = true;
      for(it = adjList[indexOfPerson].second.begin(); it != adjList[indexOfPerson].second.end(); it++)
      {
        visited[mapper[it->name]] = true;
      }
      for(int j=0; j<numbering; j++)
      {
        if(!visited[j])
        {
          connectHelper(indexOfPerson,j,visited);
        }
      }
    }
    else
    {
      cout<<"OOPS User Id not found on the network"<<endl;
    }
  }

  //4. Minimum Degree Of Separation
  void BFS(string name1,string name2)
  { 
    int v1=mapper[name1]; 
    int v2=mapper[name2]; 
    unordered_map<int,int> m; 
    int sv=v1; 
    bool found=false; 
    queue<int> bfs; 
    bfs.push(sv); 
    m[sv]=-1; 
    vector<bool> visited(numbering,false);
    visited[sv] = true;
    while(!bfs.empty() && !found)
    { 
      list<person>:: iterator it;
      for(it=adjList[sv].second.begin();it!=adjList[sv].second.end();it++)
      { 
        if(!visited[mapper[it->name]])
        { 
          if(mapper[it->name]==v2)
          {
            found=true;
          }
          visited[mapper[it->name]] = true;
          m[mapper[it->name]]=sv;
          bfs.push(mapper[it->name]);
        }
      }
      bfs.pop(); 
      sv=bfs.front();  
    }
    if(found)
    {
      int count = -2;
      for(int i=v2;i!=-1;i=m[i])
      {
        cout<<adjList[i].first.name<<" "<<endl;
        count++;
      }
      cout<<name1<<" and "<<name2<<" are separated by a degree of "<<count<<" persons."<<endl;
    } 
    else
    {
      cout<<name1<<" and "<<name2<<" are not connected"<<endl; 
    } 
  }
  void min_degree_of_separation()
  {
    string name1,name2; 
    cout<<"Enter the name of person1 and person2 : "; 
    cin>>name1>>name2; 
    if(mapper.count(name1) > 0 && mapper.count(name2))
    {
      BFS(name1,name2);
    } 
    else
    {
      cout<<"!!! Users not found on the network !!!"<<endl;
    }
  }

  //5.Print Contact List and Network
  void print_network_dfs(int sv,vector<bool> &visited,unordered_map<int,bool> &m)
  {
    visited[sv]=true;
    list<person>:: iterator it;
    for(it=adjList[sv].second.begin(); it!=adjList[sv].second.end(); it++)
    {
      if(!visited[mapper[it->name]] && !m.count(mapper[it->name]))
      {
        person p = *it;
        print_details(&p);
        print_network_dfs(mapper[it->name],visited,m);
      }
    }
  }
  
  void contact_list_and_network()
  {
    string name;
    cout<<"Enter the name of person to show the contact list: ";
    cin>>name;
    int index=mapper[name];
    vector<bool> visited(numbering,false); 
    unordered_map<int,bool> m;
    list<person>:: iterator it;
    cout<<"The contact-list of "<<name<<"is"<<endl;
    for(it=adjList[index].second.begin(); it!=adjList[index].second.end(); it++)
    { 
      person p = *it;
      print_details(&p);
      m[mapper[it->name]]=true;
    }
    cout<<"The complete Network for"<<name<<"is"<<endl;
    print_network_dfs(index,visited,m);
  } 

  //6
  int maxDegreeUsingDFS(int sv,vector<bool>& visited)
  {
    visited[sv] = true;
    int maxDegree = 0;
    list<person>::iterator it;
    for(it=adjList[sv].second.begin(); it != adjList[sv].second.end(); it++)
    {
      if(!visited[mapper[it->name]])
      {
        int degree = maxDegreeUsingDFS(mapper[it->name],visited);
        if(degree > maxDegree)
        {
          maxDegree = degree;
        }
      }
    }
    return maxDegree+1;
  }
  void maxDegreeOfSeparationOnTheNetwork()
  {
    vector<bool> visited(numbering,false);
    int maxDegree = 0;
    for(int index = 0; index < numbering; index++)
    {
      if(!visited[index])
      {
        int degree = maxDegreeUsingDFS(index,visited);
        if(maxDegree < degree)
        {
          maxDegree = degree;
        }
      }
    }
    cout<<"Maximum degree of separation between any two people on the network is "<<maxDegree<<endl;
  }

  //7.Listing Of potential groups based on similar hobbies;
  void ListHobbies()
  {
    unordered_map<string,vector<int> > groups;
    for(int index = 0; index < numbering; index++)
    {
      vector<string> hobbies = adjList[index].first.hobbies;
      for(int j = 0; j < hobbies.size(); j++)
      {
        groups[hobbies[j]].push_back(mapper[adjList[index].first.name]);
      }
    }
    unordered_map<string,vector<int> >::iterator it;
    for(it = groups.begin(); it!= groups.end(); it++)
    {
      cout<<it->first<<endl;
      for(int j=0; j<it->second.size(); j++)
      {
        cout<<adjList[it->second[j]].first.name<<endl;
      }
      cout<<endl;
    }
  }
  //8.Listing of recent connections for everyone.
  void ListRecentConnections()
  {
    for(int index = 0; index < numbering; index++)
    {
      if(adjList[index].second.size() != 0)
      {
        cout<<adjList[index].first.name<<" has a recent connection "<<endl;
        print_details(&adjList[index].second.front());
      }
      else
      {
        cout<<adjList[index].first.name<<" has no connections"<<endl;
      }
    }
  }

  //9.Delete UserId
  void delete_id()
  { 
   string name; 
   cout<<"Enter person name to delete: ";
   cin>>name; 
   if(mapper.count(name)>0)
   { 
      int index = mapper[name]; 
      list<person>::iterator it; 
      for (it = adjList[index].second.begin(); it != adjList[index].second.end(); it++) 
      { 
          int neighbour_index = mapper[it->name]; 
          list<person>& neighbour = adjList[neighbour_index].second;
          auto pt = find(neighbour.begin(),neighbour.end(),adjList[index].first);
          neighbour.erase(pt);
      }
      adjList[index].second.clear();
      adjList[index].first.name = "";
      adjList[index].first.college.first = "";
      adjList[index].first.college.second = 0;
      adjList[index].first.school.first = "";
      adjList[index].first.school.second = 0;
      adjList[index].first.hobbies.clear();
  }
 }
};

int main()
{
  Graph linkedIn;
}
