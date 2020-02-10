#include <tools.h>
int filled = 0;
int sorted[array_len];
// C substring function definition
void substring(char s[], char sub[], int p, int l) {
	int c = 0;

	while (c < l) {
		sub[c] = s[p + c];
		c++;
	}
	sub[c] = '\0';
}

int sonar_filtering(int ds, int dsarray[array_len], int i) {
	//fill array with values
	if (i <= array_len) {
		dsarray[i] = ds;
		if (filled == 1) {
			//start filtering as soon as 5 values are written into the array
			for (int i = 0; i <= array_len; i++) {
				sorted[i] = dsarray[i];
			}
			Array_sort(sorted, array_len);
			ds = Find_median(sorted, array_len);

		}
		i++;
	} else {
		i = 0;
		filled = 1;
	}
	return ds, i;
}

// function to sort the array in ascending order
void Array_sort(int *array, int n) {
	// declare some local variables
	int i = 0, j = 0, temp = 0;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n - 1; j++) {
			if (array[j] > array[j + 1]) {
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}

	printf("\nThe array after sorting is..\n");
	for (i = 0; i < n; i++) {
		printf("\narray_1[%d] : %d", i, array[i]);
	}
}

// function to calculate the median of the array
int Find_median(int array[], int n) {
	float median = 0;

	// if number of elements are even
	if (n % 2 == 0)
		median = (array[(n - 1) / 2] + array[n / 2]) / 2.0;
	// if number of elements are odd
	else
		median = array[n / 2];
	return (int) median;
}

int ds_true(ds) {
	ds = ds * ds_multiplier;
	return ds;
}

void cell_followR() {
	ds = ds_true(cell/2);
}

