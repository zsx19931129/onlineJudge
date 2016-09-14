class Solution {
public:
    string addBinary(string a, string b) {
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        int slen1 = a.length(), slen2 = b.length();
        string lstr = a, sstr = b;
        if(slen1 < slen2){
        	lstr = b;
        	sstr = a;
        }
        string ret(lstr.length(), 0);

        int i=0;
        int carry=0;
        while(i<lstr.length()){
        	int cur = lstr[i] - '0' + carry;
        	if(i<sstr.length()){
        		cur += sstr[i] - '0';
        	}
        	ret[i] = cur%2 + '0';
        	carry = cur/2;
        	++i;
        }
        if(carry){
        	ret += '1';
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};