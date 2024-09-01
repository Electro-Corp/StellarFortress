#ifndef READJSON_H
#define READJSON_H
#include <json/value.h>
#include <json/json.h>
#include <fstream>
class JsonReader {
    public:
    std::string name;
    JsonReader(std::string fileName);
    /*
        How to use JSON Reader
        It will return a var (crazy)
        To get value use var["KeyName"]
        so if json look like
        {
        "goof": 3
        }
        u use varName["goof"]
    */

    Json::Value read();
    

};
#endif