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
#include <map>
#include <unordered_map>

using namespace std;

int main() {
    int n, m;
    cin>>n>>m;
    string str;
    vector<string> a;
    for(int i=0;i<n;++i){
        cin>>str;
        a.push_back(str);
    }
    unordered_map<string, int> lastVisit;
    int s = 0, cnt = 0;
    for(int i=0;i<n;++i){
        if(lastVisit.find(a[i]) != lastVisit.end() && lastVisit[a[i]] >= s && lastVisit[a[i]] <= i){
            cout<<"Cache"<<endl;
        }else{
            ++cnt;
            if(cnt>m){
                ++s;
            }
            cout<<"Internet"<<endl;
        }
        lastVisit[a[i]] = i;
        while(lastVisit[a[s]] != s){
            ++s;
        }
    }
    return 0;
}
