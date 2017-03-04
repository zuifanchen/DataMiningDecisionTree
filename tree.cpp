/*****************************************************************************
Copyright: 2017,Fucheng Zhang,all rights reserved
File name: tree.cpp
Description:
Author: Fucheng Zhang,SDU,zhangfc@zhangfc.com
Version: 1.0
Date: 2017.1.19
History:
*****************************************************************************/
#include"tree.h"
#include<iostream>
#include<cstdlib>
using namespace std;
/*
    name:
        tree::tree
    parameter:
        data &dat --reference of data object
    description:
        construct a tree using a data object
*/
tree::tree(data &dat)
{
    //create a shared_ptr<data> so that it can be passed to the creatNode function
    shared_ptr<data> da(new data(dat));

    columnN=da->countOfColumn;
    majority=dat.majority(dat.countOfColumn-1);

    vector<int> v;
    //initialize the vector with all attribute column
    for(int i=0;i<da->countOfColumn-1;i++)
        v.push_back(i);
    //create the tree using recursion method
    root=creatNode(da,v);
}
/*
    name:
        tree::creatNode
    parameter:
        shared_ptr<data> da,
        vector<int> v --v is a vector using to store the attribute column which is unused
    return:
        shared_ptr<node>
    description:
        create a node using a data pointer and a list of unused attribute column stored in vector
*/
shared_ptr<node> tree::creatNode(shared_ptr<data> da,vector<int> v)
{
    shared_ptr<node> temp(new node);
    //judge that if it should be a leaf node
    if(v.size()==0||da->entropy()<=0.20)
    {
        temp->isleaf=true;
        temp->attribute=da->majority(da->countOfColumn-1);
        return temp;
    }
    else
    {   //attribute node
        temp->isleaf=false;
        float ga=0;
        int pos=0;
        //find the biggest gain
        for(unsigned int i=0;i<v.size();i++)
        {
            float temp=gain(da,v[i]);
            if(temp>=ga)
            {
                ga=temp;
                pos=i;
            }
        }
        //fill the node
        temp->column=v[pos];
        temp->attributeType=da->attributeType(temp->column);
        v.erase(v.begin()+pos);//delete the used column in the vector
        int length=(temp->attributeType)->size();
        //recursive create node and store it in the node list
        for(int i=0;i<length;i++)
        {
            (temp->nodelist).push_back(creatNode(da->createData(temp->column,(*(temp->attributeType))[i]),v));
        }

        return temp;
    }
}
/*
    name:
        tree::gain
    parameter:
        shared_ptr<data> da
        int column
    return:
        float
    description:
        calculate the gain if the data object is divided by the attribute column
*/
float tree::gain(shared_ptr<data> da,int column)
{
    float con=da->entropy();
    //find all attribute type in this column
    shared_ptr<vector<string>>  attType=da->attributeType(column);
    //calculate the gain
    for(unsigned int i=0;i<attType->size();i++)
    {
        con=con-(da->countNum(column,(*attType)[i]))*1.0/(da->database).size()*((da->createData(column,(*attType)[i]))->entropy());
    }
    return con;
}
/*
    name:
        tree::forecast
    parameter:
        shared_ptr<vector<string>> row
    return:
        string
    description:
        forecast a item
*/
string tree::forecast(shared_ptr<vector<string>> row)
    {
        shared_ptr<node> temp=root;
        //traverse the tree
        while(!(temp->isleaf))
        {
            string s=(*row)[temp->column];
            unsigned int i;
            for(i=0;i<temp->attributeType->size();i++)
            {
                if(s==(*(temp->attributeType))[i])
                    break;
            }
            //if not find the leaf node for the item in the tree,use the majority to judge it
            if(i==temp->attributeType->size())
                return majority;
            temp=(temp->nodelist)[i];
        }
        return temp->attribute;
    }
/*
    name:
        tree::generateRule
    parameter:
        int n-- n retracts before the rule
    return:
        string
    description:
        generate the classification rule e
*/
string tree::generateRule(shared_ptr<node> nodeptr,int n)
{
    string str;
    //temp is used to store the retract
    string temp;
    for(int i=0;i<n;i++)
        temp+="\t";
    if(nodeptr->isleaf)
    {
        str=temp+"return "+'\"'+nodeptr->attribute+'\"'+'\n';
        return str;
    }
    else
    {
        for(int i=0;i<nodeptr->attributeType->size();i++)
        {
            if(i==0)
                str=str+temp;
            else str=str+temp+"else ";
            str=str+"if column "+to_string(nodeptr->column)+"==\""+
                (*(nodeptr->attributeType))[i]+"\"\n"+
                generateRule((nodeptr->nodelist)[i],n+1);
        }
        return str;
    }
}
