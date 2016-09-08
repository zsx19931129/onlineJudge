class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n));
        if(n==0){
            return matrix;
        }
        int val = 1, width = n;
        for(int i=0;i<(n+1)/2-1;++i){
            width = n - 2*i;
            for(int j=0;j<width;++j){
                matrix[i][i+j] = val++;
            }
            for(int j=1;j<width;++j){
                matrix[i+j][i+width-1] = val++;
            }
            for(int j=width-2;j>=0;--j){
                matrix[i+width-1][i+j] = val++;
            }
            for(int j=width-2;j>0;--j){
                matrix[i+j][i] = val++;
            }
        }
        if(n&1){
            matrix[(n+1)/2-1][(n+1)/2-1] = val++;
        }else{
            matrix[(n+1)/2-1][(n+1)/2-1] = val++;
            matrix[(n+1)/2-1][(n+1)/2] = val++;
            matrix[(n+1)/2][(n+1)/2] = val++;
            matrix[(n+1)/2][(n+1)/2-1] = val++;
        }
        return matrix;
    }
};