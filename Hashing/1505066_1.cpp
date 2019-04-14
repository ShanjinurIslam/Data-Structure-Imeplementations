#include <bits/stdc++.h>
#include <cstdlib>
using namespace std ;
class node{
private:
    int value ;
    char *key ;
    node *prev ;
    node *next ;
public:
    node(char a[],int value){
        key = new char[strlen(a)] ;
        strcpy(key,a) ;
        this->value = value ;
        prev = next = 0 ;
    }

    node* getPrev(){
        return prev ;
    }

    node* getNext(){
        return next ;
    }

    char* getKey(){
        return key ;
    };

    void setPrev(node *x){
        prev = x ;
    }

    void setNext(node *x){
        next = x ;
    }

    int getValue(){
        return value ;
    }
};

class LinkedList{
private:
    node *head,*tail ;
public:
    LinkedList(){
        head = 0 ;
        tail = 0 ;
    }

    void insertItem(char key[],int value){
        node *temp = new node(key,value) ;
        if(head==0){
            temp->setNext(0) ;
            temp->setPrev(0) ;
            head = temp ;
            tail = temp ;
        } else{
            temp->setNext(head) ;
            head->setPrev(temp) ;
            temp->setPrev(0) ;
            head = temp ;
        }
    }

    bool searchKey(char a[]){
        node *temp = head ;
        while (temp!=0){
            if(strcmp(temp->getKey(),a)==0){
                return true ;
            }
            temp = temp->getNext();
        }

        return false ;
    }

    bool deleteItem(char key[]){
        bool b = false ;
        node *temp = head ;
        if(temp==NULL) return false;
        else if(temp->getNext()== NULL){
            if(strcmp(temp->getKey(),key)==0){
                head = tail = 0 ;
                free(temp) ;
                return true ;
            }
        }
        while (temp!=0){
            if(strcmp(temp->getKey(),key)==0){
                if(temp->getPrev()==NULL){
                    temp = temp->getNext() ;
                }
                else if(temp->getNext()==NULL){
                    temp->getPrev()->setNext(0) ;
                }
                else{
                    temp->getPrev()->setNext(temp->getNext());
                    temp->getNext()->setPrev(temp->getPrev());
                }
                b = true ;
                break ;
            }
            temp = temp->getNext() ;
        }

        free(temp) ;

        return b ;
    }

    void printList(){
        node *temp = head ;
        if(temp== NULL){
            return;
        }
        while(temp!=0){
            cout<<"("<<temp->getKey()<<","<<temp->getValue()<<")  ";
            temp = temp->getNext() ;
        }

        cout<<endl ;
    }

    int getLength(){
        node *temp = head ;
        int len = 0 ;
        if(temp== NULL){
            return 0 ;
        }
        while(temp!=0){
            len++ ;
            temp = temp->getNext() ;
        }

        return len ;
    }
};

char* RandomWordGenerator(int size){
    char *a = new char[size] ;
    for(int i=0;i<size;i++){
        int output = abs(rand()%(25)) ;
        a[i] = 'a' + output ;
    }
    return a ;
}


class HashTable{
private:
    int length ;
    int current ;
    LinkedList *hashTable1 ;
    LinkedList *hashTable2 ;
    LinkedList *hashTable3 ;

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
                sum += (sum*255) + (int) key[i] ;
            }
        }
        hash = abs(sum%length);
        return hash;
    }
public:
    HashTable(int l) {
        length = l;
        current = 0;
        //set LinkedList
        hashTable1 = new LinkedList[length];
        hashTable2 = new LinkedList[length];
        hashTable3 = new LinkedList[length];
    }

    void insert(char *key){
        int h1 = hash1(key) ;
        int h2 = hash2(key) ;
        int h3 = hash3(key) ;
        if(!hashTable1[h1].searchKey(key)){
            hashTable1[h1].insertItem(key,current) ;
        }
        if(!hashTable2[h2].searchKey(key)){
            hashTable2[h2].insertItem(key,current) ;
        }
        if(!hashTable3[h3].searchKey(key)){
            hashTable3[h3].insertItem(key,current) ;
        }
        current++ ;
    }

    void searchKey(char *key){
        int h1 = hash1(key) ;
        int h2 = hash2(key) ;
        int h3 = hash3(key) ;
        if(hashTable1[h1].searchKey(key)){
            cout<<"Found in HashTable1"<<endl ;
        }
        else{
            cout<<"Not Found in HashTable1"<<endl ;
        }
        if(hashTable2[h2].searchKey(key)){
            cout<<"Found in HashTable2"<<endl ;
        }
        else{
            cout<<"Not Found in HashTable2"<<endl ;
        }
        if(hashTable3[h3].searchKey(key)){
            cout<<"Found in HashTable3"<<endl ;
        }
        else{
            cout<<"Not Found in  HashTable3"<<endl ;
        }
    }

    void deleteKey(char key[]){
        int h1 = hash1(key) ;
        int h2 = hash2(key) ;
        int h3 = hash3(key) ;
        if(hashTable1[h1].searchKey(key)){
            hashTable1[h1].deleteItem(key) ;
            cout<<"Deleted from HashTable1"<<endl ;
        }
        else{
            cout<<"Not Found in HashTable1"<<endl ;
        }
        if(hashTable2[h2].searchKey(key)){
            hashTable2[h2].deleteItem(key) ;
            cout<<"Deleted from HashTable2"<<endl ;
        }
        else{
            cout<<"Not Found in HashTable2"<<endl ;
        }
        if(hashTable3[h3].searchKey(key)){
            hashTable3[h3].deleteItem(key) ;
            cout<<"Deleted from HashTable3"<<endl ;
        }
        else{
            cout<<"Not Found in  HashTable3"<<endl ;
        }
    }

    void getReport(int size,int key_length){
        int col1 = 0;
        int col2 = 0;
        int col3 = 0;

        for(int i=0;i<length;i++){
            int x =hashTable1[i].getLength() ;
            int y =hashTable2[i].getLength() ;
            int z =hashTable3[i].getLength() ;
            if(x>1){
                col1 += x-1 ;
            }
            if(y>1){
                col2 += y-1 ;
            }
            if(z>1){
                col3 += z-1 ;
            }
        }
        clock_t start = clock() ;
        for(int i=0;i<size;i++){
            char *k ;
            k = new char[key_length] ;
            strcpy(k,RandomWordGenerator(key_length)) ;
            int h1 = hash1(k) ;
            hashTable1[h1].searchKey(k) ;
            free(k) ;
        }
        cout<<"Search Time for Hash Function 1: "<<(clock()-start)/(double) CLOCKS_PER_SEC<<endl ;
        cout<<"Collution for Hash Function 1: "<<col1<<endl ;
        start = clock() ;
        for(int i=0;i<size;i++){
            char *k ;
            k = new char[key_length] ;
            strcpy(k,RandomWordGenerator(key_length)) ;
            int h2 = hash2(k) ;
            hashTable1[h2].searchKey(k) ;
            free(k) ;
        }
        cout<<"Search Time for Hash Function 2: "<<(clock()-start)/(double) CLOCKS_PER_SEC<<endl ;
        cout<<"Collution for Hash Function 2: "<<col2<<endl ;
        start = clock() ;
        for(int i=0;i<size;i++){
            char *k ;
            k = new char[key_length] ;
            strcpy(k,RandomWordGenerator(key_length)) ;
            int h3 = hash3(k) ;
            hashTable1[h3].searchKey(k) ;
            free(k) ;
        }
        cout<<"Search Time for Hash Function 3: "<<(clock()-start)/(double) CLOCKS_PER_SEC<<endl ;
        cout<<"Collution for Hash Function 3: "<<col3<<endl ;
    }

    int getNoKeys(){
        return current ;
    }

    void view1(){
        for(int i=0;i<length;i++){
            cout<<i<<" : " ;
            hashTable1[i].printList() ;
            cout<<endl ;
        }
    }

    void view2(){
        for(int i=0;i<length;i++){
            cout<<i<<" : " ;
            hashTable2[i].printList() ;
            cout<<endl ;
        }
    }

    void view3(){
        for(int i=0;i<length;i++){
            cout<<i<<" : " ;
            hashTable3[i].printList() ;
            cout<<endl ;
        }
    }

    ~HashTable(){
        delete hashTable1 ;
        delete hashTable2;
        delete hashTable3 ;
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

    char c ;
    while(1){
        cout<<"1.Insert Key 2.Search Key 3.Delete Key 4.Get Report 5.View HashTable1 6.View HashTable2 7.View HashTable3 8.Exit"<<endl ;
        cin>>c;

        if(c=='1'){
            char key[key_length] ;
            cin>>key;
            h.insert(key) ;
        }


        if(c=='2'){
            char key[key_length] ;
            cin>>key;
            h.searchKey(key) ;
        }

        if(c=='3'){
            char key[key_length] ;
            cin>>key;
            h.deleteKey(key) ;
        }

        if(c=='4'){
            h.getReport(num_key,key_length) ;
        }

        if(c=='5'){
            h.view1();
        }

        if(c=='6'){
            h.view1();
        }

        if(c=='7'){
            h.view1();
        }
        if(c=='8'){
            break ;
        }
    }

    return 0;
}
