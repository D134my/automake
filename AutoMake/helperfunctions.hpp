#ifndef HELPERFUNCTIONS_HPP
#define HELPERFUNCTIONS_HPP

#include "catch_errors.hpp"
#include "typeofcontents.hpp"
#include <filesystem>
#include <regex>
#include <string>
#include <vector>

inline std::string sPathToSearch{"./"};

namespace fs = std::filesystem;

bool bQueryContents(std::regex const &, std::vector<std::string> &);
void CreateContents(std::string const &, std::string const &, TypeOfContents);
#endif // HELPERFUNCTIONS_HPP
