#include "binaryTree.h"
#include <iostream>
#include <vector>

using namespace std;


/* ================================== Node =================================== */
Node::Node(const string &str, int num, Node *left, Node *right):str(str), num(num),left(left),right(right) {
    // REQUIRES: The input left and right point to a dynamically allocated node object,
    //           if not being NULL.
    // MODIFIES: this
    // EFFECTS: Construct a node with given input values.
}

static void deep_delete(Node *n){
if(n==nullptr){return;}
else{
deep_delete(n->leftSubtree());
deep_delete(n->rightSubtree());
delete n;}}

Node * Node::leftSubtree() const {// EFFECTS: Return the pointer to the left child of the node.
   return left;
}

void Node::setleft(Node *n) {
    // MODIFIES: this
    // EFFECTS: set the left child of the node to be n.
    deep_delete(left);
    left = n;
}

Node* Node::rightSubtree() const{
    // EFFECTS:  Return the pointer to the right child of the node.
    return right;
}

void Node::setright(Node *n) {
    // MODIFIES: this
    // EFFECTS: set the right child of the node to be n.
    deep_delete(right);
    right=n;
}

string Node::getstr() const {
    // EFFECTS:  Return the “str” component of the node.
    return str;
}

int Node::getnum() const {
    // EFFECTS:  Return the “num” component of the node.
    return num;
}

void Node::incnum() {
    // MODIFIES: this
    // EFFECTS: increment num by 1
    num++;
}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) {
    // REQUIRES: leftNode and rightNode points to dynamically allocated node objects.
    // EFFECTS: Returns a pointer to a node with "str" being the result of appending
    //          leftNode->str and rightNode->str, and "num" being leftNode->num +
    //          rightNode->num. Moreover, “left” should be leftNode and “right”
    //          should be rightNode. Also, Please allocate memory for this returned node
    //          object.
    return new Node(leftNode->getstr()+rightNode->getstr(),leftNode->getnum()+rightNode->getnum(),leftNode,rightNode);
}

/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(Node *rootNode){
    root=rootNode;
    // REQUIRES: The input rootNode points to a dynamically allocated node object,
    //           if not being NULL.
    // MODIFIES: this
    // EFFECTS: Construct a binary tree with a root node.
}

BinaryTree::~BinaryTree() {
    // MODIFIES: this
    // EFFECTS: Free all the memory allocated for this binary tree.
 if(root->leftSubtree()!= nullptr){
    auto *left=new BinaryTree(root->leftSubtree());
     delete left;}
    if(root->rightSubtree()!= nullptr){
        auto *right=new BinaryTree(root->rightSubtree());
        delete right;}
    delete root;}

static string findPathhelper(Node *p, const string &s) { 
if (p == nullptr || p->getstr() == s) return (p == nullptr) ? "-1" : ""; 
string leftPath = findPathhelper(p->leftSubtree(), s); 
if(leftPath != "-1") {
return "0" + leftPath;} 
string rightPath = findPathhelper(p->rightSubtree(), s); 
return (rightPath != "-1") ? "1" + rightPath : "-1"; 
}
    
    
string BinaryTree::findPath(const string &s) const{
    return findPathhelper(root,s);}

static int sumhelper(Node*p){
    if(p== nullptr){
        return 0;}
    return p->getnum()+ sumhelper(p->rightSubtree())+ sumhelper(p->leftSubtree());
}
int BinaryTree::sum() const {
    // EFFECTS: Returns the sum of "num" values of all nodes in the tree. If the tree is
    //          empty, return 0.
    return sumhelper(root);
}


static int depthhelper(Node *p){
    if(p== nullptr){
        return 0;}
   return max(1+ depthhelper(p->leftSubtree()),1+ depthhelper(p->rightSubtree()));
}
int BinaryTree::depth() const {
    // EFFECTS: Returns the depth of the tree, which equals the number of layers of nodes
    //          in the tree. Returns zero if the tree is empty.
    return depthhelper(root);
}


static void preorder_numhelper(Node*p){
    if (p== nullptr)return;
    cout<<p->getnum()<<" ";
    preorder_numhelper(p->leftSubtree());
    preorder_numhelper(p->rightSubtree());
}
void BinaryTree::preorder_num() const {
            //EFFECTS: Prints the "num" component of each node using a pre-order traversal.
            //          Seperate each "num" with a space. A pre-order traversal prints the
            //          current node first, then recursively visit its left subtree, and then
            //          recursively visit its right subtree and so on, until the right-most
            //          element is printed.
    preorder_numhelper(root);
    cout<<endl;
}

static void inorder_strhelper(Node *p){
    if(p== nullptr) return;
    inorder_strhelper(p->leftSubtree());
    cout<<p->getstr()<<" ";
    inorder_strhelper(p->rightSubtree());
}

void BinaryTree::inorder_str() const {
    // EFFECTS: Prints the "str" component of each node using an in-order traversal.
    //          Separate each "str" with a space. An in-order traversal prints the
    //          "left most" element first, then the second-left-most, and so on,
    //          until the right-most element is printed.
    inorder_strhelper(root);
    cout<<endl;
}


static void postorder_numhelper(Node*p){
    if(p== nullptr)return;
    postorder_numhelper(p->leftSubtree());
    postorder_numhelper(p->rightSubtree());
    cout<<p->getnum()<<" ";
}
void BinaryTree::postorder_num() const {
    // EFFECTS: Prints the "num" component of each node using a post-order traversal.
    //          Seperate each "num" with a space. A post-order traversal recursively
    //          visit its left subtree, and then recursively visit its right subtree
    //          and then print the current node.
    postorder_numhelper(root);
    cout<<endl;
}


static bool allPathSumGreaterHelper(Node *n, int numSum, int sum) {
//helper function for allPathSumGreater.
if (n == nullptr) {return numSum > sum;
} else {numSum += n->getnum();
return allPathSumGreaterHelper(n->leftSubtree(), numSum, sum) && allPathSumGreaterHelper(n->rightSubtree(), numSum, sum);}}

bool BinaryTree::allPathSumGreater(int sum) const {
    // REQUIRES: The tree is not empty
    // EFFECTS: Returns true if and only if for each root-to-leaf path of the tree,
    //          the sum of "num" of all nodes along the path is greater than "sum".
   return allPathSumGreaterHelper(root->leftSubtree(), root->getnum(), sum) && allPathSumGreaterHelper(root->rightSubtree(), root->getnum(), sum);
}

static bool covered_byhelper(Node* present,Node* given){
//helper function for covered_by
    if(present== nullptr)return true;
    if(given== nullptr)return false;
    if(present->getnum()==given->getnum()&& covered_byhelper(present->leftSubtree(),given->leftSubtree())&&
                                            covered_byhelper(present->rightSubtree(),given->rightSubtree())){
        return true;}
    return false;}
bool BinaryTree::covered_by(const BinaryTree &tree) const {
    // EFFECTS: Returns true if this tree is covered by the input binary tree "tree".
    //          (only consider the "num" component)
    return covered_byhelper(root,tree.root);
}


static bool contained_byhelper(Node*present, Node*given){
//helper function for contained_by
    if(given== nullptr){
        return false;
    }
    return (covered_byhelper(present,given)|| covered_byhelper(present,given->rightSubtree())|| covered_byhelper(present,given->leftSubtree()));
}
bool BinaryTree::contained_by(const BinaryTree &tree) const {
    // EFFECTS: Returns true if this tree is contained by the input binary tree "tree".
    //          (only consider the "num" component)
    return contained_byhelper(root,tree.root);
}

static Node* copyhelper(Node*p){
    if(p== nullptr){
        return nullptr;
    }
    return new Node(p->getstr(),p->getnum(), copyhelper(p->leftSubtree()), copyhelper(p->rightSubtree()));
}
BinaryTree BinaryTree::copy() const {
    // EFFECTS: Returns a copy of this tree. Hint: use deep copy.
        BinaryTree copy= BinaryTree(copyhelper(root));
        return copy;
}
