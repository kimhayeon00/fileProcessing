/**
 * File processing, 2020
 * AVL.cpp
 * implementation of AVL tree
 */
#include <iostream>
#include <stdio.h>
using namespace std;
/**
 * Node represents a single node in AVL tree.
 */
typedef struct Node {
  int         key, bf;
  struct Node *left, *right;
} Node;

typedef Node *Tree;

/**
 * getNode returns a new node.
 * @return a new node
 */
Node *getNode() {
  Node *temp = new Node;
  temp->key = 0;
  temp->bf = 0;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}
int height(Node *p) {
  if(!p){
    return 0;
  }
  else{
    int left_h = height(p->left);
    int right_h = height(p->right);
    return 1 + (left_h > right_h ? left_h : right_h);
  }
}

/**
 * updateBF updates balancing factors of nodes in T
 * and finds the unbalanced node nearest to y.
 * @param T: an AVL tree
 * @param y: the inserted/deleted node
 * @param x: the unbalanced node nearest to y
 * @param p: parent node of x
 */
void updateBF(Tree *T, Node *y, Node **x, Node **p) {
  if (T == NULL) {
      return;
   }
   Node *temp = *T;
   Node *node_y = y;
   Node *tmp = NULL;

  while(true){
    tmp = temp;
    temp->bf = height(temp->left) - height(temp->right);
    if(abs(temp->bf)==2){
      *p = temp;
      *x = tmp;
    }
    if(temp->key < y->key){
      temp = temp->right;
    }
    else if(temp->key > y->key){
      temp = temp->left;
    }
    else{
      break;
    }
  }
   
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
}

/**
 * rotateLL implements LL rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateLL(Tree *T, Node *x, Node *p) {
  Node* temp = x->left;
  x->left = temp->right;
  temp->right = x;
  if (p == NULL) {
    *T = temp;
  }
  else {
    if (p->left == x) p->left = temp;
    else p->right = temp;
  }
   
      
}

/**
 * rotateRR implements RR rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateRR(Tree *T, Node *x, Node *p) {
  Node *temp = x->right;
  x->right = temp->left;
  temp->left = x;
  if (p == NULL) {
    *T = temp;
  }
  else {
    if (p->left == x) p->right = temp;
    else p->left = temp;
  }
}

/**
 * rotateLR implements LR rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateLR(Tree *T, Node *x, Node *p) {
  Node* temp = x->left;
  rotateRR(T, temp, x);
  rotateLL(T, x, p);

}

/**
 * rotateRL implements RL rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateRL(Tree *T, Node *x, Node *p) {
  Node* temp = x->right;
  rotateLL(T, temp, p);
  rotateRR(T, x, x);
}

/**
 * insertBST inserts newKey into T
 * and returns the inserted node.
 * @param T: a binary search tree
 * @param newKey: a key to insert
 * @return the inserted node
 */
Node *insertBST(Tree *T, int newKey) {
  Tree q = NULL;
  Tree p = *T;
  while(p != NULL){
        if(newKey == p->key) return 0;
        q = p;
        if(newKey < p->key) p = p ->left;
        else p = p->right;
    }
    Tree newNode = getNode();
    newNode->key = newKey;
    if(*T == NULL) {
      *T = newNode;
      return *T;
      }
    else if(newKey < q->key){
        q->left = newNode;
        return q->left;
    }
    else{
      q->right = newNode;
      return q->right;
    }


}

/**
 * insertAVL inserts newKey into T.
 * @param T: an AVL tree
 * @param newKey: a key to insert
 */
void insertAVL(Tree *T, int newKey) {
  /**
   * print "NO" if not rotates
   * print "LL" if rotates LL
   * print "RR" if rotates RR
   * print "LR" if rotates LR
   * print "RL" if rotates RL
   */
  Node* temp = insertBST(T,newKey);
  Node* x = NULL;
  Node* p = NULL;
    
  updateBF(T,temp,&x,&p);
  if(x == NULL){cout << "NO";}
  else{
    if(p->bf>1 && x->bf>0){
      rotateLL(T,x,p);
      cout << "LL";
    }
    else if(p->bf>1 && x->bf<0){
      rotateLR(T,x,p);
      cout << "LR";
    }
    else if(p->bf<-1 && x->bf>0){
      rotateRL(T,x,p);
      cout << "RL";
    }
    else if(p->bf<-1 && x->bf<0){
      rotateLL(T,x,p);
      cout << "RR";
    }

  }

}

/**
 * deleteBST deletes deleteKey from T
 * and returns the parent node of the deleted node.
 * @param T: a binary search tree
 * @param deleteKey: a key to delete
 * @return the parent node of the deleted node
 */

Node *deleteBST(Tree *T, int deleteKey) {
  Node* ptr = *T;
  if(ptr != NULL) {
        if(deleteKey < ptr->key)
            ptr->left = deleteBST(&(ptr->left), deleteKey);
        else if(deleteKey > ptr->key)
            ptr->right = deleteBST(&(ptr->right), deleteKey);
        else if((ptr->left == NULL) && (&(ptr->right) == NULL))
            ptr = NULL;
        else if(ptr->left == NULL) {
            Node *p = ptr;
            ptr = ptr->right;
            delete(p);
        }
        else if(ptr->right == NULL) {
            Node *p = ptr;
            ptr = ptr->left;
            delete(p);
        }
        else {
            Node *temp = NULL;
            while(true){
               if (ptr->right == NULL){
		            temp = ptr;	break;	
	            }
	            else{
		            ptr = ptr->right;
              }
            }
            

            ptr->key = temp->key;
            ptr->left = deleteBST(&(ptr->left), ptr->key);
        }
  }

}

/**
 * deleteAVL deletes deleteKey from T.
 * @param T: an AVL tree
 * @param deleteKey: a key to delete
 */
void deleteAVL(Tree *T, int deleteKey){
  /**
   * print "NO" if not rotates
   * print "LL" if rotates LL
   * print "RR" if rotates RR
   * print "LR" if rotates LR
   * print "RL" if rotates RL
   */
  Node* temp = deleteBST(T,deleteKey);
  Node* x = NULL;
  Node* p = NULL;
    
  updateBF(T,temp,&x,&p);
  if(x == NULL){cout << "NO";}
  else{
    if(p->bf>1 && x->bf>0){
      cout << "LL";
      rotateLL(T,x,p);
    }
    else if(p->bf>1 && x->bf<0){
      cout << "LR";
      rotateLR(T,x,p);
    }
    else if(p->bf<-1 && x->bf>0){
      cout << "RL";
      rotateRL(T,x,p);
    }
    else if(p->bf<-1 && x->bf<0){
      cout << "RR";
      rotateLL(T,x,p);
    }

  }
}

/**
 * inorderAVL implements inorder traversal in T.
 * @param T: an AVL tree
 */
void inorderAVL(Tree T) {
  if (T != NULL) {
      cout << T->key << " ";
      inorderAVL(T->left);
      inorderAVL(T->right);
   }
}

int main() {
  /* Do not modify the code below */

  int testcase[] = { 40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 66, 10, 22, 30, 44, 55, 50, 60, 25, 49 };

  Tree T = NULL;

  // insertion
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); insertAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

  // deletion
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); deleteAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

  T = NULL;

  // reinsertion
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); insertAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

  // redeletion
  for (int i=19; 0<=i; i--) { printf("%d ", testcase[i]); deleteAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }
}

