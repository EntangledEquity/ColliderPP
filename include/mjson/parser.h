#pragma once

#include <vector>

struct Token;
class JObject;

class JParser{
public:
    JParser(std::vector<Token>&& tokens) noexcept;

    JObject result();
private:
    size_t m_Pos = 0;
    std::vector<Token> tokens;

    JObject parse_value();
    JObject parse_dict();
    JObject parse_list();

   
    Token peek();
    Token advance();
    bool eof();
};