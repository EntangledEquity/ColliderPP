#include "parser.h"
#include "jobject.h"
#include "lexer.h"


JParser::JParser(std::vector<Token>&& tokens) noexcept{
    this->tokens = std::move(tokens);
}
JObject JParser::result(){
    return parse_value();
}

JObject JParser::parse_value(){
    Token t = peek();

    switch(t.type){
        case TokenType::Bool:{
            return JObject(advance().lexeme == "true");
        }
        case TokenType::Int:{
            return JObject(std::stoi(std::string(advance().lexeme)));
        }
        case TokenType::Float:{
            return JObject(std::stof(std::string(advance().lexeme)));
        }
        case TokenType::String: {
            return JObject(std::string(advance().lexeme));
        }
        case TokenType::LBracket: {
            return parse_list();
        }
        case TokenType::LBrace:{
            return parse_dict();
        }
        default:
            std::cerr << "Unexpected token!" << std::endl;
            exit(1);
    }
}

JObject JParser::parse_list(){
    advance();
    std::vector<JObject> list;

    while (peek().type != TokenType::RBracket) {
        list.push_back(parse_value());

        if (peek().type == TokenType::Comma){
            advance(); // Consume ','
        }
    }
    advance(); // Consume ']'
    return JObject(list);
}

JObject JParser::parse_dict(){
    advance(); // Consume '{'
    std::unordered_map<std::string, JObject> map;

    while (peek().type != TokenType::RBrace) {
        std::string key = std::string(advance().lexeme); // Key must be string
        if(advance().type != TokenType::Colon){
            std::cerr << "Expected ':' after key!" << std::endl;
            exit(1);
        } // Consume ':'
        
        map[key] = parse_value(); // RECURSION HAPPENS HERE

        if (peek().type == TokenType::Comma) {
            advance(); // Consume ','
        }
    }
    advance(); // Consume '}'
    return JObject(map);
}


Token JParser::peek(){
    return tokens[m_Pos];
}
Token JParser::advance(){
    return tokens[m_Pos++];
}
bool JParser::eof(){
    return (m_Pos>=tokens.size());
}