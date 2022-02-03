#ifndef DO_SOMETHING_HPP
#define DO_SOMETHING_HPP

#include "catch_errors.hpp"
#include "typeofcontents.h"
#include <filesystem>
#include <regex>
#include <vector>

namespace fs = std::filesystem;

class AllContents {
public:
  virtual bool bQuery() = 0;
  virtual bool bIsEmpty(std::string const &) = 0;
  virtual void MoveToDir() = 0;
  virtual void Create() = 0;
  virtual ~AllContents() = default;
};
class Headers : public AllContents {
public:
  Headers(std::string const & = {"./"}, PlayMode = PlayMode::quick);
  bool bQuery() override;
  void MoveToDir() override;
  void Create() override;
  bool bIsEmpty(std::string const &) override;

private:
  std::string sAddressToSearch;
  std::string sAddressOfHeaders;
  std::string sMoveTo;
  std::regex const reRegex{R"(.*\.h|.*\.hpp)"};
  PlayMode pmMode;
  static inline std::vector<std::string> vContents;
};

class CPPFiles : public AllContents {
public:
  CPPFiles(std::string const & = {"./"}, PlayMode = PlayMode::quick);
  bool bQuery() override;
  bool bIsEmpty(std::string const &) override;
  void MoveToDir() override;
  void Create() override;

private:
  std::string sAddressToSearch;
  std::string sAddressOfCppFiles;
  std::string sMoveTo;
  std::regex const reRegex{R"(.*\.cpp|.*\.cc)"};
  PlayMode pmMode;
  static inline std::vector<std::string> vContents;
};

class CmakeFiles : public AllContents {
public:
  CmakeFiles(std::string const & = {"./"}, PlayMode = PlayMode::quick);
  bool bQuery() override;

  bool bIsEmpty(std::string const &) override;
  void WriteCmake();
  void MoveToDir() override;
  void Create() override;

private:
  std::string sAddressToSearch;
  std::string sAddressOfCMakeFiles;
  std::string sMoveTo;
  std::regex const reRegex{R"(CMakeLists.txt)"};
  PlayMode pmMode;
  static inline std::vector<std::string> vContents;
};

class Analyzer {
public:
  static void GetArgs(int, char **);

private:
  static inline std::vector<std::string> vArgs;
};

#endif // DO_SOMETHING_HPP
