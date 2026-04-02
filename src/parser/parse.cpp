#include "../../include/mjson/parser.h"
#include <vector>
#include <string>
uint32_t rSequence(std::string_view data, char open, char close){
    int counter=0;
    int point=0;
    int len=data.length();
    int answer=0;
    while(point<len){
        if(data[point]==open){
            counter++;
        }
        else if(data[point]==close){
            counter--;
        }
        if(counter==0){
            answer=point;
            break;
        }
        point++;
    }
    return answer;
}

std::string_view clean(std::string_view token) {
    std::string cleaned;
    cleaned.reserve(token.size()); 
    
    bool in_string = false;
    
    for (size_t i = 0; i < token.size(); ++i) {
        char c = token[i];
        
        if (c == '"' && (i == 0 || token[i - 1] != '\\')) {
            in_string = !in_string;
        }
        
        if (in_string) {
            cleaned += c; 
        } else {
            if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
                cleaned += c;
            }
        }
    }
    return cleaned;
}

std::vector<std::string_view> parser(std::string_view data,char target){

    std::vector<std::string_view> answer;
    size_t start=0;
    int depth_square = 0;
    int depth_curly = 0;
    bool in_string = false;
    
    for(size_t i=0;i<data.size();i++) {
        char c = data[i];

        if(c=='"' && (i==0 || data[i-1] != '\\')){
            in_string = !in_string;
        }
        else if(!in_string){
            if(c=='[') depth_square++;
            else if(c==']') depth_square--;
            else if(c=='{') depth_curly++;
            else if(c=='}') depth_curly--;
            else if(c==target && depth_square==0 && depth_curly==0){
                auto token = data.substr(start, i-start);
                if(token.size()) answer.push_back(token);
                start=i+1;
            }
        }
    }

    auto token = data.substr(start);
    if(token.size()) answer.push_back(token);
    
    return answer;
}
std::vector<std::string_view> parseData(std::string_view data, char target) {
    std::string_view cleaned_data = clean(data);
    std::vector<std::string_view> storage = parser(cleaned_data, target);
    int len=storage.size();
    std::vector<std::string_view> answer;
    for(int i=0;i<len;i++)
    {
        if(storage[i].front()=='"' && storage[i].back() == '"'){
            int len1=storage[i].length();
            std::vector<std::string_view> term=parseData(storage[i].substr(1,len1-2),target);
            int len2=term.size();
            for(int j=0;j<len2;j++)
            {
                answer.push_back(term[j]);
            }
        }
        else if(storage[i].front()=='[' && storage[i].back()==']'){
            int len1=storage[i].length();
            std::vector<std::string_view> term=parseData(storage[i].substr(1,len1-2),target);
            int len2=term.size();
            for(int j=0;j<len2;j++)
            {
                answer.push_back(term[j]);
            }
        }
        else if(storage[i].front()=='{' && storage[i].back()=='}'){
            int len1=storage[i].length();
            std::vector<std::string_view> term=parseData(storage[i].substr(1,len1-2),target);
            int len2=term.size();
            for(int j=0;j<len2;j++)
            {
                answer.push_back(term[j]);
            }
        }
        else if(storage[i].find('.') != std::string_view::npos){   
                std::vector<std::string_view> term=parser(storage[i],target);
                int len2=term.size();
                for(int j=0;j<len2;j++)
                {
                    answer.push_back(term[j]);
                }
        }
        else {
                std::vector<std::string_view> term=parser(storage[i],target);
                int len2=term.size();
                for(int j=0;j<len2;j++)
                {
                    answer.push_back(term[j]);
                }
        }
    }

    return answer;
} 


