#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>

#define SIZE 10

using namespace std;

int DivideAndConquer(int [], int);
int SuffixPrefix(int [], int[], int, int);

int partition(int arr[], int lo, int hi)
{
	int pivot = arr[hi];
	int i = lo;
	
	for (int j = lo; j < hi; j++)
	{
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
		i++;
	}
	int temp = arr[i];
	arr[hi] = arr[i];
	arr[i] = temp;
	
	return i;
}

void quicksort(int arr[], int lo, int hi)
{
	int p;
	if (lo < hi)
	{
		p = partition(arr, lo, hi);
		quicksort(arr, lo, p-1);
		quicksort(arr, p+1, hi);
	}
}

int main()
{
    string line;
	int result;
    //ifstream myfile ("test_cases_with_solutions.txt");
    //ifstream myfile ("test_cases_without_solutions.txt");
	
	
//	int arr[] = {258821, 306066, -231500, -436295, 306425, 241361, 68153, 216106, -353968, 425757, 438111, -65653, -90992, -408188, -319437, 151786, -356247, -424078, -230531, 51863, 371945, 439278, -98784, 445010, -8235, 177337, 123174, 375508, -308068, 420045, 410467, 344006, 272623, 226552, -198151, -38586, 233206, -479137, -64701, -185958, 17319, 9237, -451752, 28414, 45946, -99873, -451984, 325519, -372670, 330385, 26093, 331932, 66849, -346808, 105535, 313619, -437154, 489421, -294743, -82994, -328806, 425808, -4951, 380292, -284245, -263289, 99328, -136943, 334475, -488275, 45777, 462572, -105101, -268580, 445742, 228270, -386481, -311534, -493956, -465020, 414547, -407161, 62069, -258371, 442358, 170609, -337386, 316532, -247616, 281311, -327522, -472093, -418488, 45369, -122124, 356880, 392005, -228005, -404684, -315306};
	int arr[] = {31, -41, 59, 26, -53, 58, -6, 97, -93, -23};
	int n = sizeof(arr)/sizeof(int);
	
	result = DivideAndConquer(arr, n);
	cout << result << endl;
	
	
	/*
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
	
	
	*/
	
    return 0;
}

int DivideAndConquer(int arr[], int n)
{	
	if (n == 1)
	{
//		cout << "Base case!!!" << endl;
		return abs(arr[0]);
	}
	
	int n_half = n / 2;
	int first[n_half], second[n_half+1];
	int suffix[n_half], prefix[n_half+1];
	int count = n_half - 1;
	
	
//	cout<< "start DivideAndConquer"<<endl;
	
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
		second[i-n_half] = arr[i];
		if (i == n_half)
			prefix[i-n_half] = arr[i];
		else
			prefix[i-n_half] = arr[i-1] + arr[i];
	}
	
//	cout<< "after second loop"<<endl;
	
	int min1 = 0, min2 = 0, min3 = 0;
	min1 = DivideAndConquer(first, n_half);
	min2 = DivideAndConquer(second, n-n_half);
	min3 = SuffixPrefix(suffix, prefix, n_half, n-n_half);
	
	if(min1 < min2 && min1 < min3)
	{
		return min1;
	}
	else if(min2 < min1 && min2 < min3)
	{
		return min2;
	}
	else
	{
		return min3;
	}
	
	
	//return min(min3, min(min1, min2));
}
int SuffixPrefix(int first[], int second[], int n, int m)
{
	// Put sorts in here
	quicksort(first, 0, n);
	quicksort(second, 0, m);
	
	int iFinal, jFinal;
	int min = 65535;	// Largest 8bit int
	int prev = 65535;
	int sum;
	
	//cout<< "SECOND[0]: " << second[0] << endl;
	
	for (int i = n-1; i >= 0; i--)
	{
		for (int j = 0; j < m; j++)
		{
			cout << "FIRST: " << first[i] << " SECOND: " << second[j] << endl;
			sum = abs(first[i] + second[j]);
			cout << "SUM: " << sum << endl;
			if (sum > prev)	// The sum will now be going up because they are sorted
			{
				cout << "Going up now, stop." << endl;
				break;
			}
			prev = sum;
			if (sum < min)
			{
				cout << "Sum now becoming minimum." << endl;
				min = sum;
				iFinal = i;
				jFinal = j;
			}				
		}
	}
	
	return min;
}