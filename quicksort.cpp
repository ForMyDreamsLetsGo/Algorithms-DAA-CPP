#include<iostream>
using std::cout,std::endl;
#include<vector>
using std::vector;
#include<algorithm>
#include<utility>
#include<fstream>
using std::ifstream,std::ofstream;
#include<iomanip>
#include <chrono>
#include <iterator>

template<typename comparable>
const comparable & median3(vector<comparable> & values, int left, int right){
    int center = (left+right)/2;
    if (values[right]<values[left]){
        std::swap(values[left],values[right]);
    }
    if(values[center]<values[left]){
        std::swap(values[center],values[left]);
    }
    if(values[right]<values[center]){
        std::swap(values[center],values[right]);
    }

    std::swap(values[center],values[right-1]);
    return(values[right-1]);
}

template<typename comparable>
void helper_isort(vector<comparable> & values, int left, int right){
    for(int p= left+1; p<=right;++p){
        comparable temp=std::move(values[p]);
        int j;
        for (j=p;j>left&& temp<values[j-1]; --j){
            values[j] = std::move(values[j-1]);
        }
        values[j]=std::move(temp);
    }
}

template<typename comparable>
void quicksort(vector<comparable> & values,int left, int right){
    if (left +10<= right){
        const comparable & pivot = median3(values,left,right);

        int i=left, j=right-1;
        for(;;){
            while(values[++i]<pivot){}
            while (pivot<values[--j]){}
            if(i<j){ std::swap(values[i],values[j]);}
            else{
                break;
            } 
            
        }
        std::swap(values[i],values[right-1]) ;
         /* don't think about using pivot here. first, it is cost . 
         second, it is better to swap directly when you know the location rather than 
         going through reference route. things might go awry and complicated*/

         quicksort(values, left, i-1);
         quicksort (values, i+1,right);
    }
    else{
        helper_isort (values,left,right);
    }
}

template<typename comparable>
vector<comparable>& createVec(comparable range, vector<comparable> & values){
    ifstream input ("numbers.txt");
    if (input){
    cout<<"input file open success!\n";
    std::istream_iterator<comparable> start(input);
    std::copy_n(start,range,std::back_inserter(values));
    input.close();
    }
    else{
        std::cerr<<"oops! something wrong with input file opening!";
    }
    return values;
}

template<typename comparable>
void quicksort(vector<comparable> & values){

    quicksort(values,0, values.size()-1);
}


int main(){
   vector<unsigned long> values; //change the data type here.
   cout<<"enter the number of values to take from the file";
   unsigned long num;
   std::cin>>num;
   values.reserve(num);
   createVec(num,values);
   
   
   auto start = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);
    
    quicksort(values);
   
   auto end= std::chrono::high_resolution_clock::now();
    double time_taken=std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    time_taken*=1e-9;
    cout<<"time taken by quicksort algorithm is:"<<std::fixed<<std::setprecision(9)<<time_taken<<"sec"<<endl;
    
   
   ofstream output("sorted.txt");
    if(output){
        cout<<"output file opened successfully!\n";
        for (const auto & i: values){
            output<<i<<'\n';
        }
        output.close();
    }
    else{
        cout<<"oops! something went wrong while opening output file!";
    }
}