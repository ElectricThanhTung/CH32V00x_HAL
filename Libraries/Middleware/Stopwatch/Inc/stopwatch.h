
#ifndef __STOPWATCH_H
#define __STOPWATCH_H

#include "ch32v00x_hal.h"

class Stopwatch {
public:
    Stopwatch(void);
    void Start(void);
    void Stop(void);
    uint32_t ElapsedTicks(void);
    uint32_t ElapsedMilliseconds(void);
    uint32_t ElapsedMicroseconds(void);
private:
    bool enabled;
    uint32_t startTick;
};

#endif /* __STOPWATCH_H */
