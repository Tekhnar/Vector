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
    printf ("Capacity: %llu Size: %llu\n", test_cat.capacity(), test_cat.size());


    Vector<int> a (1), b(2);
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

    Vector<int> c = a;

    Vector<int> d = 7;

    d = a;
    printf ("print: %d\n", c.at(0));
    d.dumpInt();
    return 0;
}
