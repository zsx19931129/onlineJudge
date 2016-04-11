// Write a function

// int solution(vector<int> &A);

// that, given a zero-indexed array A consisting of N integers, returns the number of distinct values in array A.

// Assume that:

// N is an integer within the range [0..100,000];
// each element of array A is an integer within the range [−1,000,000..1,000,000].
// For example, given array A consisting of six elements such that:

// A[0] = 2    A[1] = 1    A[2] = 1
// A[3] = 2    A[4] = 3    A[5] = 1
// the function should return 3, because there are 3 distinct values appearing in array A, namely 1, 2 and 3.

// Complexity:

// expected worst-case time complexity is O(N*log(N));
// expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).
// Elements of input arrays can be modified.

// Copyright 2009–2016 by Codility Limited. All Rights Reserved. Unauthorized copying, publication or disclosure prohibited.


// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

//考察排序

#include <random>
#include <ctime>
using namespace std;

inline void myswap(vector<int> &A, int i, int j)
{
    int tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

void qsort(vector<int> &A, int begin, int end)
{
    if(begin>=end)
    {
        return ;
    }
    default_random_engine random(time(NULL));
    uniform_int_distribution<int> dis(begin, end);
    
    int pivot = dis(random);
    
    cout<<"pivot:"<<pivot<<endl;
    
    myswap(A, pivot, end);
    
    int bound = begin;
    for(int i=begin;i<end;i++)
    {
        if(A[i] <= A[end])
        {
            myswap(A, i, bound);
            bound++;
        }
    }
    
    myswap(A, bound, end);
    
    qsort(A, begin, bound-1);
    qsort(A, bound+1, end);
}

int solution(vector<int> &A) {
    // write your code in C++11 (g++ 4.8.2)
    int asize = A.size();
    if(asize == 0)
    {
        return 0;
    }
    
    qsort(A, 0, asize - 1);
    
    // cout<<A[0];
    // for(int i=1;i<asize;i++)
    // {
    //     cout<<" "<<A[i];
    // }
    // cout<<endl;
    
    int lastNumber = -1000005;
    int res = 0;
    for(int i=0;i<asize;i++)
    {
        if(A[i] != lastNumber)
        {
            res++;
            lastNumber = A[i];
        }
    }
    
    return res;   
}