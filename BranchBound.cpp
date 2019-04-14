#include <bits/stdc++.h>

using namespace std ;

class vertex_set{
private:
    int *item ;
    int length ;
    int current ;
public:
    vertex_set(){
        length = 0 ;
        item = 0;
        current = 0;
    }

    explicit vertex_set(int length){
        this->length = length ;
        item = new int[length] ;
        current = 0;
    }

    explicit vertex_set(string a){
        for(int i=0;i<a.size();i++){
            if(a[i]!=' '){
                length++ ;
            }
        }

        item = new int[length] ;
        int j=0 ;
        int k=1 ;
        int tem=0 ;
        a += ' ' ;
        for(int i=0;i<a.size();i++){
            if(a[i]!=' '){
                tem = tem*k + (a[i]-'0') ;
                k = k*10 ;
            }
            else{
                k = 1 ;
                item[j++] = tem ;
                tem = 0 ;
            }
        }
        current = j ;
    }

    void setItems(int a){
        length = a ;
        item = new int[length] ;
        for(int i=0;i<length;i++){
            item[i] = i+1 ;
            current++ ;
        }
    }

    void setItems(string a){
        for(int i=0;i<a.size();i++){
            if(a[i]!=' '){
                length++ ;
            }
        }

        item = new int[length] ;
        int j=0 ;
        int k=1 ;
        int tem=0 ;
        a += ' ' ;
        for(int i=0;i<a.size();i++){
            if(a[i]!=' '){
               tem = tem*k + (a[i]-'0') ;
               k = k*10 ;
            }
            else{
                k = 1 ;
                item[j++] = tem ;
                tem = 0 ;
            }
        }

        current = j ;

        sort(item,item+current) ;
    }

    bool searchItem(int x){
        bool b = false ;
        for(int i=0;i<this->length;i++){
            if(item[i]==x){
                b = true ;
                break ;
            }
        }
        return b;
    }

    int compare(vertex_set a){
        int c = 0 ;
        for(int i=0;i<current;i++){
            if(a.item[i]!=this->item[i]){
                c++ ;
            }
        }

        return c ;
    }

    vertex_set operator + (vertex_set a){
        int new_len = this->length + a.length ;
        vertex_set tem(new_len) ;
        int j= 0 ;
        for(int i=0;i<this->current;i++){
            if(!tem.searchItem(this->item[i])){
                tem.item[j++] = this->item[i] ;
            }
        }
        for(int i=0;i<a.current;i++){
            int x = a.item[i] ;
            bool b = tem.searchItem(x) ;
            if(!b){
                tem.item[j++] = x ;
            }
        }
        tem.current = j ;
        return tem ;
    }


    vertex_set& operator = (vertex_set a){
        this->length = a.length ;
        this->current = a.current ;
        this->item = new int[length] ;
        for(int i=0;i<this->current;i++){
            this->item[i] = a.item[i] ;
        }

        return *this ;
    }

    void showSet(){
        for(int i=0;i<current;i++){
            cout<<item[i]<<"    " ;
        }

        cout<<endl ;
    }

    int getLength(){
        return current ;
    }
};

bool comp(vertex_set a,vertex_set b){
    if(a.getLength()>b.getLength()){
        return true ;
    }
    else{
        return false ;
    }
}

struct tree_node{
    vertex_set set ;
    float bound ;
    vector<int> items ;
    vector<int> selected ;
    int level ;
};

class branch_bound{
private:
    queue<tree_node> set_queue ;
    vertex_set universal_set ;
    vertex_set *arr ;
    int length ;
    int n ;
public:
    branch_bound(vertex_set x,vertex_set *items,int len){
        length = len ;
        universal_set = x;
        arr = new vertex_set[length] ;
        for(int i=0;i<length;i++){
            arr[i] = items[i] ;
        }
        n = length ;
    }


    void showSets(){
        for(int i =0 ;i<length;i++){
            arr[i].showSet() ;
        }
    }

    float find_bound(tree_node node, vertex_set *pSet) {
        float max = 0 ;
        float s ;
        float b ;
        for(int i=0;i<length;i++){
            if(find(node.items.begin(),node.items.end(),i)==node.items.end()){
                if(pSet[i].getLength()>max){
                    max = pSet[i].getLength() ;
                }
            }
        }
        if(node.level==0){
            s = node.items.size() ;
        }
        else{
            s = node.selected.size() ;
        }
        float r_i = (float) (universal_set.getLength()-node.set.getLength()) ;
        if(r_i==0){
            b = s ;
        } else{
            b = s + (r_i)/max ;
        }
        return b ;
    }

    void run() {
        sort(arr, arr + length, comp);
        tree_node p, q, r;

        p.level = -1;

        set_queue.push(p);
        int c = 0;
        tree_node result = tree_node();
        int min = 99999 ;
        float size = (float) length;
        while (!set_queue.empty()) {
            p = set_queue.front();
            set_queue.pop();
            if(p.set.getLength()==universal_set.getLength()){
                if(min>p.items.size()){
                    min = (int) p.items.size() ;
                    result = p ;
                }
            }

            if (p.level == -1) {
                q.level = 0;
            }

            if (p.level == n - 1) {
                continue;
            }
            q.level = p.level + 1;
            q.set = p.set + arr[q.level];
            q.items = p.items ;
            q.items.push_back(p.level+1) ;
            q.bound = find_bound(q, arr);
            if (q.bound <= size) {
                set_queue.push(q);
            }
            r.level = q.level;
            r.set = p.set;
            r.items = p.items;
            r.bound = find_bound(r, arr);

            if (r.bound <= size) {
                set_queue.push(r);
            }
        }

        int cmp = result.items.size();

        if(cmp>0){
            cout<<cmp<<endl ;
            for(auto m:result.items){
                arr[m].showSet() ;
            }
        }
        else{
            cout<<"Not enough elements in the subset"<<endl ;
        }
    }


};
int main() {
    int m,n;
    vertex_set *arr ;
    cin>>m>>n ;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    arr = new vertex_set[n] ;
    for(int i=0;i<n;i++){
        string s ;
        getline(cin,s) ;
        arr[i].setItems(s) ;
    }
    vertex_set universal;
    universal.setItems(m) ;
    branch_bound b(universal,arr,n) ;
    b.run() ;
    return 0;
}