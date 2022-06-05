#ifndef CORE_UTILS_H
#define CORE_UTILS_H

#include <aro/io/impl/Streamable-impl.hpp>


namespace aro {

template <class T, class ...Args>
inline Ref<T> rnew(Args&&... args)
{
   return new T(std::forward<Args>(args)...);
}


template <class T>
inline Ref<T> thisRef(T* const ptr)
{
   return Ref<T>(ptr);
}


 /* Used for type casting between of reference types
    usage: RString var = type_cast<String>(obj); */

template <class T>
inline Ref<T> type_cast(Object*const obj)
{
   return type_cast<T>(Ref<Object>(obj))
}

template <class T>
inline Ref<T> type_cast(const RObject& obj)
{
   if(obj.ref != nullptr)
   {
      T* tPtr = dynamic_cast<T*>(obj.ref);

      if(tPtr == nullptr)
      {
         Ref<String> type = typeid(T).name();
         int space = type->lastIndexOf(" ") + 1;
         if(space>0) type = type->substring(space);
         throw RException(new CastException(obj->getType() +
            " cannot be converted to " + type));
      }

      return tPtr;
   }
   
   return Ref<T>();
}

/* Checks if an object is an "instance of" or
 is "derived from" a specified class given by T.
 usage example:
 if(type_of<String>(obj))
    return type_cast<String>(obj); */
template <class T>
bool type_of(const RObject& obj)
{
   if(dynamic_cast<T*>(obj.ref))
      return true;
   
   return false;
}

template <class T>
bool type_of(Object*const obj)
{
   return type_of(Ref<Object>(obj))
}


/* Type definition of the ARO Libray's entry point */
typedef void(*MainFunction)(RArray<String> args);

extern MainFunction mainFunction;


/* An exception referenece wrapper
* that is used for the safe and proper
* handling and debugging of exceptions. */
struct ExceptionWrapper final
{
   const RException& operator=(const RException& ex);
   
   ExceptionWrapper(RString file, vint line);
   
   RString fileName;
   vint lineNo;
};

/* Used to implement the ex_finally facilty */
class __FinalEx__ : public Exception {};

} /* namespace aro */

//#define ARO_TYPE_OF(TYPE, OBJ) aro::typeOf<TYPE>(OBJ)
//#define type_of ARO_TYPE_OF // usage: if(type_of(String, obj)) return type_cast(String, obj);
//
///* General purpose type casting (references and primitives) */
//#define ARO_TYPE_CAST(TYPE, OBJ)  aro::typeCast<TYPE>(OBJ)
//#define type_cast ARO_TYPE_CAST // usage: type_cast<toTypeName>(srcObject)

/* Used as a type safe reference in place of "this" */
#define aro_this_ref aro::thisRef(this)
#define thisref aro_this_ref // usage: if(obj==thisref)return true;


/* Used to create a multi-threading safe sychronized block */
#define ARO_SYNC_LOCK(MUTEX)    if(aro::SyncLock _aro_mutex_ = MUTEX)
#define sync_lock ARO_SYNC_LOCK // usage: sync_lock(obj){ statements; }


/* Used to implement the ARO Library's exception handling facility */
#define ARO_EX_TRY          try{
#define ARO_EX_THROW        throw aro::ExceptionWrapper(__FILE__,__LINE__) =
#define ARO_EX_CATCH        /*throw RException(new __FinalEx__());*/         \
                              }catch(RException __aro_ex){                   \
                              bool ex_hndle=false,ex_final=false;            \
                              if(type_of<__FinalEx__>(__aro_ex))             \
                              ex_hndle=true;if(ex_hndle)
#define ARO_EX_HANDLE(T)    }else if(!ex_final && type_of<T>(__aro_ex)){     \
                              Ref<T> ex_var = type_cast<T>(__aro_ex);        \
                              ex_hndle = true;
#define ARO_EX_RETHROW      if(!ex_final)throw __aro_ex
#define ARO_EX_FINALLY      }if(!ex_final){ex_final=true;
#define ARO_EX_END          if(!ex_hndle)throw __aro_ex;}

#define ex_try       ARO_EX_TRY		// syntax: ex_try {
#define ex_throw     ARO_EX_THROW	// syntax: ex_throw new Exception();
#define ex_catch     ARO_EX_CATCH	// syntax: } ex_catch {
#define ex_handle    ARO_EX_HANDLE	// syntax: ex_handle(ArgumentException){ ex_var->printMessage(); }
#define ex_rethrow   ARO_EX_RETHROW	// syntax: ex_handle(Exception){ ex_rethrow; }
#define ex_finally   ARO_EX_FINALLY	// syntax: ex_finally{ System::out->println("always executed"); }
#define ex_end       ARO_EX_END		// syntax: } ex_end

//NOTE: An ex_catch block does not automatically handle exceptions.
//      An ex_handle block must be specified inside of the ex_catch
//      block to handle a specific exception type (or a base type)
//      otherwise the unhandled exception will be passed along
//      out unto to the next enclosing function block.
//      
//      Also ex_finally doesn't handle exceptions. It's merely a
//      mechanism to allow for carrying out activities that must
//      occur regardless of whether or not an exception occurs,
//      or whether or not it was handled. If an excepton wasn't
//      handled prior to the ex_finally block it will be passed
//      along after the ex_finally block is executed.
//      
//      The ex_finally block must be the last or the only block
//      within the ex_catch block.
//      
//      The ex_rethrow statement causes an exception to be passed
//      along after being caught. An ex_rethrow may be used in an
//      ex_handle block only; it has no effect in the ex_finally
//      block.
//      
//      The ex_end statement indicates the end of the ex_catch
//      block and must always be specified.


/* Used to specify the function that is the program's main function */
#define ARO_MAIN_FUNCTION   struct MF { static const MF mf;   \
                             MF(aro::MainFunction m)          \
                             {aro::mainFunction=m;}           \
                             }; const MF MF::mf

/* usage: main_function = functName; */
#define main_function      ARO_MAIN_FUNCTION 

/* The C++ standard program entry point */
int main(int argc, char** argv);

#endif /* CORE_UTILS_H */
