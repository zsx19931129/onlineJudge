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
#include <climits>
#include <unordered_map>
#include <queue>

using namespace std;

#define MAXN 101

char room[MAXN][MAXN];
int dist[MAXN][MAXN];
bool visited[MAXN][MAXN];
int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
int n,m;

void bfs(int x, int y){
    visited[x][y] = true;
    dist[x][y] = 0;
    
    queue<pair<int, int>> q;
    pair<int, int> item;
    q.push(make_pair(x, y));
    while(!q.empty()){
        item = q.front();
        q.pop();
        for(int i=0;i<4;++i){
            int newx = item.first + dir[i][0];
            int newy = item.second + dir[i][1];
            if(newx<n && newx>=0 && newy<m && newy>0 && room[newx][newy] != '#' && room[newx][newy] != 'P' && !visited[newx][newy]){
                visited[newx][newy] = true;
                dist[newx][newy] = dist[item.first][item.second] + 1;
                if(room[newx][newy] != 'S'){
                    q.push(make_pair(newx, newy));
                }
            }
        }
    }
}

int main() {
    cin>>n>>m;
    for(int i=0;i<n;++i){
        scanf("%s", room[i]);
    }
    int sx, sy;
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            if(room[i][j] == 'H'){
                sx = i;
                sy = j;
                break;
            }
        }
    }
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            dist[i][j] = INT_MAX;
            visited[i][j] = false;
        }
    }
    bfs(sx, sy);
    int ret = INT_MAX;
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            if(room[i][j] == 'S' && dist[i][j] != INT_MAX){
                int newi = i+1, newj = j+1;
                if(newi<n && room[newi][j] == 'S' && dist[newi][j] != INT_MAX){
                    if(ret > dist[i][j] + dist[newi][j]){
                        ret = dist[i][j] + dist[newi][j];
                    }
                }
                if(newj<m && room[i][newj] == 'S' && dist[i][newj] != INT_MAX){
                    if(ret > dist[i][j] + dist[i][newj]){
                        ret = dist[i][j] + dist[i][newj];
                    }
                }
            }
        }
    }
    if(ret == INT_MAX){
        cout<<"Hi and Ho will not have lunch."<<endl;
    }else{
        cout<<ret<<endl;
    }
    return 0;
}
