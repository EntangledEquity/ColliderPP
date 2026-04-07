#include "jobject.h"
#include "lexer.h"
#include "parser.h"

void JObject::check_error(JType target) const {
    if (target != type)
        std::cerr << "Invalid type conversion of JObject"<< "\n";
}

void JObject::clean_data() {
    if (type == JType::String) delete data.svalue;
    if (type == JType::List)   delete data.lvalues;
    if (type == JType::Dict)   delete data.mvalues;
    type = JType::Null;
}

void JObject::deep_copy_data(const JObject& other) {
    type = other.type;
    if (type == JType::Bool) data.bvalue = other.data.bvalue;
    else if (type == JType::Int) data.ivalue  = other.data.ivalue;
    else if (type == JType::Float) data.fvalue  = other.data.fvalue;
    else if (type == JType::String) data.svalue  = new std::string(*other.data.svalue);
    else if (type == JType::List) data.lvalues = new std::vector<JObject>(*other.data.lvalues);
    else if (type == JType::Dict) data.mvalues = new std::unordered_map<std::string, JObject>(*other.data.mvalues);
    else std::cerr << "Uninitialised JObject being copied\n";
}


JObject::JObject(const char* file_path){
    Lexer lexer(file_path);
    JParser parser(std::move(lexer.tokens));
    *this = std::move(parser.result());
}

JObject::JObject():type(JType::Null) {}
JObject::JObject(bool a):type(JType::Bool), data{.bvalue = a} {}
JObject::JObject(int a):type(JType::Int), data{.ivalue = a} {}
JObject::JObject(float a):type(JType::Float), data{.fvalue = a} {}
JObject::JObject(const std::string& a):type(JType::String), data{.svalue = new std::string(a)} {}
JObject::JObject(const std::vector<JObject>& a):type(JType::List), data{.lvalues = new std::vector<JObject>(a)} {}
JObject::JObject(const std::unordered_map<std::string, JObject>& a):type(JType::Dict), data{.mvalues = new std::unordered_map<std::string, JObject>(a)} {}


// Copy constructor
JObject::JObject(const JObject& other) {
    deep_copy_data(other);          
}

// Move constructor 
JObject::JObject(JObject&& other) noexcept {
    type = other.type;         
    data = other.data;         
    other.type = JType::Null;                
}

// Copy assignment 
JObject& JObject::operator=(const JObject& other) {
    if (this == &other) return *this;   
    clean_data();                       
    deep_copy_data(other);            
    return *this;
}

//  Move assignment 
JObject& JObject::operator=(JObject&& other) noexcept {
    if (this == &other) return *this;
    clean_data();                       
    type = other.type;            
    data = other.data;
    other.type = JType::Null;                   
    return *this;
}


JObject::~JObject() {
    clean_data();
}

JObject::operator bool() const {
    check_error(JType::Bool);
    return data.bvalue;
}
JObject::operator int() const {
    check_error(JType::Int);
    return data.ivalue;
}

JObject::operator float() const {
    check_error(JType::Float);
    return data.fvalue;
}

JObject::operator std::string() const {
    check_error(JType::String);
    return *data.svalue;
}

JObject::operator std::vector<JObject>() const {
    check_error(JType::List);
    return *data.lvalues;
}

JObject::operator std::unordered_map<std::string, JObject>() const {
    check_error(JType::Dict);
    return *data.mvalues;
}

const JObject& JObject::operator[](int idx) const {
    check_error(JType::List);
    return data.lvalues->at(idx);
}

const JObject& JObject::operator[](const std::string& key) const {
    check_error(JType::Dict);
    return data.mvalues->at(key);
}
const JObject& JObject::operator[](const char* key) const{
    return this->operator[](std::string(key));
}

