#include <iostream>
using std::cout,std::endl,std::cerr;
#include<unordered_map>
using std::unordered_map;
#include <string>
using std::string;
#include<sstream>
using std::stringstream;
#include<fstream>
using std::ifstream;
#include <vector>
using std::vector;
#include<queue>
using std::queue;
#include <utility>
using std::move;
#include <exception>
/*#include<iomanip> //io manipulation . here used for setprecision function. 
#include <chrono>*/


template <typename T>
using graph=unordered_map<T,vector<T>>;

template <typename T>
const vector<T> & topological_sort(const graph<T>& digraph, vector<T>&result){

    //initialising the indegrees
    unordered_map<T,unsigned int> indegrees;
    for(const auto & pair:digraph){
        indegrees[pair.first]=0;
    }
    for(const auto & pair:digraph){
        for(const auto& adj_vertices:pair.second){
            ++indegrees[adj_vertices];
        }
    }

    //queue to store all vertices with zero degrees.
    queue<T> zero_degrees;
    for (const auto & pair:indegrees){
        if (pair.second==0){
            zero_degrees.push(std::move(pair.first));
        }
    }

    while(!zero_degrees.empty()){
        const T& remove= zero_degrees.front();
        
         for(const auto& adj_vertex:(*digraph.find(remove)).second){
            --indegrees[adj_vertex];
            if(indegrees[adj_vertex]==0){
                zero_degrees.push(adj_vertex);
            }
        }
        result.push_back(std::move(remove));
        zero_degrees.pop();

    }
     // Check if there are remaining edges in the graph (indicating a cycle)
    for (auto it = indegrees.begin(); it != indegrees.end(); ++it) {
        if (it->second > 0) {
            throw std::runtime_error("Input graph contains cycles");
        }
    }
    return result;
}

template<typename T>
const graph<T>& create_graph(ifstream& input_file,graph<T>& digraph){ 
    string line;
    T vertex,neighbour;
    while (std::getline(input_file,line))
    {
        stringstream vertices(line);
       if(!( vertices>>vertex)){
        cerr<<"Error parsing line:"<<line<<'\n'; 
        //vertices.setstate(std::ios_base::iostate::_S_goodbit);
        };
        //cout<<"vertex added is"<<vertex<<'\n';
        digraph.insert({vertex,vector<T>(0)});
        while(vertices>>neighbour){
            digraph[vertex].push_back(neighbour);
        }
        
    }
    return digraph;
    
}

int main(int argc, char**argv){
    if(argc!=2){
        cerr<<"Usage: "<<argv[0]<<"  name of input file";
        return -1;
    }
    ifstream input_file(argv[1]);
    if (!input_file){ 
        cerr<<"error opening this file";
        return -1;
    }
    graph<int> digraph;                //you can change data type here
    vector<int> result;
    create_graph(input_file,digraph);
    input_file.close();

    /*auto start = std::chrono::high_resolution_clock::now();
    //unsyncing the I/O of c and c++
    std::ios_base::sync_with_stdio(false);*/
    try
    {
        const auto & topological_sequence=topological_sort(digraph,result);       
     cout<<"the topologically sorted sequence is: ";
    for(const auto& vertices:topological_sequence){
        cout<<vertices<<" ";
    } 
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception:"<<e.what() <<endl;
    }
    
    

    /*auto end= std::chrono::high_resolution_clock::now();
    double time_taken=std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    time_taken*=1e-9;
    cout<<"time taken by program is:"<<std::fixed<<time_taken<<std::setprecision(9)<<"sec"<<endl;*/

   
   
   //printing the graph
  /* for (const auto & w:digraph){
        cout<<w.first<<'\t';
      for (const auto & i:w.second){
            cout<<i<<",";
        }
        cout<<endl;
    }*/
    
}