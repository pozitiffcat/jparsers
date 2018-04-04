#include "jboolean.h"

jboolean::jboolean()
{
}

jboolean::jboolean(bool value)
    : m_value(value)
{
}

bool jboolean::value() const
{
    return m_value;
}
