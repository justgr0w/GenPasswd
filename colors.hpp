#if !defined(__COLORS__)
#define __COLORS__
#include <iostream>
using namespace std;

namespace Color
{
    const char *BLACK   = "\033[30m";
    const char *RED     = "\033[31m";
    const char *GREEN   = "\033[32m";
    const char *YELLOW  = "\033[33m";
    const char *BLUE    = "\033[34m";
    const char *MAGENTA = "\033[35m";
    const char *CYAN    = "\033[36m";
    const char *WHITE   = "\033[37m";
    const char *RESET   = "\033[37m\033[38m";

    const char *LIGHTBLACJ_EX   = "\033[90m";
    const char *LIGHTRED_EX     = "\033[91m";
    const char *LIGHTGREEN_EX   = "\033[92m";
    const char *LIGHTYELLOW_EX  = "\033[93m";
    const char *LIGHTBLUE_EX    = "\033[94m";
    const char *LIGHTMAGENTA_EX = "\033[95m";
    const char *LIGHTCYAN_EX    = "\033[96m";
    const char *LIGHTWHITE_EX   = "\033[97m";

    void _UP(const char *data, int number){
        cout<<"\033["<<number<<"A"<<data;
    }
    void _DOWN(const char *data, int number){
        cout<<"\033["<<number<<"B"<<data;
    }
    void _FORDWARD(const char *data, int number){
        cout<<"\033["<<number<<"C"<<data;
    }
    void _BACK(const char *data, int number){
        cout<<"\033["<<number<<"D"<<data;
    }
    void _POS(const char *data, int number1, int number2){
        cout<<"\033[%s"<<number1<<";"<<number2<<"h"<<data;
    }
    void _SET_TITLE(const char *title){
        cout<<"\033]"<<"2;"<<title<<"\007";
    }
    void _CLEAR(void){
        cout<<"\033[3J"<<"\033[H"<<"\033[2J";
    }
}

void POINTGREEN(const char *data){
    cout<<Color::LIGHTGREEN_EX<<Color::BLUE<<"*"<<Color::LIGHTGREEN_EX<<Color::LIGHTWHITE_EX<<data<<Color::RESET;
}

void POINTRED(const char *data){
    cout<<Color::LIGHTYELLOW_EX<<Color::RED<<"*"<<Color::LIGHTYELLOW_EX<<Color::LIGHTMAGENTA_EX<<data<<Color::RESET;
}

#endif
