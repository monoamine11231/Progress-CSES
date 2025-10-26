#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define u64 uint64_t

u64 lu[1000000] = {0};


int main() {
	int T;
	scanf("%d\n", &T);

	for (int i = 0; i < T; ++i) {
		int N;
		scanf("%d\n", &N);

		if (N == 1) {
			printf("%d\n", 2);
			continue;
		}

		if (lu[N-1] != 0) {
			printf("%ld\n", lu[N-1]);
			continue;
		} 

		// `categories` track the count of possible towers that aren't finished
		u64 categories[5] = {2, 1, 1, 1, 1};
		for (int j = 1; j < N-1; ++j) {
			u64 categories_new[5] = {0};
			categories_new[0] = categories[0] * 2 + categories[1] + categories[2] + categories[3] + categories[4];
			categories_new[1] = categories[0] + categories[1];
			categories_new[2] = categories[0] + categories[2] + categories[3] + categories[4];
			categories_new[3] = categories[0] + categories[2] + categories[3] + categories[4];
			categories_new[4] = categories[0] + categories[2] + categories[3] + categories[4];

			categories_new[0] %= 1000000007;
			categories_new[1] %= 1000000007;
			categories_new[2] %= 1000000007;
			categories_new[3] %= 1000000007;
			categories_new[4] %= 1000000007;
		

			memcpy(&categories[0], &categories_new[0], sizeof(u64) * 5);
		}

		u64 count = categories[0] * 2 + categories[1] + categories[2] + categories[3] + categories[4];
		count %= 1000000007;
		lu[N-1] = count;
		
		printf("%ld\n", count);
	}

	return 0;
} 
