//
//  JSONParser.cpp
//  rz_Zom
//
//  Created by ly on 14-12-13.
//
//

#include "cocostudio/CocoStudio.h"
#include "JSONParser.h"

JSONParser* JSONParser::create(const char* fileName){
    return new JSONParser(fileName);
}

JSONParser::JSONParser(const char* fileName){
    std::string filePath = FileUtils::getInstance()->fullPathForFilename(fileName);
    std::string contentStr = FileUtils::getInstance()->getStringFromFile(filePath);
    
    _doc.Parse<0>(contentStr.c_str());
    if (_doc.HasParseError()) {
        CCLOG("GetParseError %s\n",_doc.GetParseError());
    }
}
JSONObject* JSONParser::getJsonRoot(){
    return new JSONObject(_doc);
}

//============================================================================
//这是一条邪恶的分割线
//============================================================================

int JSONObject::getInt(const char *key){
    //根据下标得到值
    return _array[key].GetInt();
}

double JSONObject::getDouble(const char *key){
    return _array[key].GetDouble();
}
const char * JSONObject::getChar(const char *key){
    if (_array.HasMember(key)) {
        return _array[key].GetString();
    }
    CCLOG("this object not hava %s key",key);
    
}
JSONObject::JSONObject(const rapidjson::Value &pArray): _array(pArray){
    
}
JSONObject* JSONObject::seachJsonObject(const char *key){
    if (_array.HasMember(key)) {
        if (_array[key].IsObject()) {
            return new JSONObject(_array[key]);
        }
        return new JSONArray(_array[key]);
        
    }
    CCLOG("this object not hava %s",key);
    return nullptr;
}
//============================================================================
//这是一条邪恶的分割线
//============================================================================

int JSONArray::getLength(){
    if (_array.IsObject()) {
        CCLOG("this json is object");
        return 0;
    }
    return _array.Size();
}
int JSONArray::arrayIntValue(int i){
    return _array[i].GetInt();
}
double JSONArray::arrayDoubleValue(int i){
    return _array[i].GetDouble();
}

void JSONArray::fillJsonIntArray(int * array, int length){
    for (int i = 0; i < length; i++) {
        array[i] = this->arrayIntValue(i);
    }
}
void JSONArray::fillJsonFloatArray(float * array, int length){
    for (int i = 0; i < length; i++) {
        array[i] = arrayDoubleValue(i);
    }
}
JSONArray* JSONArray::getJsonArray(int index){
    if (_array.IsObject()) {
        CCLOG("this array is object");
        return nullptr;
    }
   
    return new JSONArray(_array[index]);
}
JSONObject* JSONArray::getJsonObj(int index){
    if (_array.IsObject()) {
        CCLOG("this array is object");
        return nullptr;
    }
    
    return new JSONObject(_array[index]);
}

JSONObject* JSONArray::seachJsonObject(const char *key){
    if (_array.HasMember(key)) {
        if (_array[key].IsObject()) {
            return new JSONObject(_array[key]);
        }
        return new JSONArray(_array[key]);
        
    }
    for (int i = 0; i < _array.Size(); i++) {
        if (_array[i].HasMember(key)) {
            if (_array[i].IsArray()) {
                CCLOG("this is array");
            }
            return getJsonArray(i);
        }
    }
    
    CCLOG("array not hava %s",key);
    return nullptr;
}
JSONArray::JSONArray(const rapidjson::Value &pArray): JSONObject(pArray){
    
}






