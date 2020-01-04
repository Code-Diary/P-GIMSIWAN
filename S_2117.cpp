#include <stdio.h>
#include <vector>

using namespace std;

int cost(int K) {
	return K * K + (K - 1)*(K - 1);
}

int length(pair<int, int> loc1, pair<int, int> loc2) {
	return abs(loc1.first - loc2.first) + abs(loc1.second - loc2.second);
}

int check(vector <pair<int, int>> house, pair<int, int> loc, int N, int M) {

	int k = 2;
	int answer = 1;

	while (k<=N + 1) {
		int count = 0;
		
		for (int i = 0; i < house.size(); i++) {
			if (length(house[i], loc) < k) count += 1;
		}
		if (count * M - cost(k) >= 0) answer = count;
		k++;
	}

	return answer;
}

int main(void) {

	int N, M;
	vector<pair<int, int>> house;

	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int input;
			scanf("%d", &input);
			if (input == 1) house.push_back(make_pair(i, j));
		}
	}

	int k = 1;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int t = check(house, make_pair(i, j), N, M);
			if(k < t) k = t;
		}
	}

	printf("%d\n", k);

	return 0;
}