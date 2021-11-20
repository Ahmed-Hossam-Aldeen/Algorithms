#include <bits/stdc++.h>
using namespace std;
/**
 * implement the naive matrix multiplication algorithm
 * 
 * @param
 *  a --> a 2d vector
 *  b --> a 2d vector
 * 
 * @return
 * the result of a*b "matrix multiplcation"
*/

//const int n = 128;


vector<vector<int>> naive(vector<vector<int>>a, vector<vector<int>>b) {
    int n = 128;
    vector<vector<int>> c(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

    
