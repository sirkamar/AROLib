#ifndef UTIL_QUEUE_H
#define UTIL_QUEUE_H

#include <aro/util/Collection.hpp>

namespace aro {

namespace util {

template <class T> interface Queue;

template <class T>
using RQueue = Ref<Queue<T>>;

/*
 A collection designed for holding elements prior to processing.

 Besides basic Collection operations, queues provide additional
 insertion, extraction, and inspection operations. Queues typically,
 but do not necessarily, order elements in a FIFO (first-in-first-out) manner.

 This interface is a member of the AROLib Collections Framework.
*/
template <class T>
interface Queue extends virtual Collection<T>
{
	virtaul vbool offer(Ref<T> e) = 0;
	virtual vbool add(Ref<T> e) = 0;
	virtual Ref<T> remove() = 0;
	virtual Ref<T> poll() = 0;
	virtual Ref<T> item() = 0;
	virtual Ref<T> peek() = 0;
};

} // namespace util

} // namespace aro

#endif /* UTIL_QUEUE_H */
