#ifndef JOBJECT_H
#define JOBJECT_H

#include <map>
#include <vector>
#include "jvalue.h"

class jobject : public jvalue
{
public:
    ~jobject();

    void set_value(const std::string &name, jvalue *value);
    jvalue *value(const std::string &name) const;

    std::vector<std::pair<std::string, jvalue *> > to_pairs() const;

private:
    std::map<std::string, jvalue *> m_values;
};

#endif // JOBJECT_H

