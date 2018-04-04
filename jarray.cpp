#include "jarray.h"

jarray::~jarray()
{
    for (std::vector<jvalue *>::iterator it = m_values.begin(); it != m_values.end(); ++it)
        delete (*it);
}

void jarray::append_value(jvalue *value)
{
    m_values.push_back(value);
}

jvalue *jarray::value(int index) const
{
    return m_values[index];
}

int jarray::count() const
{
    return m_values.size();
}
