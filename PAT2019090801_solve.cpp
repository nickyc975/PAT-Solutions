#include<bits/stdc++.h>
#define FI first
#define SE second

using namespace std;
typedef long long ll;
typedef pair<int, int> P;
const int maxn = 10 + 777;

int k, m;
int a[maxn];
bool okk = false;
set<P> ans;

int num(int n) {
    int res = 0;
    while(n) {
        res += (n % 10);
        n /= 10;
    }
    return res;
}
bool isp(int n) {
    if(n == 0 || n == 1) return false;
    for(int i = 2; i*i <= n; ++i) {
        if(n%i == 0) return false;
    }
    return true;
}
bool ok() {
    int n = 0;
    for(int i = 1; i <= k; ++i) {
        n = n*10 + a[i];
    }
    //cout << n << endl;
    int t1 = num(n);
    if(t1 != m) return false;
    int t2 = num(n+1);
    int t = __gcd(t1, t2);
    if(t > 2 && isp(t)){
        ans.insert(P(t2, n));
        //printf("%d %d\n", t2, n);
        return true;
    }
    return false;
}
int sum(int t) {
    int res = 0;
    for(int i = 1; i <= t; ++i) {
        res += a[i];
    }
    return res;
}
void work(int cnt) {
    //cout << cnt << endl;
    if(cnt == k-1) {
        if(ok()) {
            okk = true;
        }
        return;
    }
    for(int i = 0; i <= 9; ++i) {
        if(i == 0 && cnt == 1) continue;
        a[cnt] = i;
        if(sum(cnt) > (m-18)) break;
        work(cnt+1);
    }
    return;
}
void solve() {
    scanf("%d%d", &k, &m);
    a[k-1] = a[k] = 9;
    okk = false;
    ans.clear();
    work(1);
    for(auto i : ans) {
        printf("%d %d\n", i.FI, i.SE);
    }
    if(!okk)
        puts("No Solution");
    return;
}
int main() {
    int T; scanf("%d", &T);
    for(int i = 1; i <= T; ++i) {
        printf("Case %d\n", i);
        solve();
    }

    return 0;
}