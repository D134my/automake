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

class Headers : public Query, public Create {
public:
  bool bDoQuery() override;
  void DoCreate() override;

private:
  std::string const sAddressOfHeaders{sPathToSearch + "/*.hpp " +
                                      sPathToSearch + "/*.h"};

  std::string const sMoveHeadersTo{sPathToSearch + "/include"};
  std::regex const HeaderRegex{R"(.*\.h|.*\.hpp)"};
  std::vector<std::string> vAllHeaderFiles;
};

#endif // SCAN_HPP
