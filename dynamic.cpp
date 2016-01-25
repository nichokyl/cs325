#include <iostream>
#include <cstdio>
#include <cstring>

#define N 67
#define K 16
#define B 14
#define LINE1 40
#define LINE2 41

using std::cout;
using std::endl;

int dist(int *lockers, int *balls, int *keys, int i, int n)
{
	int j, k, idx;
	int distance, minDistance = n;
	int firstLoop, secondLoop;
	
//	cout << "in dist " << minDistance << " " << i << endl;
	
	// Checking after i
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
				break;
			}
		}
	}
	
	// Checking before i
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
				break;
			}
		}
	}
	
	if (firstLoop)
	{
		for (k = j; k >= i; k--)
		{
//			cout << "opening " << k << endl;
			lockers[j] = 1;
			keys[k-1] = 1;
			keys[k+1] = 1;
		}
	}
	else if (secondLoop)
	{
		for (j = k; j <= i; j++)
		{
//			cout << "opening " << j << endl;
			lockers[j] = 1;
			keys[j-1] = 1;
			keys[j+1] = 1;
		}
	}
	
/*	for (int i = 0; i < N; i++)
		cout << lockers[i] << " ";
	cout << endl;
*/
	
	return minDistance;
}

int minLockers(int *lockers, int *balls, int *keys, int n, int k, int b)
{	
	// Initialize table
	int *d = new int[n+1];
	d[0] = 0;
	
	for (int i = 1; i <= n; i++)
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
			int distance = dist(lockers, balls, keys, i-1, n);
//			cout << "Distance is " << distance << endl;
			d[i] = 1 + distance + d[(i-distance)];
		}
		else if (balls[i-1] == 1 && keys[i-1] == 1)	// There is a ball, but we have the key
		{
//			cout << "There is a ball and a key at index" << i << endl;
			if (lockers[i-1] == 1)	// Already opened
			{
//				cout << "Already opened\n";
				d[i] = d[i-1];
			}
			else	// Not yet opened
			{
//				cout << "Not yet opened\n";
				d[i] = 1 + d[i-1];
				lockers[i-1] = 1;
				keys[(i-1)-1] = 1;
				keys[(i-1)+1] = 1;
			}
		}
		else
		{
//			cout << "Something's wrong!\n";
		}
		
//		cout << endl;
	}
/*	for (int i = 0; i <= N; i++)
		cout << d[i] << " ";
	cout << endl;
*/
	
	return d[n];
}

int main()
{
	int *lockers = new int[N];
	int *keys = new int[N];
	int *balls = new int[N];
	
	for (int i = 0; i < N; i++)
		lockers[i] = 0;
	for (int i = 0; i < N; i++)
		keys[i] = 0;
	for (int i = 0; i < N; i++)
		balls[i] = 0;
	
	// Read input
	char line[1024];
	int val, count = 1;
	FILE *fp = fopen("dp.txt", "r");

	for (int i = 1; i < LINE1; i++)
		fgets(line, 1024, fp);
	
	for (int i = 0; i < K; i++)
	{
		fscanf(fp, "%d ", &val);
//		cout << val << " ";
		keys[val-1] = 1;
	}
//	cout << endl;
	
//	cout << "done reading keys" << endl;
	
	fp = fopen("dp.txt", "r");
	for (int i = 1; i < LINE2; i++)
		fgets(line, 1024, fp);
	
//	cout << line << endl;
//	cout << "now at line " << LINE2 << endl;
	
	for (int i = 0; i < B; i++)
	{
		fscanf(fp, "%d ", &val);
//		cout << val << " ";
		balls[val-1] = 1;
	}
//	cout << endl;
	
/*	for (int i = 0; i < N; i++)
		cout << keys[i] << " ";
	cout << endl;
	
	for (int i = 0; i < N; i++)
		cout << balls[i] << " ";
	cout << endl;
*/

	fclose(fp);
	
	int min = minLockers(lockers, balls, keys, N, K, B);
	cout << min << endl;
/*	for (int i = 0; i < N; i++)
		cout << lockers[i] << " ";
	cout << endl;
*/
	
	return 0;
}
