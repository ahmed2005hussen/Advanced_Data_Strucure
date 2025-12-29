#include <iostream>
#include <vector>

using namespace std ;

class DisjointSet{
private:

    int *array ;
    int size ;
public:

    DisjointSet(int n ){
        size = n+1;
        array = new int[size];

        for(int i = 0 ; i < size; i++){
            array[i] = -1;
        }
    }

    int find(int n){

        while(true){
            int index = array[n];
            if(index == -1){
                return n;
            }
            n = index;
        }
    }

    void Union(int n , int m ){

        int rootN = find(n);
        int rootM = find(m);

        if(rootN == rootM){
            return;
        }
        array[rootM] = rootN;
    }

    ~DisjointSet(){
    delete []array;
    }
};

void solve(){

    int v ;
    int e ;

    cin>>v>>e;

    vector<vector<int>> mst(e , vector<int>(3,0));

    for(int i = 0 ; i< e ;i++){
        int a , b ,c;
        cin>> a >> b >> c;

        mst[i][0] = a ;
        mst[i][1] = b ;
        mst[i][2] = c ;
    }

    DisjointSet d(v);

    vector<bool> selected(e, false);
    int countMin = 0 ; 
    for(int i = 0 ; i<v-1 ;i++){

        int min = INT_MAX;

        int select = 0 ;
        int u ;
        int V ;
        for(int j = 0 ; j < mst.size(); j++){

            if(!selected[j] && (d.find(mst[j][0]) != d.find(mst[j][1]) )
                    && mst[j][2] < min){

                    min = mst[j][2];
                    u =mst[j][0];
                    V =mst[j][1];

                    select = j ;
            }
        }

        d.Union(u,V);
        countMin += min;
        selected[select] = true;
    }

    cout<<"MST: "<< countMin;
}

int main() {

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    long long tc = 1 ;

    while(tc--){
        solve();
    }

    return 0;
}
