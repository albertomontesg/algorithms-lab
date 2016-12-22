#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;


// Binary Search
int binary(int b, vector<int>& path, vector<int>& age) {
    int l = 0; int r = path.size()-1;
    while(l != r){
        int m = (l+r)/2;
        if (age[path[m]] > b) l = m+1; else r = m;
    }
    return path[l];
}

// DFS
void dfs(int u, vector<vector<int> >& tree, vector<int>& path, vector<vector<pair<int,int> > >& query, vector<int>& result, vector<int>& age) {
    // process queries
    for (int i = 0; i < query[u].size(); i++) {
        result[query[u][i].second] = binary(query[u][i].first,path,age);
    }

    // continue search
    for (int i = 0; i < tree[u].size(); ++i){
        int v = tree[u][i];
        path.push_back(v);
        dfs(v,tree,path,query,result,age);
    }
    path.pop_back();
}

void evolution() {
    int n, q; cin >> n >> q;

    // Store the names and respective ages
    unordered_map<string, int> species_to_index;
    vector<string> species(n);
    vector<int> age(n);
    string name;
    for (int i = 0; i < n; i++) {
        cin >> name;
        species_to_index[name] = i;
        species[i] = name;
        cin >> age[i];
    }

    // Find root
    int root = max_element(age.begin(), age.end()) - age.begin();

    // Read tree
    vector<vector<int> > tree(n);
    string child, parent;
    for (int i = 0; i < n - 1; i++) {
        cin >> child >> parent;
        tree[species_to_index[parent]].push_back(species_to_index[child]);
    }

    // Read queries: for each species store a vector of queries consisting of the age b and the
    // index of the query i
    vector<vector<pair<int, int> > > query(n);
    for (int i = 0; i < q; i++) {
        cin >> name;
        int b; cin >> b;
        query[species_to_index[name]].push_back(make_pair(b, i));
    }

    // Process queries in one tree transversal
    vector<int> path; path.push_back(root);
    vector<int> result(q);
    dfs(root, tree, path, query, result, age);



    // Output result
    for (int i = 0; i < q; i++) {
        cout << species[result[i]];
        if ( i < q - 1 ) cout << " ";
    }
    cout << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        evolution();
    }
}
