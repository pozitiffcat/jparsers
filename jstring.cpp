#include "jstring.h"

jstring::jstring()
{
}

jstring::jstring(const std::string &value)
    : m_value(value)
{
}

std::string jstring::value() const
{
    return m_value;
}
