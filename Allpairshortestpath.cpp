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
    int** edgeWeight ;
    int** distMap ;
    int** preMat ;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v,int weight);
    void removeEdge(int u, int v);
    int getWeight(int u,int v) ;
    void printGraph();
    void bfs(int source) ;
    int bfsForDist(int source,int target) ;
    void dfs() ;
    void dfs_visit(int vertex) ;
    bool BellmanFord(int source) ;
    void printPath(int value);
    void AllPairShortestPath() ;
};

Graph::Graph(bool dir) {
    directed = dir ;
    vertexs = NULL ;
    nVertices = nEdges = 0 ;
    MST_Weight = 0 ;
    edgeWeight = NULL ;
    adjList = NULL ;
    distMap = 0 ;
    preMat = 0 ;
}

int Graph::getWeight(int u,int v){
    if(edgeWeight[u][v]) return edgeWeight[u][v] ;
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

    edgeWeight = reinterpret_cast<int **>(new int[n + 1]);
    for(int i=0;i<n+1;i++){
        edgeWeight[i] = new int[n+1] ;
    }
    distMap = reinterpret_cast<int **>(new int[n + 1]);
    for(int i=0;i<n+1;i++){
        distMap[i] = new int[n+1] ;
    }

    preMat = reinterpret_cast<int **>(new int[n + 1]);
    for(int i=0;i<n+1;i++){
        preMat[i] = new int[n+1] ;
    }

    for(int i =1 ;i<=n;i++){
        for(int j=1;j<=n;j++){
            distMap[i][j] = INFINITY ;
            preMat[i][j] = INFINITY ;
        }
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
        edgeWeight[u][v] = weight ;
        distMap[u][u] = 0 ;
        distMap[u][v] = weight ;
        if(u!=v){
            preMat[u][v] = u ;
        }
    }
    else{
        adjList[u].insertItem(v) ;
        adjList[v].insertItem(u) ;
        edgeWeight[u][v] = weight ;
        distMap[u][u] = 0 ;
        distMap[u][v] = weight ;
        preMat[u][v] = u ;
        edgeWeight[v][u] = weight ;
        distMap[v][v] = 0 ;
        distMap[v][u] = weight ;
        preMat[v][u] = v ;
    }
    nEdges++ ;
}

void Graph::removeEdge(int u, int v) {
    if(directed==true){
        adjList[u].removeItem(v) ;
        edgeWeight[u][v] = 0 ;
        distMap[u][v] = INFINITY ;
    } else{
        adjList[u].removeItem(v) ;
        adjList[v].removeItem(u) ;
        edgeWeight[u][v] = 0 ;
        edgeWeight[v][u] = 0 ;
        distMap[u][v] = INFINITY ;
        distMap[v][u] = INFINITY ;
    }
    nEdges-- ;
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
    delete[] edgeWeight ;
    delete[] color ;
    delete[] parent ;
    delete[] dist;
    delete[] start_time ;
    delete[] end_time ;
}


void Graph::printPath(int value) {
    for(int i=1;i<nVertices;i++){
        if(i==value){

            cout<<i<<"     "<<vertexs[i].getDistance()<<"      "<<"nil"<<endl ;
        } else
            cout<<i<<"     "<<vertexs[i].getDistance()<<"      "<<vertexs[i].getParent()<<endl ;
    }
}

void Graph::bfs(int source)
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
        printf("%d ",u) ;
        int i = 0 ;
        while(i<adjList[u].getLength()){
            int v = adjList[u].getItem(i) ;
            if(color[v]==WHITE){
                color[v] = GREY ;
                dist[v] = dist[u] + 1 ;
                parent[v] = u ;
                q.enqueue(v) ;
            }
            i++ ;
        }
    }
}

int Graph::bfsForDist(int source,int target)
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
            if(color[v]==WHITE){
                color[v] = GREY ;
                dist[v] = dist[u] + 1 ;
                parent[i] = u ;
                q.enqueue(v) ;
            }
            i++ ;
        }
    }

    return dist[target] ;
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
    printf("%d ",vertex) ;
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

void Graph::AllPairShortestPath() {
    cout<<"Intial Graph::"<<endl ;
    for(int i =1 ;i<nVertices;i++){
        for(int j=1;j<nVertices;j++){
            if(distMap[i][j]==INFINITY) cout<<"INF   " ;
            else cout<<distMap[i][j]<<"     " ;
        }
        cout<<endl ;
    }
    cout<<endl ;
    for(int k=1;k<nVertices;k++){
        for(int i=1;i<nVertices;i++){
            for(int j=1;j<nVertices;j++){
                if(distMap[i][j]>distMap[i][k]+distMap[k][j]){
                    distMap[i][j] = distMap[i][k] + distMap[k][j] ;
                    preMat[i][j] = preMat[k][j] ;
                }
            }
        }
    }
    cout<<"Distance Matrix::"<<endl ;
    for(int i =1 ;i<nVertices;i++){
        for(int j=1;j<nVertices;j++){
            if(distMap[i][j]==INFINITY) cout<<"INF   " ;
            else cout<<distMap[i][j]<<"     " ;
        }
        cout<<endl ;
    }
    cout<<endl ;
    cout<<"Predecessor Matrix::"<<endl ;
    for(int i =1 ;i<nVertices;i++){
        for(int j=1;j<nVertices;j++){
            if(preMat[i][j]==INFINITY) cout<<"INF   " ;
            else cout<<preMat[i][j]<<"     " ;
        }
        cout<<endl ;
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
    G.AllPairShortestPath() ;
    return 0;
}