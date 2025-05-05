#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

void merge(int *arr,int low,int mid,int high)
{
    int size=high-low+1;
    int *temp=new int[size];
    int left=low;
    int right=mid+1;
    int index=0;

    while(left<=mid && right<=high)
    {
        if(arr[left] <= arr[right])
        {
            temp[index++]=arr[left++];
        }
        else
        {
            temp[index++]=arr[right++];
        }
    }
    while(left<=mid)
    {
        temp[index++]=arr[left++];   
    }
    while(right<=high)
    {
        temp[index++]=arr[right++];   
    }

    for(int i=0;i<size;i++)
    {
        arr[low+i]=temp[i];
    }
    delete []temp;
}

void seqmerge(int *arr,int low,int high)
{
    if(low < high)
    {
        int mid=low+(high-low)/2;
        seqmerge(arr,low,mid);
        seqmerge(arr,mid+1,high);
        merge(arr,low,mid,high);
    }
}

void pmerge(int *arr,int low,int high)
{
    if(low < high)
    {
        int mid=low+(high-low)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
            pmerge(arr,low,mid);
            #pragma omp section
            pmerge(arr,mid+1,high);
        }
        merge(arr,low,mid,high);
    }   
}

void printarr(int *arr,int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}
int main()
{
    int n;
    cout<<"Enter number of elements: "<<endl;
    cin>>n;

    int *arr=new int[n];

    for(int i=0;i<n;i++)
    {
        arr[i]=rand()%100;
    }

    int *orig=new int[n];

    for(int i=0;i<n;i++)
    {
        orig[i]=arr[i];
    }

    double start,end;

    start=omp_get_wtime();
    seqmerge(arr,0,n-1);
    end=omp_get_wtime();
    cout<<"Time for sequential: "<<end-start<<endl;
    printarr(arr,n);

    for(int i=0;i<n;i++)
    {
        arr[i]=orig[i];
    }

    start=omp_get_wtime();
    pmerge(arr,0,n-1);
    end=omp_get_wtime();
    cout<<"Time for parallel: "<<end-start<<endl;
    printarr(arr,n);

    delete[]arr;
    delete[] orig;
}