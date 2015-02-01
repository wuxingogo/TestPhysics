//
//  JSONParser.h
//  rz_Zom
//
//  Created by ly on 14-12-13.
//
//

#ifndef __rz_Zom__JSONParser__
#define __rz_Zom__JSONParser__

#include "cocos2d.h"

USING_NS_CC;

class JSONArray {
public:
    int getLength();
    void fillJsonIntArray(int *array , int length);
    void fillJsonFloatArray(float* array, int length);
    int getInt(int index);
    double getDouble(int index);

    JSONArray(const rapidjson::Value &pArray);
private:
    const rapidjson::Value * _array;
};

class JSONParser{
public:
    static JSONParser* create(const char * fileName);
    double getDouble(const char * key);
    int getInt(const char * key);
    double getArrayValueByIndex(const char * key , int index);
    int getArrayLength(const char * key);
    JSONArray* getArray(const char * key);
protected:
    JSONParser(const char * fileName);
    rapidjson::Document _doc;
};



#endif /* defined(__rz_Zom__JSONParser__) */
