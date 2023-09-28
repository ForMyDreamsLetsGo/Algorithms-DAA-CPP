#include <iostream>
using std::cout,std::endl,std::cerr;
#include<unordered_map>
using std::unordered_map;
#include <string>
using std::string,std::getline;
#include<sstream>
using std::stringstream;
#include<fstream>
using std::ifstream;
#include <vector>
using std::vector;
#include<utility>
using std::pair, std::move;
#include<limits>
#include<queue>

template <typename T>
using graph= unordered_map<T,vector<pair<T,unsigned int>>>;

template<typename T>
struct vertex
{   vertex()=default;
    vertex(T n, unsigned int dist=std::numeric_limits<unsigned int>::max(),T p=T() , bool r=false):
            name(n),distance(dist),parent(p),removed(r){}
    T name;
    unsigned int distance=std::numeric_limits<unsigned int>::max();
    T parent= T();
    bool removed=false;
};


template <typename T>
unordered_map<T,vertex<T>> &dijkstra(const T & source,const graph<T> & G , unordered_map<T,vertex<T>>& vertices){
    //Initialisation
    
    for(const auto& element:G){
        vertices[element.first]=vertex<T>(element.first);  
    }

    //setting the distance of source vertex to zero
    vertices[source].distance=0;

    //creating the priority queue
    std::priority_queue<pair<unsigned int, T>,vector<pair<unsigned int,T>>,std::greater<pair<unsigned int,T>>> min_heap;
    min_heap.push({0,(source)});

    //updating the distances
//    auto it= vertices.begin();

    while(!min_heap.empty()){

        T current_min=min_heap.top().second;
        min_heap.pop();
        vertices[current_min].removed=true;  

        // cout<<it->first<<'\t'<<it->second.name<<" "<<it->second.parent<<" "<<it->second.distance<<"\n";
        // ++it;

        for (const auto & element: (*G.find(current_min)).second){
            const auto & adj_vertex=element.first;
            if (vertices[adj_vertex].removed==true){ continue;}
            else {
                auto & old_dist=vertices[adj_vertex].distance;
                unsigned int new_dist=vertices[current_min].distance+element.second;
                if(new_dist < old_dist){
                    old_dist=new_dist;
                    vertices[adj_vertex].parent=current_min;
                    min_heap.push({new_dist,adj_vertex});
            }
            }

        }
    }
    return vertices;
}

template<typename T>
const graph<T>& create_graph(ifstream & input_file, graph<T>&G){
    string line;
    while(getline(input_file,line)){
        G.insert({line[0],vector<pair<T,unsigned int>>(0)});
        stringstream adj_vertices(line.substr(3));
        string adj_line;
        T name;
        unsigned int weight;
        while(getline(adj_vertices,adj_line,'}')){
            name=adj_line[2];
            stringstream distance(adj_line.substr(4));
            distance>>weight;
            G[line[0]].push_back({name,weight});
        }        
    }
    return G;
    
}

int main(int argc, char **argv){
    if(argc!=2){
        cerr<<"Usage: "<<argv[0]<<"  name of input file";
        return -1;
    }    
    ifstream input_file(argv[1]);
    if (!input_file){ 
        cerr<<"error opening this file";
        return -1;
    }
    graph<char> G;
    create_graph(input_file,G);
    input_file.close();
    //printing the graph
   /* for (const auto & i: G){
        cout<<i.first<<'\t';
        for(const auto & j:i.second){
            cout <<j.first<<','<<j.second<<" ";
        }
        cout<<"\n";
    }*/
    unordered_map<char,vertex<char>> vertices;
    dijkstra('a',G,vertices);
    cout<<"node\t"<<"parent\t"<<"distance from source"<<endl;
    for(auto i= vertices.begin();i!=vertices.end();++i){
        cout<<i->first<<'\t'<<i->second.parent<<'\t'<<i->second.distance<<'\n';
    }  

}
