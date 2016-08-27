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
#include <cmath>
#include <vector>

using namespace std;


int main(int argc, const char * argv[]) {
    ifstream in("C-small-practice-2.in");
    streambuf *cinbuf = cin.rdbuf();    // save old buf
    cin.rdbuf(in.rdbuf());              // redirect std::cin to in.txt


    ofstream out("C-small-practice-2.out");
    streambuf *coutbuf = cout.rdbuf();
    cout.rdbuf(out.rdbuf());
    
    
    int T;
    cin>>T;
    
    for(int i=1;i<=T;++i){
        int N;
        cin>>N;
        string cardName;
        // get newline character
        getline(cin, cardName);
        string curMaxName = "";
        int cost = 0;
        for(int j=0;j<N;++j){
            getline(cin, cardName);
            if(j == 0){
                curMaxName = cardName;
            }else{
                if(cardName < curMaxName){
                    ++cost;
                }else{
                    curMaxName = cardName;
                }
            }
        }
        cout<<"Case #"<<i<<": "<<cost<<endl;
        
    }
    
    cin.rdbuf(cinbuf);
    cout.rdbuf(coutbuf);
    return 0;
}
