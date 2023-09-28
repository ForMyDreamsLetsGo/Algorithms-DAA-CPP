#include <unordered_map>
using std::unordered_map;
#include<vector>
using std::vector;
#include<fstream>
using std::ifstream;
#include<sstream>
using std::stringstream;
#include<string>
using std::getline,std::string;
#include<iostream>
using std::cout,std::endl,std::cerr;
#include<queue>
using std::queue;
#include<unordered_set>
using std::unordered_set;
#include<stdexcept>

template<typename KeyType>
using graph=unordered_map<KeyType,vector<KeyType>>;

template<typename KeyType>
void BFS(const graph<KeyType> & digraph, const KeyType& source){
    queue<KeyType> to_process;
    unordered_set<KeyType> visited;
    to_process.push(source);
    visited.insert(source);
    cout<<"The nodes reachable from the source node are:-"<<endl;
    while (!to_process.empty())
    {   
        auto processed=to_process.front();
        cout<<processed<<" ";
        to_process.pop();
        try{
        for (const auto & neighbour: digraph.at(processed)){
            if(visited.find(neighbour)==visited.end()){
                to_process.push(neighbour);
                visited.insert(neighbour);
            }
        }
    }
    catch(std::out_of_range){
        cout<<endl;
        cout<<processed<<" was the terminating node"<<endl;
        cout<<"The unreachable nodes are:- "<<endl;
        for(const auto & element:digraph){
            if(visited.find(element.first)==visited.end()){
                cout<<element.first<<" ";
            }
        }
        break;
    }
  }  
}

int main(int argc, char**argv){
    if(argc!=2){
        cerr<<"Usage: "<<argv[0]<<"  name of input file";
        return -1;
    }
    ifstream input(argv[1]);
    if (!input){ 
        cerr<<"error opening this file";
        return -1;
    }

    //initialisations
    graph<char> digraph;
    char source;
    cout<<"enter the source node"<<endl;
    std::cin>>source;
    
    string line;
    while(getline(input,line)){
        digraph.insert({line[0],vector<char>(0)});
        stringstream tokens(line.substr(1));
        char keys;
        while(tokens>>keys){
            digraph[line[0]].push_back(keys);
        }

    }
    input.close();
   //driver
    BFS(digraph,source);
}