#ifndef CORE_ARRAYBASE_H
#define CORE_ARRAYBASE_H

#include <aro/core/Weak.hpp>

namespace aro {

/* Private base class for Array and Array2D */
template <class T>
class ArrayBase extends public Object
{
   public:
      const vint length;
      
      virtual RObject clone();

      virtual RString toString();
      
      //virtual Ref<ArrayBase<T>> copyOf(vint size) = 0;
      //virtual Ref<ArrayBase<T>> copyOf(vint offset, vint size) = 0;
      //virtual void copy(vint offset, Ref<ArrayBase<T>> src, vint srcOffset, vint num) = 0;

      virtual T get(vint index);
      virtual void set(vint index, T item);
   
   protected:
      virtual T& item(vint index) final; // allows inserting item into Array
      virtual void resize(vint length) final; // used by Array<T>::readObject 
      virtual const T& item(vint index) const final; // retrieve item from Array
      
      virtual void copyItems(vint offset, Ref<ArrayBase<T>> src, vint srcOffset, vint num) final;
      
      ArrayBase(); // used by Ref<Array<T>> to create empty array
      ArrayBase(vint size); // ArrayBase primary constructor
      ArrayBase(Ref<ArrayBase<T>> arr); // ArrayBase copy constructor
      //template <class U>
      //ArrayBase(Ref<ArrayBase<U>> arr); // ArrayBase conversion constructor
      ArrayBase(std::initializer_list<T> elems); // ArrayBase sequence constructor
   
   private:
      // ArrayBase data of type T
      std::shared_ptr<T[]> data;
      
      void init(); // allocate required memory
      void checkIndex(vint index, vbool includeLength=false) const; // check for valid index
   
   template <class U, class V> friend class RefArrayBase;
   template <class U> friend class Array;
   template <class U> friend class Ref;
};

} /* namespace aro */

#endif /* CORE_ARRAYBASE_H */
