#include <iostream>
#include <fstream>
#include <stack>
#include <string>

using string = std::string;
template <typename T> using stack = std::stack<T>;

bool isFileType(const string& filename, const string& extension) {
  stack<char> ext;

  for (string::const_reverse_iterator it = filename.rbegin(); it != filename.rend(); it++) {
    if (*it == '.') {
      break;
    }
    ext.push(*it);
  }

  if (ext.size() != extension.size()) {
    return false;
  }

  for (string::const_iterator it = extension.begin(); it != extension.end(); it++) {
    if (*it != ext.top()) {
      return false;
    }
    ext.pop();
  }

  return true;
}

int main(int argc, char** argv) {
  if (argc == 1) {
    std::cout << "\033[31mInvalid number of arguments, expected:\n    " << argv[0] << " <filename>\e[0m\n";
  }

  string filename(argv[1]);
  if (isFileType(filename, "math")) {
    std::cout << "File Detected\n";
  }

  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Unable to open file '" << filename << "'\n";
    return 1;
  }
  
  

  file.close();
  return 0;
}
