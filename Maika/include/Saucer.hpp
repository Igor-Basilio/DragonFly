
#ifndef SAUCER_H
#define SAUCER_H

#include "../../dragonfly/include/Object.h"

class Saucer : public df::Object
{
    public :
    Saucer();
    int eventHandler(const df::Event *p_e) override;
    int moveToStart();

    private :
    void out();
};

#endif

