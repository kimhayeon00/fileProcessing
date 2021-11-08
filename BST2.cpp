#include <iostream>
using namespace std;

class Node{
    private:
        int key;
        Node *left;
        Node *right;
        Node(int value){ key = value; left = NULL; right = NULL;}
    friend class Tree;
};
class Tree{
    private:
        Node *T;
        int H;
        int MaxH;
        int leafNum;
        string flag;
    public:
        Tree(){T = NULL;};
        ~Tree(){};
        void insertBST(Node *, int);
        void deleteBST(Node *, int);
        void inorderBST(Node *);

        int height(Node *);
        int noNodes(Node *);
        Node* getT(){return T;};
        Node* getNode(int);
        Node* searchBST(Node *, int);
        Node* searchParentBST(Node *, int, Node *, Node *);
        Node* maxNode(Node *);
        Node* minNode(Node *);


};
Node* Tree::getNode(int newKey) {
    Node* p;
    p = new Node(newKey);
    return p;
   }

int Tree::height(Node *p) {
  if(!p){
    return 0;
  }
  else{
    int left_h = height(p->left);
    int right_h = height(p->right);
    return 1 + (left_h > right_h ? left_h : right_h);
  }
}


int Tree::noNodes(Node *p){
    if (p == NULL){
     return 0;
    }
     return 1 + noNodes(p->left) + noNodes(p->right);
}

Node* Tree:: maxNode(Node *p){
    while(p->right){
        p = p->right;
    }
    return p;
}
Node* Tree:: minNode(Node *p){
    while(p->left){
        p = p->left;
    }
    return p;
}


void Tree::insertBST(Node *t, int newKey){
    Node *q = NULL;
    Node *p = t;
    while(p != NULL){
        if(newKey == p->key) return;
        q = p;
        if(newKey < p->key) p = p->left;
        else p = p->right;
    }
    Node *newNode = getNode(newKey);
    newNode->key = newKey;
    newNode->right = NULL;
    newNode->left = NULL;

    if(T == NULL) T = newNode;
    else if(newKey < q->key){
        q->left = newNode;
    }
    else{
            q->right = newNode;
    }
    return;
}

void Tree::inorderBST(Node *t){
    if(t){
        inorderBST(t->left);
        cout << t->key << " ";
        inorderBST(t->right);
    }
}

void Tree::deleteBST(Node *t, int deleteKey) {
  Node *q = NULL;
  Node *p = getT();
  while(p->key != deleteKey){
      if(deleteKey == p->key) return;
      q = p;
      if(deleteKey < p->key) p = p->left;
      else p = p->right;
  }
    if(p == NULL) return;
    else if(q == NULL) {
        if(p->left == NULL && p->right == NULL) T = NULL;
        else if (p->left == NULL || p->right == NULL) {
            if(p->left != NULL) {
                T = T->left;
            }
            else {
                T = T->right;
            }
        }
        else {
            Node *r = NULL;
            if(height(p->left) > height(p->right)) {
                r = maxNode(p->left);
                flag = "LEFT";
            }
            else if(height(p->left) < height(p->right)) {
                r = minNode(p->right);
                flag = "RIGHT";
            }
            else if(height(p->left) == height(p->right)) {
                if(noNodes(p->left) >= noNodes(p->right)){
                    r = maxNode(p->left);
                    flag = "LEFT";
                }
                else if(noNodes(p->left) < noNodes(p->right)){
                    r = minNode(p->right);
                    flag = "RIGTH";
                }
            }

            if(flag == "LEFT") deleteBST(p->left, r->key);
            else deleteBST(p->right, r->key);
            p->key = r->key;
        }
    }

    else if((p->left == NULL) && (p->right == NULL)) {
        if(q->left == p) q->left = NULL;
        else q->right = NULL;
    }
    else if((p->left == NULL) || (p->right == NULL)) {
        if(p->left != NULL) {
            if(q->left == p) {
                q->left = p->left;
            }
            else {
                q->right = p->left;
             }
        }
        else {
            if(q->left == p) {
                q->left = p->right;
            }
            else {
                q->right = p->right;
            }
        }
    }
    else if((p->left != NULL) && (p->right != NULL)) {
        Node *r = NULL;
        if(height(p->left) > height(p->right)) {
            r = maxNode(p->left);
            flag = "LEFT";
        }
        else if(height(p->left) < height(p->right)) {
            r = minNode(p->right);
            flag = "RIGHT";
        }
        else if(height(p->left) == height(p->right)) {
            if(noNodes(p->left) >= noNodes(p->right)){
                r = maxNode(p->left);
                flag = "LEFT";
            }
            else if(noNodes(p->left) < noNodes(p->right)){
                r = minNode(p->right);
                flag = "RIGTH";
            }
        }
        if(flag == "LEFT") deleteBST(p->left, r->key);
        else deleteBST(p->right, r->key);
        p->key = r->key;
    }
}


Node* Tree::searchBST(Node *t, int searchKey){
    Node *p = t;
    if(p == NULL) return NULL;
    else if(searchKey == p->key){
        return p;
    }
    else if(searchKey > p->key){
        return searchBST(p->right,searchKey);
    }
    else{
        return searchBST(p->left,searchKey);
    }
}
Node* Tree::searchParentBST(Node *t, int searchKey, Node *p, Node *q){

    p = t;
    if(p == NULL) return NULL;
    else if(searchKey == p->key){
        return q;
    }
    else if(searchKey > p->key){
        q = p;
        return searchParentBST(p->right,searchKey,p,q);
    }
    else{
        q = p;
        return searchParentBST(p->left,searchKey,p,q);
    }
}

int main()
{
    Tree t;

    int list[20] = {25, 500, 33, 49, 17, 403, 29, 105, 39, 66, 305, 44, 19, 441, 390, 12, 81, 50, 100, 999};
    for(int i=0;i<20;i++){
      t.insertBST(t.getT(), list[i]);
      t.inorderBST(t.getT());
      cout << endl;
    }
    for(int i=0;i<20;i++){
      t.deleteBST(t.getT(), list[i]);
      t.inorderBST(t.getT());
      cout << endl;
    }
    Tree t2;
    for(int i=0;i<20;i++){
      t2.insertBST(t2.getT(), list[i]);
      t2.inorderBST(t2.getT());
      cout << endl;
    }
    for(int i=19;i>=0;i--){
      t2.deleteBST(t2.getT(), list[i]);
      t2.inorderBST(t2.getT());
      cout << endl;
    }
}
