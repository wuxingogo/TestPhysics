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
#include "json/rapidjson.h"
#include "json/document.h"

USING_NS_CC;

class JSONArray;

class JSONObject {
public:
    int getInt(const char * key);
    double getDouble(const char * key);
    const char * getChar(const char * key);
    
    JSONObject(const rapidjson::Value &pArray);
    
    virtual JSONObject * seachJsonObject(const char * key);
    
protected:
    const rapidjson::Value &_array;
};

class JSONArray : public JSONObject {
public:
    int getLength();
    void fillJsonIntArray(int *array , int length);
    void fillJsonFloatArray(float* array, int length);
    
    JSONArray * getJsonArray(int index);
    JSONObject * getJsonObj(int index);
    JSONObject * seachJsonObject(const char * key) override;
    
    int arrayIntValue(int i);
    double arrayDoubleValue(int i);
    
    JSONArray(const rapidjson::Value &pArray);
    

};

class JSONParser{
public:
    static JSONParser* create(const char * fileName);
    
    JSONObject* getJsonRoot();
protected:
    JSONParser(const char * fileName);
    rapidjson::Document _doc;
};





#endif /* defined(__rz_Zom__JSONParser__) */
