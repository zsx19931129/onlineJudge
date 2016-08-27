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

using namespace std;


int main(int argc, const char * argv[]) {
    ifstream in("B-small-practice.in");
    streambuf *cinbuf = cin.rdbuf();    // save old buf
    cin.rdbuf(in.rdbuf());              // redirect std::cin to in.txt


    ofstream out("B-small-practice.out");
    streambuf *coutbuf = cout.rdbuf();
    cout.rdbuf(out.rdbuf());
    
    
    int T;
    cin>>T;
    
    const double g = 9.8;
    const double pi = asin(1)*2;


    for(int i=1;i<=T;++i){
        int V, D;
        cin>>V>>D;
        double sin2theta = (g*D)/(V*V);
        // float caculation overflow.
        if(sin2theta>1.0){
            sin2theta = 1.0;
        }
        double theta = asin(sin2theta)*180/(2*pi);
        cout.setf(ios::fixed);
        cout.precision(7);
        cout<<"Case #"<<i<<": "<<theta<<endl;
    }
    
    cin.rdbuf(cinbuf);
    cout.rdbuf(coutbuf);
    return 0;
}
