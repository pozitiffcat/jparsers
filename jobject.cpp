#include "jobject.h"

jobject::~jobject()
{
    for (std::map<std::string, jvalue *>::iterator it = m_values.begin(); it != m_values.end(); ++it)
        delete (it->second);
}

void jobject::set_value(const std::string &name, jvalue *value)
{
    m_values[name] = value;
}

jvalue *jobject::value(const std::string &name) const
{
    return m_values.at(name);
}
