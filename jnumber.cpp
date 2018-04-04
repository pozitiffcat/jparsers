#include "jnumber.h"

jnumber::jnumber()
    : m_value(0)
{
}

jnumber::jnumber(long value)
    : m_value(value)
{
}

long jnumber::value() const
{
    return m_value;
}
