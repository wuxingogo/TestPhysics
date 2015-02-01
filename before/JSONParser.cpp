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
JSONArray* JSONParser::getArray(const char * key){
    const rapidjson::Value &pArray = _doc[key];
    return new JSONArray(pArray);
}
int JSONParser::getArrayLength(const char *key){
    return _doc[key].Size();
}
double JSONParser::getArrayValueByIndex(const char * key, int index){
    return _doc[key][index].GetDouble();
}
double JSONParser::getDouble(const char * key){
    return _doc[key].GetDouble();
}
int JSONParser::getInt(const char * key){
    return _doc[key].GetInt();
}

//============================================================================
//这是一条邪恶的分割线
//============================================================================

int JSONArray::getInt(int index){
    const rapidjson::Value &pArray = *_array;
    return pArray[index].GetInt();
}
double JSONArray::getDouble(int index){
    const rapidjson::Value &pArray = *_array;
    return pArray[index].GetDouble();
}
int JSONArray::getLength(){
    return _array->Size();
}
JSONArray::JSONArray(const rapidjson::Value &pArray){
    _array = &pArray;
}
void JSONArray::fillJsonIntArray(int * array, int length){
    for (int i = 0; i < length; i++) {
        array[i] = this->getInt(i);
    }
}
void JSONArray::fillJsonFloatArray(float * array, int length){
    for (int i = 0; i < length; i++) {
        array[i] = getDouble(i);
    }
}




