#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ll uint64_t

void list_max(ll *list, ll n, ll *max_ret, ll *index_ret) {
	ll index = 0;
	ll max = list[0];
	for (ll i = 1; i < n; ++i) {
		if (list[i] > max) {
			max = list[i];
			index = i;
		}
	}

	if (max_ret)	*max_ret = max;
	if (index_ret)	*index_ret = index;
}

int main() {
	int n,m;
	scanf("%d\n%d\n", &n, &m);

	ll *arr1 = malloc(sizeof(ll) * (n+1));
	ll *arr2 = malloc(sizeof(ll) * (m+1));

	for (int i = 1; i <= n; ++i) {
		scanf("%lu ", &arr1[i]);
	}

	for (int i = 1; i <= m; ++i) {
		scanf("%lu ", &arr2[i]);
	}

	ll *t = calloc((n+1)*(m+1),sizeof(ll));
	for (int row = 1; row <= m; ++row) {
		for (int col = 1; col <= n; ++col) {
			if (arr1[col] == arr2[row]) {
				t[row*(n+1)+col] = 1 + t[(row-1)*(n+1)+(col-1)];
			} else {
				ll values[2] = {
					t[(row-1)*(n+1)+col],
					t[row*(n+1)+(col-1)]
				};
				list_max(&values[0], 2, &t[row*(n+1)+col], NULL);
			}
		}
	}

	// print
// 	printf("| |");
// 	for (int i = 1; i <= n; ++i) {
// 		printf("%ld|",arr1[i]);
// 	}
// 	printf("\n");
// 
// 	for (int j = 1; j <= m; ++j) {
// 		printf("|%ld|",arr2[j]);
// 		for (int i = 1; i <= n; ++i) {
// 			printf("%ld|",t[j*n+i]);
// 		}
// 		printf("\n");
// 	}

	ll length = t[(n+1)*(m+1)-1];
	ll *stack = malloc(sizeof(ll) * length);
	ll stack_size = length;


	ll current_row = m, current_col = n;
	while (stack_size > 0) {
		if (arr1[current_col] == arr2[current_row]) {
			stack[--stack_size] = arr1[current_col];
			current_row -= 1;
			current_col -= 1;
			continue;
		}
	
		ll values[2] = {
			t[(current_row-1)*(n+1)+current_col],	
			t[current_row*(n+1)+(current_col-1)]
		};

		ll max, index;
		ll assignment_list[2][2] = {
			{current_row-1, current_col},
			{current_row, current_col-1}
		};
		list_max(&values[0], 2, &max, &index);

		current_row = assignment_list[index][0];
		current_col = assignment_list[index][1];
	}

	printf("%ld\n", length);
	for (ll i = 0; i < length; ++i)
		printf("%ld ", stack[i]);
	printf("\n");


	free(stack);
	free(arr1);
	free(arr2);
	free(t);

	return 0;
}
