#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<double>> mk(n, vector<double>(3, 0));
    for (int i = 0; i < n; ++i) scanf("%lf", &mk[i][0]);
    for (int i = 0; i < n; ++i) {
        scanf("%lf", &mk[i][1]);
        mk[i][2] = mk[i][1] / mk[i][0];
    }
    sort(mk.begin(), mk.end(), [](vector<double>& m1, vector<double>& m2) { return m1[2] > m2[2]; });
    double res = 0;
    for (auto& iter : mk) {
        if (m > iter[0]) {
            m -= iter[0];
            res += iter[1];
        } else {
            res += m * iter[2];
            break;
        }
    }
    printf("%.2f", res);
    return 0;
}
