#include "AVLT.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>

AVLT::AVLT()//constructor sets the root of the tree to null
{
    root = NULL;
}


AVLT::NodeAVL* AVLT::NewNodeAVL(string x)//creation of new node
{

    struct NodeAVL *newleaf = new NodeAVL;
    newleaf->content = x;//content is set as the parameter given
    newleaf->ladd = newleaf->radd = NULL;//since the node is new, it has no children
    newleaf->counter = 1;//it also can not have a counter other than 1
    newleaf->height_left = newleaf->height_right = 0;//hence the lack of height
    newleaf->parent = NULL;//the parent is set to null temporarily
    return newleaf;
}


void AVLT::setheight(NodeAVL *p, bool option)
{

    if(p == NULL)//the tree has reached the root
        return;
    if(p->ladd == NULL && p->radd == NULL)//the node has no children
    {
        p->height_left = 0;//so no height
        p->height_right = 0;
    }
    else if(p->ladd == NULL && p->radd != NULL)//it has a right child
    {
        if(p->radd->height_left>p->radd->height_right)//if the right child's left height is bigger than the right
        {
            p->height_right = p->radd->height_left + 1;//p's height is the right child's left height +1
            p->height_left = 0;
        }
        else
        {
            p->height_right = p->radd->height_right + 1;//otherwise p's height is the right child's right height +1
            p->height_left = 0;
        }
    }
    else if(p->ladd != NULL && p->radd == NULL)//it has a left child
    {
        if(p->ladd->height_left>p->ladd->height_right)//if the left child's left height is bigger than the right
        {
            p->height_left = p->ladd->height_left + 1;//p's height is the left child's left height +1
            p->height_right = 0;
        }
        else
        {
            p->height_left = p->ladd->height_right + 1;//otherwise p's height is the left child's right height +1
            p->height_right = 0;
        }
    }
    else
    {
        if(p->radd->height_left>p->radd->height_right)//if right child's left height is bigger than its right height
        {
            p->height_right = p->radd->height_left + 1;//p's right height is right child's left height
        }
        else
        {
            p->height_right = p->radd->height_right + 1;//otherwise its right child's right height
        }
        if(p->ladd->height_left>p->ladd->height_right)//if left child's left height is bigger than its right height
        {
            p->height_left = p->ladd->height_left + 1;//p's left height is left child's left height
        }
        else
        {
            p->height_left = p->ladd->height_right + 1;//otherwise its left child's right height
        }
    }

    if(abs(p->height_left-p->height_right)==2 && option==true)//if the difference between  heights is 2 and option is true
            rotationSelection(p);//perform a rotation
    setheight(p->parent,option);//recursively execute the function for the parent of the current node
}




AVLT::NodeAVL* AVLT::searchNode(string x, NodeAVL* p)
{

    if(root == NULL)//if the root is null the tree is null
    {
        return NULL;
    }
    else
    {
        if(p->content == x)//the node is found
        {
            return p;
        }

        else
        {
            if(p->content < x)//if the parameter is larger than the content of the node
            {
                if(p->radd != NULL)//and it has a right child
                    return searchNode(x, p->radd);//recursively execute the function for the right child
            }
            else if(p->content > x)//if the parameter is smaller than the content of the node
            {
                if(p->ladd != NULL)//and it has a left child
                    return searchNode(x, p->ladd);//recursively execute the function for the left child
            }
        }
    }

    cout<<"There's no such word."<<endl;
    return NULL;

}


void AVLT::insertNewNodeAVL(string x, NodeAVL *p)
{

    if(root == NULL) //if the root is null the tree is empty
    {
        root = NewNodeAVL(x);//so the first insertion will correspond to the root of the tree
    }

    else
    {
        if(p->content == x)//if the parameter is the same as the content of the node
            p->counter++;//the counter is increased

        else if(p->content < x)//if the parameter is larger than the content of the node
        {
            if(p->radd != NULL)//if the node has a left child
                insertNewNodeAVL(x, p->radd);//recursively execute insertnewnode for the right child
            else
            {
                p->radd = NewNodeAVL(x);//if it doesnt, create a new node with x as the content
                p->radd->parent = p;//set new node's parent as p
                if(p->ladd==NULL)//if there is no left child
                    setheight(p->radd,true);//call setheight
                else
                    p->height_right++;//else the addition of a new node is guaranteed to not cause a problem, so we simply increase the height by 1
            }
        }

        else if(p->ladd != NULL)//if the parameter is smaller than the content of the node and it has a left child
            insertNewNodeAVL(x, p->ladd);//recursively execute insertnewnode for the left child

        else
        {
            p->ladd = NewNodeAVL(x);//if it doesnt, create a new node with x as the content
            p->ladd->parent = p;//set new node's parent as p
            if(p->radd==NULL)//if there is no right child
                setheight(p->ladd,true);//call setheight
            else
                p->height_left++;//else the addition of a new node is guaranteed to not cause a problem, so we simply increase the height by 1
        }
    }
}


AVLT::NodeAVL* AVLT::minofmax(string x)
{

    NodeAVL* temp=searchNode(x, root)->radd;//treats temp as the root of the right subtree
    while (temp->ladd!=NULL)//while there are left nodes
    {
        temp=temp->ladd;//keep changing temp to said node
    }
    return temp;
}

AVLT::NodeAVL* AVLT::deleteNode(string x, NodeAVL*& p){


    if(root == NULL)//if the tree is empty
    {
        cout<<"No nodes in the tree"<<endl;
        return p;
    }
    if(!p)//word is not found
    {
        return NULL;
    }
    else
    {
        if(x > p->content)//if the parameter is larger than the content of node
        {
            p->radd = deleteNode(x, p->radd);//execute the function recursively for the right child
            if (!p->radd)//recursively call setheight to update the heights of the nodes affected
                setheight(p->radd,true);
            else if (!p->ladd)
                setheight(p->ladd,true);
            return p;
        }

        else if(x < p->content)//if the parameter is smaller than the content of node
        {
            p->ladd = deleteNode(x, p->ladd);//execute the function recursively for the left child
            if (!p->radd)//recursively call setheight to update the heights of the nodes affected
                setheight(p->radd,true);
            else if (!p->ladd)
                setheight(p->ladd,true);
            return p;
        }

        //No children
        else if(p->ladd == NULL && p->radd == NULL && p->content == x)
        {
            if (p->counter>1)//if the word is saved more than once
            {
                p->counter--;//delete one of them
                    return p;
            }
            else//if its saved only once
            {
                delete p;//delete the whole node
                p = NULL;
                return p;
            }
        }

        //One child
        else if(p->ladd != NULL && p->radd==NULL && p->content == x)//the node has a left child
        {
            NodeAVL* temp=p->ladd;//saves the pointer pointing to the left child
            if (p->counter>1)//if the word is saved more than once
            {
                p->counter--;//delete one of them
                return p;
            }
            else if (root==p)//if root is the node that we want to delete
            {
                root=temp;//then the root will be equal to its left child
                return root;
            }
            else
            {
                temp->parent=p->parent;//parent of temp becomes p's parent since p is deleted
                delete p;//delete node
                p=NULL;
                return temp;
            }
        }

        else if(p->radd != NULL&&p->ladd==NULL && p->content == x)//the node has a right child
        {
            NodeAVL* temp=p->radd;//saves the pointer pointing to the right child
            if (p->counter>1)//if the word is saved more than once
            {
                p->counter--;//delete one of them
                return p;
            }
            else if (root==p)//if root is the node that we want to delete
            {
                root=temp;//then the root will be equal to its right child
                return root;
            }
            else//if none of the above
            {
                temp->parent=p->parent;//parent of temp becomes p's parent since p is deleted
                delete p;//delete node
                p=NULL;
                return temp;
            }
        }

        //Two children
        else if (p->radd!=NULL && p->ladd!=NULL && p->content==x)
        {
            if (p->counter>1)//if the word is saved more than once
            {
                p->counter--;//delete one of them
                return p;
            }
            else
            {
                NodeAVL* tempadd=minofmax(p->content);//find the minimum of the right subtree
                if (p->radd==tempadd)
                {
                    p->radd=tempadd->radd;//if that minimum is the root of the right subtree
                    if (tempadd->radd!=NULL)//if minimum has a right child
                        tempadd->radd->parent=p;//make that child's parent p
                    p->content=tempadd->content;//and then change the content
                    p->counter=tempadd->counter;//and the counter to that of minimum, basically swapping places
                    delete tempadd;//delete node
                    tempadd=NULL;

                    if (p==root)//if p is root
                        setheight(p,true);//there is no recursion being executed after the end of this function so we must setheight now
                    return p;
                }

                else
                {
                    p->content=tempadd->content;//change the content of the node
                    p->counter=tempadd->counter;//and the counter of the node to that of tempadd's
                    tempadd->counter=1;//set the counter of tempadd to 1
                    deleteNode(tempadd->content,p->radd);//so it can be deleted immediately by calling deleteNode
                    return p;
                }
            }
        }
    }
    return p;
}



//Rotations

void AVLT::rotationSelection(NodeAVL* probp)//selects the appropriate rotation
{

    if(probp->height_left>probp->height_right)//if the left height is larger than the right height
    {
        if(probp->ladd->height_left<probp->ladd->height_right)//and the left child's left height is larger than its right
        {

            LRrotation(probp);//perform an LR rotation

        }

        else
        {
            LLrotation(probp);//otherwise perform an LL rotation
            setheight(probp,true);//and finally set the height

        }

    }

    else
    {
        if(probp->radd->height_left>probp->radd->height_right)//if the right height is larger than the left height
        {
            RLrotation(probp);//and the right child's left height is larger than its right perform an RL rotation
        }

        else
        {
            RRrotation(probp);//otherwise perform an RR rotation
            setheight(probp,true);//and finally set the height

        }
    }
}







AVLT::NodeAVL* AVLT::LRrotation(NodeAVL* probp)
{

    RRrotation(probp->ladd);//performs an RR rotation first
    setheight(probp->ladd->ladd,false);//then calls setheight to update the heights with option as false
    //so setheight doesnt call rotationselection unwantedly
    LLrotation(probp);//performs an LL rotation
    setheight(probp,false);//and finally calls setheight with option as true meaning it can now safely acknowledge the next problematic node

    return probp;
}

AVLT::NodeAVL* AVLT::RLrotation(NodeAVL* probp)
{

    LLrotation(probp->radd);//performs an LL rotation first
    setheight(probp->radd->radd,false);//then calls setheight to update the heights with option as false
    //so setheight doesnt call rotationselection unwantedly
    RRrotation(probp);//performs an RR rotation
    setheight(probp,false);//and finally calls setheight with option as true meaning it can now safely acknowledge the next problematic node

    return probp;
}

AVLT::NodeAVL* AVLT::RRrotation(NodeAVL* p)
{
    NodeAVL *trouble;
    trouble = p->radd;//right child is saved
    p->radd = trouble->ladd;//the right child of p becomes trouble's left child

    if (p->radd!=NULL)//if p's updated right child is in fact a node
        p->radd->parent=p;//change that child's parent to be p

    trouble->ladd = p;//make trouble's left child p

    if (!p->parent)//if p doesnt have a parent
    {
        root=trouble;//that means it is the root. Trouble has to take the place as the root
        trouble->parent=NULL;//the root has no parent
    }

    else
    {
        if (p->parent->radd==p)//if p is the right child of its parent
            p->parent->radd=trouble;//change it to trouble
        else//if p is the left child of its parent
            p->parent->ladd=trouble;//change it to trouble
        trouble->parent=p->parent;//trouble's parent is now p's  parent
    }

    p->parent=trouble;//and finally p's parent is trouble
    return trouble;

}

AVLT::NodeAVL* AVLT::LLrotation(NodeAVL* p)
{

    NodeAVL *trouble;
    trouble = p->ladd;//left child is saved
    p->ladd = trouble->radd;//the left child of p becomes trouble's right child

    if (p->ladd!=NULL)//if p's updated left child is in fact a node
        p->ladd->parent=p;//change that child's parent to be p

    trouble->radd = p;//make trouble's right child p

    if (!p->parent)//if p doesnt have a parent
    {
        root=trouble;//that means it is the root. Trouble has to take the place as the root
        trouble->parent=NULL;//the root has no parent
    }

    else
    {
        if (p->parent->ladd==p)//if p is the left child of its parent
            p->parent->ladd=trouble;//change it to trouble
        else//if p is the right child of its parent
            p->parent->radd=trouble;//change it to trouble
        trouble->parent=p->parent;//trouble's parent is now p's  parent
    }

    p->parent=trouble;//and finally p's parent is trouble
    return trouble;

}








//Tree traversals

void AVLT::inOrder(NodeAVL* p)
{
    if(p == NULL)
        return;
    inOrder(p->ladd);
    cout<<p->content<<" ("<<p->height_left<<","<<p->height_right<<")"<<"("<<p->counter<<")"<<endl;//also prints heights
    inOrder(p->radd);
}


void AVLT::postOrder(NodeAVL* p)
{

    if(p == NULL)
        return;
    postOrder(p->ladd);
    postOrder(p->radd);
    cout<<p->content<<" ("<<p->height_left<<","<<p->height_right<<")"<<"("<<p->counter<<")"<<endl;//also prints heights

}


void AVLT::preOrder(NodeAVL* p)
{
    if(p == NULL)
        return;
    cout<<p->content<<" ("<<p->height_left<<","<<p->height_right<<")"<<"("<<p->counter<<")"<<endl;//also prints heights
    postOrder(p->ladd);
    postOrder(p->radd);
}
