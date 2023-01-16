#ifndef AVLT_H
#define AVLT_H
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;


class AVLT
{

    private:
        struct NodeAVL//a struct node that saves a word along its necessary info
        {
            string content;//the word itself
            NodeAVL* ladd, *radd, *parent;//children
            int counter, height_left, height_right;//counter left and right height of the node
        };

        NodeAVL* root;//root of the tree
        NodeAVL* NewNodeAVL(string); //creates new node
        NodeAVL* searchNode(string, NodeAVL*);//searches a node based on its content
        NodeAVL* deleteNode(string, NodeAVL*&);//deletes a node if counter==1, otherwise the counter is subtracted by one
        NodeAVL* minofmax(string); //minimum value of a right subtree; It's used in deleteNode

        void insertNewNodeAVL(string, NodeAVL*);//inserts a new node in the right place

        //tree traversals
        void inOrder(NodeAVL*);
        void postOrder(NodeAVL*);
        void preOrder(NodeAVL*);
        void setheight(NodeAVL*,bool);

        //Rotation methods
        void rotationSelection(NodeAVL*);
        NodeAVL* LRrotation(NodeAVL*);
        NodeAVL* RLrotation(NodeAVL*);
        NodeAVL* RRrotation(NodeAVL*);
        NodeAVL* LLrotation(NodeAVL*);

    public:
        //public versions of functions above
        AVLT();
        void printsearch(string x,ofstream &y){NodeAVL* temp=searchNode(x,root); y<<temp->content<<":"<<temp->counter<<"   ";}
        void GetIns(string x){insertNewNodeAVL(x, root);}
        void inOrderPub(){inOrder(root);}
        void preOrderPub(){preOrder(root);}
        void postOrderPub(){postOrder(root);}
        void GetDel(string x){deleteNode(x, root);}
        void GetSer(string x){searchNode(x, root);}

};

#endif // AVLT_H
