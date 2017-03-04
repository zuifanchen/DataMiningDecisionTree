/*****************************************************************************
Copyright: 2017,Fucheng Zhang,all rights reserved
File name: main.cpp
Description:
Author: Fucheng Zhang,SDU,zhangfc@zhangfc.com
Version: 1.0
Date: 2017.1.19
History:
*****************************************************************************/
#include<iostream>
#include"data.h"
#include"tree.h"
#include<fstream>
using namespace std;

int main()
{
    //open source data
    data a("1.data");
    //construct a tree using source data
    tree t(a);
    //write the rule to the file
    //ofstream of("rule.txt");
    //of<<t.generateRule(t.root,0);
    //of.close();
    //open test data
    data b("1.test");
    int count[4]={0};//count the number of correct forecast
    //forecast each item
    unsigned int length=b.database.size();
    for(unsigned int i=0;i<length;i++)
    {
        if(b.truth(i)=="<=50K"&&t.forecast(b.item(i))=="<=50K")
            count[0]++;
        else if (b.truth(i)=="<=50K"&&t.forecast(b.item(i))==">50K")
            count[1]++;
        else if (b.truth(i)==">50K"&&t.forecast(b.item(i))=="<=50K")
            count[2]++;
        else if (b.truth(i)==">50K"&&t.forecast(b.item(i))==">50K")
            count[3]++;
    }
    //calculate the percentage
    //float consequence=count*100.0/length;
    for(int i=0;i<4;i++)
        cout<<count[i]<<endl;
    cout<<((count[0]+count[3])*1.0/length)*100<<"\%"<<endl;
   //cin.get();

    return 0;
}
