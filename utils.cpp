#include "utils.h"

Utils::Utils()
{
}

Utils::~Utils()
{
    delete this;
}


QTextStream& Utils::qStdOut()
{
    static QTextStream ts(stdout);
    return ts;
}
