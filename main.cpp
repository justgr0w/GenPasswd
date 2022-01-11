#include "ArgParse.hpp"
#define __GenPassword__
#define _VERSION_ "0.1"
#define __PROFILE__ "justgr0w(David)"
#define __GITHUB_PROFILE__ "https://github.com/justgr0w"

int main(int argc, char **argv){
    setlocale(LC_ALL, "spanish");
    // Set Flags (I / O)
    cout.setf(std::ios::boolalpha);
    // Init Obj
    ArgParse MyObj(argc, argv);
    return 0;
}
