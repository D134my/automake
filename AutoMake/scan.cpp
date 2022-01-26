#include "scan.hpp"
#include "catch_errors.hpp"

bool Headers::bDoQuery() {
  return bQueryContents(HeaderRegex, vAllHeaderFiles);
}

void Headers::DoCreate() {
  CreateContents(sAddressOfHeaders, sMoveHeadersTo, TypeOfContents::HeaderFile);
}
