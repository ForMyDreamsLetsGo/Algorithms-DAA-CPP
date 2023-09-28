#include<iostream>
using std::cout,std::endl,std::cerr;
#include<vector>
using std::vector;
#include<string>
using std::string,std::getline;
#include <unordered_map>
using std::unordered_map,std::make_pair;
#include<fstream>
using std::ifstream;
#include<sstream>
using std::stringstream;
#include<iomanip>
using std::setw;


vector<vector<bool>> & transitive_closure(vector<vector<bool>> & graph){
    for(unsigned k=0;k<graph.size();++k){
        for(unsigned row=0;row<graph.size();++row){
            for(unsigned col=0;col<graph.size();++col){
                graph[row][col]=graph[row][col] || (graph[row][k] && graph[k][col]); 
            }
        }
    }
    return graph;
}

template <typename NodeType>
vector<vector<bool>> CreateGraph(ifstream & input,unordered_map<unsigned,NodeType>& NumIndices,unordered_map<NodeType,unsigned> &KeyIndices ){
    unordered_map<NodeType,vector<NodeType>> map;  
    unsigned ctr=0;
     string line; 
    while (getline(input,line))
    {
        stringstream tokens(line);
        //taking input as adjacency list
        //filling maps containing conversions from given type to unsigned and vice-versa
        NodeType Key;
        tokens>>Key;
        if(KeyIndices.emplace(make_pair(Key,ctr)).second==true){
        NumIndices.emplace(make_pair(ctr,Key));
        ++ctr;}
        map.emplace(make_pair( Key,vector<NodeType>(0)));
        NodeType value;
        while(tokens>>value){
        if(KeyIndices.emplace(make_pair(value,ctr)).second==true){
        NumIndices.emplace(make_pair(ctr,value)).second==true;
        ++ctr;};
        map[Key].emplace_back(value);

        }
    }
    // creating adjacency matrix
    vector<vector<bool>> graph(map.size(),vector<bool>(map.size(),false));
    for(const auto &row:map){
        for (const auto & col:row.second){
            graph[KeyIndices.at(row.first)][KeyIndices.at(col)]=true;
        }
    }
    return graph;
}

int main(int argc, char**argv){
    if(argc!=2){
        cerr<<"Usage: "<<argv[0]<<"  name of input file";
        return EXIT_FAILURE;
    }
    ifstream input(argv[1]);
    if (!input){ 
        cerr<<"error opening this file";
        return EXIT_FAILURE;
    }
    unordered_map<unsigned,string> NumIndices;
    unordered_map<string,unsigned> KeyIndices;
    
   auto graph=CreateGraph(input,NumIndices,KeyIndices);
    input.close();

    transitive_closure(graph);

    // for(auto i: KeyIndices){
    //     cout<<i.first<<" "<<i.second<<endl;
    // }
    // cout<<endl;
    // for(auto i: NumIndices){
    //     cout<<i.first<<" "<<i.second<<endl;
    // }
    //  cout<<endl;
     cout<<setw(12)<<" ";
    for(auto i=0;i<graph.size();++i){
        cout<<setw(10)<<NumIndices[i];}
        cout<<endl;
        for(auto i=0;i<graph.size();++i){
            cout<<setw(12)<<NumIndices[i];
        for(auto j=0;j<graph.size();++j){
            cout<<setw(10)<<graph[i][j];
        }
        cout<<endl;
    }
}