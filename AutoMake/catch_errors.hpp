#ifndef CATCH_ERRORS_H
#define CATCH_ERRORS_H

#include <iostream>

inline void Lippincott() {
  try {
    throw;
  } catch (std::runtime_error const &error) {
    std::cerr << "runtime error !! " << error.what() << '\n';
  } catch (std::exception const &error) {
    std::cerr << "exception error !! : " << error.what() << '\n';
  } catch (...) {
    std::cerr << "unknown error !!\n";
  }
}
#endif // CATCH_ERRORS_H
