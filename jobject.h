#ifndef JOBJECT_H
#define JOBJECT_H

#include <map>
#include "jvalue.h"

class jobject : public jvalue
{
public:
    ~jobject();

    void set_value(const std::string &name, jvalue *value);
    jvalue *value(const std::string &name) const;

private:
    std::map<std::string, jvalue *> m_values;
};

#endif // JOBJECT_H

