#include "helperfunctions.hpp"
#include "scan.hpp"
#include <fstream>

namespace fs = std::filesystem;

bool bQueryContents(std::regex const &Regex,
                    std::vector<std::string> &vContents) {

  std::uint8_t uContentsSize = vContents.size();

  // checks if any header/file/cmake exist in path
  try {
    for (auto const &file : fs::recursive_directory_iterator(sPathToSearch)) {
      if (std::regex_search(std::string(file.path().filename()), Regex)) {
        vContents.push_back(std::string(file.path().filename()));
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
        EditCmakeFiles(sAddressOfContents, ContentMode);
      }
    }
  }
}

auto EditCmakeFiles(std::string const &sAddressOfCmake, Mode CmakeMode) {
  std::string sProjectName{"TestProject"};
  std::string sProjectDescription{"test c++ project"};
  float fProjectVersion{1.0};
  float fCmakeVersion{3.5};
  std::string sExecName{"TestApp"};
  std::string sExtraLibs{"no"};

  if (CmakeMode == Mode::quick) { // return default arguments
    // return std::make_tuple(sProjectName, sProjectDescription,
    // fProjectVersion,
    //                   fCmakeVersion, sExecName, sExtraLibs);
  } else if (CmakeMode == Mode::norm) {

    try {

      std::cout << "Project Name : ";
      std::cin >> sProjectName;
      std::cout << "\nProject Description : ";
      std::cin >> sProjectDescription;
      std::cout << "\n Project Version : ";
      std::cin >> fProjectVersion;
      std::cout << "\nCmake Version : ";
      std::cin >> fCmakeVersion;
      std::cout << "Extra Libs ? (Enter no if you don't have any) : ";
      std::cin >> sExtraLibs;

    } catch (...) {
      Lippincott();
      std::exit(EXIT_FAILURE);
    }

    // return std::make_tuple(sProjectName, sProjectDescription,
    // fProjectVersion,
    //                      fCmakeVersion, sExecName, sExtraLibs);

  } else {
    std::exit(EXIT_FAILURE);
  }
}
