#include <iostream>
#include <vector>

using namespace std;

struct node {
  int value;
  node *left;
  node *right;
};

/**************************************
 * @class Queue
 * @desc  Implements Queue
 *************************************/
template <class T>
class Queue{
private:
  int front, rear, max;
  T *q;
public:
  Queue(int size=0){
    front = rear = 0;
    max = size;
    q = new T[size];
  }
  ~Queue(){
    delete []q;
  }
  int enqueue(T);
  T dequeue();
  T printQueue();
  T getItemAt(int index);
};


template <class T>
int Queue<T>::enqueue(T elem){
  if(front>=max){
    return -2;
  }
  q[front] = elem; front++;
}

template <class T>
T Queue<T>::dequeue(){
  if(front<=0){
    return -1;
  }
  T result = q[rear];
  ++rear;
  return result;

}

template <class T>
T Queue<T>::printQueue(){
  for (int i = 0; i < front; ++i){
    cout << q[i] << endl;
  }
}

template <class T>
T Queue<T>::getItemAt(int index){
  if (index <= max) {
    return q[index];
  }

  return -1;
}
//End Class


/**************************************
 * @class Stack
 * @desc  Implements Stack
 *************************************/
template <class T>
class Stack{
private:
  int front, rear, max;
  T *s;
public:
  Stack(int size=0){
    front = rear = 0;
    max = size;
    s = new T[size];
  }

  ~Stack(){
    delete []s;
  }

  int insert(T);
  T pop();
  T printStack();
  T getItemAt(int index);
  bool isEmpty();
};

template <class T>
int Stack<T>::insert(T item){
  if (rear >= max) {
    return -2;
  }
  s[rear] = item;
  rear++;
}

template <class T>
T Stack<T>::pop(){
  if(rear<=0){
    return -1;
  }
  T result = s[rear - 1];
  --rear;
  return result;
}

template <class T>
T Stack<T>::printStack(){
  for (int i = 0; i < rear; ++i){
    cout << s[i] << endl;
  }
}

template <class T>
T Stack<T>::getItemAt(int index){
  if (index < rear) {
    return s[index];
  }

  return -1;
}

template <class T>
bool Stack<T>::isEmpty(){
  if (rear <= 0) {
    return true;
  }

  return false;
}
// End Class

/**************************************
 * @class btree
 * @desc  Implements btree
 *************************************/
class btree{
public:
  btree();
  ~btree();

  int getBTreeSize();
  void insert(int key);
  node *search(int key);
  void destroy_tree();
  void inorder_print();
  void postorder_print();
  void preorder_print();
  void breadth_first_search(Queue<int> *myQueue);
  void depth_first_search(Stack<int> *myStack, string order);
  bool is_valid_bst();

private:
  void setBTreeSize(int newSize);
  void destroy_tree(node *leaf);
  void insert(int key, node *leaf);
  node *search(int key, node *leaf);
  void inorder_print(node *leaf);
  void postorder_print(node *leaf);
  void preorder_print(node *leaf);
  void breadth_first_search(node *leaf, Queue<int> *myQueue);
  void depth_first_search(node *leaf, Stack<int> *myStack, string order);
  bool is_valid_bst(node *leaf, int min, int max);

  node *root;
  int BTreeSize;
};


btree::btree(){
  root = NULL;
}

btree::~btree(){
  destroy_tree();
}

int btree::getBTreeSize(){
  return BTreeSize;
}

void btree::destroy_tree(node *leaf){
  if(leaf != NULL){
    destroy_tree(leaf->left);
    destroy_tree(leaf->right);
    delete leaf;
  }
}

void btree::insert(int key, node *leaf){

  if(key < leaf->value){
    if(leaf->left != NULL){
      insert(key, leaf->left);
    }else{
      leaf->left = new node;
      leaf->left->value = key;
      leaf->left->left = NULL;
      leaf->left->right = NULL;
      setBTreeSize(this->BTreeSize + 1);
    }
  }else if(key >= leaf->value){
    if(leaf->right != NULL){
      insert(key, leaf->right);
    }else{
      leaf->right = new node;
      leaf->right->value = key;
      leaf->right->right = NULL;
      leaf->right->left = NULL;
      setBTreeSize(this->BTreeSize + 1);
    }
  }

}

void btree::insert(int key){
  if(root != NULL){
    insert(key, root);
  }else{
    root = new node;
    root->value = key;
    root->left = NULL;
    root->right = NULL;
    setBTreeSize(1);
  }
}

void btree::setBTreeSize(int newSize) {
  BTreeSize = newSize;
}


node *btree::search(int key, node *leaf){
  if(leaf != NULL){
    if(key == leaf->value){
      return leaf;
    }
    if(key < leaf->value){
      return search(key, leaf->left);
    }else{
      return search(key, leaf->right);
    }
  }else{
    return NULL;
  }
}

node *btree::search(int key){
  return search(key, root);
}

void btree::destroy_tree(){
  destroy_tree(root);
}

void btree::inorder_print(){
  inorder_print(root);
  cout << "\n";
}

void btree::inorder_print(node *leaf){
  if(leaf != NULL){
    inorder_print(leaf->left);
    cout << leaf->value << ",";
    inorder_print(leaf->right);
  }
}

void btree::postorder_print(){
  postorder_print(root);
  cout << "\n";
}

void btree::postorder_print(node *leaf){
  if(leaf != NULL){
    inorder_print(leaf->left);
    inorder_print(leaf->right);
    cout << leaf->value << ",";
  }
}

void btree::preorder_print(){
  preorder_print(root);
  cout << "\n";
}

void btree::preorder_print(node *leaf){
  if(leaf != NULL){
    cout << leaf->value << ",";
    inorder_print(leaf->left);
    inorder_print(leaf->right);
  }
}

void btree::breadth_first_search(Queue<int> *myQueue){
  return breadth_first_search(root, myQueue);
}

void btree::breadth_first_search(node *leaf, Queue<int> *myQueue){
  vector<node> current;
  current.reserve(this->BTreeSize);
  current.push_back(*leaf);

  while (current.size() > 0) {
    vector<node> next;
    myQueue->enqueue(current[0].value);

    if (current[0].left){
      next.resize(1, *current[0].left);
    }

    if (current[0].right){
      next.resize(2, *current[0].right);
    }

    for(int i = 1; i < current.size(); i++){
      myQueue->enqueue(current[i].value);

      if(current[i].left){
        next.resize(next.size() + 1, *current[i].left);
      }

      if(current[i].right){
        next.resize(next.size() + 1, *current[i].right);
      }
    }

    if (next.size() != 0) {
      int add_size = next.size();
      vector<node> new_current;
      new_current.reserve(next.size());
      new_current = next;
      current = new_current;
    } else {
      current.clear();
    }
  }
}

void btree::depth_first_search(Stack<int> *myStack, string order){
  return btree::depth_first_search(root, myStack, order);
}

void btree::depth_first_search(node *leaf, Stack<int> *myStack, string order){
  if (order == "pre_order") {
    myStack->insert(leaf->value);
    if (leaf->left) {
      depth_first_search(leaf->left, myStack, order);
    }

    if (leaf->right) {
      depth_first_search(leaf->right, myStack, order);
    }
  } else if (order == "in_order") {
    if (leaf->left) {
      depth_first_search(leaf->left, myStack, order);
    }

    myStack->insert(leaf->value);

    if (leaf->right) {
      depth_first_search(leaf->right, myStack, order);
    }
  } else if (order == "post_order") {
    if (leaf->left) {
      depth_first_search(leaf->left, myStack, order);
    }

    if (leaf->right) {
      depth_first_search(leaf->right, myStack, order);
    }

    myStack->insert(leaf->value);
  }
}

bool btree::is_valid_bst() {
  return is_valid_bst(root, INT_MIN, INT_MAX);
}

bool btree::is_valid_bst(node *leaf, int min, int max) {
  if (leaf != NULL){
    return true;
  }

  if (leaf->value < min || leaf->value > max) {
    return false;
  }

  return (is_valid_bst(leaf->left, min, leaf->value - 1) && is_valid_bst(leaf->right, leaf->value + 1, max));
}
//End Class


int main(void){
  btree *tree = new btree();

  tree->insert(10);
  tree->insert(6);
  tree->insert(11);
  tree->insert(18);
  tree->insert(8);
  tree->insert(5);
  tree->insert(14);

  tree->preorder_print();
  tree->inorder_print();
  tree->postorder_print();

  Queue<int> myQueue(tree->getBTreeSize());
  tree->breadth_first_search(&myQueue);

  cout << "\nBFS: " << endl;
  myQueue.printQueue();
  Stack<int> myStack(tree->getBTreeSize());
  tree->depth_first_search(&myStack, "in_order");
  cout << "\nDFS: " << endl;
  myStack.printStack();
  cout << "STACK IS EMPTY??: " << myStack.isEmpty() << endl;
  cout << "IS TREE VALID BST??:: " << tree->is_valid_bst() << endl;
  tree->~btree();
  tree = NULL;

  return 0;
}
