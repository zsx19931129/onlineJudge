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

//对double的数字上下取整时，用ceil和floor，不用int强制类型转换

double ox, oy, r;

double getDistance(int x, int y){
    return (ox-x)*(ox-x) + (oy-y)*(oy-y);
}

bool bigger(double a, double b){
    double eps = 1e-6;
    return a - b > eps;
}

bool equals(double a, double b){
    double eps = 1e-6;
    return abs(a-b) < eps;
}

void better(int x, int y, double &dist, int &resx, int &resy){
    double dis = getDistance(x, y);
    if(bigger(dis, dist)){
        dist = dis;
        resx = x;
        resy = y;
    }else if(equals(dis, dist)){
        if(x>resx){
            resx = x;
            resy = y;
        }else if(x == resx && y > resy){
            resy = y;
        }
    }
}

int main() {
    cin>>ox>>oy>>r;
    int leftx = ceil(ox-r), rightx = floor(ox+r);
    double rsquare = r*r, dist = -1;
    int resx = INT_MIN, resy = INT_MIN;
    for(int i=leftx;i<=rightx;++i){
        double d = sqrt(rsquare - (ox - i)*(ox - i));
        int y1 = floor(oy + d);
        better(i, y1, dist, resx, resy);
        int y2 = ceil(oy - d);
        better(i, y2, dist, resx, resy);
    }
    cout<<resx<<" "<<resy<<endl;
    return 0;
}
