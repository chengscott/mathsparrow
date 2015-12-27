#include "sparrow.h"

// string map
const char* mahjong[34] = {
	"1T", "2T", "3T", "4T", "5T", "6T", "7T", "8T", "9T",
	"1S", "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S",
	"1W", "2W", "3W", "4W", "5W", "6W", "7W", "8W", "9W",
	"DONG", "NAN", "XI", "BEI",
	"ZHONG", "FA", "BAI"
};
// count for each mahjong
int cnt[34];

int convert(const char *s) {
    int i;
	for (i = 0; i < 34; ++i)
		if (s == mahjong[i]) return i;
	return -1;
}

int search(int dep) {
    int i;
	for (i = 0; i < 34; ++i)
		// triplet
		if (cnt[i] >= 3) {
			if (dep == 3) return 1;
			cnt[i] -= 3;
			if (search(dep + 1)) return 1;
			cnt[i] += 3;
		}
	for (i = 0; i <= 24; ++i)
		if (i % 9 <= 6 && cnt[i] > 0 && cnt[i + 1] > 0 && cnt[i + 2] > 0) {
			// sequence
			if (dep == 3) return 1;
			--cnt[i], --cnt[i + 1], --cnt[i + 2];
			if (search(dep + 1)) return 1;
			++cnt[i], ++cnt[i + 1], ++cnt[i + 2];
		}
	return 0;
}

int check() {
    int i;
	for (i = 0; i < 34; ++i) {
		// eye
		if (cnt[i] >= 2) {
			cnt[i] -= 2;
			if (search(0)) return 1;
			cnt[i] += 2;
		}
	}
	return 0;
}

int test(const int mj[13], int *list) {
	int i, j, count = 0;//, mj[13];
	// for (i = 0; i < 13; ++i)
	//	mj[i] = convert(s[i]);
	for (i = 0; i < 34; ++i) {
		memset(cnt, 0, sizeof(cnt));
		for (j = 0; j < 13; ++j) ++cnt[mj[j]];
		// kong
		if (cnt[i] >= 4) continue;
		++cnt[i];
		if (check()) list[count++] = i;
		--cnt[i];
	}
	return count;
}
