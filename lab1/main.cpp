#include <iostream>
#include <Token.h>

int main() {
  Token t = Token(COMMA, ",", 2);
  cout << t.toString() << endl;
}