#include <stdio.h>
#include <stdlib.h>

void maxTripletSum(int arr[], int n) {
	// Your code here 
	if (n < 3) {
        printf("Invalid input\n");
        return;
    }

    int best = 0;
    long long maxSum = (long long)arr[0] + arr[1] + arr[2];

    for (int i = 1; i + 2 < n; i++) {
        long long sum = (long long)arr[i] + arr[i + 1] + arr[i + 2];
        if (sum >= maxSum) {
            maxSum = sum;
            best = i;
        }
    }

    printf("%d %d %d\n", arr[best], arr[best + 1], arr[best + 2]);
}

int main() {
	int T, t, n, i;
	int *arr;
	FILE *fin, *fout;
	// Redirect input and output streams
	fin  = freopen("input.txt", "r", stdin);
	fout = freopen("output.txt", "w", stdout);

	// Input the number of test cases
	scanf("%d", &T);

	for (t = 0; t < T; t++) {
		// Input the size of  the array
		scanf("%d", &n);
		// Dynamically allocate the size of the array
		arr = (int *)malloc(n * sizeof(int));
		// Input the elements of the array
		for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		}
		// Find and print the max-triplet
		maxTripletSum(arr, n);
		free(arr);
	}
	// Close the file streams
	fclose(fin);
	fclose(fout);
	return 0;
}

