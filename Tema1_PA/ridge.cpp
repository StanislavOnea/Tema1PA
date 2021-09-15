#include <bits/stdc++.h>

using namespace std;

long long solve(long long height[], long long cost[], long long N) {
    // Creez tabela dp
    vector<vector<long long> > dp(N, vector<long long>(3));

    // Caz de baza nu decrementez primul elem
    dp[0][0] = 0;

    /* In acest if si anteriore verifc daca valorile nu
    devin mai mici ca 0 confirm enutului. Setez costurile
    in table pentru decrementare cu 1 si 2 */
    if (height[0] - 1 >= 0)
    dp[0][1] = cost[0];

    if (height[0] - 2 >= 0)
    dp[0][2] = cost[0] * 2;

    for (long long i = 1; i < N; i++) {
        for (long long j = 0; j < 3; j++) {
            // Setez minul extrem de mare
            long long minimum = LLONG_MAX;

            // Daca elem curent nu este egal cu precedentul nedecrementat
            if (height[i] - j != height[i - 1]) {
                minimum = min(minimum, dp[i - 1][0]);
            }

            // Daca elem curent nu este egal cu precedentul decrementat cu 1
            if (height[i] - j != height[i - 1] - 1 && height[i - 1] - 1 >= 0) {
                minimum
                    = min(minimum,
                          dp[i - 1][1]);
            }

            // Daca elem curent nu este egal cu precedentul decrementat cu 2
            if (height[i] - j != height[i - 1] - 2 && height[i - 1] - 2 >= 0) {
                minimum
                    = min(minimum,
                          dp[i - 1][2]);
            }

            // Salveaza minnul dupa toate if-urile
            dp[i][j] = j * cost[i] + minimum;
        }
    }

    long long ans = LLONG_MAX;

    // Gaesec costul minim
    for (long long i = 0; i < 3; i++)
        ans = min(ans, dp[N - 1][i]);

    return ans;
}

int main() {
    ifstream fin("ridge.in");
    ofstream fout("ridge.out");

    // Parses si afisez rezultatul
    long long n;
    long long *height;
    long long *cost;

    fin >> n;

    height = new long long[n];
    cost = new long long[n];

    for (long long i = 0; i < n; i++) {
        fin >> height[i] >> cost[i];
    }

    fout << solve(height, cost, n);

    free(height);
    free(cost);
    fin.close();
    fout.close();
    return 0;
}
