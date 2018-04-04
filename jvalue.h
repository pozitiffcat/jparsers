#ifndef JVALUE_H
#define JVALUE_H

#include <string>

class jobject;
class jarray;

class jvalue
{
public:
    virtual ~jvalue() {}

    bool is_null() const;
    long as_number() const;
    bool as_boolean() const;
    std::string as_string() const;
    const jobject *as_object() const;
    const jarray *as_array() const;
};

#endif // JVALUE_H

