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

using namespace std;

#define MAXLEN 10000005

char buffer[MAXLEN];

inline bool solution(const char *ch, const int *cnt){
    return ch[0]+1 == ch[1] && ch[1]+1 == ch[2] && cnt[0] >= cnt[1] && cnt[1] <= cnt[2];
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--){
        int slen;
        scanf("%d", &slen);
        char ch[3] = {0};
        int cnt[3] = {0};
        int off = -1;
        scanf("%s", buffer);
        char lastch = 0;
        bool yes = false;
        for(int i=0;i<slen;++i){
            if(buffer[i] != lastch){
                if(off == 2){
                    if(solution(ch, cnt)){
                        yes = true;
                        break;
                    }
                    ch[0] = ch[1];
                    ch[1] = ch[2];
                    ch[2] = buffer[i];
                    cnt[0] = cnt[1];
                    cnt[1] = cnt[2];
                    cnt[2] = 1;
                }else{
                    ++off;
                    ch[off] = buffer[i];
                    cnt[off] = 1;
                }
                lastch = buffer[i];
            }else{
                ++cnt[off];
            }
        }
        if(solution(ch, cnt)){
            yes = true;
        }
        if(yes){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
    return 0;
}
