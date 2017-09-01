
#include "stdafx.h"
#define MY_LIBRARY_COMPILATION
#include "my_library.h"

int MY_LIBRARY_API foo() {
    // ±¸Çö
    // ...
    return 0;
}

int bar::meow() const {
    throw bar_exception();
}
