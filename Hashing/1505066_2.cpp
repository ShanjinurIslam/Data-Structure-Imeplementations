#include <bits/stdc++.h>
#define DELETED -1
using namespace std;
char* RandomWordGenerator(int size){
    char *a = new char[size] ;
    for(int i=0;i<size;i++){
        int output = abs(rand()%(25)) ;
        a[i] = 'a' + output ;
    }
    return a ;
}

struct node{
    char *key= NULL ;
    int value=0 ;
};

class HashTable{
private:
    int length ;
    int current ;
    node *hashTable1;
    node *hashTable2;
    node *hashTable3;
    int col_hash1;
    int col_hash2;
    int col_hash3;
    int hash1(char key[]) {
        int hash = 0;
        for(int i = 0; i < strlen(key); ++i)
        {
            hash += key[i];
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);
        return abs(hash%length);
    }


    int hash2(char key[]) {
        int hash = 0;
        for (int i = 0; i < strlen(key); i++) {
            hash = hash*31 + key[i];
        }
        return abs(hash%length) ;
    }

    int hash3(char key[]) {
        int hash ;
        int sum = 0 ;
        for(int i=0;i< strlen(key);i++){
            if(i%2==0){
                sum += (int) key[i] ;
            }
            else{
                sum += (sum*37) + (int) key[i] ;
            }
        }
        hash = abs(sum%length);
        return hash;
    }

public:
    HashTable(int l){
        length = l ;
        current = 0;
        col_hash1 = 0;
        col_hash2 = 0;
        col_hash3 = 0;
        hashTable1 = new node[length] ;
        hashTable2 = new node[length] ;
        hashTable3 = new node[length] ;
    }

    void insert(char key[]){
        int h1 = hash1(key) ;
        int h2 = hash2(key) ;
        int h3 = hash3(key) ;
        int len = static_cast<int>(strlen(key));
        int i =0 ;
        if(hashTable1[h1].key== NULL || hashTable1[h1].value==DELETED){
            hashTable1[h1].key = new char[len] ;
            strcpy(hashTable1[h1].key,key) ;
            hashTable1[h1].value = current+1 ;
        }
        else{
            col_hash1++ ;
            while(i<=length){
                h1 = h1%length ;
                if(hashTable1[h1].key== NULL || hashTable1[h1].value==DELETED){
                    hashTable1[h1].key = new char[len] ;
                    strcpy(hashTable1[h1].key,key) ;
                    hashTable1[h1].value = current+1 ;
                    break ;
                }
                i++ ;
                h1++ ;
            }
        }
        if(i>length){
            cout<<"Error : Hash1 overflow"<<endl ;
        }
        i = 0 ;
        if(hashTable2[h2].key== NULL || hashTable2[h2].value==DELETED){
            hashTable2[h2].key = new char[len] ;
            strcpy(hashTable2[h2].key,key) ;
            hashTable2[h2].value = current+1 ;
        }
        else{
            col_hash2++ ;
            while(i<=length){
                h2 = h2%length ;
                if(hashTable2[h2].key== NULL || hashTable2[h2].value==DELETED){
                    hashTable2[h2].key = new char[len] ;
                    strcpy(hashTable2[h2].key,key) ;
                    hashTable2[h2].value = current+1 ;
                    break ;
                }
                i++ ;
                h2++ ;
            }
        }
        if(i>length){
            cout<<"Error : Hash2 overflow"<<endl ;
        }
        i = 0 ;

        if(hashTable3[h3].key== NULL || hashTable3[h3].value==DELETED){
            hashTable3[h3].key = new char[len] ;
            strcpy(hashTable3[h3].key,key) ;
            hashTable3[h3].value = current+1 ;
        }
        else{
            col_hash3++ ;
            while(i<=length){
                h3 = h3%length ;
                if(hashTable3[h3].key== NULL || hashTable3[h3].value==DELETED){
                    hashTable3[h3].key = new char[len] ;
                    strcpy(hashTable3[h3].key,key) ;
                    hashTable3[h3].value = current+1 ;
                    break ;
                }
                i++ ;
                h3++ ;
            }
        }

        if(i>length){
            cout<<"Error : Hash3 overflow"<<endl ;
        }
        current++ ;
    }

    void searchItem(char *key){
        int h1 = hash1(key) ;
        int h2 = hash2(key) ;
        int h3 = hash3(key) ;
        bool b1,b2,b3 ;
        b1= b2 = b3 = false ;
        int i=0;
        while(i<length || (hashTable1[h1].key==0)){
            h1 = (h1)%length ;
            if(hashTable1[h1].key!= NULL) {
                if (!strcmp(hashTable1[h1].key, key)) {
                    b1 = true;
                    break;
                }
            }
            h1++ ;
            i++ ;
        }
        i = 0 ;
        while(i<length || (hashTable2[h2].key==0)){
            h2 = (h2)%length ;
            if(hashTable2[h2].key!= NULL) {
                if (!strcmp(hashTable2[h2].key, key)) {
                    b2 = true;
                    break;
                }
            }
            h2++ ;
            i++ ;
        }
        i=0 ;
        while(i<length || (hashTable3[h3].key==0)){
            h3 = (h3)%length ;
            if(hashTable3[h3].key!= NULL) {
                if (!strcmp(hashTable3[h3].key, key)) {
                    b3 = true;
                    break;
                }
            }
            h3++ ;
            i++ ;
        }

        if(b1){
            cout<<"Found in HashTable1"<<endl ;
        }
        if(b2){
            cout<<"Found in HashTable2"<<endl ;
        }
        if(b3){
            cout<<"Found in HashTable3"<<endl ;
        }
    }

    void deleteItem(char key[]){
        int h1 = hash1(key) ;
        int h2 = hash2(key) ;
        int h3 = hash3(key) ;
        bool b1,b2,b3 ;
        b1= b2 = b3 = false ;
        int i=0;
        while(i<length || (hashTable1[h1].key==0)){
            h1 = (h1)%length ;
            if(hashTable1[h1].key!= NULL){
                if(!strcmp(hashTable1[h1].key,key)){
                    hashTable1[h1].key = "DELETED" ;
                    hashTable1[h1].value = DELETED ;
                    break ;
                }
            }
            h1++ ;
            i++ ;
        }
        i = 0 ;
        while(i<length || (hashTable2[h2].key==0)){
            h2 = (h2)%length ;
            if(hashTable2[h2].key!= NULL) {
                if (!strcmp(hashTable2[h2].key, key)) {
                    hashTable2[h2].key = "DELETED" ;
                    hashTable2[h2].value = DELETED ;
                    break;
                }
            }
            h2++ ;
            i++ ;
        }
        i=0 ;
        while(i<length || (hashTable3[h3].key==0)){
            h3 = (h3)%length ;
            if(hashTable3[h3].key!= NULL) {
                if (!strcmp(hashTable3[h3].key, key)) {
                    hashTable3[h3].key = "DELETED" ;
                    hashTable3[h3].value = DELETED ;
                    break;
                }
            }
            h3++ ;
            i++ ;
        }
    }

    void getReport(int size,int key_length){
        clock_t start = clock() ;
        for(int j=0;j<size;j++){
            char *key ;
            key = new char[key_length] ;
            strcpy(key,RandomWordGenerator(key_length)) ;
            int h = hash1(key) ;
            int i=0;
            while(i<length || (hashTable1[h].key==0)){
                h = (h+i)%length ;
                if(hashTable1[h].key!= NULL) {
                    if (!strcmp(hashTable1[h].key, key)) {
                        break;
                    }
                }
                h++ ;
                i++ ;
            }
            free(key) ;
        }
        cout<<"Search Time for Hash Function 1: "<<(clock()-start)/(double) CLOCKS_PER_SEC<<endl ;
        cout<<"Collution for Hash Function 1: "<<col_hash1<<endl ;
        start = clock() ;
        for(int j=0;j<size;j++){
            char *key ;
            key = new char[key_length] ;
            strcpy(key,RandomWordGenerator(key_length)) ;
            int h = hash2(key) ;
            int i=0;
            while(i<length || (hashTable2[h].key==0)){
                h = (h)%length ;
                if(hashTable2[h].key!= NULL) {
                    if (!strcmp(hashTable2[h].key, key)) {
                        break;
                    }
                }
                h++ ;
                i++ ;
            }
            free(key) ;
        }
        cout<<"Search Time for Hash Function 2: "<<(clock()-start)/(double) CLOCKS_PER_SEC<<endl ;
        cout<<"Collution for Hash Function 2: "<<col_hash2<<endl ;
        start = clock() ;
        for(int j=0;j<size;j++){
            char *key ;
            key = new char[key_length] ;
            strcpy(key,RandomWordGenerator(key_length)) ;
            int h = hash3(key) ;
            int i=0;
            while(i<length || (hashTable2[h].key==0)){
                h = (h)%length ;
                if(hashTable3[h].key!= NULL) {
                    if (!strcmp(hashTable3[h].key, key)) {
                        break;
                    }
                }
                h++;
                i++ ;
            }
            free(key) ;
        }
        cout<<"Search Time for Hash Function 3: "<<(clock()-start)/(double) CLOCKS_PER_SEC<<endl ;
        cout<<"Collution for Hash Function 3: "<<col_hash3<<endl ;
    }

    void view1(){
        for(int i=0;i<length;i++){
            if(hashTable1[i].key!= NULL){
                cout<<i<<"  : ("<<hashTable1[i].key<<","<<hashTable1[i].value<<")"<<endl ;
            }
            else{
                cout<<i<<"  : (NULL,NULL)"<<endl ;
            }
        }
        cout<<endl ;
        for(int i=0;i<length;i++){
            if(hashTable2[i].key!= NULL){
                cout<<i<<"  : ("<<hashTable2[i].key<<","<<hashTable2[i].value<<")"<<endl ;
            }
            else{
                cout<<i<<"  : (NULL,NULL)"<<endl ;
            }
        }

        cout<<endl;
        for(int i=0;i<length;i++){
            if(hashTable3[i].key!= NULL){
                cout<<i<<"  : ("<<hashTable3[i].key<<","<<hashTable3[i].value<<")"<<endl ;
            }
            else{
                cout<<i<<"  : (NULL,NULL)"<<endl ;
            }
        }
    }
    int getNoKeys(){
        return current ;
    }
};
int main() {
    srand((unsigned) time(NULL));
    int size, num_key,key_length;
    cout << "Enter size of hash: ";
    cin >> size;
    cout << "Enter number of keys: ";
    cin >> num_key;
    cout << "Enter length of a key: ";
    cin >> key_length;
    HashTable h(size);
    while(h.getNoKeys()!=num_key){
        h.insert(RandomWordGenerator(key_length)) ;
    }

    char option ;
    while(true){
        cout<<"Choose Operation: 1.Insert Item 2.Search Item 3. Delete Item 4.Get Report 5.View HashTable 6.Exit"<<endl ;
        cin>>option ;
        if(option=='1'){
            char key[key_length] ;
            cout<<"Enter String: " ;
            cin>>key ;
            h.insert(key) ;
        }
        if(option=='2'){
            char key[key_length] ;
            int data ;
            cout<<"Enter String: " ;
            cin>>key ;
            h.searchItem(key) ;
        }

        if(option=='3'){
            char key[key_length] ;
            int data ;
            cout<<"Enter String: " ;
            cin>>key ;
            h.deleteItem(key) ;
        }

        if(option=='4'){
            h.getReport(size,key_length) ;
        }
        if(option=='5'){
            h.view1() ;
        }
        if(option=='6'){
            break ;
        }
    }
}
