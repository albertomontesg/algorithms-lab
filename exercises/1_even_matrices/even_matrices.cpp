#include <vector>
#include <iostream>

using namespace std;

void do_even_count_matrices(){
    int n; cin >> n;
    vector<vector<int> > bits(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> bits[i][j];

    // Precompute Si's
    vector<vector<int> > S(n, vector<int>(n));
    for (int j = 0; j < n; j++) {
        S[0][j] = bits[0][j];
        for (int i = 1; i < n; i++) {
            S[i][j] = S[i-1][j] + bits[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j++) {
            S[i][j] += S[i][j-1];
        }
    }

    // Compute Evens and Odds at the S matrix
    vector<vector<int> > evens(n, vector<int>(n)), odds(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        if (bits[i][0] == 0) {
            evens[i][0] = 1;
            odds[i][0] = 0;
        } else {
            evens[i][0] = 0;
            odds[i][0] = 1;
        }
        for (int j = 1; j < n; j++) {
            evens[i][j] = evens[i][j-1];
            odds[i][j] = odds[i][j-1];
            if (S[i][j] % 2 == 0)
                evens[i][j]++;
            else
                odds[i][j]++;
        }
    }
    // for (int i = 0; i < n; i++) {
    //     for (int j = 1; j < n; j++) {
    //         evens[i][j] += evens[i][j-1];
    //         odds[i][j] += odds[i][j-1];
    //     }
    // }

    vector<vector<int> > pair(n, vector<int>(n)), impair(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        if (S[i][0] % 2 == 0) {
            pair[i][0] = 1;
            impair[i][0] = 0;
        }
        else {
            pair[i][0] = 0;
            impair[i][0] = 1;
        }
        for (int j = 1; j < n; j++) {
            if (S[i][j] % 2 == 0) {
                pair[i][j] = evens[i][j-1];
                impair[i][j] = odds[i][j-1];
            } else {
                pair[i][j] = odds[i][j-1];
                impair[i][j] = evens[i][j-1];
            }
        }
    }
    for (int j = 0; j < n; j++) {
        for (int i = 1; i < n; i++) {
            pair[i][j] += pair[i-1][j];
            impair[i][j] += impair[i-1][j];
        }
    }

    int counter = 0;
    for (int j = 0; j < n; j++) {
        counter += pair[0][j];
        for (int i = 1; i < n; i++) {
            counter += pair[i][j] + pair[i-1][j];
            counter += impair[i][j] + impair[i-1][j];
        }
    }



    // Brute force
    // int counter = 0;
    // for (int i2 = 0; i2 < n; i2++) {
    //     for (int j2 = 0; j2 < n; j2++) {
    //         for (int i1 = 0; i1 <= i2; i1++) {
    //             for (int j1 = 0; j1 <= j2; j1++) {
    //                 int sum = 0;
    //                 if (i1 > 0 && j1 > 0)
    //                     sum = S[i2][j2] - S[i2][j1-1] - S[i1-1][j2] + S[i1-1][j1-1];
    //                 else if (i1 > 0)
    //                     sum = S[i2][j2] - S[i1-1][j2];
    //                 else if (j1 > 0)
    //                     sum = S[i2][j2] - S[i2][j1-1];
    //                 else
    //                     sum = S[i2][j2];
    //
    //                 if (sum % 2 == 0)
    //                     counter++;
    //             }
    //         }
    //     }
    // }

    cout << counter << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        do_even_count_matrices();
    }
}
