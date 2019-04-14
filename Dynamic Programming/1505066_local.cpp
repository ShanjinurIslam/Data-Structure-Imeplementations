#include <iostream>
using namespace std ;

int match(int a,int b,int sc1,int sc2){
    if(a==b) return sc1 ;
    else return sc2 ;
}
int max(int a,int b,int c){
    return a>b?(a>c?a:c):(b>c?b:c) ;
}

void Smith_Waterman(int l1,int l2,int sc1,int sc2,int sc3,char a[],char b[]){
    int grid[l2+2][l1+2] ;
    for(int i=0;i<l2+2;i++){
        for(int j=0;j<l1+2;j++){
            grid[i][j] = 0;
        }
    }
    for(int i=2;i<l1+2;i++){
        grid[0][i] = a[i-2] ;
    }
    for(int i=2;i<l2+2;i++){
        grid[i][0] = b[i-2] ;
    }
    grid[1][1] = 0 ;
    int max1 = -1 ;
    int m,n ;
    m=-1 , n=-1 ;
    for(int i=2;i<l2+2;i++){
        for(int j=2;j<l1+2;j++){
            int a = grid[i-1][j-1] + match(grid[i][0],grid[0][j],sc1,sc2) ;
            int b = grid[i-1][j] + sc3;
            int c = grid[i][j-1] + sc3;
            grid[i][j] = max(a,b,c)>0?max(a,b,c):0 ;
            if(grid[i][j]>=max1){
                max1 = grid[i][j] ;
                m = i ;
                n = j ;
            }
        }
    }

    for(int i=0;i<l2+2;i++) {
        for (int j = 0; j < l1 + 2; j++) {
            if((i==0 || j==0)&& grid[i][j]>=65){
                cout << (char)grid[i][j] << "         ";
            } else{
                cout << grid[i][j] << "         ";
            }
        }
        cout << endl;
    }
    cout<<endl ;
    char A[1000],B[1000] ;
    int i = 0 ;
    while(m>1 && n>1 && grid[m][n]>0){
        if(m>1 && n>1 && grid[m][n]==grid[m-1][n-1] + match(grid[m][0],grid[0][n],sc1,sc2)){
            B[i] = (char) grid[m][0] ;
            A[i] = (char) grid[0][n] ;
            m-- ;
            n-- ;
        }
        else if(m>1 && grid[m][n]==grid[m-1][n] + sc3){
            B[i] = (char) grid[m][0] ;
            A[i] = '-';
            m-- ;
        }
        else{
            B[i] = '-';
            A[i] = (char) grid[0][n] ;
            n-- ;
        }
        i++ ;
    }
    int  l = i ;
    for(int i=1;i<=l;i++){
        cout<<A[l-i];
    }
    cout<<endl ;
    for(int i=1;i<=l;i++){
        cout<<B[l-i];
    }
    cout<<endl ;
}
int main() {
    int l1,l2,sc1,sc2,sc3 ;
    cin>>l1>>l2>>sc1>>sc2>>sc3 ;
    char a[l1],b[l2] ;
    cin>>a>>b ;
    Smith_Waterman(l1,l2,sc1,sc2,sc3,a,b) ;
    return 0;
}