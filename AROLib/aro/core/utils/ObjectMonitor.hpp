#ifndef CORE_UTILS_OBJECTMONITOR_H
#define CORE_UTILS_OBJECTMONITOR_H

namespace aro {

class Object;

class ObjectMonitor final
{
    public:
        void wait();

        void lock();

        void unlock();

        void notify();

        void notifyAll();

    private:
        ObjectMonitor() = default;

        /** Used to implement exclusion */
        std::recursive_mutex mutex;

        /** Used to implement wait/notify */
        std::condition_variable_any cva;

        ObjectMonitor(const ObjectMonitor&);

        ObjectMonitor& operator=(const ObjectMonitor&);

    friend class Object;
};

} /* namespace aro */

#endif /* CORE_UTILS_OBJECTMONITOR_H */
