#include <bits/stdc++.h>

using namespace std;

long long solve(long long *val, long long n, long long b) {
    // Initializez toate varibailele pe care le voi folosi
    long long costs = 0, result = 0, res = 0, pos = 0;
    long long pos_end = n - 1;
    long long min = val[0];
    long long min_end = val[n - 1];

    // Functie care geseste minmul dinte-un vector, de la 0 la n
    for (long long i = 0; i < n; i++) {
        if (val[i] < min) {
            pos = i;
            min = val[i];
        }
    }

    // Functia care gaseste minimul da la n la 0;
    for (long long i = (n - 2); i >= 0; i--) {
        if (val[i] < min_end) {
            pos_end = i;
            min_end = val[i];
        }
    }

    /* Urmatoarele doua conditii trateza cazurile cand
    minimul se afla la inceput sau la sfarsitul vectorului */
    if (pos == 0) {
        res += val[1] - min;
        val[1] = min;
    }

    if (pos_end == n - 1) {
        res += val[n - 2] - min_end;
        val[n - 2] = min_end;
    }

    /* Daca pozotiile lui min si min_end sunt aceleasi,
    adica primul si ultimul minim coincid setez variabilele
    intre doua minime egale acet minim */
    if (pos != pos_end) {
        for (long long i = pos + 1; i < pos_end; i++) {
            res += val[i] - min;
            val[i] = min;
        }
    }

    // Pana la minim fac componentele descrescatoare
    for (long long i = 0; i < pos; i++) {
        if (val[i] < val[i + 1]) {
            res += val[i + 1] - val[i];
            val[i + 1] = val[i];
        }
    }

    // Pana la minim fac componentele descrescatoare
    for (long long i = n - 1; i > pos_end; i--) {
        if (val[i] < val[i - 1]) {
            res += val[i - 1] - val[i];
            val[i - 1] = val[i];
        }
    }
    return res;
}

int main() {
    ifstream fin("valley.in");
    ofstream fout("valley.out");

    long long n, b;
    long long *val;

    fin >> n;
    val = new long long[n];

    for (long long i = 0; i <= n; ++i) {
    	fin >> val[i];
    }

    fout << solve(val, n, b);

    free(val);
    fin.close();
    fout.close();
    return 0;
}
