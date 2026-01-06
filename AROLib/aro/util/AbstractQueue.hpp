#ifndef UTIL_ABSTRACTQUEUE_H
#define UTIL_ABSTRACTQUEUE_H

#include <aro/util/Queue.hpp>
#include <aro/util/AbstractCollection.hpp>


namespace aro {

namespace util {

template <class T> class AbstractQueue;

template< class T>
using RAbstractQueue = Ref<AbstractQueue<T>>;

/*
 This class provides a skeletal implementations the Queue interface,
 to minimize the effort required to implement the interface.

 This class is a member of the AROLib Collections Framework.
*/
template <class T>
class AbstractQueue extends public AbstractCollection<T> implements public Queue<T>
{
	public:
		virtual vbool addAll(RCollection<T> c);
		virtual vbool add(Ref<T> e);
		virtual Ref<T> remove();
		virtual Ref<T> item();
		virtual void clear();
	
	protected:
		AbstractQueue();
};

template <class T>
AbstractQueue<T>::AbstractQueue()
{
	// do nothing
}

template <class T>
vbool AbstractQueue<T>::add(Ref<T> obj)
{
	if(offer(obj))
		return true;
	else
		ex_throw new StateException("Queue full");
}

template <class T>
Ref<T> AbstractQueue<T>::remove()
{
	Ref<T> obj = poll();

	if(obj != nullref)
		return obj;
	else
		ex_throw new StateException("Queue is empty");
}

template <class T>
Ref<T> AbstractQueue<T>::item()
{
	Ref<T> obj = peek();

	if(obj != nullref)
		return obj;
	else
		throw new StateException("Queue is empty");
}

template <class T>
void AbstractQueue<T>::clear()
{
	while(poll() != nullref)
		;
}

template <class T>
vbool AbstractQueue<T>::addAll(RCollection<T> c)
{
	if(c == nullref)
		ex_throw new NullException();

	if(c == thisref)
		ex_throw new ArgumentException("Cannot add Queue to itself");

	vbool modified = false;

	for(Ref<T> obj : c)
		if(add(obj))
			modified = true;

	return modified;
}

}

}


#endif /* UTIL_ABSTRACTQUEUE_H */
