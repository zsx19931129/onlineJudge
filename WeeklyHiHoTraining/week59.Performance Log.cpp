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
#include <unordered_map>

using namespace std;

int decodeTimeStamp(string ts){
    int h,m,s;
    sscanf(ts.c_str(), "%d:%d:%d", &h, &m, &s);
    return h*3600 + m*60 + s;
}

string encodeTimeStamp(int t){
    int h, m, s;
    h = t/3600;
    m = (t%3600)/60;
    s = t%60;
    char buffer[300] = {0};
    sprintf(buffer, "%02d:%02d:%02d", h, m, s);
    return string(buffer);
}

int main() {
    int n;
    cin>>n;
    unordered_map<string, int> funcidx;
    vector<int> time(n);
    vector<string> fname(n);
    int off = 0;
    stack<string> stk;
    bool legal = true;
    for(int i=0;i<n;++i){
        string name, ts, action;
        cin>>name>>ts>>action;
        if(action == "START"){
            if(funcidx.find(name) != funcidx.end()){
                cout<<"Incorrect performance log"<<endl;
                legal = false;
                break;
            }
            funcidx[name] = off;
            time[off] = decodeTimeStamp(ts);
            fname[off] = name;
            stk.push(name);
            ++off;
        }else if(action == "END"){
            if(funcidx.find(name) == funcidx.end()){
                cout<<"Incorrect performance log"<<endl;
                legal = false;
                break;
            }
            int tmp = decodeTimeStamp(ts);
            string stmp = stk.top();
            if(tmp < time[funcidx[name]] || stmp != name){
                cout<<"Incorrect performance log"<<endl;
                legal = false;
                break;
            }
            time[funcidx[name]] = tmp - time[funcidx[name]];
            stk.pop();
        }else{
            cout<<"Incorrect performance log"<<endl;
            legal = false;
            break;
        }
    }
    if(legal){
        if(!stk.empty()){
            cout<<"Incorrect performance log"<<endl;
        }else{
            for(int i=0;i<n/2;++i){
                cout<<fname[i]<<" "<<encodeTimeStamp(time[i])<<endl;
            }
        }
    }
    return 0;
}
