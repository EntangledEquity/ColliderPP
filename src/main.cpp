#include "mjson/lexer.h"
#include "mjson/jobject.h"
#include "mjson/parser.h"

using namespace std;

int main(){
    JObject json("test.json");
    bool name = json["active"]; 
    std::cout<<name<<'\n';
    

    return 0;
}