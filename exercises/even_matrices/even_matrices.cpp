#include <vector>
#include <iostream>

using namespace std;


// Implementation in O(n^3) time
void do_even_count_matrices(){
    int n; cin >> n;
    vector<vector<int> > M(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> M[i][j];

    // Precompute pMi's
    vector<vector<int> > pM(n+1, vector<int>(n+1));
    for (int i  = 0; i <= n; i++) {
        pM[i][0] = 0;
        pM[0][i] = 0;
     }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            pM[i][j] = pM[i-1][j] + pM[i][j-1] - pM[i-1][j-1] + M[i-1][j-1];
        }
    }

    int counter = 0;
    for (int i1 = 1; i1 <= n; i1++) {
        for (int i2 = i1; i2 <= n; i2++) {
            // We reduce the probelm to one dimension
            vector<int> S(n+1);     // Do even pairs on array S
            vector<int> pS(n+1);    // pS contains partial sums of S
            pS[0] = 0;
            for (int k = 1; k <= n; k++) {
                S[k] = pM[i2][k] - pM[i2][k-1] - pM[i1-1][k] + pM[i1-1][k-1];
                pS[k] = pS[k-1] + S[k];
            }

            // Do even pairs O(n) algorithm on array S
            int onedim_sol = 0;
            int even = 0, odd = 0;
            for (int j = 1; j <=n; j++) {
                // even = # of partial sums of array (S[1], ..., S[j-1]) that are even.
                // odd = # of partial sums of array (S[1], ..., S[j-1]) that are odd.
                if (pS[j] % 2 == 0){
                    onedim_sol +=  even + 1;
                    even++;
                }
                else {
                    onedim_sol += odd;
                    odd++;
                }
            }
            counter += onedim_sol;
        }
    }

    cout << counter << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        do_even_count_matrices();
    }
}
