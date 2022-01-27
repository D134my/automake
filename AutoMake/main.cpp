#include "scan.hpp"
#include <iostream>

int main() {
  Headers h;
  h.DoCreate();
  CPPFiles f;
  f.DoCreate();

  CMakeFile c;
  c.DoCreate();
  c.DoEdit();
  return 0;
}
