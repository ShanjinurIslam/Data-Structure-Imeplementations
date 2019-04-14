#include <iostream>
#include <cstdlib>
#define NIL -1
#define MAX_HEAP_SIZE 100000
#define NULL_VALUE -999999
#define INFINITY 1000
#define WHITE 1
#define GREY 2
#define BLACK 3
int t = 0 ;
int MAX = 0 ;
using namespace std ;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}


int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}


class vertex{
    int value ;
    int distance ;
    int parent ;
public:
    vertex(){
        value = distance = 0 ;
    }
    vertex(int v){
        this->value = v ;
        distance = 0 ;
    }

    void setValue(int i){
        value = i ;
    }

    int getValue(){
        return value ;
    }

    void setDistance(int d){
        this->distance = d;
    }

    int getDistance(){
        return distance ;
    }

    int getParent(){
        return parent ;
    }

    void setParent(int p){
        parent = p ;
    }
};

class MinHeap
{
public:
    int map[INFINITY] ;
    vertex * A; //stores heap items, e.g., vertexs
    int heapLength;

    MinHeap() //constructor
    {
        A = new vertex[MAX_HEAP_SIZE];
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
            else if( A[l].getDistance() < A[r].getDistance() )
                smallest = l;
            else
                smallest = r;

            if(A[i].getDistance() <= A[smallest].getDistance())
                break;
            else
            {
                vertex t;
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
            if(A[i].getDistance()<A[parent].getDistance()){
                vertex t ;
                t = A[i] ;
                A[i] = A[parent] ;
                map[A[i].getValue()] = i ;
                A[parent] = t ;
                map[A[parent].getValue()] = parent ;
            }
            i = parent ;
        }
    }

    void insertvertex(vertex vertex){
        heapLength++ ;
        A[heapLength] = vertex ;
        map[A[heapLength].getValue()] = heapLength ;
        buHeapify(heapLength) ;
    }

    vertex removeMin()
    {
        vertex new_item ;
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

    void updateKey(int value,int key){
        A[map[value]].setDistance(key) ;
        heapify(1) ;
    }
    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1;i<=heapLength;i++)
        {
            printf("%d %d\n",A[i].getValue() ,A[i].getDistance())  ;
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
    vertex * list;
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
    list = new vertex[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    vertex * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new vertex[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };
    vertex n(newitem) ;
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
    int *color ;
    int *parent ;
    int *dist ;
    int *start_time ;
    int *end_time ;
    vertex *vertexs ;
    bool directed ;
    int MST_Weight ;
    ArrayList  * adjList ;
    int** edgeCapacity ;
    int** edgeFlow ;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v,int weight);
    void removeEdge(int u, int v);
    int getWeight(int u,int v) ;
    void printGraph();
    bool bfs(int source,int target) ;
    int bfsForDist(int source,int target) ;
    void dfs() ;
    void dfs_visit(int vertex) ;
    void MaxFlow(int source, int target);
};

Graph::Graph(bool dir) {
    directed = dir ;
    vertexs = NULL ;
    nVertices = nEdges = 0 ;
    MST_Weight = 0 ;
    edgeCapacity = NULL ;
    adjList = NULL ;
    edgeFlow =  NULL ;
}

int Graph::getWeight(int u,int v){
    if(edgeCapacity[u][v]) return edgeCapacity[u][v] ;
    else return -1 ;
}
void Graph::setnVertices(int n) {
    nVertices = n+1 ;
    nEdges = 0;
    vertexs = new vertex[n+1] ;
    adjList = new ArrayList[n+1] ;
    for(int i=1;i<n+1;i++){
        vertexs[i].setValue(i) ;
    }

    edgeCapacity = reinterpret_cast<int **>(new int[n + 1]);
    for(int i=0;i<n+1;i++){
        edgeCapacity[i] = new int[n+1] ;
    }

    edgeFlow = reinterpret_cast<int **>(new int[n + 1]);
    for(int i=0;i<n+1;i++){
        edgeFlow[i] = new int[n+1] ;
    }
    color = new int[nVertices] ;
    parent = new int[nVertices] ;
    dist = new int[nVertices] ;
    start_time = new int [nVertices] ;
    end_time = new int[nVertices] ;
}

void Graph::addEdge(int u, int v,int weight) {
    if(directed==true){
        adjList[u].insertItem(v) ;
        edgeCapacity[u][v] = weight ;
    }
    else{
        adjList[u].insertItem(v) ;
        adjList[v].insertItem(u) ;
        edgeCapacity[u][v] = weight ;
        edgeCapacity[v][u] = weight ;
    }
    nEdges++ ;
}

void Graph::removeEdge(int u, int v) {
    adjList[u].removeItem(v) ;
    adjList[v].removeItem(u) ;
    edgeCapacity[u][v] = 0 ;
    edgeCapacity[v][u] = 0 ;
    nEdges-- ;
}

void Graph::printGraph() {
    for(int i=1;i<nVertices;i++){
        for(int  j=1;j<nVertices;j++){
            cout<<edgeCapacity[i][j]<<"     " ;
        }
        cout<<endl ;
    }
}

Graph::~Graph()
{
    delete[] adjList ;
    delete[] edgeCapacity ;
    delete[] color ;
    delete[] parent ;
    delete[] dist;
    delete[] start_time ;
    delete[] end_time ;
}

bool Graph::bfs(int source,int target)
{
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        int u = q.dequeue() ;
        int i = 0 ;
        while(i<adjList[u].getLength()){
            int v = adjList[u].getItem(i) ;
            if((color[v]==WHITE) && (edgeFlow[u][v]!=edgeCapacity[u][v])){
                color[v] = GREY ;
                parent[v] = u ;
                q.enqueue(v) ;
            }
            i++ ;
        }
    }
    if(color[target]==GREY){
        int y = target ;
        int min = INFINITY ;
        while(y!=source){
            int x = parent[y] ;
            if(min>(edgeCapacity[x][y]-edgeFlow[x][y])){
                min = edgeCapacity[x][y]-edgeFlow[x][y] ;
            }
            y = x ;
        }
        MAX += min ;
        y = target ;
        while(y!=source){
            int x = parent[y] ;
            if(edgeCapacity[x][y]>0){
                edgeFlow[x][y] += min ;
            }
            else{
                edgeFlow[y][x] -= min ;
            }
            y = x ;
        }
        return true ;
    }
    return false ;
}


void Graph::dfs()
{
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
    }
    t = 0 ;
    for(int i =0;i<nVertices;i++){
        if(color[i]==WHITE){
            dfs_visit(i) ;
        }
    }
}

void Graph::dfs_visit(int vertex){
    t = t + 1;
    start_time[vertex] = t ;
    color[vertex] = GREY ;
    int i = 0 ;
    while(i<adjList[vertex].getLength()){
        int v = adjList[vertex].getItem(i) ;
        if(color[v]==WHITE){
            parent[v] = vertex ;
            dfs_visit(v) ;
        }
        i++;
    }
    color[vertex] = BLACK ;
    t = t + 1 ;
    end_time[vertex] = t ;
}

void Graph::MaxFlow(int source,int target){
    MAX = 0 ;
    for(int i=1;i<nVertices;i++){
        for(int  j=1;j<nVertices;j++){
            edgeFlow[i][j] = 0 ;
        }
    }
    while(1){
        bool b = bfs(source,target) ;
        if(b== false){
            break ;
        }
    }

    cout<<"Max Flow : "<<MAX<<endl ;

    for(int i=1;i<nVertices;i++){
        for(int j=1;j<nVertices;j++){
            if(edgeCapacity[i][j]>0){
                cout<<"Edge "<<"("<<i<<","<<j<<") : "<<edgeFlow[i][j]<<"/"<<edgeCapacity[i][j]<<"    " ;
                cout<<endl ;
            }
        }
    }

    cout<<endl<<"Min Cut Edges"<<endl ;

    for(int i=1;i<nVertices;i++){
        for(int j=1;j<nVertices;j++){
            if(edgeCapacity[i][j]>0 && color[i]==GREY && color[j]==WHITE){
                cout<<i<<"-"<<j<<" : "<<edgeCapacity[i][j]<<endl ;
            }
        }
    }
}

int main() {
    int n,inputs,v1,v2,w;
    cin>>n ;
    cin>>inputs ;
    Graph G(true) ;
    G.setnVertices(n) ;
    int i = 0 ;
    while (i<inputs){
        cin>>v1>>v2>>w ;
        G.addEdge(v1,v2,w) ;
        i++ ;
    }
    int source,target ;
    cout<<"Enter source :" ;
    cin>>source ;
    cout<<"Enter target :" ;
    cin>>target ;
    G.MaxFlow(source,target) ;
    return 0;
}