// Write a function:

// int solution(int A, int B, int K);

// that, given three integers A, B and K, returns the number of integers within the range [A..B] that are divisible by K, i.e.:

// { i : A ≤ i ≤ B, i mod K = 0 }

// For example, for A = 6, B = 11 and K = 2, your function should return 3, because there are three numbers divisible by 2 within the range [6..11], namely 6, 8 and 10.

// Assume that:

// A and B are integers within the range [0..2,000,000,000];
// K is an integer within the range [1..2,000,000,000];
// A ≤ B.
// Complexity:

// expected worst-case time complexity is O(1);
// expected worst-case space complexity is O(1).
// Copyright 2009–2016 by Codility Limited. All Rights Reserved. Unauthorized copying, publication or disclosure prohibited.


// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(int A, int B, int K) {
    // write your code in C++11 (g++ 4.8.2)
    if(A>B)
    {
        return 0;
    }
    
    //计算AB中间的元素有多少个，即使AB相同也正确
    int between = B - A + 1 - 2;
    if(between == -1 && A%K==0)
    {
        return 1;
    }
    
    int cnt = between / K;
    if(A%K==0)
    {
        cnt++;
    }
    if(B%K==0)
    {
        cnt++;
    }
    
    int remain = between%K;
    if(A%K+remain>=K)
    {
        cnt++;
    }
    return cnt;
}