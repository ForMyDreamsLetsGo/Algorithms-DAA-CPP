#include <iostream>
using std::cout,std::cin,std::cerr,std::endl;
#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<fstream>
using std::ifstream;
#include<string>
using std::string,std::stod;
#include<sstream>
using std::stringstream;
#include<cmath>
using std::pow;
#include<iomanip>

template<typename NameType,typename WeightType,typename ValueType>
using item_vector= vector<pair<NameType,pair<WeightType,ValueType>>>;

item_vector<string,double,double> data;  // change the data type here

void InitialiseData(ifstream & input){
    string line,name,weight,value;
    while (std::getline(input,line))
    {   
        // it is better to initialise the varaibles inside cause if we encounter an empty string in the txt file
        //then the previous values (which are retained!) keep getting pushed to the vector.
        //also it is better to generally initialise variables where they are to be actually used.
        //BUT ALAS!! STOD STOPS WORKING WHEN VARIABLES DECLARED INSIDE
        stringstream tokens(line);
        tokens>>name>>weight>>value;
        data.push_back({name,{stod(weight),stod(value)}});
    }
}

vector<vector<double>> memo_table;
unsigned decimal_places=0;

void InitialiseMemoTable(const double & capacity){
    //counting number of columns
    double min_weight=data[0].second.first;
    for(const auto &i:data){
        if (i.second.first<min_weight){
            min_weight=i.second.first;
            }
    }

    decimal_places=0;
    while(min_weight<1){
        min_weight*=10;
        ++decimal_places;
    }    
    
    unsigned columns=(capacity*pow(10,decimal_places))+1;
    
    
    //initialsing memoization table
    memo_table= vector<vector<double>>(data.size()+1,vector<double>(columns,-1));
}



double knapsackRecursive(double remaining_capacity,  std::size_t ItemIndex){
    //base case
    if(ItemIndex==0 || remaining_capacity==0){ 
        memo_table[ItemIndex][remaining_capacity*pow(10,decimal_places)]=0;
        return 0;
     }
    //if the value is already computed
    if (memo_table[ItemIndex][remaining_capacity*pow(10,decimal_places)] != -1) {
        return memo_table[ItemIndex][remaining_capacity*pow(10,decimal_places)];
    }
    // If the weight of the current item is more than the remaining capacity,
    // skip the item and recursively call with the next item index
    if (data[ItemIndex].second.first > remaining_capacity) {
        memo_table[ItemIndex][remaining_capacity*pow(10,decimal_places)] = knapsackRecursive(remaining_capacity, ItemIndex-1);
        return memo_table[ItemIndex][remaining_capacity*pow(10,decimal_places)];
    }
    // Calculate the maximum value by either including or excluding the current item
    double includeItem = data[ItemIndex].second.second + knapsackRecursive(remaining_capacity-data[ItemIndex].second.first, ItemIndex - 1);
    double excludeItem = knapsackRecursive(remaining_capacity, ItemIndex-1);

    // Store the maximum value in the memoization table
    memo_table[ItemIndex][remaining_capacity*pow(10,decimal_places)] = std::max(includeItem, excludeItem);
    return memo_table[ItemIndex][remaining_capacity*pow(10,decimal_places)];

 }

 void Show_knapsack(double remaining_capacity, std::size_t ItemIndex){
    cout<<"The maximum value of items in knapsack is :"<<std::fixed<<std::setprecision(decimal_places)<<memo_table[data.size()][remaining_capacity*pow(10,decimal_places)]<< " rupees"<<endl;
    cout<<"The contents of the Knapsack are:- \n";
    double max_value=1;
    unsigned max_row=0;
    double remaining_value=1;
    std::size_t current_limit=memo_table.size();
    while(remaining_value>0){
    max_row=0;
    auto current_column=remaining_capacity*(pow(10,decimal_places));
    max_value= memo_table[max_row][current_column];
    for (std::size_t current_row=0; current_row<current_limit;++current_row){
        if (memo_table[current_row][current_column]>max_value){
            max_value=memo_table[current_row][current_column];
            max_row=current_row;
        }
    }
    remaining_value=max_value-data[max_row].second.second;
    current_limit=max_row;
    remaining_capacity -= data[max_row].second.first;
    cout<<data[max_row].first<<'\t'<<data[max_row].second.first<<"grams  "<<data[max_row].second.second<<"rupees\n"<<endl;
    }
    cout<<"The unused capacity of the knapsack is:"<<remaining_capacity<<endl;
}

 void knapsack(const double & capacity){
    InitialiseMemoTable(capacity);
    //calling the recursive function
    std::size_t ItemIndex=data.size();
    knapsackRecursive(capacity,ItemIndex);
    Show_knapsack(capacity,ItemIndex);
}

int main(int argc, char**argv){
    if(argc!=2){
        cerr<<"Usage: "<<argv[0]<<"  name of input file";
        return -1;
    }    
    double capacity;
    cout<<"Pleae Enter the capacity(positive!) of the kanapsack"<<endl;
    cin>>capacity;
    if (capacity<0){
        cerr<<"I told you to enter non- negative values!!";
        return -1;
    }
    else{

    ifstream input(argv[1]);
    if (!input){ 
        cerr<<"error opening this file";
        return -1;}
    InitialiseData(input);
    input.close();
    knapsack(capacity);
    //printing the vector
    // for(const auto & n:data){
    //     cout<<n.first<<'\t'<<n.second.first<<" "<<n.second.second<<endl;
    // }
    }
}