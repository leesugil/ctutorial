#include <stdio.h>

#define	MAX	26

main() {
	int c, i, j, other;
	int freq[MAX];

	other = 0;
	for (i = 0; i < MAX; ++i) {
		freq[i] = 0;
	}

	while ((c = getchar()) != EOF) {
		if (c >= 'a' && c <= 'z') {
			++freq[c - 'a'];
		}
		else {
			++other;
		}
	}

	for (i = 0; i < MAX; ++i) {
		printf("%c: ", 'a' + i);
		printf("%d", freq[i]);
		for (j = 0; j < freq[i]; ++j) {
			printf("*");
		}
		printf("\n");
	}
	printf("other: %d\n", other);
}
