#include<iostream>
#include <queue>

using namespace std;

template<class t>
struct Node {
    t data;
    Node *lchild;
    Node *rchild;
    Node *parent;
    char color;
};

template<class t>
class RBTree {
private:
    Node<t> *root;

    void fixInsert(Node<t> *node) {
        Node<t> *parent = nullptr;
        Node<t> *grandparent = nullptr;

        while (node != root && node->color == 'r' && node->parent->color == 'r') {
            parent = node->parent;
            grandparent = parent->parent;


            if (parent == grandparent->lchild) {

                Node<t> *uncle = grandparent->rchild;
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
                Node<t> *uncle = grandparent->lchild;
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

    void leftRotation(Node<t> *node) {

        Node<t> *nodeRight = node->rchild;
        Node<t> *nodeRightLeft = nodeRight->lchild;

        nodeRight->lchild = node;
        node->rchild = nodeRightLeft;

        if (nodeRightLeft != nullptr) {
            nodeRightLeft->parent = node;
        }
        Node<t> *oldParent = node->parent;

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

    void rightRotation(Node<t> *node) {

        Node<t> *nodeLeft = node->lchild;
        Node<t> *nodeLeftRight = nodeLeft->rchild;

        nodeLeft->rchild = node;
        node->lchild = nodeLeftRight;

        if (nodeLeftRight != nullptr) {
            nodeLeftRight->parent = node;
        }

        Node<t> *oldParent = node->parent;

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

    void inorder(Node<t> *p) {
        if (!p)return;
        inorder(p->lchild);
        cout << p->data << "(" << p->color << ")";
        inorder(p->rchild);
    }

    Node<t> *InPre(Node<t> *p) {
        while (p && p->rchild != nullptr) {
            p = p->rchild;
        }
        return p;
    }

    Node<t> *search(t value) {
        Node<t> *p = root;
        while (p != nullptr) {
            if (p->data < value) {
                p = p->rchild;
            } else if (p->data > value) {
                p = p->lchild;
            } else {
                return p;
            }
        }

        return p;
    }

    void fixDelete(Node<t> *x) {
        // x is double black ('d')

        while (x != root && x->color == 'd') {
            Node<t> *parent = x->parent;
            Node<t> *sibling;

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

    void levelOrder(Node<t> *root) {
        if (root == nullptr) {
            cout << "Tree is empty" << endl;
            return;
        }

        queue<Node<t> *> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();

            // Print all nodes at current level
            for (int i = 0; i < levelSize; i++) {
                Node<t> *current = q.front();
                q.pop();

                // Print node data and color
                cout << current->data << "(" << current->color << ") ";

                // Add children to queue
                if (current->lchild != nullptr) {
                    q.push(current->lchild);
                }
                if (current->rchild != nullptr) {
                    q.push(current->rchild);
                }
            }

            cout << endl;  // New line after each level
        }
    }

public:
    RBTree() {
        root = nullptr;
    }

    void insert(t element) {
        if (!root) {
            root = new Node<t>;
            root->lchild = nullptr;
            root->rchild = nullptr;
            root->parent = nullptr;
            root->color = 'b';
            root->data = element;
            return;
        }

        Node<t> *tail = nullptr;
        Node<t> *node = root;
        auto *p = new Node<t>;


        while (node != nullptr) {
            tail = node;
            if (node->data == element) {
                delete p;
                return;
            }

            if (node->data < element) {
                node = node->rchild;
            } else {
                node = node->lchild;
            }
        }
        if (tail->data < element) {
            tail->rchild = p;


        } else {
            tail->lchild = p;
        }
        p->data = element;
        p->parent = tail;
        p->rchild = nullptr;
        p->lchild = nullptr;
        p->color = 'r';
        fixInsert(p);

    }

    bool Delete(t value) {
        Node<t> *x = search(value);

        if (x == nullptr) {
            return false;
        }

        char xColor = x->color;

        if (x->lchild == nullptr) {
            Node<t> *xChild = x->rchild;
            Node<t> *xParent = x->parent;

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
                return true;
            } else {
                if (xChild == nullptr) {
                    // create node to represent double black null
                    Node<t> *dummy = new Node<t>;
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

                return true;
            }
        }
        else if (x->rchild == nullptr) {
            Node<t> *xChild = x->lchild;
            Node<t> *xParent = x->parent;

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
                return true;

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
                return true;
            }
        }
        else {
            // x has both children
            Node<t> *pre = InPre(x->lchild);

            // Swap values
            t temp = x->data;
            x->data = pre->data;
            pre->data = temp;

            // Now delete pre (which has at most left child)
            Node<t> *preChild = pre->lchild;
            Node<t> *preParent = pre->parent;

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
                    Node<t> *dummy = new Node<t>;
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

            return true;
        }
    }

    void Inorder() {
        inorder(root);
        cout << endl;
    }

    void LevelOrder() {
        levelOrder(root);
        cout << endl;
    }
};

