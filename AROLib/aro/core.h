/********************************************************************
*           Advanced References & Objects (ARO) Library             *
*********************************************************************
* Includes all of the core classes & utilities clients need to use  *
* the library. All non-core class files should include <aro/core.h> *
* into their source or header files.                                *
********************************************************************/
#ifndef ARO_CORE_H
#define ARO_CORE_H

//#include <aro/core/Interface.h>            // Interface interface declaration
//#include <aro/core/Object.h>               // Object class declaration
//#include <aro/core/Null.h>                 // Null class declaration
//#include <aro/core/Weak.h>                 // Weak class declaration
//#include <aro/core/Array.h>                // Array class declaration
//#include <aro/core/Array2D.h>              // Array2D class declaration
#include <aro/core/String.h>               // String class declaration

//#include <aro/core/Math.h>                 // Math class declaration
#include <aro/core/Number.h>               // Number class declaration
#include <aro/core/System.h>               // System class declaration

//#include <aro/core/Iterable.h>             // Iterable interface declaration
//#include <aro/core/Runnable.h>             // Runnable interface declaration
//#include <aro/core/Comparable.h>           // Comparable interface declaration

/* Wrapper Classes - Type A: One class for each built-in type used */
#include <aro/core/Int.h>                  // Int wrapper class declaration
#include <aro/core/Bool.h>                 // Bool wrapper class declaration
#include <aro/core/Char.h>                 // Char wrapper class declaration
#include <aro/core/Long.h>                 // Long wrapper class declaration
#include <aro/core/Float.h>                // Float wrapper class declaration
#include <aro/core/Short.h>                // Short wrapper class declaration
#include <aro/core/Double.h>               // Double wrapper class declaration

/* Wrapper Classes - Type B: One class for each built-in type group used */
//#include <aro/core/Boolean.h>              // Boolean wrapper class declaration
//#include <aro/core/Decimal.h>              // Decimal wrapper class declaration
//#include <aro/core/Integer.h>              // Integer wrapper class declaration
//#include <aro/core/Character.h>            // Character wrapper class declaration

#include <aro/core/Thread.h>               // Thread class declaration
#include <aro/core/StringBuffer.h>         // StringBuffer class declaration
#include <aro/core/StringBuilder.h>        // StringBuilder class declaration

//#include <aro/core/Exception.h>            // Exception class declaration
//#include <aro/core/CastException.h>        // CastException class declaration
//#include <aro/core/NullException.h>        // NullException class declaration
//#include <aro/core/IndexException.h>       // IndexException class declaration
//#include <aro/core/ArgumentException.h>    // ArgumentException class declaration
#include <aro/core/StateException.h>       // StateException class declaration
#include <aro/core/ThreadException.h>      // ThreadException class declaration
#include <aro/core/UnsupportedException.h> // UnsupportedException class declaration

//#include <aro/core/utils/Utils.h>          // common utilities macro definitions
#include <aro/core/utils/Foreach.h>        // for_each utility macro definition

#endif /* ARO_CORE_H */
