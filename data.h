/*****************************************************************************
Copyright: 2017,Fucheng Zhang,all rights reserved
File name: data.h
Description:
Author: Fucheng Zhang,SDU,zhangfc@zhangfc.com
Version: 1.0
Date: 2017.1.19
History:
*****************************************************************************/
#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED
#include<string>
#include<vector>
#include<memory>
using namespace std;
class data
{
public:
    //default constructor
    data(){};
    //construct a data object using a file name
    data(const char *);
    //calculate the entropy of this data
    float entropy();
    //print the items in this data
    void show(unsigned int countOfItem);
    //1 parameter:count the items of this column
    //2 parameter:count the number of the specific attribute name in the column
    int countNum(int column,string attribute=" ");
    //return all the attribute type in the column
    shared_ptr<vector<string>> attributeType(int column);
    //create a data object using specific attribute in the column
    shared_ptr<data> createData(int column,string attribute);
    //return the majority attribute name in the column
    string majority(int column);
    //return the truth of item i
    string truth(unsigned int i);
    //return the item i
    shared_ptr<vector<string>> item(unsigned int i);
    //record the count of columns
    int countOfColumn;
    //database to store the pointer to the items
    vector<shared_ptr<vector<string>>>database;
};


#endif // DATA_H_INCLUDED
