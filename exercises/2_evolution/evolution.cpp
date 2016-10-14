#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

void evolution() {
    int n; cin >> n;
    int q; cin >> q;

    // Store the names and respective ages
    map<string, int> species_age;
    map<string, string> species_relations;
    for (int i = 0; i < n; i++) {
        string key; cin >> key;
        int age; cin >> age;
        species_age[key] = age;
        species_relations[key] = "";
    }


    // Store the map with the relations
    for (int i = 0; i < n - 1; i++) {
        string s; cin >> s;
        string p; cin >> p;
        species_relations[s] = p;
    }

    // For each query
    for (int i = 0; i < q; i++) {
        string specie; cin >> specie;
        int limit_age; cin >> limit_age;

        int current_age = species_age[specie];
        string current_specie;
        string next_specie = specie;

        while (current_age <= limit_age) {
            //cout << current_age << " ";
            current_specie = next_specie;
            next_specie = species_relations[current_specie];
            if (next_specie == "") {
                break;
            }
            current_age = species_age[next_specie];
        }

        string con_str = i == n-1 ? "\n" : " ";
        cout << current_specie << con_str;

    }

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        evolution();
    }
}
