#include <bits/stdc++.h>

using namespace std;

// Structura pentru datele de input
struct Updates {
    long long pi;
    long long ui;
};

int compare(const void* a, const void* b) {
	const int* x = (int*) a;
	const int* y = (int*) b;

	if (*x > *y)
		return 1;
	else if (*x < *y)
		return -1;

	return 0;
}

long long solve(Updates *up, long long n, long long b) {
    long long costs = 0, result = 0;

    // Creez si aloc memeorie pentru sirul de sume partiale
    long long *part = new long long[n];

    // Sortez si pi-urile si ui-urile crescator
    qsort(up, n, sizeof(Updates), compare);

    // Setez sumele partiale
    part[0] = up[0].ui;

    for (int i = 1; i < n; i++)
		part[i] = part[i-1] + up[i].ui;

    /* Actualizez cheltuielile pana cand mai am buget, 
    daca cheltuielile sunt mai mare ca bugetul setez rezultatul conform formulei,
    si opresc loop-ul. La fel in unele cazuri furmula de calcuare a cheltuielilor 
    poate fi negativa ce strica implimentarea de aia verific daca nu e negativa. */
    for (int i = 0; i < n; i++) {
        if ((costs + part[i] * (up[i+1].pi - up[i].pi)) <= b &&
            (costs + part[i] * (up[i+1].pi - up[i].pi)) >= 0) {
            costs += part[i] * (up[i+1].pi - up[i].pi);
        } else {
            result = up[i].pi + ((b - costs) / part[i]);
            break;
        }
    }
    return result;
    free(part);
}

int main() {
    ifstream fin("crypto.in");
    ofstream fout("crypto.out");

    long long n, b;

    Updates *up;

    // Parsez datele, si aloc vectorulde structura Update
    fin >> n >> b;
    up = new Updates[n];

    for (int i = 0; i <= n; ++i) {
    	fin >> up[i].pi >> up[i].ui;
    }

    // Afisez rezultatul
    fout << solve(up, n, b);

    free(up);
    fin.close();
    fout.close();
    return 0;
}
