//
//  SkeletalArray.h
//  MyCppGame
//
//  Created by ly on 14-12-22.
//
//

#ifndef __MyCppGame__SkeletalArray__
#define __MyCppGame__SkeletalArray__

#include <iostream>
#include "JSONParser.h"

using namespace std;
class SkeletalArray{
public:
    
    static SkeletalArray* getInstence();
    void loadData(JSONObject* root,const char * key);
    const map<std::string,int *> getData(const char* key);
    
private:
    
    typedef map<std::string,int *> mymap;
    map<std::string,mymap> seq;

    
    SkeletalArray();
    static SkeletalArray* _array;
};

#endif /* defined(__MyCppGame__SkeletalArray__) */
