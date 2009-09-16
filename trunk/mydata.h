#ifndef MYDATA_H
#define MYDATA_H


#include "l2aconversion.h"



class MyData
{
public:
    MyData();
    static void Init();

public:
    static L2AConversion* l2aEngine;
};

//L2AConversion* MyData::l2aEngine;

#endif // MYDATA_H
