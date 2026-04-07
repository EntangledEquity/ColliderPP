#include "lexer.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include <map>

bool is_digit(char c){
    return c>='0' && c<='9';
}
bool is_alpha(char c){
    return (c>='a' && c<='z') || (c>='A' && c<='Z');
}

Lexer::Lexer(const char* file_path){
    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    this->file_data = new char[size];

    if(file.read(file_data, size)){
        this->m_Source = std::string_view(file_data, size);
    }else{
        delete[] file_data;
        file_data = nullptr;
    }
    
    file.close();

    tokenize();
}
Lexer::~Lexer(){
    if(file_data){
        delete[] file_data;
        file_data = nullptr;
    }
}

void Lexer::debug_print(){
    for(const auto& token:tokens){
        std::cout<<"Token: "<<static_cast<char>(token.type)<<" Lexeme: "<<token.lexeme<<"\n";
    }
}

//Looks at current char without consuming it
char Lexer::peek(){
    if (eof()) return '\0';
    return m_Source[m_Pos];
}
//Consumes and returns the current char
char Lexer::advance(){
    if (eof()) return '\0';
    return m_Source[m_Pos++];
}
bool Lexer::eof(){
    return m_Pos>=m_Source.size();
}

void Lexer::skip_whitespace(){
    while (!eof()){
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                advance();
                break;
            default:
                return;
        }
    }
}

//Assume the current char is '"'
void Lexer::read_string(){
    if(peek()!='"'){
        std::cerr<<"String read error"<<std::endl;
        exit(1);
    }advance();

    int start = m_Pos;

    while(peek()!='"' && !eof()){
        advance();
    }
    std::string_view lexme = m_Source.substr(start,m_Pos-start);
    if(eof()){
        std::cerr<<"Incomplete string: "<<lexme<<std::endl;
    }advance();

    tokens.emplace_back(TokenType::String,lexme);
}
//Assume the current char is a digit or '-'
//Only - and only . are allowed be careful
void Lexer::read_number(){
    if(!is_digit(peek()) && peek()!='-'){
        std::cerr<<"Number read error"<<std::endl;
        exit(1);
    }

    int start = m_Pos;
    bool has_dot = false;

    if(peek()=='-') advance(); //Negative number

    while(is_digit(peek()) || peek()=='.'){
        if(peek()=='.'){
            if(has_dot){
                std::cerr<<"Invalid number format: "<<m_Source.substr(start,m_Pos-start)<<std::endl;
                exit(1);
            }
            has_dot = true;
        }
        advance();
    }

    std::string_view lexme = m_Source.substr(start,m_Pos-start);
    if(has_dot){
        tokens.emplace_back(TokenType::Float,lexme);
    }else{
        tokens.emplace_back(TokenType::Int,lexme);
    }
}

bool Lexer::read_single(){
    char c = peek();
    TokenType type;

    auto single_sucess = [&](TokenType type){
        std::string_view lexeme = m_Source.substr(m_Pos, 1);
        tokens.emplace_back(type, lexeme);
        advance();
        return true;
    };

    switch (c) {
        case '{': return single_sucess(TokenType::LBrace);
        case '}': return single_sucess(TokenType::RBrace);
        case '[': return single_sucess(TokenType::LBracket);
        case ']': return single_sucess(TokenType::RBracket);
        case ',': return single_sucess(TokenType::Comma);
        case ':': return single_sucess(TokenType::Colon);
        default:return false;
    }

}
std::map<std::string, TokenType> identifiers = {
    {"true", TokenType::Bool},
    {"false", TokenType::Bool},
};
void Lexer::read_identifier(){
    int start = m_Pos;
    while (is_alpha(peek()) || peek()=='_'){
        advance();
    }
    std::string_view lexme = m_Source.substr(start,m_Pos-start);
    auto it = identifiers.find(std::string(lexme));
    if(it != identifiers.end()){
        tokens.emplace_back(it->second,lexme);
    }else{
        std::cerr<<"Unknown identifier: "<<lexme<<std::endl;
    }
}
//Identifiers not implemented yet true, false and null left
void Lexer::tokenize() {
    while (!eof()){
        skip_whitespace();
        if (eof()) break;

        // Try single characters first
        if (read_single()) continue;

        // If not a single char, check other types
        char c = peek();
        if (c == '"') {
            read_string();
        } else if (is_digit(c) || c == '-') {
            read_number();
        } else {
            read_identifier();
        }
    }
}

