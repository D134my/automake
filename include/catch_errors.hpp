#ifndef CATCH_ERRORS_H
#define CATCH_ERRORS_H

#include <iostream>
//#include <source_location> stupid clang doesn't support this header yet

inline void Lippincott() {
  try {
    throw;
  } catch (std::invalid_argument const& error) {
    std::cerr << "invalid argument  error !! " << error.what() << '\n';
  }

  catch (std::runtime_error const& error) {
    std::cerr << "runtime error !! " << error.what() << '\n';
  } catch (std::exception const& error) {
    std::cerr << "exception error !! : " << error.what() << '\n';
  } catch (...) {
    std::cerr << "unknown error !!\n";
  }
}
#endif  // CATCH_ERRORS_H
