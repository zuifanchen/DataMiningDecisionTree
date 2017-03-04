/*****************************************************************************
Copyright: 2017,Fucheng Zhang,all rights reserved
File name: tree.h
Description:
Author: Fucheng Zhang,SDU,zhangfc@zhangfc.com
Version: 1.0
Date: 2017.1.19
History:
*****************************************************************************/
#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include<vector>
#include<string>
#include<memory>
#include"data.h"
class node
{
public:
    //default constructor
    node(){};
    //isleaf is used to judge a attribute node or leaf node
    bool isleaf;
    //attribute column
    int column;
    //attributeType is a pointer point to a vector which is used to store the attribute type
    shared_ptr<vector<string>> attributeType;
    //nodelist is a vector used to store pointer which is point to the child node
    vector<shared_ptr<node>> nodelist;
    //leaf node's forecast
    string attribute;
};

class tree
{
public:
    //construct a tree using a data object
    tree(data &dat);
    //create a node using a data pointer and a list of left column stored in vector
    shared_ptr<node> creatNode(shared_ptr<data> da,vector<int> v);
    //calculate the gain if the data object is divided by the attribute column
    float gain(shared_ptr<data> da,int column);
    //forecast a item and return the consequence
    string forecast(shared_ptr<vector<string>> row);
    //columnN is to store the number of column
    int columnN;
    //majority
    string majority;
    //the root of the tree
    shared_ptr<node> root;
    //generate the classification rule e
    string generateRule(shared_ptr<node> nodeptr,int n);

};
#endif // TREE_H_INCLUDED
