#include<iostream>
using std::cout; using std::endl;
#include<chrono>
#include<iomanip>
#include<fstream>

using big = unsigned long int;
void swap(big*a,big*b){
    big temp=*a;
    *a=*b;
    *b=temp;
}

//pivoting
big median3(big arr[],const big &left , const big & right){
     big center=(left+right)/2;
     if (arr[right]<arr[left]){
         swap(&arr[left],&arr[right]);
    }
    if(arr[center]<arr[left]){
         swap(&arr[center],&arr[left]);
    }
    if(arr[right]<arr[center]){
         swap(&arr[center],&arr[right]);
    }

     swap(&arr[center],&arr[right-1]);
    return(arr[right-1]);
}

void helper_isort(big arr[], const big& left, const big& right){
    for(big p= left+1; p<=right;++p){
        big temp=arr[p];
        big j;
        for (j=p;j>left&& temp< arr[j-1]; --j){
             arr[j] =  arr[j-1];
        }
         arr[j]=temp;
    }
}

void quicksort (big arr[], const big &left, const big& right){
    if (left+10<=right){
       const big & pivot = median3 (arr, left, right);

       big i =left, j=right-1;
       for(;;){
        while(arr[++i]<pivot){}
        while(pivot<arr[--j]){}
        if(i<j){swap(&arr[i],&arr[j]);}
        else{break;}
       }
       swap(&arr[i],&arr[right-1]);
       quicksort(arr,left,i-1);
       quicksort(arr,i+1,right);

    }
    else{
        helper_isort(arr,left,right);
    }
}


int main(){
    std::ifstream input("numbers.txt");
    if (input){
        cout<<"file opening success \n";
    }
    else{
        cout<<"failed to open file\n";        
    }
        big arr[110000];
         for (big i=0;i<100000;++i){
         input>>arr[i];
        // cout<<arr[i]<<'\n';
    }
    input.close();
    
    auto start = std::chrono::high_resolution_clock::now();
    //unsyncing the I/O of c and c++
    std::ios_base::sync_with_stdio(false);
    //code starts here

    quicksort(arr,0,99999);
     auto end= std::chrono::high_resolution_clock::now();
    double time_taken=std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    time_taken*=1e-9;
    cout<<"\ntime taken by quicksort is:"<<std::fixed<<time_taken<<std::setprecision(9)<<"sec"<<endl;

    
    std::ofstream output("sortedp3.txt");
    if(output){
        cout<<"output file opened successfully!\n";
        for (big i=0; i<100000;++i)
        {
           // cout<<i<<'\t'<<arr[i]<<'\n';
            output<<arr[i]<<'\n';
        }
        output.close();
    }
    else{
        cout<<"oops! something went wrong while opening output file!";
    }
}
