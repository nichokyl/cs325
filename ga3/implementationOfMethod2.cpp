#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;
int method1(int arr1[], int arr2[], int n1, int n2){
    int smallestD = 100;
    int loc1 = 0;
    int loc2 = 0;
    for(int i = 0; i < n1; i++){
        for(int j = 0; j < n2; j++){
            int temp;
            temp = abs(arr1[i] + arr2[j]);
            if(temp < smallestD){
                smallestD = temp;
                loc1 = i;
                loc2 = j;
            }
        }
    }
    cout << "Location in the first list: " << loc1 + 1 << endl;
    cout << "Location in the 2nd list: " << loc2 + 1 << endl;
    return smallestD;
}
int method1v(vector<int>& arr1, vector<int>& arr2){
    int smallestD = 100;
    int loc1 = 0;
    int loc2 = 0;
    int n1 = arr1.size();
    int n2 = arr2.size();
    for(int i = 0; i < n1; i++){
        for(int j = 0; j < n2; j++){
            int temp;
            temp = abs(arr1[i] + arr2[j]);
            if(temp < smallestD){
                smallestD = temp;
                loc1 = i;
                loc2 = j;
            }
        }
    }
    cout << "Location in the first list: " << loc1 + 1 << endl;
    cout << "Location in the 2nd list: " << loc2 + 1 << endl;
    return smallestD;
}
void divAndCon(int arr[], int n){
        int nHalf = n/2;
        int arr1[5];
        int arr2[5];
        int count = nHalf-1;
        //suffix array
        for (int i = nHalf-1; i >= 0; i--){
            if(count == nHalf-1){
                arr1[i] = arr[count];
                count--;
                //cout << arr1[i] << ", ";
            }else if (count >= 0){
                arr1[i] = arr1[i+1] + arr[count];
                //cout << "a[i+1]:" << arr1[i+1] << " + " << "arr[count]:" << arr[count] << arr1[i] << endl;
                count--;
                //cout << arr1[i] << ", ";
            }
        }
        cout << endl;
        //prefix array
        count = 0;
        for(int i = nHalf; i < n; i++){
            if( i == nHalf){
                arr2[count] = arr[i];
                count++;
            }else{
                arr2[count] = arr2[count-1] + arr[i];
                count++;
            }
        }
        for(int i = 0; i < nHalf; i++){
            cout << arr1[i] << ", ";
        }
        cout << endl;
        for(int i = 0; i < nHalf; i++){
            cout << arr2[i] << ", ";
        }
        cout << endl;
        int result = method1(arr1, arr2, nHalf, nHalf);
        cout << "closest-to-0: " << result << endl;
}
void divAndConV(vector<int>& arr){
        int n = arr.size();
        int nHalf = n/2;
        int arr1[5];
        int arr2[5];
        int count = nHalf-1;
        //suffix array
        for (int i = nHalf-1; i >= 0; i--){
            if(count == nHalf-1){
                arr1[i] = arr[count];
                count--;
                //cout << arr1[i] << ", ";
            }else if (count >= 0){
                arr1[i] = arr1[i+1] + arr[count];
                //cout << "a[i+1]:" << arr1[i+1] << " + " << "arr[count]:" << arr[count] << arr1[i] << endl;
                count--;
                //cout << arr1[i] << ", ";
            }
        }
        cout << endl;
        //prefix array
        count = 0;
        for(int i = nHalf; i < n; i++){
            if( i == nHalf){
                arr2[count] = arr[i];
                count++;
            }else{
                arr2[count] = arr2[count-1] + arr[i];
                count++;
            }
        }
        cout << "first list" << endl;
        cout << "2nd list" << endl;
        for(int i = 0; i < nHalf; i++){
            cout << arr1[i] << ", ";
        }

        for(int i = 0; i < nHalf; i++){
            cout << arr2[i] << ", ";
        }
        cout << endl;
        int result = method1(arr1, arr2, nHalf, nHalf);
        cout << "closest-to-0: " << result << endl;
        cout << "******************** end of algorithm ******************" << endl;
}
int SuffixPrefix(vector<int>& first, vector<int>& second)
{
    // Put sorts in here

    int iFinal, jFinal;
    int min = 65535;	// Largest 8bit int
    int prev = 65535;

    for (int i = 0; i < first.size(); i++)
    {
        for (int j = 0; j < first.size(); j++)
        {
            int sum = abs(first[i] + second[j]);
            if (sum > prev)	// The sum will now be going up because they are sorted
                break;

            if (sum < min)
            {
                min = sum;
                iFinal = i;
                jFinal = j;
            }
        }
    }

    return min;
}
int DivideAndConquer(vector<int>& arr)
{
    int n = arr.size();
    int n_half = n / 2;
    //int first[n_half], second[n_half+1];
    //int suffix[n_half], prefix[n_half+1];
    vector<int> first;
    vector<int> second;
    vector<int> suffix;
    vector<int> prefix;
    int count = n_half - 1;

    // The first array of suffix  sums
    for (int i = count; i >= 0; i--)
    {
        first[i] = arr[i];
        if (i == count)
            suffix[i] = arr[i];
        else
            suffix[i] = arr[i+1] + arr[i];	// Previous sum plus element value
    }

    // The second array of prefix sums
    for (int i = n_half; i < n; i++)
    {
        second[i] = arr[i];
        if (i == n_half)
            prefix[i] = arr[i];
        else
            prefix[i] = arr[i-1] + arr[i];
    }

    int min1, min2, min3;
    //min1 = DivideAndConquer(first, n_half);
    //min2 = DivideAndConquer(second, n_half);
    min1 = DivideAndConquer(first);
    min1 = DivideAndConquer(second);
    min3 = SuffixPrefix(first, second);
}


int main()
{
    string line;
    //ifstream myfile ("test_cases_with_solutions.txt");
    //ifstream myfile ("test_cases_without_solutions.txt");
    ifstream myfile ("test.txt");
    if(myfile.is_open()){
        cout << "Read test cases .txt file" << "\n";
        bool endOfLine = false;
        while(getline(myfile, line)){
            stringstream ss(line);
            string value;
            int intValue;
            vector<int> valuesV;
            while(getline(ss, value, ',')){
                size_t foundB = value.find("[");
                if(foundB != string::npos){
                    value = value.substr(1, value.length());
                }
                size_t foundB1 = value.find("]");
                if(foundB1 != string::npos){
                    value = value.substr(1, value.length()-1);
                    endOfLine = true;
                }
                intValue = atoi(value.c_str());
                valuesV.push_back(intValue);
                if(endOfLine == true){
                    //print out what we read in
                    for(int i = 0; i < valuesV.size(); i++){
                        cout << valuesV[i] << ", ";
                    }
                    cout << endl;
                    //do the algorithm
                    //divAndConV(valuesV);
                    int result = DivideAndConquer(valuesV);
                    cout << result << endl;
                    //end
                    endOfLine = false;
                    valuesV.clear();
                    break;
                }
            }
        }
        myfile.close();
    }else{
        cout << "can't open the test cases *.txt file (required the file to be in the same location in order to run) \n";
    }

    //int arr1[5] = {22, -9, 32, -27, -53};
    //int arr2[5] = {58, 52, 149, 56, 33};
    //int arr[10] = {31, -41, 59, 26, -53, 58, -6, 97, -93, -23};
    //divAndCon(arr, 10);
    //int result = method1(arr1, arr2, 5, 5);
    //cout << result << endl;
    return 0;
}
