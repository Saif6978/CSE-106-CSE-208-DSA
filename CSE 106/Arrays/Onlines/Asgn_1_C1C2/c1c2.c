#include <stdio.h>
#include <stdlib.h>

void findSecondLargest(int arr[], int n) {
    if (n < 2) {
        printf("Invalid input\n");
        return;
    }
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    int second = 0;
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < max) {
            if (!found || arr[i] > second) {
                second = arr[i];
                found = 1;
            }
        }
    }

    if (!found) {
        printf("Second largest element not found\n");
    } else {
        printf("%d\n", second);
    }
}

int main() {
	int T, t, n, i, second;
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
		// Find and print the second largest element
		findSecondLargest(arr, n);
		free(arr);
	}
	// Close the file streams
	fclose(fin);
	fclose(fout);
	return 0;
}

