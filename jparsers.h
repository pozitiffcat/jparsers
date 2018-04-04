#ifndef S_JPARSERS_H
#define S_JPARSERS_H

#include <iostream>

class jobject;
class jarray;

namespace jparsers
{

jobject *read_object(std::istream &stream);
jarray *read_array(std::istream &stream);

}

#endif // S_JPARSERS_H

