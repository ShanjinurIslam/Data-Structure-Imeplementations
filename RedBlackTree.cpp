#include <bits/stdc++.h>
#define BLACK 0
#define RED 1
using namespace std ;

struct tree_node{
    int value ;
    int color ;
    tree_node *parent ;
    tree_node *left ;
    tree_node *right;
};

class RedBlackTree{
private:
    tree_node *root ;

public:
    RedBlackTree(){
        root = 0 ;
    }

    void bfs()
    {
        queue<tree_node*> q;
        tree_node *tem = root ;
        q.push(tem);

        while (!q.empty()) {

            tree_node *f = q.front();
            q.pop();

            cout << f->value << "   ";
            if(f->left!=0){
                q.push(f->left) ;
            }
            if(f->right!=0){
                q.push(f->right) ;
            }
        }
    }

    int calcNodeHeight(struct tree_node * node) //return height of a node
    {
        if(node==0) return -1;
        int l, r;
        l = calcNodeHeight(node->left);
        r = calcNodeHeight(node->right);
        if(l>r) return l+1;
        else return r+1;
    }

    tree_node *search_node(tree_node *node,int value){
        if(node==0) return 0 ;
        if(node->value == value )
            return node;
        tree_node *t = 0;
        if(value < node->value)
            t = search_node(node->left, value);
        else
            t = search_node(node->right, value);
        return t;
    }

    tree_node* make_tree_node(int value,tree_node *parent){
        tree_node *new_node ;
        new_node = (struct tree_node *)malloc(sizeof(struct tree_node));
        new_node->value = value ;
        new_node->parent = parent ;
        new_node->left = 0 ;
        new_node->right = 0 ;
        new_node->color = RED ;
        return new_node;
    }

    void left_rotate(tree_node *x){
        tree_node *y = x->right ;
        if(y!=0){
            x->right = y->left ;
            if(y->left==0){
                y->left = new tree_node() ;
                y->left->parent = x ;
            }
            else{
                y->left->parent = x ; //
            }
            y->parent = x->parent ;
            if(x->parent == 0){
                root = y ;
            }
            else if(x == x->parent->left){
                x->parent->left = y ;
            }
            else{
                x->parent->right = y ;
            }
            y->left = x ;
            x->parent = y ;
        }
    }

    void right_rotate(tree_node *x){
        tree_node *y = x->left ;
        //
        if(y!=0){
            x->left = y->right ;
            if(y->right==0){
                y->right = new tree_node() ;
                y->right->parent = x ;
            }
            else{
                y->right->parent = x ;
            }
            y->parent = x->parent ;
            if(x->parent == 0){
                root = y ;
            }
            else if(x == x->parent->right){
                x->parent->right = y ;
            }
            else{
                x->parent->left = y ;
            }
            y->right = x ;
            x->parent = y ;
        }
    }

    void insert_fix(tree_node *z){
        if(z->parent!=0){
            if(z->parent->color==RED){
                while (z->parent!=0 && z->parent->color==RED){
                    if(z->parent->parent!=0){
                        if(z->parent == z->parent->parent->left){
                            tree_node *y = z->parent->parent->right;
                            if(y!=0){
                                if(y->color==RED){ // change color to both parent and uncle
                                    z->parent->color = BLACK ;
                                    y->color = BLACK ;
                                    z->parent->parent->color = RED ;
                                    if(z->parent->parent!=0){
                                        z = z->parent->parent ; //for fixing up
                                    }
                                }
                                else{
                                    if(z==z->parent->right){ //for fixing where uncle is black
                                        z = z->parent ;
                                        left_rotate(z) ;
                                    }
                                    z->parent->parent->color = RED ;
                                    z->parent->color = BLACK ;
                                    right_rotate(z->parent->parent) ;
                                }
                            }
                            else{
                                if(z == z->parent->left){ //20-15-10 --> 15/10 \20
                                    z->parent->parent->color = RED ;
                                    z->parent->color = BLACK ;
                                    right_rotate(z->parent->parent) ;
                                }
                                else{ // 20-10-15 -> 15 / 10 \20
                                    z->color = BLACK ;
                                    z->parent->color = RED ;
                                    z->parent->parent->color = RED ;
                                    left_rotate(z->parent) ;
                                    right_rotate(z->parent) ;
                                }
                            }
                        }
                        else{
                            tree_node *y = z->parent->parent->left;
                            if(y!=0){
                                if(y->color==RED){
                                    z->parent->color = BLACK ;
                                    y->color = BLACK ;
                                    z->parent->parent->color = RED ;
                                    if(z->parent->parent!=0){
                                        z = z->parent->parent ;
                                    }
                                }
                                else{
                                    if(z==z->parent->left){
                                        z = z->parent ;
                                        right_rotate(z) ;
                                    }
                                    z->parent->parent->color = RED ;
                                    z->parent->color = BLACK ;
                                    left_rotate(z->parent->parent) ;
                                }
                            }
                            else{
                                if(z == z->parent->right){
                                    z->parent->parent->color = RED ;
                                    z->parent->color = BLACK ;
                                    left_rotate(z->parent->parent) ;
                                }
                                else{
                                    z->color = BLACK ;
                                    z->parent->color = RED ;
                                    z->parent->parent->color = RED ;
                                    right_rotate(z->parent) ;
                                    left_rotate(z->parent) ;
                                }
                            }
                        }
                    }
                    root->color = BLACK ;
                }
            }
            else{ //corner case when parent is white but left child or right child is black also.
                if(z->parent!=0){
                    if(z == z->parent->left){
                        if(z->parent->right!=0){
                            if(z->parent->right->color==BLACK){
                                z->color = BLACK ;
                            }
                        }
                    }
                    if(z == z->parent->right){
                        if(z->parent->left!=0){
                            if(z->parent->left->color==BLACK){
                                z->color = BLACK ;
                            }
                        }
                    }
                }
            }
        }

        else{
            z->color = BLACK ;
        }

    }

    void insert(int value){
        tree_node *parent = 0 ;
        tree_node *tem = root ;
        while(tem!=0){ //to search the parent
            parent = tem ;
            if(value<tem->value){
                tem = tem->left ;
            }
            else tem = tem->right ;
        }

        tree_node *z = make_tree_node(value,parent) ;
        if(parent==0){
            root = z ;
        }
        else if(z->value<parent->value){
            parent->left = z ;
        }
        else if(z->value>=parent->value){
            parent->right = z ;
        }
        else{
            return;
        }

        z->left = 0 ;
        z->right= 0 ;
        z->color= RED ;
        insert_fix(z) ;
    }

    void transplant(tree_node *u, tree_node *v){
        if(u->parent==0){
            root = v ;
        }
        else if(u == u->parent->left){
            u->parent->left = v ;
        }
        else{
            u->parent->right = v ;
        }

        if(v!=0){
            if(v->parent!=0){
                v->parent = u->parent ;
            }
        }
    }
    tree_node* getMinimum(tree_node *node){
        if(node->left==0) return node ;
        else return getMinimum(node->left) ;
    }

    void delete_fixup(tree_node *x){
        if(x!=0){
            while(x!=root && x->color == BLACK){
                if(x->parent!=0){
                    if(x==x->parent->left){
                        tree_node *w = x->parent->right ; //sibling of x
                        if(w!=0){
                            if(w->color==RED){ //if color of sibling of w is red
                                w->color = BLACK ;
                                x->parent->color = RED ;
                                left_rotate(x->parent) ;
                            }

                            if(w->color==BLACK && w->right!=0 && w->right->color==BLACK){ // if siblings both child color is black
                                w->color = RED ;
                                x = x->parent ;
                            }

                            else if(w->right!=0 && w->right->color==BLACK){ //if sibling left child color is red
                                if(w->left!=0){
                                    w->left->color = BLACK ;
                                }
                                w->color = RED ;
                                right_rotate(w) ;
                                w = x->parent->right ;
                            }
                            w->color = x->parent->color ; //if sibling right child color is red
                            x->parent->color = BLACK ;
                            w->right->color = BLACK ;
                            left_rotate(x->parent) ;
                            x = root ;
                        }
                    }
                    else if(x==x->parent->right){
                        tree_node *w = x->parent->left ;
                        if(w!=0){
                            if(w->color==RED){
                                w->color = BLACK ;
                                x->parent->color = RED ;
                                right_rotate(x->parent) ;
                            }

                            if(w->color==BLACK && w->left!=0 && w->left->color==BLACK){
                                w->color = RED ;
                                x = x->parent ;
                            }

                            else if(w->left!=0 && w->left->color==BLACK){
                                if(w->right!=0){
                                    w->right->color = BLACK ;
                                }
                                w->color = RED ;
                                left_rotate(w) ;
                                w = x->parent->left ;
                            }
                            w->color = x->parent->color ;
                            x->parent->color = BLACK ;
                            w->left->color = BLACK ;
                            right_rotate(x->parent) ;
                            x = root ;
                        }
                    }
                }
                else{
                    x->color = BLACK ;
                }
            }

            x->color = BLACK ;
        }
    }
    void delete_node(int value){
        tree_node *z = search_node(root,value) ;
        if(z!=0){
            tree_node *y = z ;
            int y_original_color = y->color ;
            if(z->left==0){
                transplant(z,z->right) ;
            }
            else if(z->right==0){
                transplant(z,z->left) ;
            }
            else{
                y = getMinimum(z->right) ; //to get the successor
                y_original_color = y->color ;
                tree_node *x = y->right ;
                if(y->parent==z) {
                    if(x!=0){
                        if(x->parent!=0){
                            x->parent = y ;
                        }
                    }
                }
                else{
                    transplant(y,y->right) ; // set y to y->right
                    y->right = z->right ;
                    y->right->parent = y ;
                }
                transplant(z,y) ;
                y->left = z->left ;
                y->left->parent = y ;
                y->color = z->color ;
                if(y_original_color==BLACK){
                    delete_fixup(x) ;
                }
            }

            cout<<"Deleted" ;
        }
        else{
            cout<<"Not Found in  this Red Black Tree"<<endl ;
        }
    }

    void printInOrder(tree_node *node,int height){
        if(node==NULL) return ;
        printInOrder(node->left, height-1);
        for(int i=0;i<height;i++)printf("   ");
        printf("%03d %d\n",node->value,node->color);
        printInOrder(node->right, height-1);
    }

    tree_node* getRoot(){
        return root ;
    }
};


int main(){
    RedBlackTree tree ;
    char option ;
    while(true){
        cout<<"1.Insert 2.Show Tree 3. Search Tree 4.Delete 5.exit"<<endl ;
        cin>>option ;
        if(option=='1'){
            int v ;
            cin>>v ;
            tree.insert(v) ;
        }
        if(option=='2'){
            tree.printInOrder(tree.getRoot(),tree.calcNodeHeight(tree.getRoot())) ;
            cout<<endl ;
            //tree.bfs() ;
        }
        if(option=='3'){
            int v ;
            cin>>v ;
            tree_node *b = tree.search_node(tree.getRoot(),v) ;
            if(b!=0){
                cout<<"Found" ;
            }
            else{
                cout<<"Not Found" ;
            }
        }
        if(option=='4'){
            int v ;
            cin>>v ;
            tree.delete_node(v) ;
        }
        if(option=='5'){
            break ;
        }
    }
    return 0 ;
}
