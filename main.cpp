#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <set>
#include <iostream>
using namespace std;

#define MAX 21
int n;
double m[MAX][MAX];
double min_dist[MAX];
int pre[MAX];

void print_matrix(){
    printf("%d\n",n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%f\t", m[i][j]);
        }
        printf("\n");
    }
}


int main() {
    set<int> s1;
    double rate; 
    while(scanf("%d",&n)!=EOF){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if (i == j) {
                    m[i][j] = 0.0;
                }else {
                    scanf("%lg",&rate);
                    //m[i][j] = rate;
                    m[i][j] = -log(rate);
                }
            }
        }
        print_matrix();
        int source = 0;
        for(int i = 0;i<n;i++){
            min_dist[i] = DBL_MAX;
            pre[i] = -1; 
        }
        min_dist[source] = source;


        // 'Relax edges |V-1| times'

        for (int i =0; i<n-1; i++){
            //printf("Interação: %d\n",i);
            for (int source_curr=0; source_curr<n; source_curr++){
                //printf("source_curr: %d\n",source_curr);
                for (int dest_curr=0; dest_curr<n; dest_curr++){
                    //printf("dest_curr: %d\n",dest_curr);
                    if (min_dist[dest_curr] > min_dist[source_curr] + m[source_curr][dest_curr]){
                        min_dist[dest_curr] = min_dist[source_curr] + m[source_curr][dest_curr];
                        pre[dest_curr] = source_curr;
                       /*
                        printf("min_dist\n");
                        for(int i = 0;i<n;i++){
                            printf("%lg\t",min_dist[i]);
                        }
                        printf("\n");

                        printf("pre\n");
                        for(int i = 0;i<n;i++){
                            printf("%d\t",pre[i]);
                        }
                        printf("\n");
                        */
                    }
                }
            }
        }
        
        
        // if we can still relax edges, then we have a negative cycle

        bool has_cycle = false; 
        for (int source_curr=0; source_curr<n; source_curr++){
            for (int dest_curr=0; dest_curr<n;dest_curr++){
                if (min_dist[dest_curr] > min_dist[source_curr] + m[source_curr][dest_curr]){
                    // negative cycle exists, and use the predecessor chain to print the cycle
                    has_cycle = true; 
                    s1.clear();
                    s1.insert(source_curr);
                    s1.insert(dest_curr);
                    
                    while (s1.find(pre[source_curr]) != s1.end()){
                        s1.insert(pre[source_curr]);
                        source_curr = pre[source_curr];
                    }
                    s1.insert(pre[source_curr]);
                    for (auto it = s1.begin(); it != s1.end(); ++it){
                        if (it == s1.begin()){
                            cout << *it+1;
                        }else{
                            cout << ' ' << *it +1;
                        }
                    }
                    cout << ' ' << source_curr+1 << '\n';
                    break;
                }
            } 
            if(has_cycle){
                break;
            }
        }
        if (!has_cycle){
            printf("no arbitrage sequence exists\n");
        }
    
    }   
    return 0;
}