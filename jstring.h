#ifndef JSTRING_H
#define JSTRING_H

#include "jvalue.h"

class jstring : public jvalue
{
public:
    jstring();
    explicit jstring(const std::string &value);

    std::string value() const;

private:
    std::string m_value;
};

#endif // JSTRING_H

