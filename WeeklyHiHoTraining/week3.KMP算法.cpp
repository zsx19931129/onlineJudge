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

using namespace std;

void showVec(vector<int> v){
    for(int i=0;i<v.size();++i){
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

vector<int> genNextVec(string &pattern){
    int plen = pattern.length();
    vector<int> next(plen+1);
    next[0] = -1;
    int k=-1, j=0;
    while(j<plen){
        if(k==-1 || pattern[j] == pattern[k]){
            ++k;
            ++j;
            if(pattern[j] == pattern[k]){
                next[j] = next[k];
            }else{
                next[j] = k;
            }
        }else{
            k = next[k];
        }
    }
    return next;
}

int kmp(int sstart, const char *str, int pstart, const char *pattern, vector<int> &next, int plen){
    int i=sstart, j=pstart;
    while(*(str+i) && j<plen){
        if(j == -1 || str[i] == pattern[j]){
            ++i;
            ++j;
        }else{
            j = next[j];
        }
    }
    if(!*(pattern+j)){
        return i - j;
    }else{
        return -1;
    }
}

int main() {
    int n;
    cin>>n;
    while(n--){
        string pattern, str;
        cin>>pattern>>str;
        vector<int> next = genNextVec(pattern);
//        showVec(next);
        int cnt = 0;
        int plen = pattern.length();
        const char *pstr = str.c_str(), *ppattern = pattern.c_str();
        int res = kmp(0, pstr, 0, ppattern, next, plen);
        while(res != -1){
            ++cnt;
            res = kmp(res+plen, pstr, next[plen], ppattern, next, plen);
        }
        cout<<cnt<<endl;
    }
    return 0;
}
