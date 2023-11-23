#include <iostream>
#include <Events.h>


int main()
{
    std::string s = "mama, i love cocks";
    Event ev(s);
    ev.print();


    return 0;
}