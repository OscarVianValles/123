#include "rmdir.hpp"

rmdir::rmdir(std::list<std::string> inputParams) { params = inputParams; }

rmdir::~rmdir() {}

bool rmdir::execute(FileTree &t) {
    if (params.empty()) {
        std::cout << "rmdir: directory name cannot be blank" << std::endl;
        return false;
    }

    std::list<std::string> tokens = tokenize(params.front(), '/');

    Node *curr = t.current();

    if (tokens.back() == "") {
        tokens.pop_back();
    }

    std::string name = tokens.back();
    tokens.pop_back();

    if (tokens.size() >= 1) {
        curr = t.search(tokens, false);
    }

    if (curr == nullptr) {
        std::cout << "rmdir: no such directory" << std::endl;
        return false;
    }

    t.remove(curr);
    return true;
}