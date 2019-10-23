#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

int *bubble_sort(int *arr,int n)
{
    int *ans=new int[n];
    for(int i=0;i<n;i++)
    {
        ans[i]=arr[i];

    }
    for(int i=0;i<n;i++)
    {
        bool flag=false;
        for(int j=0;j<n-i-1;j++)
        {
            if(ans[j]>ans[j+1])
            {
                swap(ans[j],ans[j+1]);
                flag=true;
            }
        }
        if(!flag)
        {
            break;
        }
    }
    return ans;
}
int *bubble_sort_parallel(int *arr,int n)
{
    bool flag=false;
    int *ans=new int[n];
    for(int i=0;i<n;i++)
    {
        ans[i]=arr[i];
    }
    for(int i=0;i<n;i++)
    {
        int first=i%2;
        flag=false;
        #pragma omp parallel for shared(ans,flag,first)
        for(int j=first;j<n-1;j+=2)
        {  
            if(ans[j]>ans[j+1])
            {
                swap(ans[j],ans[j+1]);
                flag=true;
            }
            
        }
        if(!flag)
        {
            break;
        }
    }
    return ans;
}
void merge(int *arr,int n,int *temp)
{
    int i=0,j=n/2,k=0;
    while(i<n/2 && j<n)
    {
        if(arr[i]<arr[j])
        {
            temp[k]=arr[i];
            i++;
            k++;
        }
        else
        {
            temp[k]=arr[j];
            j++;
            k++;
        }
        
    }
    while(i<n/2)
    {
        temp[k]=arr[i];
        i++;
        k++;

    }
    while(j<n)
    {
        temp[k]=arr[j];
        j++;
        k++;

    }
    memcpy(arr,temp,n*sizeof(int));
}

void merge_sort(int *arr,int n,int *temp)
{
    if(n<2)
        return;
    
    merge_sort(arr,n/2,temp);
    merge_sort(arr+n/2,n-(n/2),temp);

    merge(arr,n,temp);
}
void merge_sort_parallel(int *arr,int n,int *temp)
{
    if(n<2)
        return;
    #pragma omp task firstprivate(arr,n,temp)
    merge_sort_parallel(arr,n/2,temp);
    #pragma omp task firstprivate(arr,n,temp)
    merge_sort_parallel(arr+(n/2),n-(n/2),temp);

    #pragma omp taskwait
    merge(arr,n,temp);
}
void print_list(int *arr,int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<"\n";
}
int main()
{
    int *arr;
    int n=100;
    arr=new int[n];
    for(int i=0;i<n;i++)
    {
        arr[i]=rand()%10000;
    }

    cout<<"Before Sorting : \n";
    print_list(arr,n);


    
    double start_bs,stop_bs,start_bp,stop_bp;
    double start_ms,start_mp,stop_mp,stop_ms;

    start_bs=omp_get_wtime();    
    int *ans_b=bubble_sort(arr,n);
    stop_bs=omp_get_wtime();    

    cout<<"After Bubble Sorting(Serial) : \n";
    print_list(ans_b,n);
    
    int *ans_m=new int[n];
    start_ms=omp_get_wtime();
    merge_sort(arr,n,ans_m);
    stop_ms=omp_get_wtime();

    cout<<"After Merge Sorting(Serial) : \n";
    print_list(arr,n);

    start_bp=omp_get_wtime();
    int *ans=bubble_sort_parallel(arr,n);
    stop_bp=omp_get_wtime();

    cout<<"After Bubble Sorting(Parallel) : \n";
    print_list(ans,n);
    
    int *ans_p=new int[n];
    start_mp=omp_get_wtime();
    merge_sort_parallel(arr,n,ans_p);
    stop_mp=omp_get_wtime();
    cout<<"After Merge Sorting (Parallel): \n";
    print_list(arr,n);


    cout<<"\n********Timing********";
    cout<<"\nFor Bubble sort";
    cout<<"\nSerial : "<<stop_bs-start_bs<<"\tParallel : "<<stop_bp-start_bp;

    cout<<"\nFor Merge sort";
    cout<<"\nSerial : "<<stop_ms-start_ms<<"\tParallel : "<<stop_mp-start_mp;
    
    return 0;
}
