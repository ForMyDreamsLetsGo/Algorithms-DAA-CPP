#include <iostream>
#include<iomanip> //io manipulation . here used for setprecision function. 
#include <chrono>
using  std::cout, std::cin,std::endl;
int main(){
    auto start = std::chrono::high_resolution_clock::now();
    //unsyncing the I/O of c and c++
    std::ios_base::sync_with_stdio(false);
    //code starts here
    auto end= std::chrono::high_resolution_clock::now();
    double time_taken=std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    time_taken*=1e-9;
    cout<<"time taken by program is:"<<std::fixed<<time_taken<<std::setprecision(9)<<"sec"<<endl;
}