#ifndef CORE_ARRAYBASE_H
#define CORE_ARRAYBASE_H

#include <aro/core/Weak.hpp>

namespace aro {

template <class T>
class ArrayBase : public Object
{
   public:
      const vint length;
      
      virtual RObject clone();

      virtual vint getLenth() final;
      
      virtual T get(vint index) final;
      virtual void set(vint index, T item) final;
   
   protected:
      virtual void finalize() final; // ArrayBase class finalizer
	   
      virtual T& item(vint index) final; // allows inserting item into Array
      virtual void setLength(vint length) final; // used by Array<T>::readObject 
      virtual const T& item(vint index) const final; // retrieve item from Array
      
      virtual void copyItems(vint offset, Ref<ArrayBase<T>> src, vint srcOffset, vint num) final;
      
      ArrayBase(vint size); // ArrayBase primary constructor
      ArrayBase(Ref<ArrayBase<T>> arr); // ArrayBase copy constructor
      //template <class U>
      //ArrayBase(Ref<ArrayBase<U>> arr); // ArrayBase conversion constructor
      ArrayBase(std::initializer_list<T> elems); // ArrayBase sequence constructor
   
   private:
      T* data; // ArrayBase data of type T
      
      void init(); // allocate required memory
      void freeMemory(); // free allocated memory
      void checkIndex(vint) const; // check for valid index
   
   //template <class U> friend class ArrayBase;
};

} /* namespace aro */

#endif /* CORE_ARRAYBASE_H */
