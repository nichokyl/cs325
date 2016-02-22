#include <cstdlib>

#def SIZE 10

int DivideAndConquer(int [], int);
int SuffixPrefix(int [], int []);

int main()
{
	int arr[SIZE];
	
	DivideAndConquer(arr, SIZE);
}

int DivideAndConquer(int arr[], int n)
{
	int n_half = n / 2;
	int first[n_half], second[n_half+1];
	int suffix[n_half], prefix[n_half+1];
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
	min1 = DivideAndConquer(first, n_half);
	min2 = DivideAndConquer(second, n_half);
	min3 = SuffixPrefix(first, second)
}

int SuffixPrefix(int first[], second[])
{
	// Put sorts in here
	
	int iFinal, jFinal;
	int min = 65535;	// Largest 8bit int
	int prev = 65535;
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
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