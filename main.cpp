#include <cstdio>
#include "Vector.h"


struct cat {
    int data_;
    cat () { printf ("Construct cat\n");}
   ~cat () { printf ("Destructor cat\n"); }
};

int main() {
    cat temp_cat;
    Vector<cat> test_cat;
    test_cat.push_back (temp_cat);


    Vector<int> a (1), b(2);
    a.dumpInt();
    a.push_back (6);
    a.push_back (6);
    a.push_back (6);
    a.push_back (6);
    a.push_back (6);
    a.push_back (6);
    a.push_back (6);
    a.push_back (6);
    a.push_back (6);
    a.push_back (6);

    a.pop_back();

    Vector<int> c = a;

    Vector<int> d = 7;

    d = a;
    printf ("print: %d\n", c.at(0));
    d.dumpInt();

    Vector<int> e(10);
    e.dumpInt();
    return 0;
}
