#include <iostream>

#define N 8
#define K 2
#define B 2

using std::cout;
using std::endl;

int dist(int balls[], int keys[], int i, int n)
{
	int j, k, idx;
	int distance, minDistance = n;
	int firstLoop, secondLoop;
	
//	cout << "in dist " << minDistance << " " << i << endl;
	
	// Checking second half
	for (j = i+1; j < n; j++)
	{
//		cout << "first loop i " << j << " keys is " << keys[j] << endl;
		if (keys[j] == 1)
		{
			distance = j - i;
			if (distance < minDistance)
			{
//				cout << "distance is now " << distance << endl;
				minDistance = distance;
				firstLoop = 1;
				secondLoop = 0;
			}
		}
	}
	
	// Checking first half
	for (k = i-1; k >= 0; k--)
	{
//		cout << "second loop i " << k << " keys is " << keys[k] << endl;
		if (keys[k] == 1)
		{
			distance = i - k;
//			cout << "distance is " << distance << endl;
			if (distance < minDistance)
			{
				minDistance = distance;
//				cout << "min is now " << minDistance << endl;
				firstLoop = 0;
				secondLoop = 1;
			}
		}
	}
	
	if (firstLoop)
	{
		for (k = i; k < i+minDistance; k++)
		{
//			cout << "opening " << k << endl;
			keys[k-1] = 1;
			keys[k+1] = 1;
		}
	}
	else if (secondLoop)
	{
		for (j = i; j > i-minDistance; j--)
		{
//			cout << "opening " << j << endl;
			keys[j-1] = 1;
			keys[j+1] = 1;
		}
	}
	
	return minDistance;
}

int minLockers(int balls[], int keys[], int n, int k, int b)
{
	int i;
	
	// Initialize table
	int *d = new int[b+1];
	d[0] = 0;
	
	for (i = 1; i <= n; i++)
	{
//		cout << "at " << i << " balls is " << balls[i-1] << " and keys is " << keys[i-1] << endl;
		if (balls[i-1] == 0)	// There is no ball
		{
//			cout << "There is no ball\n";
			d[i] = d[i-1];
		}
		else if (balls[i-1] == 1 && keys[i-1] == 0)	// There is a ball, but we don't have a key
		{
					
//			cout << "There is a ball but no key\n";
			int distance = dist(balls, keys, i-1, n);
//			cout << "Distance is " << distance << endl;
			d[i] = 1 + distance + d[i-distance];
		}
		else if (balls[i-1] == 1 && keys[i-1] == 1)	// There is a ball, but we have the key
		{
//			cout << "There is a ball and a key\n";
			d[i] = 1 + d[i-1];
		}
		else
		{
//			cout << "Something's wrong!\n";
		}
	}
	
	return d[n];
}

int main()
{
	int lockers[N];
	int keys[N];
	int balls[N];
	
	int i;
	for (i = 0; i < N; i++)
		keys[i] = 0;
	for (i = 0; i < N; i++)
		balls[i] = 0;
	
	keys[0] = 1;
	keys[7] = 1;
	
	balls[4] = 1;
	balls[3] = 1;
	
	int min = minLockers(balls, keys, N, K, B);
	cout << min << endl;
	
	return 0;
}