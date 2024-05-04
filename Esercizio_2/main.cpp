#include <SortingAlgorithm.hpp>
#include <chrono>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <Eigen/Eigen>
#include <cstdlib>

using namespace std;
using namespace SortLibrary;

int main(int argc, char *argv[])
{
    vector<int> nValues;

    // Read from command line
    for(int i = 0; i < argc; i++)
    {
        nValues.push_back(atoi(argv[i]));
    }

    // Remove the first element
    nValues.erase(nValues.begin());

    for(size_t i = 0; i < nValues.size(); i++)
    {
        unsigned int n = nValues[i];

        double sum1 = 0;
        double sum2 = 0;
        double sum3 = 0;
        double sum4 = 0;
        double sum5 = 0;
        double sum6 = 0;

        vector<double> ElapsedTimeRand1;
        vector<double> ElapsedTimeRand2;

        vector<double> ElapsedTimeOrd1;
        vector<double> ElapsedTimeOrd2;

        vector<double> ElapsedTimePer1;
        vector<double> ElapsedTimePer2;

        unsigned int iter = 100;
        for(unsigned int j = 0; j < iter; j++)
        {
            // generate random vectors
            vector<int> v1;
            vector<int> v2;
            for(unsigned int k = 0; k < n; k++)
            {
                int kElement = rand() % 100 + 1;
                v1.push_back(kElement);
                v2.push_back(kElement);
            }

            chrono::steady_clock::time_point t_begin1 = chrono::steady_clock::now();
            MergeSort(v1);
            chrono::steady_clock::time_point t_end1 = chrono::steady_clock::now();
            chrono::steady_clock::time_point t_begin2 = chrono::steady_clock::now();
            BubbleSort(v2);
            chrono::steady_clock::time_point t_end2 = chrono::steady_clock::now();

            ElapsedTimeRand1.push_back(chrono::duration_cast<chrono::nanoseconds>(t_end1-t_begin1).count());
            ElapsedTimeRand2.push_back(chrono::duration_cast<chrono::nanoseconds>(t_end2-t_begin2).count());

            sum1 += ElapsedTimeRand1[j];
            sum2 += ElapsedTimeRand2[j];

            // ordered vectors (those ordered before)
            chrono::steady_clock::time_point t_begin3 = chrono::steady_clock::now();
            MergeSort(v1);
            chrono::steady_clock::time_point t_end3 = chrono::steady_clock::now();
            chrono::steady_clock::time_point t_begin4 = chrono::steady_clock::now();
            BubbleSort(v2);
            chrono::steady_clock::time_point t_end4 = chrono::steady_clock::now();

            ElapsedTimeOrd1.push_back(chrono::duration_cast<chrono::nanoseconds>(t_end3-t_begin3).count());
            ElapsedTimeOrd2.push_back(chrono::duration_cast<chrono::nanoseconds>(t_end4-t_begin4).count());

            sum3 += ElapsedTimeOrd1[j];
            sum4 += ElapsedTimeOrd2[j];

            // perturbed vectors (using the previous ordered vectors)
            int perturbation = rand() % (1 - (-1) + 1) + (-1);
            for(unsigned int k = 0; k < n; k++)
            {
                v1[k] += perturbation;
                v2[k] += perturbation;
            }

            chrono::steady_clock::time_point t_begin5 = chrono::steady_clock::now();
            MergeSort(v1);
            chrono::steady_clock::time_point t_end5 = chrono::steady_clock::now();
            chrono::steady_clock::time_point t_begin6 = chrono::steady_clock::now();
            BubbleSort(v2);
            chrono::steady_clock::time_point t_end6 = chrono::steady_clock::now();

            ElapsedTimePer1.push_back(chrono::duration_cast<chrono::nanoseconds>(t_end5-t_begin5).count());
            ElapsedTimePer2.push_back(chrono::duration_cast<chrono::nanoseconds>(t_end6-t_begin6).count());

            sum5 += ElapsedTimePer1[j];
            sum6 += ElapsedTimePer2[j];


        }

        // compute average time of two methods with different size's vectors
        cout << " Average time for vectors of size " << n << endl;
        cout << " MergeSort  -> Random vector = " << sum1/iter << "; Ordered vector = " <<  sum3/iter <<  "; Perturbed vector = "<< sum5/iter << endl;
        cout << " BubbleSort -> Random vector = " << sum2/iter << "; Ordered vector = " <<  sum4/iter <<  "; Perturbed vector = "<< sum6/iter << endl;
        cout << endl;

    }

    cout << "MergeSort is a more efficient algorithm for large unordered vectors and has a complexity equal to O(n log(n)), while BubbleSort "
            "is more efficient for already sorted or slightly perturbed vectors and has a complexity equal to O(n^2) ." << endl;

    return 0;
}
