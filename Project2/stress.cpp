#include <bits/stdc++.h>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "quicksort.h"
#include "introsort.h"

#define ARRAY_SIZE 100000
using namespace std;

/**
 * generate 1d vector with size = ARRAY_SIZE
 *
 * @param
 *
 * isRandom --> boolean variable to return random or sorted array
 * if isRandom == true, then the array should look like this [0, 1, 2, 3]
 *
 * @return
 *  a 1d vector with size = ARRAY_SIZE, you have the choice to pass vector by reference or to return a vector
 * make sure to change the code in main to match your change
 *
 */
vector<int> generate_vector(bool isRandom) {
    vector<int> a(ARRAY_SIZE);
    if (isRandom) {
        for (size_t i = 0; i < ARRAY_SIZE; i++) a[i] = rand() % 100;
        sort(a.begin(), a.end());
        return a;
    }

    else {
        for (size_t i = 0; i < ARRAY_SIZE; i++) a[i] = rand() % 100;
        return a;
    }
}

/**
 * driving stress test for both algorithms
 *
 * generate 1d vector
 * compare their output and runnig time
*/
int main(int argc, char** argv){
    while (true){
        vector<int> v1 = generate_vector(false);
        vector<int> b = v1; //copy vector v1 into vector B
        vector<int> sorted_array = v1;
        sort(sorted_array.begin(), sorted_array.end());

        auto quick_start = std::chrono::high_resolution_clock::now();
        // fill this line
        Quicksort(v1, 0, v1.size() - 1);
        auto quick_finish = std::chrono::high_resolution_clock::now();

        auto intro_start = std::chrono::high_resolution_clock::now();

        //Here we transfom the vector to an array to enter the introsort algorithm   
        int a[ARRAY_SIZE];
        std::copy(b.begin(), b.end(), a);
        int n = sizeof(a) / sizeof(a[0]);
        // get the maximum depth
        int maxdepth = log(n) * 2;
        // sort the array using introsort the algorithm
        introsort(a, a, a + n - 1, maxdepth);

        //Here we transfom the array back to a vector to compare between two algorithms
        std::vector<int> v2(std::begin(a), std::end(a));

        auto intro_finish = std::chrono::high_resolution_clock::now();

        auto quick_time = (quick_finish - quick_start).count();
        auto intro_time = (intro_finish - intro_start).count();

        if (v1 == sorted_array && v2 == sorted_array)
        {
            cout << "=======Equivalent Result========";
            cout << endl;
            cout << "quick_time ==> " << quick_time;
            cout << endl;
            cout << "intro_time ==> " << intro_time;
            cout << endl;
            cout << "performance enhancment ==>" << quick_time / intro_time << endl;
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