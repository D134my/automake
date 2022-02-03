#include "do_something.hpp"
#include <algorithm>
#include <fstream>
#include <map>
#include <ranges>
#include <set>

std::string sAllClass;
std::string sAllSingleFiles;
std::string sEchoCommand;
std::vector<std::string> vOtherFiles;
std::vector<std::string> vSingleFiles;
std::vector<std::string> vSameFilesCpp;
std::vector<std::string> vSameFilesHpp;

void removeDuplicates(std::string &str) {
  std::set<char> S, Sd;
  std::string reduced;

  for (char c : str) {
    if (S.insert(c).second)
      reduced += c;
  }
}

Headers::Headers(std::string const &sAddressToSearch, PlayMode Mode) {
  this->sAddressToSearch = sAddressToSearch;
  this->sAddressOfHeaders =
      std::string(sAddressToSearch + "/*.hpp " + sAddressToSearch + +"/*.h ");
  this->sMoveTo = std::string(sAddressToSearch + "/include/");
}

bool Headers::bQuery() {
  try {
    int i{};
    for (auto const &file :
         fs::recursive_directory_iterator(sAddressToSearch)) {
      if (std::regex_search(std::string(file.path().filename()), reRegex)) {
        vContents.push_back(std::string(file.path().filename()));
        // sAllContents += sMoveTo + std::string(file.path().filename()) + " ";

        std::string path = file.path().c_str();
        if (bIsEmpty(path)) {
          sEchoCommand =
              "echo  \"#ifndef __" + std::string(file.path().filename()) +
              "__H\n#define __" + std::string(file.path().filename()) +
              "__H\n\n\n\n#endif\" >> ";
          sEchoCommand += file.path();
          std::system(sEchoCommand.c_str());
        }
        i++;
      }
    }

  } catch (...) {
    Lippincott();
    std::exit(EXIT_FAILURE);
  }

  if (vContents.empty())
    return false;

  return true;
}

bool Headers::bIsEmpty(std::string const &pFile) {
  return fs::file_size(pFile) == 0;
}

void Headers::MoveToDir() {
  auto h = std::make_unique<Headers>(sAddressToSearch, pmMode);
  std::string sMvCommand{"mv " + sAddressOfHeaders + " " + sMoveTo};
  if (h->bQuery()) {
    fs::create_directory(sMoveTo);
    std::system(sMvCommand.c_str());
  }

  else {
    // Create();
  }
}

void Headers::Create() {
  std::cout << "\nCreate Header File ? (y/n) : ";
  std::string sAnswer;
  std::size_t uiNumberOfHeaders;
  try {
    std::cin >> sAnswer;
    if (sAnswer == "y") {
      std::cout << "how many header wanna create ? ";
      std::cin >> uiNumberOfHeaders;
      std::vector<std::string> vHeadersNames(uiNumberOfHeaders);

      for (std::size_t i{}; i < uiNumberOfHeaders; ++i) {
        std::cout << "\nEnter file name " << i << " : ";
        std::cin >> vHeadersNames.at(i);
      }
      for (std::size_t i{}; i < vHeadersNames.size(); i++)
        vContents.push_back(vHeadersNames.at(i));

      for (std::size_t i{}; i < uiNumberOfHeaders; i++) {
        sEchoCommand = "echo \"#ifndef __" + vHeadersNames.at(i) +
                       "__H\n#define __" + vHeadersNames.at(i) +
                       "__H\n\n\n\n#endif\" >> ";
        sEchoCommand += sAddressToSearch + vHeadersNames.at(i);
        std::system(sEchoCommand.c_str());
      }
      MoveToDir();
    }
  } catch (...) {
    Lippincott();
    std::exit(EXIT_FAILURE);
  }
}

/////////////////////////////// CPPFiles
/////////////////////////////////////////////

CPPFiles::CPPFiles(std::string const &sAddressToSearch, PlayMode Mode) {
  this->sAddressToSearch = sAddressToSearch;
  this->sAddressOfCppFiles =
      std::string(sAddressToSearch + "/*.cpp " + sAddressToSearch + +"/*.cc ");
  this->sMoveTo = std::string(sAddressToSearch + "/src/");
}

bool CPPFiles::bIsEmpty(std::string const &pFile) {
  return fs::file_size(pFile) == 0;
}

bool CPPFiles::bQuery() {
  for (auto const &file : fs::recursive_directory_iterator(sAddressToSearch)) {
    if (std::regex_search(file.path().filename().string(), reRegex)) {
      vContents.push_back(file.path().filename().string());

      // remove file extenstion
      std::regex Cppre(R"([^(?:.cpp|.cc)]*)");
      std::string sCppName = file.path().filename();
      std::string sExacCppFile;
      std::smatch CppSm;

      std::regex Hppre(R"([^(?:.hpp|.h)]*)");
      std::string sHppName;
      std::string sExacHppFile;
      std::smatch HppSm;
      std::regex const reIsHeader{R"(.*\.h|.*\.hpp)"};
      bool bAnyHeaderExist = false;

      if (std::regex_search(sCppName, CppSm, Cppre)) {
        sExacCppFile = CppSm.str();
      }
      for (auto const &file2 :
           fs::recursive_directory_iterator(sAddressToSearch)) {
        if (std::regex_search(file2.path().filename().string(), reIsHeader)) {
          bool bAnyHeaderExist = true;
          sHppName = file2.path().filename().string();

          if (std::regex_search(sHppName, HppSm, Hppre)) {
            sExacHppFile = HppSm.str();
          }

          if (sExacCppFile == sExacHppFile) {
            vSameFilesCpp.push_back(file.path().filename());
            vSameFilesHpp.push_back(sHppName);
            if (bIsEmpty(file.path().string())) {
              std::string sEcho = R"(echo '#include ")" + sHppName +
                                  R"(" ' >)" + file.path().string();
              std::cout << sEcho << std::endl;
              std::system(sEcho.c_str());
            }
          }

        } // if it wasn't header ignore it !
      }   // end of header search
      for (auto const &f : vSameFilesCpp) {
      }

      vOtherFiles.push_back(file.path().filename());

    } // end of if cpp founded
  }
  for (auto const &f : vOtherFiles) {
    if (std::find(vSameFilesCpp.begin(), vSameFilesCpp.end(), f) ==
        vSameFilesCpp.end()) {
      vSingleFiles.push_back(f);
    }
  }

  for (std::size_t i{}; i < vSingleFiles.size(); ++i) {
    if (std::find(vSingleFiles.begin(), vSingleFiles.end(), "main.cpp") !=
        vSingleFiles.end()) {
      if (bIsEmpty(std::string(sAddressToSearch + "main.cpp"))) {
        std::string sEchoCommandSingleFile1{
            R"(echo '#include <iostream>\n\n\n)"};
        std::string sEchoCommandSingleFile2{
            R"(int main(int argc, char** argv) {\n\n)"};
        std::string sEchoCommandSingleFile3{
            R"(    return EXIT_SUCCESS;\n'} >)"};

        std::string sResultOfEcho = sEchoCommandSingleFile1 +
                                    sEchoCommandSingleFile2 +
                                    sEchoCommandSingleFile3 +
                                    std::string(sAddressToSearch + "main.cpp");

        std::system(sResultOfEcho.c_str());
      }

    } else {
      try {
        std::smatch sm;
        for (auto const &test : vSingleFiles) {
          std::ifstream fi(sAddressToSearch + test);
          std::string sFileHasMain(std::istreambuf_iterator<char>(fi.rdbuf()),
                                   std::istreambuf_iterator<char>());

          if (std::regex re("int main*");
              std::regex_search(sFileHasMain, sm, re)) {
            std::cout << "there's no main.cpp but I realized " << test
                      << " has main so I trait to it as main.cpp \n";
            break;
          }
        }
      } catch (...) {
        Lippincott();
        std::exit(EXIT_FAILURE);
      }
    }
  }

  if (vContents.empty()) {
    return false;
  }
  return true;
}

void CPPFiles::MoveToDir() {
  std::ranges::sort(vSingleFiles);
  std::ranges::sort(vSameFilesCpp);

  vSingleFiles.erase(
      std::unique(std::begin(vSingleFiles), std::end(vSingleFiles)),
      vSingleFiles.end());

  vSameFilesCpp.erase(std::unique(vSameFilesCpp.begin(), vSameFilesCpp.end()),
                      vSameFilesCpp.end());

  for (auto const &alone : vSingleFiles) {
    sAllSingleFiles += alone + " ";
  }
  for (auto const &cl : vSameFilesCpp) {
    sAllClass += cl + " ";
  }
  std::cout << "\n\nclass " << sAllClass << "\n single " << sAllSingleFiles
            << std::endl;

  auto cpp = std::make_unique<CPPFiles>(sAddressToSearch, pmMode);
  std::string sMvCommand{"mv " + sAddressOfCppFiles + " " + sMoveTo};
  if (cpp->bQuery()) {
    fs::create_directory(sMoveTo);
    std::system(sMvCommand.c_str());
  }
}

void CPPFiles::Create() {
  std::cout << "\nCreate Cpp File ? (y/n) : ";
  std::string sAnswer;
  std::size_t uiNumberOfCppFiles;
  std::string sTouchCommand;
  try {
    std::cin >> sAnswer;
    if (sAnswer == "y") {
      std::cout << "how many cpp wanna create ? ";
      std::cin >> uiNumberOfCppFiles;
      std::vector<std::string> vCppNames(uiNumberOfCppFiles);

      for (std::size_t i{}; i < uiNumberOfCppFiles; ++i) {
        std::cout << "\nEnter file name " << i << " : ";
        std::cin >> vCppNames.at(i);
      }
      for (std::size_t i{}; i < vCppNames.size(); i++)
        vContents.push_back(vCppNames.at(i));

      for (std::size_t i{}; i < uiNumberOfCppFiles; i++) {
        sTouchCommand = "touch " + sAddressToSearch + vCppNames[i];
        std::cout << sTouchCommand << std::endl;
        std::system(sTouchCommand.c_str());
      }
      // MoveToDir();
    }
  } catch (...) {
    Lippincott();
    std::exit(EXIT_FAILURE);
  }
}

/////////////////// CmakeFiles ////////////////////

CmakeFiles::CmakeFiles(std::string const &sAddressToSearch, PlayMode Mode) {
  this->sAddressToSearch = sAddressToSearch;
  this->sAddressOfCMakeFiles = std::string(sAddressToSearch + "CMakeLists.txt");
  this->sMoveTo = std::string(sAddressToSearch);
}

bool CmakeFiles::bQuery() {
  for (auto const &file : fs::recursive_directory_iterator(sAddressToSearch)) {
    if (std::regex_search(std::string(file.path().filename()), reRegex)) {
      vContents.push_back(std::string(file.path().filename()));
    }
  }
  if (vContents.empty())
    return false;

  return true;
}

bool CmakeFiles::bIsEmpty(std::string const &pFile) {
  return fs::file_size(pFile) == 0;
}

void CmakeFiles::WriteCmake() {
  auto cmake = std::make_unique<CmakeFiles>(sAddressToSearch);
  if (!cmake->bQuery()) {

    std::string sProjectName{"TestProject"};
    std::string sProjectDescription{"test c++ project"};
    float fProjectVersion{1.0};
    float fCmakeVersion{3.5};
    std::string sExecName{"TestApp"};
    std::string sExtraLibs{"no"};

    if (pmMode == PlayMode::norm) {
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

      /*
    of << "cmake_minimum_required(VERSION " << fCmakeVersion << " )"
       << std::endl;
    of << "project( " << sProjectName << " VERSION " << fProjectVersion
       << " DESCRIPTION " << '\"' << sProjectDescription << '\"'
       << " LANGUAGES CXX )" << std::endl;
    of << "set(CMAKE_CXX_STANDARD 20)" << std::endl;
    of << "set(CMAKE_CXX_STANDARD_REQUIRED ON)" << std::endl;
    of << "include_directories(include)" << std::endl;
    of << "include_directories(src)" << std::endl;
    of << "add_executable( " << sExecName << " " << sAllContents << " )"
       << std::endl;

    if (sExtraLibs != "no") {
      of << "target_link_libraries( " << sExecName << " " << sExtraLibs
         << " )" << std::endl;
*/

      std::ofstream of1(sAddressOfCMakeFiles);
      of1 << "cmake_minimum_required(VERSION " << fCmakeVersion << " )"
          << std::endl;
      of1 << "project( " << sProjectName << " VERSION " << fProjectVersion
          << " DESCRIPTION " << '\"' << sProjectDescription << '\"'
          << " LANGUAGES CXX )" << std::endl;
      of1 << "set(CMAKE_CXX_STANDARD 20)" << std::endl;
      of1 << "set(CMAKE_CXX_STANDARD_REQUIRED ON)" << std::endl;
      of1 << "if(MSVC)" << std::endl;
      of1 << "      add_compile_options(/W4 /WX)" << std::endl;
      of1 << "else()" << std::endl;
      of1 << "    add_compile_options(-Wall -Wextra -Wpedantic)" << std::endl;

      of1 << "endif()" << std::endl;
      of1 << "add_subdirectory(src)" << std::endl;
      of1.close();

      std::ofstream of2(sAddressToSearch + "/src/CMakeLists.txt");
      of2 << "include_directories(../include)" << std::endl;
      of2 << "add_library(lib " << sAllClass << " )" << std::endl;
      of2 << "add_executable( " << sExecName << " " << sAllSingleFiles << " )";

    } catch (...) {
      Lippincott();
      std::exit(EXIT_FAILURE);
    }
  }
}

void CmakeFiles::Create() {}
void CmakeFiles::MoveToDir() {}

////////////////////// Analyzer //////////////////////////
/// \brief Analyzer::GetArgs
/// \param Argc
/// \param Argv

void Analyzer::GetArgs(int Argc, char **Argv) {
  /*
    if (Argc == 1) {
      auto header = std::make_unique<Headers>();
      header->MoveToDir();
    } else if (Argc > 2) {
      std::string path{"./"};
      std::string mode;
      PlayMode RealMode{PlayMode::quick};

      for (std::size_t index{1}; index != Argc; ++index) {
        vArgs.push_back(Argv[index]);
      }

      auto iterResultSearch = std::find(vArgs.begin(), vArgs.end(), "path");
      if (iterResultSearch != vArgs.end()) {
        path = *(iterResultSearch + 1);
      }

      iterResultSearch = std::find(vArgs.begin(), vArgs.end(), "mode");
      if (iterResultSearch != vArgs.end()) {
        mode = *(iterResultSearch + 1);
      }

      if (!mode.empty()) {
        if (mode == "norm") {
          RealMode = PlayMode::norm;
        }
      }
      auto header = std::make_unique<Headers>(path, RealMode);
      header->MoveToDir();
      if (RealMode == PlayMode::norm) {
        header->Create();
        header->MoveToDir();
      }
    }
    */
  try {
    CPPFiles c("/home/ice/hhh/");
    Headers h("/home/ice/hhh/");

    //   h.Create();
    h.bQuery();
    h.MoveToDir();

    // c.Create();
    c.bQuery();
    c.MoveToDir();
    CmakeFiles cmake("/home/ice/hhh/", PlayMode::norm);
    cmake.bQuery();
    cmake.WriteCmake();
  } catch (...) {
    Lippincott();
    std::exit(EXIT_FAILURE);
  }
}
