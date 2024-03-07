#include <iostream>
#include "Token.h"
# include "Scanner.h"

int main() {
  Scanner s = Scanner("  ,  ,  ");
  Token t = s.scanToken();
  cout << t.toString() << endl;
}