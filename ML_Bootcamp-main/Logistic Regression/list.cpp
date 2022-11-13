#include<bits/stdc++.h>
 
using namespace std;
 class linked_list
 {
    int val;
    linked_list *add;
 };
 int median(vector<int> arr)
 {
    int temp,n=arr.size();

    for(int i=0;i<n/2;i++)
    {
        temp=i;
        for (int j = i+1; j < n; j++)
        {
            if(arr[temp]>arr[j]) temp=j;
        }
        int dump=arr[i];
        arr[i]=arr[temp];
        arr[temp]=dump;
    }
    if( n%2 ==0)
    {
        return (arr[n/2]+arr[(n/2)-1])/2;
    }
    else 
        return arr[n/2];
 }
int main()
{
    vector<int> arr={4,2};
    cout<<median(arr);
    return 0;
}