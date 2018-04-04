#ifndef JNUMBER_H
#define JNUMBER_H

#include "jvalue.h"

class jnumber : public jvalue
{
public:
    jnumber();
    explicit jnumber(long value);

    long value() const;

private:
    long m_value;
};

#endif // JNUMBER_H

