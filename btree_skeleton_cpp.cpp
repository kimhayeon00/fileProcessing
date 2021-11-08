/*
 * File processing, 2020
 * btree.cpp
 * implementation of B-tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <cmath>

/**
 * BTNode represents a single node in B-tree.
 */
typedef struct BTNode {
  int           n,  *K;
  struct BTNode **P;
} BTNode;

/**
 * getBTNode retruns a new BTNode.
 * @param m: number of branch points in B-tree
 * @return a new BTNode
 */
BTNode *getBTNode(int m) {
  BTNode *node  = (BTNode *)malloc(sizeof(BTNode));
  node -> n     = 0;
  node -> K     = (int *)malloc(sizeof(int) * (m-1));
  node -> P     = (BTNode **)malloc(sizeof(BTNode *) * m);
  return node;
}

typedef BTNode *BTree;

/**
 * insertBT inserts newKey into T.
 * @param T: a B-tree
 * @param m: number of branch points in B-tree
 * @param newKey: a key to insert
 */
void insertBT(BTree *T, int m, int newKey) {
  /* write your code here */
  Node *p = T;
        Node *x = new BTNode(m);
        Node *y = nullptr;
        stack<Node *> s;
        bool overflow = false;

        if (!p->n) {
            p->K[1] = newKey;
            p->n++;
            return;
        }
        int i;
        do {
            i = 1;
            while (i <= p->n && newKey > p->K[i]) {
                i++;
            }

            if (i <= p->n && newKey == p->K[i]) {
                return;
            } else {
                s.push(p);
            }
        } while (p = p->P[i - 1]);

        p = s.top();
        s.pop();

        bool finished = false;

        do {
            if (p->n < m - 1) {

                int i = 1;

                while (i <= p->n && newKey > p->K[i]) {
                    i++;
                }

                vector<int>::iterator it = p->K.begin();

                for (int j = 0; j < i; j++) {
                    it++;
                }
                p->K.insert(it, newKey);

                for (int j = p->n + 1; j > i; j--) {
                    p->P[j] = p->P[j - 1];
                }

                p->indexP = i;

                p->n++;

                finished = true;

                if (overflow) {
                    int j = p->indexP;
                    p->P[j] = y;
                }
            } else {
                Node *tempNode = new Node(p->m + 1);

                tempNode->K = p->K;

                for (int i = 0; i < p->m; i++) {
                    tempNode->P[i] = p->P[i];
                }

                tempNode->n = p->n;

                int i = 1;
                while (i <= tempNode->n && newKey > tempNode->K[i]) {
                    i++;
                }

                vector<int>::iterator it = tempNode->K.begin();

                for (int j = 0; j < i; j++) {
                    it++;
                }

                tempNode->K.insert(it, newKey);

                for (int j = tempNode->n + 1; j > i; j--) {
                    tempNode->P[j] = tempNode->P[j - 1];
                }

                tempNode->indexP = i;

                tempNode->n++;

                newKey = tempNode->K[tempNode->m / 2];
                int j = tempNode->indexP;

                if (overflow) {
                    Node *y_old = y;
                    tempNode->P[j] = y_old;
                }

                p->K.clear();
                p->K.resize(p->m);
                p->P.clear();
                p->P.resize(p->m);
                p->n = 0;

                int sub;
                for (sub = 1; sub < tempNode->m / 2; sub++) {
                    p->K[sub] = tempNode->K[sub];
                    p->P[sub - 1] = tempNode->P[sub - 1];
                    p->n++;
                }
                p->P[sub - 1] = tempNode->P[sub - 1];

                y = new Node(tempNode->m - 1);

                j = 1;
                i = 0;
                for (i = tempNode->m / 2 + 1; i < tempNode->m; i++) {
                    y->K[j] = tempNode->K[i];
                    y->P[j - 1] = tempNode->P[i - 1];
                    y->n++;
                    j++;
                }
                y->P[j - 1] = tempNode->P[i - 1];

                overflow = true;

            }

            if (!s.empty()) {
                p = s.top();
                s.pop();
            } else if (!finished) {
                Node *T = new Node(m);
                T->K[1] = newKey;
                T->n = 1;
                T->P[0] = p;
                T->P[1] = y;
                root = T;
                finished = true;

            }
        } while (!finished);
}

/**
 * deleteBT deletes oldKey from T.
 * @param T: a B-tree
 * @param m: number of branch points in B-tree
 * @param oldKey: a key to delete
 */
void deleteBT(BTree *T, int m, int oldKey) {
  /* write your code here */
}

/**
 * inorderBT implements inorder traversal in T.
 * @param T: a B-tree
 */
void inorderBT(BTree T) {
  /* write your code here */
  int i;
  for (i = 0; i < T->n; i++){
    if (T == false)
      P[i]->inorderBT();
      cout << T->K[i] << " ";
    }
    if (T == false)
      P[i]->inorderBT();
}

int main() {
  /* do not modify the code below */
  
  int insertTestCases[] = { 40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 66, 10, 22, 30, 44, 55, 50, 60, 100, 28, 18, 9, 5, 17, 6, 3, 1, 4, 2, 7, 8, 73, 12, 13, 14, 16, 15, 25, 24, 28, 45, 49, 42, 43, 41, 47, 48, 46, 63, 68, 61, 62, 64, 69, 67, 65, 54, 59, 58, 51, 53, 57, 52, 56, 83, 81, 82, 84, 75, 89 };
  int deleteTestCases[] = { 66, 10, 22, 30, 44, 55, 50, 60, 100, 28, 18, 9, 5, 17, 6, 3, 1, 4, 2, 7, 8, 73, 12, 13, 14, 16, 15, 25, 24, 28, 40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 45, 49, 42, 43, 41, 47, 48, 46, 63, 68, 53, 57, 52, 56, 83, 81, 82, 84, 75, 89, 61, 62, 64, 69, 67, 65, 54, 59, 58, 51 };

  BTree T = NULL;

  for (int tC : insertTestCases) { insertBT(&T, 3, tC); inorderBT(T); printf("\n"); }
  for (int tC : deleteTestCases) { deleteBT(&T, 3, tC); inorderBT(T); printf("\n"); }

  T = NULL;

  for (int tC : insertTestCases) { insertBT(&T, 4, tC); inorderBT(T); printf("\n"); }
  for (int tC : deleteTestCases) { deleteBT(&T, 4, tC); inorderBT(T); printf("\n"); }
}