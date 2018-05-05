#ifndef _LOG_ASSEMBLY_H_
#define _LOG_ASSEMBLY_H_

#include "LogModule.h"

class LogAssembly {
public:
    LogModule* createModule(const double * x = nullptr);
};

#endif
