//
//  main.cpp
//  codeJamTest
//
//  Created by shaoxiong on 8/26/16.
//  Copyright © 2016 shaoxiong. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstring>

using namespace std;

#define MAXLEN 101

bool E[MAXLEN*2][MAXLEN*2];
int color[MAXLEN*2];
map<string, int> nameIdMap;

int getId(string inStr){
    auto findRes = nameIdMap.find(inStr);
    if(findRes == nameIdMap.end()){
        int size = nameIdMap.size();
        nameIdMap[inStr] = size;
    }
    return nameIdMap[inStr];
}

void init(){
    memset(color, 0, sizeof(color));
    memset(E, false, sizeof(E));
    nameIdMap.clear();
    int M;
    cin>>M;
    for(int j=0;j<M;++j){
        string a, b;
        cin>>a>>b;
        int x = getId(a), y = getId(b);
        E[x][y] = E[y][x] = true;
    }
}

bool dfs(int u, int c, int n){
    if(color[u] == 0){
        color[u] = c;
        bool ret = true;
        for(int v=0;v<n;++v){
            if(E[u][v]){
                ret &= dfs(v, 3-c, n);
            }
        }
        return ret;
    }else{
        return color[u] == c;
    }
}

bool solution(){
    int n = nameIdMap.size();
    bool legal = true;
    for(int i=0;i<n;++i){
        if(color[i] == 0){
            legal &= dfs(i, 1, n);
        }
    }
    return legal;
}

int main(int argc, const char * argv[]) {
    ifstream in("A-small-practice-2.in");
    streambuf *cinbuf = cin.rdbuf();    // save old buf
    cin.rdbuf(in.rdbuf());              // redirect std::cin to in.txt
    

    ofstream out("A-small-practice-2.out");
    streambuf *coutbuf = cout.rdbuf();
    cout.rdbuf(out.rdbuf());
    
    
    int T;
    cin>>T;
    for(int i=1;i<=T;++i){
        init();
        bool res = solution();
        cout<<"Case #"<<i<<": "<<(res?"Yes":"No")<<endl;
    }
    
    cin.rdbuf(cinbuf);
    cout.rdbuf(coutbuf);
    return 0;
}
