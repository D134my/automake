#include "scan.hpp"
#include "catch_errors.hpp"

bool Headers::bDoQuery() {
  return bQueryContents(HeaderRegex, vAllHeaderFiles,
                        TypeOfContents::HeaderFile);
}

void Headers::DoCreate() {
  CreateContents(sAddressOfHeaders, sMoveHeadersTo, TypeOfContents::HeaderFile);
}

bool CPPFiles::bDoQuery() {
  return bQueryContents(CppRegex, vAllCppFiles, TypeOfContents::CppFile);
}

void CPPFiles::DoCreate() {
  CreateContents(sAddressOfCppFiles, sMoveCppFilesTo, TypeOfContents::CppFile);
}

bool CMakeFile::bDoQuery() {
  return bQueryContents(CmakeRegex, vAllCmakeFiles, TypeOfContents::CmakeFile);
}

void CMakeFile::DoCreate() {
  CreateContents(sAddressOfCmakeFiles, sMoveCmakeFilesTo,
                 TypeOfContents::CmakeFile);
}

void CMakeFile::DoEdit() {
  EditContents(sPathToSearch, CmakeRegex, TypeOfContents::CmakeFile, CmakeMode);
}

void CMakeFile::SetMode(Mode CmakeMode) { this->CmakeMode = CmakeMode; }
