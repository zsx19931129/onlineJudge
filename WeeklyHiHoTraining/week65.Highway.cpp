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
#include <cstring>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <map>
#include <unordered_map>

using namespace std;

#define MAXN 1001

int x[MAXN], y[MAXN], v[MAXN];
int p[MAXN], r[MAXN];
float ans[MAXN], t[MAXN];       //ans按顺序存储离开时间,t存储最晚离开时间，索引与p数组对应

bool comp(const int a, const int b){
    return x[a] > x[b];
}

int main() {
    int n;
    cin>>n;
    int a,b,c;
    for(int i=0;i<n;i++){
        cin>>x[i]>>y[i]>>v[i];
        p[i] = y[i];
        r[i] = i;
    }
    sort(r,r+n,comp);
    sort(p,p+n);
    
    for(int i=0;i<n;i++){
        //这个循环计算ans[idx]
        float curt = 0.0f;
        int idx = r[i];
        int curLoc = x[idx];
        for(int j=0;j<n;j++){
            if(p[j]>curLoc){
                curt += (float)(p[j] - curLoc)/v[idx];
                curLoc = p[j];
                curt = max(curt, t[j]);
                //不论r[j]在r[i]前或后都对
                t[j] = curt;
                if(p[j] == y[idx]){
                    ans[idx] = t[j];
                    break;
                }
            }
        }
    }
    
    cout<<fixed<<setprecision(2);
    
    for(int i=0;i<n;i++){
        
        cout<<ans[i]<<endl;
    }
    
    return 0;
}
