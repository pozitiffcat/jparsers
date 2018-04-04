#ifndef JARRAY_H
#define JARRAY_H

#include <vector>
#include "jvalue.h"

class jarray : public jvalue
{
public:
    ~jarray();

    void append_value(jvalue *value);
    jvalue *value(int index) const;
    int count() const;

private:
    std::vector<jvalue *> m_values;
};

#endif // JARRAY_H
