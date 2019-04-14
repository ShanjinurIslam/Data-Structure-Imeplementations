#include <cstdio>
#include <cstring>
#define NIL -1
#define MAX_HEAP_SIZE 100000
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

class node{
    int value ;
    int key ;
    int parent ;
public:
    node(){
        value =key = parent = 0 ;
    }
    node(int value){
        this->value = value ;
        key = parent = 0 ;
    }

    void setValue(int value){
        this->value = value ;
    }
    void setKey(int key){
        this->key =key ;
    }

    void setParent(int parent){
        this->parent = parent ;
    }

    int getParent(){
        return parent ;
    }

    int getValue(){
        return value ;
    }

    int getKey(){
        return key ;
    }

    node& operator = (node &A){
        this->value = A.value ;
        this->key = A.key ;
        this->parent = A.parent ;

        return *this ;
    }

};

class MinHeap
{
public:
    int map[INFINITY] ;
    node * A; //stores heap items, e.g., nodes
    int heapLength;

    MinHeap() //constructor
    {
        A = new node[MAX_HEAP_SIZE];
        heapLength=0;
    }

    ~MinHeap() //destructor
    {
        if(A) delete [] A;
        A = 0; //set to NULL after deletion
    }

    void heapify(int i)
    {
        int l,r,smallest;
        while(1)
        {
            l=2*i;
            r=2*i+1;
            smallest=i;

            if(l>heapLength && r>heapLength)
                break;
            else if(r>heapLength)
                smallest = l;
            else if(l>heapLength)
                smallest = r;
            else if( A[l].getKey() < A[r].getKey() )
                smallest = l;
            else
                smallest = r;

            if(A[i].getKey() <= A[smallest].getKey())
                break;
            else
            {
                node t;
                t=A[i];
                A[i]=A[smallest];
                map[A[i].getValue()] = i ;
                A[smallest]=t;
                map[A[smallest].getValue()] = smallest;
                i=smallest;
            }

        }
    }

    void buHeapify(int i)
    {
        while (i>1) {
            int parent = i/2 ;
            if(A[i].getKey()<A[parent].getKey()){
                node t ;
                t = A[i] ;
                A[i] = A[parent] ;
                map[A[i].getValue()] = i ;
                A[parent] = t ;
                map[A[parent].getValue()] = parent ;
            }
            i = parent ;
        }
    }

    void insertNode(node node){
        heapLength++ ;
        A[heapLength] = node ;
        map[A[heapLength].getValue()] = heapLength ;
        buHeapify(heapLength) ;
    }

    node removeMin()
    {
        node new_item ;
        if(heapLength==0){
            return new_item ;
        }
        else{
            new_item = A[1] ;
            A[1] = A[heapLength] ;
            heapLength-- ;
            heapify(1) ;
            return new_item ;
        }
    }
    int index(int value){
        return map[value] ;
    }
    void updateKey(int i,int key){
        A[i].setKey(key) ;
        heapify(1) ;
    }
    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1;i<=heapLength;i++)
        {
            printf("%d %d\n",A[i].getValue() ,A[i].getKey())  ;
        }
        printf("\n");
    }

    bool Empty()
    {
        if(heapLength==0)return true;
        else return false;
    }

    int getLength(){
        return heapLength ;
    }
};

class ArrayList
{
    node * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new node[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    node * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new node[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };
    node n(newitem) ;
    list[length] = n; //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i].getValue() == item ) return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length ) return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}


void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return ; //nothing to remove
    removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
    if(position < 0 || position >= length) return NULL_VALUE ;
    return list[position].getValue() ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i].getValue());
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

class Graph
{
    int nVertices, nEdges ;
    node *nodes ;
    bool directed ;
    int MST_Weight ;
    ArrayList  * adjList ;
    int** edgeWeight ;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v,int weight);
    void removeEdge(int u, int v);
    int getWeight(int u,int v) ;
    void printGraph();
    int primsAlgorithm(int r) ;
};

Graph::Graph(bool dir) {
    directed = dir ;
    nodes = NULL ;
    nVertices = nEdges = 0 ;
    MST_Weight = 0 ;
    edgeWeight = NULL ;
    adjList = NULL ;
}

int Graph::getWeight(int u,int v){
    if(edgeWeight[u][v]) return edgeWeight[u][v] ;
    else return -1 ;
}
void Graph::setnVertices(int n) {
    nVertices = n+1 ;
    nEdges = 0;
    nodes = new node[n+1] ;
    adjList = new ArrayList[n+1] ;
    for(int i=1;i<n+1;i++){
        nodes[i].setValue(i) ;
    }

    edgeWeight = reinterpret_cast<int **>(new int[n + 1]);
    for(int i=0;i<n+1;i++){
        edgeWeight[i] = new int[n+1] ;
    }
}

void Graph::addEdge(int u, int v,int weight) {
    adjList[u].insertItem(v) ;
    adjList[v].insertItem(u) ;
    edgeWeight[u][v] = weight ;
    edgeWeight[v][u] = weight ;
    nEdges++ ;
}

void Graph::removeEdge(int u, int v) {
    adjList[u].removeItem(v) ;
    adjList[v].removeItem(u) ;
    edgeWeight[u][v] = 0 ;
    edgeWeight[v][u] = 0 ;
    nEdges-- ;
}

int Graph::primsAlgorithm(int r) {
    for(int i=1;i<nVertices;i++){
        nodes[i].setKey(INFINITY) ;
        nodes[i].setParent(NIL) ;
    }
    nodes[r].setKey(0);
    MinHeap minHeap;
    for(int i=1;i<nVertices;i++){
        minHeap.insertNode(nodes[i]) ;
    }
    while(minHeap.Empty()!= true){
        node u = minHeap.removeMin() ;
        for(int i=0;i<adjList[u.getValue()].getLength();i++){
            int v = adjList[u.getValue()].getItem(i) ;
            int index = minHeap.index(v) ;
            if(index!=-1 && edgeWeight[u.getValue()][v]<=minHeap.A[index].getKey()){
                minHeap.updateKey(index,edgeWeight[u.getValue()][v]);
                nodes[v].setParent(u.getValue()) ;
            }
        }
        if(minHeap.heapLength>0){
            int u  = nodes[minHeap.A[1].getValue()].getParent() ;
            int v = minHeap.A[1].getValue();
            if(u<v){
                printf("%d %d\n",u,v) ;
            }
            else{
                printf("%d %d\n",v,u) ;
            }
            MST_Weight+= edgeWeight[nodes[v].getParent()][v] ;
        }

    }
    return MST_Weight ;
}

void Graph::printGraph() {
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices-1, nEdges);
    for(int i=1;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    delete[] adjList ;
    delete edgeWeight ;
}
int main() {
    FILE *fp;
    fp = fopen("1505066/input.txt","r");
    int n,inputs,v1,v2,w;
    fscanf(fp,"%d\n",&n) ;
    Graph G ;
    G.setnVertices(n) ;
    fscanf(fp,"%d\n",&inputs) ;
    int i = 0 ;
    while (i<inputs){
        fscanf(fp,"%d %d %d\n",&v1,&v2,&w) ;
        G.addEdge(v1,v2,w) ;
        i++ ;
    }
    printf("%d\n",G.primsAlgorithm(1));
    return 0;
}