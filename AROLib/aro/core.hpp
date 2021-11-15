/********************************************************************
*           Advanced References & Objects (ARO) Library             *
*********************************************************************
* Includes all of the core classes & utilities clients need to use  *
* the library. All non-core class files should include <aro/core.hpp> *
* into their source or header files.                                *
********************************************************************/
#ifndef ARO_CORE_H
#define ARO_CORE_H

//#include <aro/core/Interface.hpp>            // Interface interface declaration
//#include <aro/core/Object.hpp>               // Object class declaration
//#include <aro/core/Null.hpp>                 // Null class declaration
//#include <aro/core/Weak.hpp>                 // Weak class declaration
//#include <aro/core/Array.hpp>                // Array class declaration
//#include <aro/core/Array2D.hpp>              // Array2D class declaration
#include <aro/core/String.hpp>               // String class declaration

//#include <aro/core/Math.hpp>                 // Math class declaration
#include <aro/core/Number.hpp>               // Number class declaration
#include <aro/core/System.hpp>               // System class declaration

//#include <aro/core/Iterable.hpp>             // Iterable interface declaration
//#include <aro/core/Runnable.hpp>             // Runnable interface declaration
//#include <aro/core/Comparable.hpp>           // Comparable interface declaration

/* Wrapper Classes - Type A: One class for each built-in type used */
#include <aro/core/Int.hpp>                  // Int wrapper class declaration
#include <aro/core/Bool.hpp>                 // Bool wrapper class declaration
#include <aro/core/Char.hpp>                 // Char wrapper class declaration
#include <aro/core/Long.hpp>                 // Long wrapper class declaration
#include <aro/core/Float.hpp>                // Float wrapper class declaration
#include <aro/core/Short.hpp>                // Short wrapper class declaration
#include <aro/core/Double.hpp>               // Double wrapper class declaration

/* Wrapper Classes - Type B: One class for each built-in type group used */
//#include <aro/core/Boolean.hpp>              // Boolean wrapper class declaration
//#include <aro/core/Decimal.hpp>              // Decimal wrapper class declaration
//#include <aro/core/Integer.hpp>              // Integer wrapper class declaration
//#include <aro/core/Character.hpp>            // Character wrapper class declaration

#include <aro/core/Thread.hpp>               // Thread class declaration
#include <aro/core/StringBuffer.hpp>         // StringBuffer class declaration
#include <aro/core/StringBuilder.hpp>        // StringBuilder class declaration

//#include <aro/core/Exception.hpp>            // Exception class declaration
//#include <aro/core/CastException.hpp>        // CastException class declaration
//#include <aro/core/NullException.hpp>        // NullException class declaration
//#include <aro/core/IndexException.hpp>       // IndexException class declaration
//#include <aro/core/ArgumentException.hpp>    // ArgumentException class declaration
#include <aro/core/StateException.hpp>       // StateException class declaration
#include <aro/core/ThreadException.hpp>      // ThreadException class declaration
#include <aro/core/UnsupportedException.hpp> // UnsupportedException class declaration

//#include <aro/core/utils/Utils.hpp>          // common utilities macro definitions
#include <aro/core/utils/Foreach.hpp>        // for_each utility macro definition

#endif /* ARO_CORE_H */
