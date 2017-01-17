#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

void evolution() {
    int n; cin >> n;
    int q; cin >> q;

    vector<string> species_name(n);
    vector<long> species_age(n);
    map<string, int> species_keys;
    for (int i = 0; i < n; i++) {
        cin >> species_name[i];
        cin >> species_age[i];
        species_keys[species_name[i]] = i;
    }

    // Store the adjecency matrix
    vector<int> relations(n, -1);
    for (int i = 0; i < n - 1; i++) {
        string s; cin >> s;
        string p; cin >> p;
        int s_index = species_keys[s];
        int p_index = species_keys[p];

        relations[s_index] = p_index;
    }

    // Store queries
    vector<pair<int, long> > queries(q);
    for (int i = 0; i < n; i++) {
        string n; cin >> n;
        cin >> queries[i].second;
        queries[i].first = species_keys[n];
    }

    // Resolve each query
    for (int j = 0; j < n; j++) {
        int q_specie = queries[j].first;
        long q_age = queries[j].second;

        int specie_result = q_specie;
        while (true) {
            int upper_specie = relations[specie_result];
            if (upper_specie == -1 || species_age[upper_specie] > q_age) {
                break;
            }
            specie_result = upper_specie;
        }

        cout << species_name[specie_result];
        if (j == n - 1) {
            cout << endl;
        } else {
            cout << ' ';
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        evolution();
    }
}
