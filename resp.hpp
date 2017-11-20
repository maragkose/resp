#include <iostream>
#include <string>
#include <regex>
#include <algorithm>

//--------------------------------------------------
class Resp {
//--------------------------------------------------

public:

                                    Resp()  {}
                                    ~Resp() {}

    std::string                     to_resp_string (const std::string str);
    std::string                     to_resp_error (const std::string str);
    std::string                     to_resp_integer (const std::string str);
    std::string                     to_resp_bstring (const std::string str);
    std::string                     to_resp_array (std::vector <std::string> v);
    std::string                     to_resp (const std::string command);
    std::vector<std::string>        split (const std::string & stringToSplit,const std::string & regexString);
    bool                            is_digits (const std::string &str);

private:

    std::string CRLF = {"\r\n"};
};

//
// Definitions
//
//====================================================
bool Resp::is_digits(const std::string &str){
//====================================================
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

//====================================================
std::string Resp::to_resp_string(const std::string str){
//====================================================
    return "+"+str+CRLF;
}
//====================================================
std::string Resp::to_resp_error(const std::string str){
//====================================================
    return "-"+str+CRLF;
}
//====================================================
std::string Resp::to_resp_integer(const std::string str){
//====================================================
    return ":"+str+CRLF;
}
//====================================================
std::string Resp::to_resp_bstring(const std::string str){
//====================================================

    if(str.size()){
        return "$" + 
            std::to_string(str.size()) +
            CRLF +
            str +
            CRLF;
    } else {
        return "$-1" +
            CRLF +
            str +
            CRLF;
    
    }
}
//====================================================
std::string Resp::to_resp_array( std::vector <std::string> v){
//====================================================
    std::string hdr = {"*" + std::to_string(v.size())};
    std::string s;
    std::for_each(v.begin(), v.end(), 
        [&](std::string &str) { 
            if(is_digits(str)){
                s+= to_resp_integer(str);
            }else{
                s+= to_resp_bstring(str);
            }
        }
    );
    return {hdr+s};
}

//====================================================
std::string Resp::to_resp(const std::string command){
//====================================================
    return to_resp_array(split(command, "\\s+"));    
}

//====================================================
std::vector<std::string> Resp::split(const std::string & stringToSplit,const std::string & regexString) {
//====================================================
    std::regex regexToSplitWith {regexString};
    std::sregex_token_iterator wordsIterator {stringToSplit.begin(),stringToSplit.end(),regexToSplitWith,-1};
    //return rvalue vector to utilize vector move semantics
    return {wordsIterator,std::sregex_token_iterator{}};
}

