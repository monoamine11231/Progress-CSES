#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ll uint64_t


int main() {
	int a,b;
	scanf("%d %d\n",&a,&b);

	ll *dp = malloc(sizeof(ll) * (a+1) * (b+1));
	for (int i = 1; i <= a; ++i) {
		for (int j = 1; j <= b; ++j) {
			if (i == j) {
				dp[i*(b+1)+j] = 0;	
			} else {
				ll min_value = 500*500;
				for (int k = 1; k < i; ++k) {
					ll value = dp[k*(b+1)+j] + dp[(i-k)*(b+1)+j] + 1;
					if (value < min_value)
						min_value = value;
				}

				for (int k = 1; k < j; ++k) {
					ll value = dp[i*(b+1)+k] + dp[i*(b+1)+(j-k)] + 1;
					if (value < min_value)
						min_value = value;
				}

				dp[i*(b+1)+j] = min_value;
			}
			// printf("%d %d | %lu\n", i, j, dp[i*(b+1)+j]);
		}
	}

	printf("%lu\n", dp[(a+1)*(b+1)-1]);
	
	free(dp);
	return 0;
}
