#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAX_LEN = 51;

//y, x, width, height
int cache[MAX_LEN][MAX_LEN][MAX_LEN][MAX_LEN];
int chocolate[MAX_LEN][MAX_LEN];
int subsum[MAX_LEN][MAX_LEN];

int raisin_sum(int y, int x, int width, int height) {
	const int& y2 = y+height-1, x2=x+width-1, y1=y, x1=x;

	return subsum[y2][x2]
		- subsum[y2][x1-1]
		- subsum[y1-1][x2]
		+ subsum[y1-1][x1-1];
}

int raisin(int y, int x, int width, int height) {
	//base
	if (width == 1 && height == 1) return 0;

	int& ret = cache[y][x][width][height];
	if (ret != -1) return ret;
	ret = INF;

	//가로로 자르기
	for (int cut_height = 1; cut_height < height; ++cut_height) {
		ret = min(
			ret,
			raisin(y, x, width, cut_height) + raisin(y+cut_height, x, width, height-cut_height) + raisin_sum(y, x, width, height)
		);
	}

	//세로로 자르기
	for (int cut_width = 1; cut_width < width; ++cut_width) {
		ret = min(
			ret,
			raisin(y, x, cut_width, height) + raisin(y, x+cut_width, width-cut_width, height) + raisin_sum(y, x, width, height)
		);
	}

	return ret;
}


int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	int test_case;
	int T;
	int n, m;

	cin >> T;


	for (test_case = 1; test_case <= T; ++test_case)
	{
		memset(cache, -1, sizeof(cache));
		memset(subsum, 0, sizeof(subsum));

		cin >> n >> m;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cin >> chocolate[i][j];
			}
		}


		//부분합 구하기
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				subsum[i][j] = (j == 0 ? chocolate[i][j] : subsum[i][j - 1] + chocolate[i][j]);
	
		for (int i = 1; i < n; ++i)
			for (int j = 0; j < m; ++j)
				subsum[i][j] = subsum[i - 1][j] + subsum[i][j];

		cout << "#" << test_case << " " << raisin(0, 0, m, n) << "\n";
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}