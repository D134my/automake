#include "helperfunctions.hpp"
#include "scan.hpp"

namespace fs = std::filesystem;

bool bQueryContents(std::regex const &regex,
                    std::vector<std::string> &vContents) {

  std::uint8_t uContentsSize = vContents.size();

  // checks if any header/file/cmake exist in path
  try {
    for (auto const &file : fs::recursive_directory_iterator(sPathToSearch)) {
      if (std::regex_search(std::string(file.path().filename()), regex)) {
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

  std::string sMvCommand{"mv " + sContentsAddresses + sMoveContentsTo};
  // using enum TypeOfContents;
  if (Type == TypeOfContents::HeaderFile) {
    Headers h;
    if (h.bDoQuery()) {
      fs::create_directory(sMoveContentsTo);
      std::system(sMvCommand.c_str());
    }
  }
}
