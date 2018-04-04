#ifndef JBOOLEAN_H
#define JBOOLEAN_H

#include "jvalue.h"

class jboolean : public jvalue
{
public:
    jboolean();
    explicit jboolean(bool value);

    bool value() const;

private:
    bool m_value;
};

#endif // JBOOLEAN_H

