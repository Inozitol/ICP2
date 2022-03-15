#pragma once

#include <map>
#include "relation.h"

class Environment
{
public:
    Environment();

protected:
    std::map<std::string, Relation*> _relations;
};
