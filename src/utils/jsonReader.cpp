#include <utils/jsonReader.h>
#include <iostream>

JsonReader::JsonReader(std::string fileName){
    this->name = fileName;
}

Json::Value JsonReader::read(){
    std::ifstream f(this->name, std::ifstream::binary);
    if (!f.good()) {
        std::cerr << "Error: Could not open file " << this->name << std::endl;
        exit(EXIT_FAILURE);
    }
    Json::Value v;
    Json::CharReaderBuilder builder;
    builder["collectComments"] = false; // ignore comments in JSON file
    std::string errs;

    bool parsingSuccessful = Json::parseFromStream(builder, f, &v, &errs);
    if (!parsingSuccessful) {
        std::cerr << "Error: Failed to parse JSON file " << this->name << std::endl;
        std::cerr << "Parsing errors: " << errs << std::endl;
        exit(EXIT_FAILURE);
    }

    return v;
}