#pragma once

#include <string_view>
#include <vector>

#include "token.h"

class Lexer{
public:
    std::string_view m_Source;
    std::vector<Token> tokens;

    Lexer(const char* file_path);
    ~Lexer();

    Lexer(const Lexer&) = delete;
    Lexer& operator=(const Lexer&) = delete;

    void debug_print();

private:
    char* file_data=nullptr;

    size_t m_Pos = 0;

    char peek();
    char advance();
    bool eof(); 

    void skip_whitespace();

    void read_string();
    void read_number();
    bool read_single();
    void read_identifier();

    void tokenize();
};