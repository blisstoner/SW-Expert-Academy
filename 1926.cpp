#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <functional>
#include <iostream>
#include <tuple>
#pragma warning(disable:4996)
#pragma comment(linker, "/STACK:336777216")
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef tuple<int, int, int> ti3;
typedef tuple<int, int, int, int> ti4;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int ddx[8] = { 0,0,1,1,1,-1,-1,-1 }, ddy[8] = { 1,-1,1,0,-1,1,0,-1 };
ll MOD = 1000000000;
ll POW(ll a, ll b, ll MMM = MOD) { ll ret = 1; for (; b; b >>= 1, a = (a*a) % MMM)if (b & 1)ret = (ret*a) % MMM; return ret; }
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { if (a == 0 || b == 0)return a + b; return a*(b / gcd(a, b)); }
bool OOB(int x, int y, int N, int M) { return 0 > x || x >= N || 0 > y || y >= M; }
#define X first
#define Y second
#define rep(i,a,b) for(int i = a; i < b; i++)
#define pb(x) push_back(x)
#define all(x) (x).begin(), (x).end()
void print_num(int a) {
	int a_cp = a;
	int cnt = 0;
	while (a) {
		if (a % 10 == 3 || a % 10 == 6 || a % 10 == 9) cnt++;
		a /= 10;
	}
	if (!cnt) {
		printf("%d ", a_cp);
		return;
	}
	while (cnt--)
		printf("-");
	printf(" ");
}
int main(void) {
	int N;
	scanf("%d", &N);
	rep(i, 1, N + 1)
		print_num(i);
}
