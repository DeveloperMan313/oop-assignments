#include "input.hpp"
#include <cstring>

char *readString(std::istream &in) {
  char buf[64];
  in >> buf;
  const size_t bufSz = strlen(buf) + 1;
  char *str = new char[bufSz];
  strncpy(str, buf, bufSz);
  return str;
}
