#include <bits/stdc++.h>

using namespace std;

int max(int a, int b) { return (a > b) ? a : b; }

int solve(int buget, int currVal[], int maxVal[],
                    int minVal[], int n, int maxLoss) {
    int l, i, w;

    /* Creez si aloc memorie pentru tabela tridimensionala
    conform restrictiilor care va contine raspunsurile pentru subprobleme */
    int ***K = new int**[n + 1];

    for (int i = 0; i <= n; i++) {
        K[i] = new int*[maxLoss + 1];
        for (int j = 0; j <= maxLoss; j++) {
            K[i][j] = new int[buget + 1];
        }
    }

    // Construisc tabela K in de jos in sus ()
    for (i = 0; i <= n; i++) {
        for (l = 0; l <= maxLoss; l++) {
            for (w = 0; w <= buget; w++) {
                // Caz de baza
                if (i == 0 || w == 0 || l == 0)
                    K[i][l][w] = 0;

                /* Aleg maximul dintre valoare noua si cea precedenta si il setez
                in celula respectiva actualizez maxLoss si bugetul */
                else if (currVal[i - 1] <= w &&
                        (currVal[i - 1] - minVal[i - 1]) <= l)
                    K[i][l][w] = max((maxVal[i - 1] - currVal[i - 1]) +
                            K[i - 1][l - (currVal[i - 1] - minVal[i - 1])]
                            [w - currVal[i - 1]],
                            K[i - 1][l][w]);
                else
                    K[i][l][w] = K[i - 1][l][w];
            }
        }
    }
    // Intorc valoare de pe ultima pozitie care e cea mia optima
    return K[n][maxLoss][buget];
}

int main() {
    ifstream fin("stocks.in");
    ofstream fout("stocks.out");

    // Parsez datele si afisez rezultatul
    int n, buget, maxLoss;

    fin >> n >> buget >> maxLoss;

    int *currVal = new int[n];
    int *maxVal = new int[n];
    int *minVal = new int[n];

    for (int i = 0; i <= n; ++i) {
    	fin >> currVal[i] >> minVal[i] >> maxVal[i];
    }

    int x = solve(buget, currVal, maxVal, minVal, n, maxLoss);

    fout << x;

    free(currVal);
    free(maxVal);
    free(minVal);
    fin.close();
    fout.close();
    return 0;
}
