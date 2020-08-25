//p11 Trees
//Rowan Briggs
//May 23, 2018
/* Description:
Use the Trees lecture to Implement and test the following tree methods:
    insert
    traverse
    inOrder
    preOrder
    postOrder
    minimum
    maximum
    displayTree()
 */
#include <stack>
#include <iostream>
using namespace std;

class Node{
public:
    int data;
    Node *pLeftChild;
    Node *pRightChild;
    Node(){
        data = 0;
        pLeftChild = NULL;
        pRightChild = NULL;
    }
    void displayNode(){
        cout << "{" << data << "}";
    }
};//end of class Node

class Tree{
private:
    Node *pRoot;
public:
    Tree() {
        pRoot = NULL;
    }
    Node* find(int key){
        Node *pCurrent = pRoot; //start at root
        while(pCurrent->data != key) { //while no match
            if(key < pCurrent->data) { //go left?
                pCurrent = pCurrent->pLeftChild;
            }
            else { //or go right?
                pCurrent = pCurrent->pRightChild;
            }
            if(pCurrent == NULL){ //if no child
                return NULL;      //didn't find it
            }
        }
        return pCurrent; //found it
    }
    void insert(int newData){
        Node *pNewNode = new Node; //makes a new node
        pNewNode->data = newData;  //insert data

        if(pRoot == NULL) {     //no node in root
            pRoot = pNewNode;
        }
        else {  //root occupied
            Node *pCurrent = pRoot; //start at root
            Node *pParent;
            while(true){    //exits internally
                pParent = pCurrent;
                if(newData < pCurrent->data){ //go left?
                    pCurrent = pCurrent->pLeftChild;
                    if(pCurrent == NULL) {  //if end of the line
                        pParent->pLeftChild = pNewNode; //insert on the left
                        return;
                    }
                } //end of go left
                else{   //now go right?
                    pCurrent = pCurrent->pRightChild;
                    if(pCurrent == NULL){
                        pParent->pRightChild = pNewNode;
                        return;
                    }
                }//end of go right
            }//end of while
        }//end of else
    }//end of insert()

    //traverses through the tree
    void traverse(int traverseType){
        if(traverseType == 1){
            inOrder(pRoot);
        }
        if(traverseType == 2){
            postOrder(pRoot);
        }
        if(traverseType == 3){
            postOrder(pRoot);
        }
    }
    void inOrder(Node *localRoot){
        if(localRoot != NULL){
            inOrder(localRoot->pLeftChild); //left child
            cout << localRoot->data << " "; //display node
            inOrder(localRoot->pRightChild);//right child
        }
    }
    void preOrder(Node *localRoot){
        if(localRoot != NULL){
            cout << localRoot->data << " ";
            preOrder(localRoot->pLeftChild);
            preOrder(localRoot->pRightChild);
        }
    }
    void postOrder(Node *localRoot){
        if(localRoot != NULL){
            postOrder(localRoot->pLeftChild); //left child
            postOrder(localRoot->pRightChild); //right child
            cout << localRoot->data << " "; //display node
        }
    }

    //finds the minimum in the tree
    void minimum() { //returns node with minimum value
        Node *pCurrent, *pLast;
        pCurrent = pRoot; //start at root
        while(pCurrent != NULL) { //until the bottom
            pLast = pCurrent; //remember node
            pCurrent = pCurrent->pLeftChild; //go to left child
        }
        cout << pLast->data << endl;
    }
    //finds maximum
    void maximum() {
        Node *pCurrent, *pLast;
        pCurrent = pRoot; //starts at the root
        while(pCurrent != NULL) {
            pLast = pCurrent; //remember the node
            pCurrent = pCurrent->pRightChild;//go to right child
        }
        cout << pLast->data << endl;
    }
    //display the entire tree
    void displayTree(){
        stack <Node*> globalStack;
        globalStack.push(pRoot);
        int nBlanks = 32;
        bool isRowEmpty = false;
        cout << "...........................................................";
        cout << endl;
        while(isRowEmpty == false){
            stack<Node*> localStack;
            isRowEmpty = true;
            for(int j= 0; j < nBlanks; j++){
                cout << ' ';
            }
            while(globalStack.empty() == false) {
                Node *temp = globalStack.top();
                globalStack.pop();
                if (temp != NULL) {
                    cout << temp->data;
                    localStack.push(temp->pLeftChild);
                    localStack.push(temp->pRightChild);

                    if (temp->pLeftChild != NULL || temp->pRightChild != NULL) {
                        isRowEmpty = false;
                    }
                }
                else {
                    cout << "--";
                    localStack.push(NULL);
                    localStack.push(NULL);
                }
                for(int j = 0; j < nBlanks*2-2; j++) {
                    cout << ' ';
                }
            } //end while glovalStack not empty
            cout << endl;
            nBlanks /= 2;
            while(localStack.empty() == false){
                globalStack.push(localStack.top());
                localStack.pop();
            }

        }//end while isRowEmpty is false
        cout << "...........................................................";
        cout << endl;
    }//end displayTree()
};

int main() {
    Tree tree;
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(9);
    tree.insert(8);

    Node *found = tree.find(3);
    if(found != NULL){
        cout << "Found the node with key 3" << endl;
    }
    else{
        cout << "Could not find node with key 3" << endl;
    }

    cout << "tree inOrder():";
    tree.traverse(1);
    cout << endl;
    tree.displayTree();
    cout << "smallest value:";
    tree.minimum();
    cout << "largest value:";
    tree.maximum();
}
/*
Found the node with key 3
tree inOrder():1 3 6 8 9
...........................................................
                                6
                1                              9
        --              3              8              --
...........................................................
smallest value:1
largest value:9

Process finished with exit code 0
 */