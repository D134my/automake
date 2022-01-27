#ifndef SCAN_HPP
#define SCAN_HPP

#include "catch_errors.hpp"
#include "helperfunctions.hpp"
#include "typeofcontents.hpp"

#include <filesystem>
#include <regex>
#include <vector>

class Query {
public:
  virtual bool bDoQuery() = 0;
  virtual ~Query() = default;
};

class Create {
public:
  virtual void DoCreate() = 0;
  virtual ~Create() = default;
};

class Edit {
public:
  virtual void DoEdit() = 0;
  virtual void SetMode(Mode) = 0;
  virtual ~Edit() = default;
};

class Headers : public Query, public Create {
public:
  bool bDoQuery() override;
  void DoCreate() override;
  // void DoEdit() override;

private:
  std::string const sAddressOfHeaders{sPathToSearch + "/*.hpp " +
                                      sPathToSearch + "/*.h"};

  std::string const sMoveHeadersTo{sPathToSearch + "/include"};
  std::regex const HeaderRegex{R"(.*\.h|.*\.hpp)"};
  std::vector<std::string> vAllHeaderFiles;
};

class CPPFiles : public Query, public Create {
public:
  bool bDoQuery() override;
  void DoCreate() override;

private:
  std::string const sAddressOfCppFiles{sPathToSearch + "/*.cpp " +
                                       sPathToSearch + "/*.cc"};

  std::string const sMoveCppFilesTo{sPathToSearch + "/src/"};
  std::regex const CppRegex{R"(.*\.cpp|.*\.cc)"};
  std::vector<std::string> vAllCppFiles;
};

class CMakeFile : public Query, public Create, public Edit {
public:
  bool bDoQuery() override;
  void DoCreate() override;
  void DoEdit() override;
  void SetMode(Mode = Mode::quick) override;

private:
  std::string const sAddressOfCmakeFiles{sPathToSearch + "/CMakeLists.txt"};
  std::string const sMoveCmakeFilesTo{sPathToSearch};
  std::regex const CmakeRegex{R"(CMakeLists.txt)"};
  std::vector<std::string> vAllCmakeFiles;
  Mode CmakeMode{Mode::quick};
};

#endif // SCAN_HPP
