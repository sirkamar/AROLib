#ifndef CORE_BASE_H
#define CORE_BASE_H

#include <aro/core/arm/SyncLock.hpp>

namespace aro {

typedef Ref<Object> RObject;
typedef Ref<String> RString;

/* Class Base is a common root for both the Object and Interface
   branches of the ARO Library class hierarchy. It exists as a
   virtual base class that ties both branches of the hierarchy
   together by enabling dynamic binding of Interface classes to
   Object classes. As such all class Object member functions are
   still accessible through a reference to an Interface-derived
   class. This class MUST ONLY be directly inherited, virtually,
   by class Object and interface Interface. */
class Base
{
   public:
      /** Returns a hash code value for the object. In general,
      * the hashCode function must consistently return the same
      * integer, provided no information used in the equals()
      * comparisons on the object is modified. If two objects
      * are equal according to the equals(RObject) function,
      * then calling the hashCode function on each of the two 
      * the two objects must produce the same integer result. */
      virtual vint hashCode() = 0;
      
      /** Creates and returns a copy of this object. The precise
      * meaning of "copy" may depend on the class of the object.
      * To perform a clone operation, a class must implement
      * the Cloneable interface, or an exception will be
      * thrown. See API document for full details. */
      virtual RObject clone() = 0;
      
      /** Returns the name of the object's class as a string.
       * This function is expected to return the string
       * "Object" for an instance of class Object. */
      virtual RString getType() = 0;
      
      /** Returns a string representation of the object. In
       * general, the toString function returns a string
       * that "textually represents" the object. The
       * string should be a concise but informative
       * representation that is easy for a person
       * to understand. Most derived classes should
       * implement this member function. */
      virtual RString toString() = 0;
      
      /** Indicates whether this object's value is "equal to" the value of
       * another. Most classes should override this function to test for
       * equality between objects of that class type. For Example: two
       * separate String objects with an equal value, s1->equals(s2)
       * should return true. See API document for more info. */
      virtual vbool equals(RObject obj) = 0;
      
      /** Notifies all waiting threads that the
       * object is about to be available. Must
       * be called while in a sync_lock. */
      virtual void notifyAll() = 0;

      /** Notifies a single waiting thread that
       * the object is about to be available. 
       * Must be called in a sync_lock. */
      virtual void notify() = 0;

      /** Releases synchronized lock on the object
       * and waits for notifcation that the
       * lock may be reacquired. Must be
       * caled in a sync_lock. */
      virtual void wait() = 0;
   
   protected:
       /** Guarateed to be called prior to object deletion
       * by the Grabage Collector to enable objects to
       * carry out final clean up and release system
       * resources that they may hold, e.g. files. */
      virtual void finalize() = 0;
      
      /** Restrict the C++ default
      * copy constructor. Derived
      * classes should define a
      * constructor that accepts
      * a Ref<T> parameter, where
      * T is the class type name */
      Base(const Base&) = default;

      /** The Base destructor is automatically called by the
       * Garbage Collector if it determines that there are
       * no references to the object remaining within the
       * application. If a derived class requires that
       * final clean up and release of held resources
       * be carried out before an object is deleted
       * (such as the closing of opened files) an
       * override of the finalize member function
       * should be provided. A member destructor
       * function should NOT be provided. */
      virtual ~Base() = default;
      
      /** The Base constructor. It is called
      * automatically upon the creation of
      * an instance of a derived class. */
      Base() = default;
   
   private:
      /** Restrict the C++ default copy operator. */
      Base& operator=(const Base&) = delete;
   
   friend class Arm;
   friend class Object;
   friend interface Interface;
   template <class T>
   friend interface Cloneable;
};

} /* namespace aro*/

#endif /* CORE_BASE_H */
