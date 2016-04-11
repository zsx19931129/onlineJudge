// A zero-indexed array A consisting of N integers is given. A triplet (P, Q, R) is triangular if 0 ≤ P < Q < R < N and:

// A[P] + A[Q] > A[R],
// A[Q] + A[R] > A[P],
// A[R] + A[P] > A[Q].
// For example, consider array A such that:

//   A[0] = 10    A[1] = 2    A[2] = 5
//   A[3] = 1     A[4] = 8    A[5] = 20
// Triplet (0, 2, 4) is triangular.

// Write a function:

// int solution(vector<int> &A);

// that, given a zero-indexed array A consisting of N integers, returns 1 if there exists a triangular triplet for this array and returns 0 otherwise.

// For example, given array A such that:

//   A[0] = 10    A[1] = 2    A[2] = 5
//   A[3] = 1     A[4] = 8    A[5] = 20
// the function should return 1, as explained above. Given array A such that:

//   A[0] = 10    A[1] = 50    A[2] = 5
//   A[3] = 1
// the function should return 0.

// Assume that:

// N is an integer within the range [0..100,000];
// each element of array A is an integer within the range [−2,147,483,648..2,147,483,647].
// Complexity:

// expected worst-case time complexity is O(N*log(N));
// expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).
// Elements of input arrays can be modified.

// Copyright 2009–2016 by Codility Limited. All Rights Reserved. Unauthorized copying, publication or disclosure prohibited.

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

//归并排序后寻找合法三角形

vector<int> B;

inline void myswap(vector<int> &A, int i, int j)
{
    int tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

void merge(vector<int> &A, int al, int ar, int bl, int br)
{
    for(int i=al;i<=ar;i++)
    {
        B[i] = A[i];
    }
    
    int pta=al, ptb=bl;
    int off=al;
    while(pta<=ar && ptb<=br)
    {
        if(B[pta]<=A[ptb])
        {
            A[off++] = B[pta];
            pta++;
        }else
        {
            A[off++] = A[ptb];
            ptb++;
        }
    }
    while(pta<=ar)
    {
        A[off++] = B[pta];
        pta++;
    }
    while(ptb<=br)
    {
        A[off++] = A[ptb];
        ptb++;
    }
}

void mergeSort(vector<int> &A, int begin, int end)
{
    if(begin == end)
    {
        return ;
    }
    if(begin == end-1)
    {
        if(A[begin] > A[end])
        {
            myswap(A, begin, end);
        }
        return ;
    }
    int mid = (begin+end)/2;
    mergeSort(A, begin, mid);
    mergeSort(A, mid+1, end);
    merge(A, begin, mid, mid+1, end);
}

int solution(vector<int> &A) {
    // write your code in C++11 (g++ 4.8.2)
    int asize = A.size();
    if(asize<3)
    {
        return 0;
    }
    B.resize(asize);
    mergeSort(A, 0, asize-1);
    
    cout<<A[0];
    for(int i=1;i<asize;i++)
    {
        cout<<" "<<A[i];
    }
    cout<<endl;
    
    for(int i=0;i<asize-2;i++)
    {
        if(A[i]<0)
        {
            continue;
        }
        if(A[i+2]-A[i+1]-A[i] < 0)
        {
            return 1;
        }
    }
    return 0;
    
}