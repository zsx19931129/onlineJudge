//
//  main.cpp
//  weeklyhiho
//
//  Created by shaoxiong on 10/2/16.
//  Copyright © 2016 shaoxiong. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <climits>
#include <cmath>

using namespace std;

#define MAXN 31
#define MAXLEVEL 146       //log2(20000)/log2(1)
#define MAXM 20001

int c[MAXN] = {0};
int w[MAXN] = {0};
int dp[MAXM] = {0};

int n,m;

int main() {
    cin>>n>>m;
    for(int i=0;i<n;++i){
        cin>>w[i]>>c[i];
    }
    for(int i=0;i<n;++i){
        for(int j=m;j>=0;--j){
            int curc = c[i];
            int totalc = curc;
            int curw = w[i];
            int totalw = curw;
            for(int k=1;k<=MAXLEVEL;++k){
                if(totalc > j){
                    break;
                }
                dp[j] = max(dp[j], dp[j-totalc] + totalw);
                curc = int(1.07*curc);
                totalc += curc;
                totalw += curw;
            }
        }
    }
    int res = 0;
    for(int i=0;i<=m;++i){
        if(res<dp[i]){
            res = dp[i];
        }
    }
    cout<<res<<endl;
    return 0;
}
