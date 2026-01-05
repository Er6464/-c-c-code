#include <iostream>
#include <string>
#include <stack>

int main() {
    // ใช้ std::string เพราะเราไม่ได้ประกาศ `using namespace std;`
    std::string number = " 122";
    std::stack<char> s;


for (char c : number) {
    s.push(c);

}

while ( !s.empty()){
    std::cout <<s.top();
    s.pop();
}

    return 0;
}