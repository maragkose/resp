#include <iostream>
#include <string>
#include <regex>
#include <algorithm>

class Resp {

public:

Resp(){}
~Resp(){}

	std::string to_resp_string(const std::string str){
		return "+"+str+CRLF;
	}
	std::string to_resp_error(const std::string str){
		return "-"+str+CRLF;
	}
	std::string to_resp_integer(const std::string str){
		return ":"+str+CRLF;
	}
	std::string to_resp_bstring(const std::string str){

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
	std::string to_resp_array( std::vector <std::string> v){
		std::string hdr = {"*"};
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
		std::cerr << "HELLO " << hdr << std::endl;
		std::cerr << "i " << s << std::endl;
		return hdr+s;
	}

	std::string to_resp(const std::string command){
		return to_resp_array(split(command, "\\s+"));	
	}

	std::vector<std::string> split(const std::string & stringToSplit,const std::string & regexString) {
		std::regex regexToSplitWith {regexString};
    		std::sregex_token_iterator wordsIterator {stringToSplit.begin(),stringToSplit.end(),regexToSplitWith,-1};
   		//return rvalue vector to utilize vector move semantics
    		return {wordsIterator,std::sregex_token_iterator{}};
	}
	bool is_digits(const std::string &str){
    		return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
	}
private:

	std::string CRLF = {"\r\n"};
};

int main() {

Resp resp;
std::cout << resp.to_resp_bstring("");
auto v = resp.to_resp("Hello world there 1233");

std::cout << v.c_str() << std::endl;
//std::for_each(v.begin(), v.end(), [](std::string &str) { std::cout << str << std::endl;});

}



