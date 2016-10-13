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

using namespace std;

string reconstruct(string str){
    int slen = str.length();
    string ret(2*slen+3, '#');
    ret[0] = '^';
    ret[2*slen+3-1] = '$';
    for(int i=0;i<slen;++i){
        ret[2*(i+1)] = str[i];
    }
    return ret;
}

int bruteforce(string &str, int center, int idx){
    int i, j;
    for(i=center+idx+1, j=center-idx-1;str[i]==str[j];++i,--j);
    return i - center;
}

int main() {
    int t;
    cin>>t;
    while(t--){
        string str;
        cin>>str;
        if(str == ""){
            cout<<0<<endl;
        }
        str = reconstruct(str);
        int slen = str.length();
        //cout<<str<<endl;
        vector<int> manacher(slen, 1);
        int center = 2, rightmost = 3;
        manacher[2] = 3;
        for(int i=3;i<slen;++i){
            if(i>=rightmost){
                int radix = bruteforce(str, i, 0);
                manacher[i] = radix;
                rightmost = i + radix - 1;
                center = i;
            }else{
                int leftmost = 2*center - rightmost;
                int left = 2*center - i;
                if(left - manacher[left] + 1 > leftmost){
                    manacher[i] = manacher[left];
                }else{
                    int radix = bruteforce(str, i, rightmost-i);
                    manacher[i] = radix;
                    rightmost = i + radix - 1;
                    center = i;
                }
            }
        }
        int maxradix = 0, maxidx = -1;
        for(int i=0;i<slen;++i){
            if(manacher[i] > maxradix){
                maxradix = manacher[i];
                maxidx = i;
            }
        }
        //cout<<maxradix<<" "<<maxidx<<endl;
        int maxlen = 2*maxradix - 1;
        cout<<maxlen/2<<endl;
    }
    return 0;
}
