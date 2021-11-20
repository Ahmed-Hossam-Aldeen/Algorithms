#include <bits/stdc++.h>
#include <chrono>
#include <thread>
#include "naive.h"
#include "strassen.h"
using namespace std;

vector<vector<int>> generate_random_vector() {
    int n = 128;
    vector<vector<int>> x(n,vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            x[i][j] = rand() % 100;
        }
    }
    return x;
  
}

/**
 * driving stress test for both algorithms
 * 
 * generate 2 2d-vectors with fixed size 128*128
 * compare their output and runnig time
*/
int main(int argc, char **argv)
{

    while (true)
    {
        vector<vector<int>> a = generate_random_vector();
        vector<vector<int>> b = generate_random_vector();
        //We will generate the C matrix for now but it will be overrided in the algorithms
        vector<vector<int>> c = generate_random_vector();
        vector<vector<int>> naive_result;
        vector<vector<int>> strassen_result;

        auto naive_start = std::chrono::high_resolution_clock::now();
        naive_result = naive(a, b);
        auto naive_finish = std::chrono::high_resolution_clock::now();

        auto strassen_start = std::chrono::high_resolution_clock::now();
        strassen_result = multiplyStrassen(a, b, c, 128);
        auto strassen_finish = std::chrono::high_resolution_clock::now();

        auto naive_time = (naive_finish - naive_start).count();
        auto strassen_time = (strassen_finish - strassen_start).count();

        if (strassen_result == naive_result)
        {
            cout << "equivalent result ";
            cout << endl;
            cout << "naive_time ==>  " << naive_time;
            cout << endl;
            cout << "strassen_time ==> " << strassen_time;
            cout << endl;
            cout << "performance enhancment ==>" << naive_time / strassen_time << endl;
            cout << endl;
        }
        else
        {
            cout << "error, check your inputs and algortihms " << endl;
            // you may want to store your variables in a file to re-run the test on the same inputs;
            break;
        }
    }
    return 0;
}