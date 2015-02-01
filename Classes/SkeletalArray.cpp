//
//  SkeletalArray.cpp
//  MyCppGame
//
//  Created by ly on 14-12-22.
//
//

#include "SkeletalArray.h"

SkeletalArray* SkeletalArray::_array = NULL;

SkeletalArray::SkeletalArray(){
    
}
SkeletalArray* SkeletalArray::getInstence(){
    if (_array == NULL) {
        _array = new SkeletalArray();
    }
    return _array;
}
void SkeletalArray::loadData(JSONObject* root,const char * key){
    JSONArray* array = (JSONArray*)root->seachJsonObject(key);
    mymap item;
    for (int i = 0; i < array->getLength(); i++) {
        JSONObject* array1 = (JSONArray*)array->getJsonArray(i);
        int *arr = new int[2];
        memset(arr, 0, sizeof(int)*2);
        arr[0] = array1->getInt("startIndex");
        arr[1] = array1->getInt("endIndex");
        std::string str=(array1->getChar("name"));

        item[str] = arr;

    }
    _array->seq[key] = item;
}

const map<std::string,int *> SkeletalArray::getData(const char *key) {
    
    map<std::string,int *> tk =_array->seq[key];

    return _array->seq[key];
}



