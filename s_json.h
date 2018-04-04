#ifndef S_JSON_H
#define S_JSON_H

#include <iostream>

class jobject;
class jarray;

namespace s_json
{

jobject *read_object(std::istream &stream);
jarray *read_array(std::istream &stream);

}

#endif // JDOCUMENT_H

