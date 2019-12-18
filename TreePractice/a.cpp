#include <cmath>
#include <iostream>

class node {
public:
  int item;
  int balance;
  int side;
  int height;
  node *left, *right, *parent;
  node(int x);
  node();
};

node::node(int x) {
  item = x;
  balance = side = height = 0;
  left = right = parent = nullptr;
}

node::node() {
  item = balance = side = height = 0;
  left = right = parent = nullptr;
}

class tree {
private:
  node *__root;
  int __height(node *);
  void __leftRotate(node *);
  void __rightRotate(node *);
  void __inOrder(node *);

public:
  tree();
  int search(int);
  void insert(int);
  void display();
  void remove(int);
};

int tree::__height(node *x) {
  if (x) {
    return x->height;
  } else {
    throw - 1;
  }
}

void tree::__inOrder(node *x) {
  __inOrder(x->left);
  std::cout << x->item << std::endl;
  __inOrder(x->right);
}

void tree::remove(int x) {
  node *currNode = __root;

  while (currNode) {
    if (currNode->item == x) {
      break;
    } else {
      if (x < currNode->item) {
        currNode = currNode->left;
      } else {
        currNode = currNode->right;
      }
    }
  }
}

void tree::insert(int x) {
  node *newNode = new node(x);
  node *currNode = __root;

  if (__root == nullptr) {
    __root = newNode;
  }

  while (true) {
    if (x < currNode->item) {
      if (currNode->left) {
        currNode = currNode->left;
      } else {
        currNode->left = newNode;
        currNode->side = -1;
        break;
      }
    } else {
      if (currNode->right) {
        currNode = currNode->right;
      } else {
        currNode->right = newNode;
        currNode->side = 1;
        break;
      }
    }
  }

  newNode->parent = currNode;

  currNode = newNode->parent;
  node *prevNode = currNode;

  do {
    int rh = __height(currNode->right);
    int lh = __height(currNode->left);
    int bal = lh - rh;
    currNode->height = 1 + std::max(lh, rh);
    currNode->balance = bal;

    if (abs(bal) > 1) {
      if (prevNode->balance < 0 && currNode->balance < 0) {
        __leftRotate(currNode);
      } else if (prevNode->balance > 0 && currNode->balance > 0) {
        __rightRotate(currNode);
      } else if (prevNode->balance < 0 && currNode->balance > 0) {
        __rightRotate(prevNode);
        __leftRotate(currNode);
      } else if (prevNode->balance > 0 && currNode->balance < 0) {
        __leftRotate(prevNode);
        __rightRotate(currNode);
      }
    }
    prevNode = currNode;
    currNode = currNode->parent;
  } while (currNode);
}

void tree::__leftRotate(node *current) {
  node *parent = current->parent;
  node *left = current->left;
  node *replacable = left->right;

  left->right = current;
  current->parent = left;
  left->parent = parent;
  current->left = replacable;
}
