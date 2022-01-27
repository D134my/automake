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

auto EditHeaders(Mode);
auto EditCppFiles(Mode);
void EditCmakeFiles(std::string const &, Mode);

bool bQueryContents(std::regex const &, std::vector<std::string> &,
                    TypeOfContents);

void CreateContents(std::string const &, std::string const &, TypeOfContents);
void EditContents(std::string const &, std::regex const &, TypeOfContents,
                  Mode);

#endif // HELPERFUNCTIONS_HPP
