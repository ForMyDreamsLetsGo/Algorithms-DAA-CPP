//23/06/22
#include<iostream>
#include<iomanip> 
#include <chrono>
using  std::cout, std::cin,std::endl;
   

void swap(int*a,int*b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
int partition(int arr[],int low,int high){
    int pivot=arr[high], i=low-1;
    for(int j=low;j!=high;++j){
        if (arr[j]<=pivot){
            ++i;
            swap(&arr[j],&arr[i]);
        }
               
    }
    swap(&arr[i+1],&arr[high]);
    return(i+1);    
}
void printarray(int arr[], int array_size){
    for (int i=0; i<array_size;++i){
        cout<<'\t'<<arr[i];
    }
}

void quicksort(int arr[], int low, int high){
    if (low<high){
    int pi= partition(arr,low,high);
    quicksort(arr, low, pi-1);
    quicksort(arr,pi+1,high);
    }
    
}
int main(){
   
  
    // sorting the data of the file from file read program
    FILE *fp = fopen("numbers.txt","r");
    if (fp==NULL){
        cout<<"failed to open file";
    }
    else{
        cout<<"file opening success \n";
    }
    int arr[110000];
    for (int i=0;i<100000;++i){
        fscanf(fp,"%d",&arr[i]);
        
    }

    if(ferror(fp)){
        printf("\n error");
    }
    fclose(fp);
//    int arr[20]={234,2,2,42,52,543,23,523,21,1354};
 auto start = std::chrono::high_resolution_clock::now();
    //unsyncing the I/O of c and c++
    std::ios_base::sync_with_stdio(false);
    //code starts here

    quicksort(arr,0,99999);
     auto end= std::chrono::high_resolution_clock::now();
    double time_taken=std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    time_taken*=1e-9;
    cout<<"\ntime taken by quicksort is:"<<std::fixed<<time_taken<<std::setprecision(9)<<"sec"<<endl;
   
    //printarray(arr,99999);

   

}
