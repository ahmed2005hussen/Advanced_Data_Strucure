#include <iostream>
#include <algorithm>
using namespace std;

using namespace std;

class AuctionTree {
private:

    // TODO: Define your Red-Black Tree node structure
    // Hint: Each node needs: id, price, color, left, right, parent pointers

    struct Node {
        int price;
        int id;
        Node *lchild;
        Node *rchild;
        Node *parent;
        char color;
    };

    Node *root;

    void fixInsert(Node *node) {
        Node  *parent = nullptr;
        Node  *grandparent = nullptr;

        while (node != root && node->color == 'r' && node->parent->color == 'r') {
            parent = node->parent;
            grandparent = parent->parent;


            if (parent == grandparent->lchild) {

                Node  *uncle = grandparent->rchild;
                if (uncle != nullptr && uncle->color == 'r') {
                    grandparent->color = 'r';
                    parent->color = 'b';
                    uncle->color = 'b';
                    node = grandparent;
                } else {
                    if (node == parent->rchild) {
                        leftRotation(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rightRotation(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            } else {
                Node  *uncle = grandparent->lchild;
                if (uncle != nullptr && uncle->color == 'r') {
                    grandparent->color = 'r';
                    parent->color = 'b';
                    uncle->color = 'b';
                    node = grandparent;
                } else {
                    if (node == parent->lchild) {
                        rightRotation(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    leftRotation(grandparent);
                    swap(grandparent->color, parent->color);
                    node = parent;
                }
            }
        }
        root->color = 'b';
    }

    void leftRotation(Node *node) {

        Node *nodeRight = node->rchild;
        Node *nodeRightLeft = nodeRight->lchild;

        nodeRight->lchild = node;
        node->rchild = nodeRightLeft;

        if (nodeRightLeft != nullptr) {
            nodeRightLeft->parent = node;
        }
        Node *oldParent = node->parent;

        nodeRight->parent = oldParent;

        node->parent = nodeRight;

        if (oldParent == nullptr) {
            root = nodeRight;
        } else if (oldParent->lchild == node) {
            oldParent->lchild = nodeRight;
        } else {
            oldParent->rchild = nodeRight;
        }
    }

    void rightRotation(Node  *node) {

        Node  *nodeLeft = node->lchild;
        Node  *nodeLeftRight = nodeLeft->rchild;

        nodeLeft->rchild = node;
        node->lchild = nodeLeftRight;

        if (nodeLeftRight != nullptr) {
            nodeLeftRight->parent = node;
        }

        Node  *oldParent = node->parent;

        nodeLeft->parent = oldParent;

        node->parent = nodeLeft;

        if (oldParent == nullptr) {
            root = nodeLeft;
        } else if (oldParent->lchild == node) {
            oldParent->lchild = nodeLeft;
        } else {
            oldParent->rchild = nodeLeft;
        }
    }

    Node *InPre(Node *p) {
        while (p && p->rchild != nullptr) {
            p = p->rchild;
        }
        return p;
    }

    Node *search(int id) {
        return searchHelper(root, id);
    }

    Node *searchHelper(Node *node, int id) {
        if (node == nullptr) return nullptr;
        if (node->id == id) return node;

        Node *left = searchHelper(node->lchild, id);
        if (left != nullptr) return left;

        return searchHelper(node->rchild, id);
    }

    void fixDelete(Node *x) {
        // x is double black ('d')

        while (x != root && x->color == 'd') {
            Node   *parent = x->parent;
            Node   *sibling;

            if (parent->lchild == x) {
                sibling = parent->rchild;

                // Case 1: Sibling is red
                if (sibling->color == 'r') {
                    sibling->color = 'b';
                    parent->color = 'r';
                    leftRotation(parent);
                    sibling = parent->rchild;  // Update sibling
                }

                // Case 2: Sibling is black with two black children
                if ((sibling->lchild == nullptr || sibling->lchild->color == 'b') &&
                    (sibling->rchild == nullptr || sibling->rchild->color == 'b')) {
                    sibling->color = 'r';

                    if (parent->color == 'r') {
                        parent->color = 'b';
                        x->color = 'b';  // Remove double black
                    } else {
                        parent->color = 'd';  // Push double black up
                        x->color = 'b';
                        x = parent;
                    }
                }
                    // Case 3: Sibling is black, at least one red child
                else {
                    //  Right child is black (or null)
                    if (sibling->rchild == nullptr || sibling->rchild->color == 'b') {
                        sibling->lchild->color = 'b';
                        sibling->color = 'r';
                        rightRotation(sibling);
                        sibling = parent->rchild;
                    }

                    //  Right child is red
                    sibling->color = parent->color;
                    parent->color = 'b';
                    sibling->rchild->color = 'b';
                    leftRotation(parent);
                    x->color = 'b';  // Remove double black
                    x = root;  // Done
                }
            } else {
                sibling = parent->lchild;

                if (sibling->color == 'r') {
                    sibling->color = 'b';
                    parent->color = 'r';
                    rightRotation(parent);
                    sibling = parent->lchild;
                }

                if ((sibling->rchild == nullptr || sibling->rchild->color == 'b') &&
                    (sibling->lchild == nullptr || sibling->lchild->color == 'b')) {
                    sibling->color = 'r';

                    if (parent->color == 'r') {
                        parent->color = 'b';
                        x->color = 'b';
                    } else {
                        parent->color = 'd';
                        x->color = 'b';
                        x = parent;
                    }
                } else {
                    if (sibling->lchild == nullptr || sibling->lchild->color == 'b') {
                        sibling->rchild->color = 'b';
                        sibling->color = 'r';
                        leftRotation(sibling);
                        sibling = parent->lchild;
                    }

                    sibling->color = parent->color;
                    parent->color = 'b';
                    sibling->lchild->color = 'b';
                    rightRotation(parent);
                    x->color = 'b';
                    x = root;
                }
            }
        }

        x->color = 'b';
    }
    void inorderHelper(Node *node) {
        if (node == nullptr) return;
        inorderHelper(node->lchild);
        cout << "ID: " << node->id << ", Price: " << node->price
             << ", Color: " << node->color << endl;
        inorderHelper(node->rchild);
    }

public:
   AuctionTree() {
        root = nullptr;
    }
    void printTree() {
        cout << "\n=== Tree Contents ===" << endl;
        inorderHelper(root);
        cout << "=====================\n" << endl;
    }
    void insertItem(int itemID, int price)  {
        // TODO: Implement Red-Black Tree insertion
        // Remember to maintain RB-Tree properties with rotations and recoloring

        if (!root) {
            root = new Node ;
            root->lchild = nullptr;
            root->rchild = nullptr;
            root->parent = nullptr;
            root->color = 'b';
            root->price = price;
            root ->id  = itemID ;
            return;
        }

        Node  *tail = nullptr;
        Node  *node = root;
        Node *p = new Node ;


        while (node != nullptr) {
            tail = node;

            if(node->price == price && node->id == itemID ){
                delete p ;
                return;
            }
            else if (node->price < price || (node->price == price && node->id < itemID) ) {
                node = node->rchild;
            } else {
                node = node->lchild;
            }
        }


        if (tail->price < price || (tail->price == price && tail->id < itemID) ) {
            tail->rchild = p;
        } else {
            tail->lchild = p;
        }
        p->price = price;
        p->parent = tail;
        p->rchild = nullptr;
        p->lchild = nullptr;
        p->color = 'r';
        p ->id  = itemID ;

        fixInsert(p);
    }

    void deleteItem(int itemID)  {
        // TODO: Implement Red-Black Tree deletion
        // This is complex - handle all cases carefully

        Node* x = search(itemID);

        if (x == nullptr) {
            return;
        }

        char xColor = x->color;

        if (x->lchild == nullptr) {
            Node  *xChild = x->rchild;
            Node  *xParent = x->parent;

            if (xColor == 'r') {
                if (xParent == nullptr) {
                    root = xChild;
                } else if (xParent->lchild == x) {
                    xParent->lchild = xChild;
                } else {
                    xParent->rchild = xChild;
                }

                if (xChild != nullptr) {  //  Update parent pointer
                    xChild->parent = xParent;
                }
                delete x;
                return ;
            } else {
                if (xChild == nullptr) {
                    // create node to represent double black null
                    Node  *dummy = new Node ;
                    dummy->color = 'd';
                    dummy->lchild = nullptr;
                    dummy->rchild = nullptr;
                    dummy->parent = xParent;

                    if (xParent == nullptr) {
                        root = dummy;
                    } else if (xParent->lchild == x) {
                        xParent->lchild = dummy;
                    } else {
                        xParent->rchild = dummy;
                    }

                    delete x;
                    fixDelete(dummy);

                    // After fixing, remove sentinel
                    if (dummy->parent == nullptr) {
                        root = nullptr;
                    } else if (dummy->parent->lchild == dummy) {
                        dummy->parent->lchild = nullptr;
                    } else {
                        dummy->parent->rchild = nullptr;
                    }
                    delete dummy;
                } else {
                    // Child exists
                    if (xParent == nullptr) {
                        root = xChild;
                    } else if (xParent->lchild == x) {
                        xParent->lchild = xChild;
                    } else {
                        xParent->rchild = xChild;
                    }
                    xChild->parent = xParent;

                    // If child is red, make it black
                    if (xChild->color == 'r') {
                        xChild->color = 'b';
                        delete x;
                    }
                        // If child is black, mark as double black
                    else {
                        xChild->color = 'd';  // double black
                        delete x;
                        fixDelete(xChild);
                    }
                }

                return ;
            }
        }
        else if (x->rchild == nullptr) {
            Node  *xChild = x->lchild;
            Node  *xParent = x->parent;

            if (x->color == 'r') {
                if (xParent == nullptr) {
                    root = xChild;
                } else if (xParent->lchild == x) {
                    xParent->lchild = xChild;
                } else {
                    xParent->rchild = xChild;
                }

                if (xChild != nullptr) {
                    xChild->parent = xParent;
                }

                delete x;
                return ;

            } else {
                // xChild can't be null here (x has left child)
                if (xParent == nullptr) {
                    root = xChild;
                } else if (xParent->lchild == x) {
                    xParent->lchild = xChild;
                } else {
                    xParent->rchild = xChild;
                }
                xChild->parent = xParent;

                if (xChild->color == 'r') {
                    xChild->color = 'b';
                    delete x;
                } else {
                    xChild->color = 'd';  // double black
                    delete x;
                    fixDelete(xChild);
                }
                return ;
            }
        }
        else {
            // x has both children
            Node  *pre = InPre(x->lchild);

            // Swap values
            int tempPrice = x->price;
            int tempID = x->id;

            x->price = pre->price;
            x->id = pre->id;

            pre->price = tempPrice;
            pre->id = tempID;

            // Now delete pre (which has at most left child)
            Node  *preChild = pre->lchild;
            Node  *preParent = pre->parent;

            bool preIsLeftChild = (preParent->lchild == pre);

            // Link parent to child
            if (preIsLeftChild) {
                preParent->lchild = preChild;
            } else {
                preParent->rchild = preChild;
            }

            if (preChild != nullptr) {
                preChild->parent = preParent;
            }

            // Now handle colors based on pre's color
            if (pre->color == 'r') {
                delete pre;
            } else {
                if (preChild != nullptr && preChild->color == 'r') {
                    preChild->color = 'b';
                    delete pre;
                } else if (preChild != nullptr) {
                    preChild->color = 'd';
                    delete pre;
                    fixDelete(preChild);
                } else {
                    Node  *dummy = new Node ;
                    dummy->color = 'd';
                    dummy->lchild = nullptr;
                    dummy->rchild = nullptr;
                    dummy->parent = preParent;

                    if (preIsLeftChild) {
                        preParent->lchild = dummy;
                    } else {
                        preParent->rchild = dummy;
                    }

                    delete pre;
                    fixDelete(dummy);

                    // After fixing, remove dummy
                    if (dummy->parent->lchild == dummy) {
                        dummy->parent->lchild = nullptr;
                    } else {
                        dummy->parent->rchild = nullptr;
                    }
                    delete dummy;
                }
            }

        }

    }
};


int main() {
    cout << "🎮 Red-Black Tree Test\n" << endl;

    AuctionTree tree;

    cout << "Test 1: Basic Insertions" << endl;
    tree.insertItem(1, 100);
    tree.insertItem(2, 50);
    tree.insertItem(3, 150);
    tree.insertItem(4, 75);
    tree.insertItem(5, 125);
    tree.printTree();

    cout << "Test 2: Same Price Different ID" << endl;
    tree.insertItem(6, 100);
    tree.printTree();

    tree.deleteItem(6);
    tree.deleteItem(1);
    tree.deleteItem(2);
    tree.deleteItem(4);
    tree.deleteItem(1);
    cout << "Test 3: Delete item 6" << endl;
    tree.printTree();

    cout << "All tests completed!" << endl;

    return 0;
}