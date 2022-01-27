#ifndef HELPERFUNCTIONS_HPP
#define HELPERFUNCTIONS_HPP

#include "catch_errors.hpp"
#include "typeofcontents.hpp"
#include <filesystem>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

inline std::string sPathToSearch{"/home/ice/hhh/"};

namespace fs = std::filesystem;

bool bQueryContents(std::regex const &, std::vector<std::string> &);
void CreateContents(std::string const &, std::string const &, TypeOfContents);
void EditContents(std::regex const &, TypeOfContents, Mode);

auto EditHeaders(Mode);

auto EditCppFiles(Mode);
auto EditCmakeFiles(std::string const &, Mode);
#endif // HELPERFUNCTIONS_HPP
