#include<iostream>
using std::cout,std::endl,std::cerr;
#include<string>
using std::string,std::getline;
#include<vector>
using std::vector;
#include<fstream>
#include<sstream>
#include<unordered_map>
using std::unordered_map;
#include<unordered_set>
using std::unordered_set;
#include<stack>
using std::stack;

template <typename VertexType>
using graph=unordered_map<VertexType,vector<VertexType>>;

template <typename VertexType>
vector<VertexType> isConnected(const graph<VertexType>& G){
    stack<VertexType> to_process;
    to_process.push(G.cbegin()->first);
    unordered_set<VertexType> visited;
    visited.insert(G.cbegin()->first);

    while(!to_process.empty()){
    VertexType current_vertex=to_process.top();
    to_process.pop();

    for(const auto & neighbour: G.at(current_vertex)){
        if(visited.find(neighbour)==visited.end()){
            to_process.push(neighbour);
            visited.insert(neighbour);
        }
    }
    }
    vector<VertexType>unVisited;
    if(visited.size()==G.size()){ return unVisited;}
    else{
        for(const auto & pair :G){
            if(visited.find(pair.first)==visited.end()){
                unVisited.push_back(pair.first);
            }
        }
        return unVisited;
    }
}

int main(int argc, char**argv){
    if(argc!=2){
        cerr<<"Usage: "<<argv[0]<<"  name of input file";
        return -1;
    }
    std::ifstream input(argv[1]);
    if (!input){ 
        cerr<<"error opening this file";
        return -1;
    }

    //initialisations
    graph<char> G;

    string line;
    while(getline(input,line)){
        G.insert({line[0],vector<char>(0)});
        std::stringstream tokens(line.substr(1));
        char keys;
        while(tokens>>keys){
            G[line[0]].push_back(keys);
        }

    }
    input.close();

    auto result=isConnected(G);
    if (result.empty()){
        cout<<"Congratulations! Given graph is connected!"<<endl;
    }
    else{
        cout<<"Sadly the given graph is not connected!"<<endl;
        cout<<"The unreachable vertices from '"<<G.begin()->first<<"' are:-"<<endl;
        for(const auto & vertex:result){
            cout<<vertex<<" ";
        }
    }

    // //printing the graph
    // for(const auto & i: G){
    //     cout<<i.first<<'\t';
    //     for(const auto& j:i.second){
    //         cout<<j<<" ";
    //     }
    //     cout<<endl;
    // }
}
