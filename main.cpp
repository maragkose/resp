#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include "resp.hpp"

int main() {

Resp resp;

std::cout << resp.to_resp_bstring("");
auto v = resp.to_resp("Hello world there 1233");
std::cout <<  v << std::endl;

}



