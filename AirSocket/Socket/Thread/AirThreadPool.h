//
//  AirThreadPool.h
//  kxmovie
//
//  Created by penghao on 16/1/25.
//
//

#ifndef AirThreadPool_h
#define AirThreadPool_h

#include <stdio.h>
#include "AirThread.h"
namespace AirCpp {
    class ThreadPool
    {
    protected:
        static int max_thread_count;
    public:
        static Thread *main_thread(){ return nullptr;};
        static Thread *get_free_thread(){ return nullptr;};
    };
 
}
#endif /* AirThreadPool_h */
