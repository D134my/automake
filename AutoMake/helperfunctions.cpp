#include "helperfunctions.hpp"
#include "scan.hpp"
#include <fstream>

std::string sAllFiles;
namespace fs = std::filesystem;

bool bQueryContents(std::regex const &Regex,
                    std::vector<std::string> &vContents, TypeOfContents Type) {

  std::uint8_t uContentsSize = vContents.size();

  // checks if any header/file/cmake exist in path
  try {
    for (auto const &file : fs::recursive_directory_iterator(sPathToSearch)) {
      if (std::regex_search(std::string(file.path().filename()), Regex)) {
        vContents.push_back(std::string(file.path().filename()));
        if (Type == TypeOfContents::HeaderFile) {
          sAllFiles +=
              std::string("./include/") + std::string(file.path().filename());
          sAllFiles += " ";
        } else if (Type == TypeOfContents::CppFile) {
          sAllFiles +=
              std::string("./src/") + std::string(file.path().filename());
          sAllFiles += " ";
        }
      }
    }
    // if no file founded return false
    if (vContents.size() == uContentsSize)
      return false;

  } catch (...) {
    Lippincott();
    std::exit(EXIT_FAILURE);
  }

  return true;
}

void CreateContents(std::string const &sContentsAddresses,
                    std::string const &sMoveContentsTo, TypeOfContents Type) {

  std::string sMvCommand{"mv " + sContentsAddresses + " " + sMoveContentsTo};
  // using enum TypeOfContents;
  if (Type == TypeOfContents::HeaderFile) {
    Headers h;
    if (h.bDoQuery()) {
      fs::create_directory(sMoveContentsTo);
      std::system(sMvCommand.c_str());
      std::system("clear");
    }

  } else if (Type == TypeOfContents::CppFile) {
    CPPFiles f;
    if (f.bDoQuery()) {
      fs::create_directory(sMoveContentsTo);
      std::system(sMvCommand.c_str());
      std::system("clear");
    }
  } else if (Type == TypeOfContents::CmakeFile) {
    CMakeFile c;
    if (c.bDoQuery()) {
      fs::create_directory(sMoveContentsTo);
      std::system(sMvCommand.c_str());
      std::system("clear");
    } else { // if no cmakefile exists create one
      std::string sTouchCommand{"touch " + sContentsAddresses};
      std::system(sTouchCommand.c_str());
      std::system("clear");
    }
  }
}

void EditContents(std::string const &sAddressOfContents,
                  std::regex const &Regex, TypeOfContents Type,
                  Mode ContentMode) {

  for (auto const &file :
       fs::recursive_directory_iterator(sAddressOfContents)) {
    if (std::regex_search(std::string(file.path().filename()), Regex)) {
      if (Type == TypeOfContents::CmakeFile) {
        EditCmakeFiles(sAddressOfContents + std::string(file.path().filename()),
                       ContentMode);
      }
    }
  }
}

void EditCmakeFiles(std::string const &sAddressOfCmake, Mode CmakeMode) {
  std::string sProjectName{"TestProject"};
  std::string sProjectDescription{"test c++ project"};
  float fProjectVersion{1.0};
  float fCmakeVersion{3.5};
  std::string sExecName{"TestApp"};
  std::string sExtraLibs{"no"};

  if (CmakeMode == Mode::norm) {

    try {

      std::cout << "Project Name : ";
      std::getline(std::cin, sProjectName);
      if (std::cin.fail() || std::cin.eof())
        throw std::invalid_argument("Enter better project name !\n");
      std::cout << "\nProject Description : ";
      std::getline(std::cin, sProjectDescription);
      if (std::cin.fail() || std::cin.eof())
        throw std::invalid_argument("Enter better project description !\n");

      std::cout << "\nProject Version : ";
      std::cin >> fProjectVersion;
      if (std::cin.fail() || std::cin.eof())
        throw std::invalid_argument("Enter a valid float number !\n");

      std::cout << "\nCmake Version : ";
      std::cin >> fCmakeVersion;
      if (std::cin.fail() || std::cin.eof())
        throw std::invalid_argument("Enter a valid float number  !\n");
      std::cout << "Extra Libs ? (Enter no if you don't have any) : ";
      std::getline(std::cin >> std::ws, sExtraLibs);
      if (std::cin.fail() || std::cin.eof())
        throw std::invalid_argument("Enter valid libs names !\n");

    } catch (...) {
      Lippincott();
      std::exit(EXIT_FAILURE);
    }
  }

  try {

    std::ofstream of(sAddressOfCmake);
    of << "cmake_minimum_required(VERSION " << fCmakeVersion << " )"
       << std::endl;
    of << "project( " << sProjectName << " VERSION " << fProjectVersion
       << " DESCRIPTION " << '\"' << sProjectDescription << '\"'
       << " LANGUAGES CXX )" << std::endl;
    of << "set(CMAKE_CXX_STANDARD 20)" << std::endl;
    of << "set(CMAKE_CXX_STANDARD_REQUIRED ON)" << std::endl;
    of << "include_directories(include)" << std::endl;
    of << "include_directories(src)" << std::endl;
    of << "add_executable( " << sExecName << " " << sAllFiles << " )"
       << std::endl;
    if (sExtraLibs != "no" || sExtraLibs != "NO" || sExtraLibs != " " ||
        sExtraLibs != "") {
      of << "target_link_libraries( " << sExecName << " " << sExtraLibs << " )"
         << std::endl;
    }

    of.close();

  } catch (...) {
    Lippincott();
    std::exit(EXIT_FAILURE);
  }
}
