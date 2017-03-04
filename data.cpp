/*****************************************************************************
Copyright: 2017,Fucheng Zhang,all rights reserved
File name: data.cpp
Description:
Author: Fucheng Zhang,SDU,zhangfc@zhangfc.com
Version: 1.0
Date: 2017.1.19
History:
*****************************************************************************/
#include<fstream>
#include<sstream>
#include<cmath>
#include<map>
#include<iostream>
#include"data.h"
/*
    name:
        data::data
    parameter:
        str  --char pointer to the file name
    description:
        default constructor
*/
data::data(const char* str)
{
    ifstream in(str);
    string line,temp;
    //get a line from the source file
    while(std::getline(in,line))
    {   //using std::shared_ptr in c++11 to point to the vector of string to prevent the leak of memory
        shared_ptr<vector<string>> row(new vector<string>);
        istringstream iss(line);
        //store every attribute in the vector
        while(iss>>temp)
        {
            row->push_back(temp);
        }
        countOfColumn=row->size();
        //store this ptr in database
        database.push_back(row);
    }
    in.close();
}
/*
    name
        data::show
    parameter:
        int countOfItem
    return:
        void
    description:
        print the first "countOfItem" items in this data
*/
void data::show(unsigned int countOfItem)
{
    //if countOfItem is bigger then the count of items, print all items
    for(unsigned int i=0;i<countOfItem&&i<database.size();i++)
    {
        for(int j=0;j<countOfColumn;j++)
            cout<<(*database[i])[j]<<" ";
        cout<<endl;
    }
}
/*
    name:
        data::entropy
    parameter:
        void
    return:
        float
    description:
        calculate the entropy of this data
*/
float data::entropy()
{
    float consequence=0;
    //count the items of last column
    int count_column=countNum(countOfColumn-1);
    //get all the attribute type in the last column
    shared_ptr<vector<string>> att(attributeType(countOfColumn-1));
    //calculate
    for(unsigned int i=0;i<att->size();i++)
    {
        float temp=countNum(countOfColumn-1,(*att)[i])*1.0/count_column;
        consequence=consequence-temp*log2(temp);
    }
    return consequence;
}
/*
    name:
        data::countNum
    parameter:
        int column
        string attribute--default " "
    return:
        int
    description:
        1 parameter:count the items of this column
        2 parameter:count the number of the specific attribute name in the column
*/
int data::countNum(int column,string attribute)
{

    if (attribute==" ")//1 parameter
        return database.size();
    else
    {//2 parameter
        int count=0;
        for(unsigned int i=0;i<database.size();i++)
        {
            if ((*database[i])[column]==attribute)
                count++;
        }
        return count;
    }
}
/*
    name:
        data::attributeType
    parameter:
        int column
    return:
        shared_ptr<vector<string>>
    description:
        get all the attribute type in the column
*/
shared_ptr<vector<string>> data::attributeType(int column)
{
    shared_ptr<vector<string>> temp(new vector<string>);//using the vector to store the attributeType
    map<string,int> m;//using map to judge if the attributeType has put into the vector
        for(unsigned int i=0;i<database.size();i++)
        {
            string s=(*database[i])[column];
            if(m[s]==0)//this attributeType has not put into the vector
            {
                m[s]++;
                temp->push_back(s);
            }

        }
    return temp;
}
/*
    name:
        data::createData
    parameter:
        int column
        string attribute
    return:
        shared_ptr<data>
    description:
        create a data object using specific attribute in the column
*/
shared_ptr<data> data::createData(int column,string attribute)
{
    shared_ptr<data> temp(new data);
    temp->countOfColumn=countOfColumn;
    for(unsigned int i=0;i<database.size();i++)
    {
        string s=(*database[i])[column];
        if(s==attribute)
            (temp->database).push_back(database[i]);
    }
    return temp;
}
/*
    name:
        data::majority
    parameter:
        int column
    return:
        string
    description:
        return the majority attribute type in the column
*/
string data::majority(int column)
{
    int num=0;
    string temp;
    shared_ptr<vector<string>> vs=attributeType(column);//get all the attribute type in the column
    //for each attribute type,count the number and find the biggest
    for(unsigned int i=0;i<vs->size();i++)
    {
        if(countNum(column,(*vs)[i])>num)
        {
            num=countNum(column,(*vs)[i]);
            temp=(*vs)[i];
        }
    }
    return temp;
}
/*
    name:
        data::truth
    parameter:
        int i
    return:
        string
    description:
        return the real truth of item i
*/
string data::truth(unsigned int i)
{
    if(i>=database.size())
        return NULL;
   return (*(database[i]))[countOfColumn-1];
}
/*
    name:
        data::item
    parameter:
        int i
    return:
       shared_ptr<vector<string>>
    description:
        return the item i
*/
shared_ptr<vector<string>> data::item(unsigned int i)
{
     if(i>=database.size())
        return NULL;
   return database[i];
}
