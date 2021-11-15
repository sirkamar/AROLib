# AROLib
The Advanced References and Objects Library (AROLib) for C++


## Contents
- [What is ARO?](#what-is-aro)
- [Naming Convention](#naming-convention)
- [Namespaces](#namespaces)
- [Value Types and Reference Types](#value-types-and-reference-types)
- [Classes and Interfaces](#classes-and-interfaces)
- [Automatic Reference Management](#automatic-reference-management)
- [Reference Type Redefinition](#reference-type-redefinition)
- [The Null Reference](#the-null-reference)
- [The “this” Reference](#the-this-reference)
- [Array References](#array-references)
- [String References](#string-references)
- [Operators and References](#operators-and-references)
- [Collection Iteration](#collection-iteration)
- [Reference Type Checking and Casting](#reference-type-checking-and-casting)
- [The Weak Reference](#the-weak-reference)
- [The Main Function](#the-main-function)
- [Exception Handling](#exception-handling)
- [Data and Object Serialization](#data-and-object-serialization)


## What is ARO?
The Advanced References & Objects (ARO) Library for C++ is collection of classes (and supporting utilities) that form a class hierarchy having the class _Object_ as its root (i.e. the base class). The class _Object_ defines and implements behaviours (i.e. member functions) that are common to all objects. All classes in the ARO Library are derived either from class _Object_ or from other _Object_-derived classes. Similarly, programmers' client classes are required to be derived (i.e. inherit) from class _Object_ or one of its derived classes in order to effectively use the ARO Library.


## Naming Convention
The ARO Library uses a very easily understood naming convention that makes reading the code pretty simple. The names of all created types, such as classes and interfaces, begin with an uppercase letter, while the names of all variables, functions and namespaces begin with a lowercase letter. If the name of a class, interface, function, variable or namespace is composed of multiple words each of the subsequent words begin with an uppercase letter (e.g. ClassName, or variableName).

Constants defined within the ARO Library are declared using all uppercase letters, while macro-based operators use all lowercase letters. If the name of a constant or macro-based operator is composed of multiple words, each word is separated using an underscore (e.g. CONST_VAR_NAME, or macro_operator).


## Namespaces
All of the classes and functions in the ARO Library are categorized into groups, i.e. namespaces, to make them easier to identify and to import. Each namespace corresponds to a folder on the file system. A namespace folder contains the header files for all the classes and utilities categorized as belonging to that namespace. All users of the library are required to add **_“#include <aro/core.hpp>”_** in their header or source files which will automatically include all the class files and related utilities belonging to aro namespace (referred to as the ARO Core).

Header files in the library are typically named for the classes they contain or the utility they implement. Therefore, for example, one would use the statement **_“#include <aro/util/date.hpp>”_** to import the class `aro::util::Date` into a header or source file, or alternatively use the statement **_“#include <aro/util/all.hpp>”_** to import all the header files belonging to the `aro::util` namespace.

When a class is being used by other classes and functions that are not members of the same namespace, then the class name must be preceded by its namespace specifier (e.g. `aro::Object`) or the C++ **_using_** directive must be employed. For simplicity, this document will hereinafter assume that the **_using namespace aro_** directive is applied to all code snippets and examples.

The wiki for the repository provides a detailed description of each of the library's namespaces and their members.


## Value Types and Reference Types
Data types in the ARO Library fall into one of two categories: value types or reference types. The value types (i.e. `int`, `char`, `bool`, `long`, `short`, `float` and `double`) are copied when making function calls while reference types (see below) enable functions to directly access the original object, i.e. instances are passed by reference.


## Classes and Interfaces
Reference types in the ARO Library are divided along two separate hierarchies: the class hierarchy and the interface hierarchy, each implemented using the **class** and **interface** keywords, respectively. Each represents a different tool in the development process and are both integral to the library’s design.

A class (also called an “object class”) is an encapsulation of the properties and behaviours (i.e. data members and member functions) of a certain type of object. An interface, however, is a general specification of behaviours that a set of object classes must implement. All object classes in the library have class `Object` as their direct or indirect base class, while all interfaces inherit from the interface `Interface` directly or otherwise inherts (i.e. extends) one or more existing interfaces.

An interface typically includes only “pure virtual”, i.e. abstract, functions but may also include data members, however these should be static constants. Note that the default access type for all member functions and data members declared in an interface is public. As a general rule, all public and protected member functions of object classes and interfaces should be declared as virtual functions.

The general contract of the ARO Library is that all object classes **_must_** inherit (i.e. extend) a single object class but **_may_** inherit (i.e. implement) as many interfaces as necessary, or none at all.

```cpp
1.  #include <aro/core.hpp>
2.  
3.  using namespace aro;
4.  
5.  interface MyInterface : Interface
6.  {
7.    static const int CONST_VARIABLE = 25; // static constant data member
8.    
9.    virtual void requiredFunction() = 0; // pure virtual (abstract) function
10. };
11.
```

Interfaces <u>must</u> be applied to `Object`-derived classes. A class that is implementing an interface should use the syntax illustrated below.

```cpp
1.  #include “MyInterface.h”
2.  
3.  class CustomClass : public Object, public MyInterface
4.  {
5.    public:
6.      CustomClass(); // default constructor
7.      virtual void functionName(); // member function
9.      virtual void requiredFunction(); // from MyInterface
8.    
9.    private:
10.     int variableName; // data member
11. };
12. 
```

Additionally, all interfaces implicitly include access to the public member functions from class `Object`, as such they can be invoked directly from references to interface types.


## Automatic Reference Management
All objects created from the classes contained within or derived from the ARO Library are required to be dynamically instantiated using the C++ **new** operator. As such, the library provides an Automatic Reference Management (ARM) facility to simplify memory management and monitoring. The ARM facility defines the template `Ref` that is used to manage raw pointers from the **new** operator.

```cpp
Ref<Object> obj = new Object();
```

The above statement is read: “reference to an Object, obj, is assigned a new instance of class Object”. The template Ref represents a reference (i.e. a smart pointer) and allows access to the referenced object by dereferencing it using the C++ arrow operator, i.e. `->`. For the purpose of clarity, unless otherwise specified, all instances of the term “reference” or “references” within this document shall hereinafter be interpreted to mean an instance or instances, respectively, of the template `Ref`.

```cpp
Ref<String> str = obj->toString();
```

To prevent accidental incorrect usage of the raw pointer returned by the **new** operator, the ARO Library provides a wrapper template `rnew` to safely instantiate and return a reference to an instance of a given class. The required constructor parameters, if any, should be specified within parentheses as usual.

```cpp
// never do this, as it will cause a memory leak
new String(“Text”)->toUpperCase();

// Either do it like this
Ref<String> str = new String("Text");
str->toUpperCase();

// or use rnew to create a temporary reference
rnew<String>(“Text”)->toUpperCase();
```

The ARM facility also provides a garbage collector that is responsible for the automatic deallocation of memory when it determines that no active references to an object remains within an application. As such users of the ARO Library should <u>never</u> explicitly use the **delete** operator on any class object defined by or derived from a class in the library. The ARM facility is included as a part of the ARO Core.


## Reference Type Redefinition
The ARO Library has adopted a simplified convention for handling reference types by using the C++ **typedef** or **using** directive. For Example, given a class `CustomClass` the following convention is used:

```cpp
1.  #include “MyInterface.h”
2.  
3.  class CustomClass; // forward declaration
4.  typedef Ref<CustomClass> RCustomClass; // reference type
5.  
6.  class CustomClass : public Object, public MyInterface
7.  {
8.    public:
9.      CustomClass(); // default constructor
10.     CustomClass(RCustomClass rcc); // copy constructor
11.     // other constructors, member functions, and data members
12. };
```

As a result, declaring a reference to an instance of `CustomClass` may be simplified to:

```cpp	
RCustomClass rcc = new CustomClass();
```

The reference types for all object classes and interfaces defined within the library have been similarly redefined to conform to this convention, e.g. class `Object` references are declared as follows:

```cpp
RObject obj = new Object();
```

It is recommended that clients and users of the library also adopt this convention of reference type redefinition for use with their own object classes and interfaces.


## The Null Reference
For the purpose of initialization, the ARO Library has declared and defined a single constant reference, `nullref`, called the null reference. It is type convertible to all reference types and may be passed as a parameter to a function or used to clear a reference from pointing to an object. By default, all uninitialized references are equivalent to the null reference unless and until an object is assigned it. Any attempt to initialize a reference with a null pointer, or to dereference an uninitialized reference (or a reference that has been assigned the null reference) will cause a `NullException` to be thrown.

```cpp
RObject obj = new Object(); // declare and initialize obj

obj = nullref; // clear obj from pointing to the Object instance

if(obj == nullref)
    System::out->println(“obj is null”);
```

As the throwing of a `NullException` is typically a runtime error caused by a flaw in program design rather than as a normal expected possible error condition, it is only listed in the <u>@throws</u> section of function specifications in the wiki for the repository where it may be explicitly thrown by that function.


## The “this” Reference
The C++ “this” pointer is an implicit raw pointer to an instance of a class. To avoid situations where the pointer could be improperly used, the library defines a macro constant `thisref` that evaluates to a reference to the object pointed to by the “this” pointer. It may be used in all contexts where the “this” pointer may be legally used.

```cpp
System::out->println(thisref->toString());
```


## Array References
The ARO Library has defined the `Object`-derived template class `Array`, which represents a single dimension array. An `Array` class instance may be of any value type (e.g. `int`, `float`, etc.) or reference type (e.g. `Object`, `String`, etc.), or even an array of array references. The ARO Library has, however, also defined the template class `Array2D` to embody 2 Dimensional arrays (i.e. array of arrays). Note that, similarly to that done for value types, the type parameter for `Array` and `Array2D` instances should be the class or interface name, not the reference type name. For example:

```cpp
Ref<Array<Object>> objArr = new Array<Object>(5); // never use “Array<RObject>”
```

Similar to that done for other classes, `Ref<Array>` and `Ref<Array2D>` have also been type redefined as `RArray` and `RArray2D`, respectively. The following examples demonstrate how to declare references to arrays:

 ```cpp
// creates a 5-element array of ints
RArray<int> intArr = new Array<int>(5); 

// creates and initializes a 4-element array of chars
RArray<char> charArr = {‘A’, ‘B’, ‘C’, ‘D’};

// creates a 10-element array of Object references (i.e. Refs, not actual objects)
RArray<Object> objArr = new Array<Object>(10);

// creates a 3-row by 2-column (2 dimensional) array of long integers
RArray2D<long> lngArr = new Array2D<long>(3, 2);

// creates and initializes a mixed-length 2-dimensional array of Strings
RArray2D<String> strArr = { {“1”, “2”, “3”, “4”}, {“6”, “7”}, {“8”, “9”, “10”} };
```


## String References
For simplicity, the ARO Library has been customized to seamlessly interact with C++ native string literals by treating them, as much as is possible, as instances of class `String`. As a result, a native string literal can be used in any situation where a reference to a `String` object is required, such as being used as a function parameter. String literals, however, cannot be directly dereferenced and must first be assigned to a regular string reference variable in order to access any class `String` member functions.

```cpp
// initialize explicitly via call to constructor
RString str = new String(“a string text”);

// initialize implicitly via direct assignment
RString str2 = “another string”;
```

It should be noted that, performance wise, it is more efficient to initialize `String` references via direct assignment than via an explicit call to the constructor.


## Operators and References
For the purpose of convenience, the ARO Library has defined several operator functions that are designed to work in collaboration with references in general or with references to specific types. The following operator functions have been defined:

Operator/Operation | Description | Applies to Reference Types
------------------ | ----------- | --------------------------
= | Assignment | All
-> | Member Access | All
!= | Inequality | All
== | Equality | All
\+ | Concatenation | String
+= | Concatenate and Assign | String
[] | Subscript | Array
for(:) | Collection Iteration | Array and Iterable
type_cast | Type Casting | All
type_of | Type Checking | All
sync_lock | Multi-threading Synchronization | All

Note:<br/>
The equality and inequality operators do not actually compare the objects being pointed to by the references but rather the system memory address (i.e. pointer value) of the objects being referenced. As such the operators are used to determine whether or not two references are pointing to the same exact object. See also `Object::equals(RObject)`.


## Collection Iteration
For ease of use, the ARO Library has included support for the “range-based for” iteration to allow for simplified traversal over the elements of an `Array`, or an interable collection (i.e. any class that implements the `Iterable` interface), such as `ArrayList`, `LinkedList`, `Vector` or several other collection implementations within the ARO Utilities namespace. Please note: the “range-based for” iteration provides a <u>read-only</u> view of the elements within a collection.

```cpp
RArray<int> intArr = {1, 2, 3, 4, 5};
for(int n : intArr)
   System::out->print(n);

util::RVector<String> strVec = new util::Vector<String>(2);
strVec->add(“A String”);
strVec->add(“Another”);
for(RString str : strVec)
   System::out->println(str);
```


## Reference Type Checking and Casting
A reference variable may be directly assigned to another reference variable of the same type or a base type. However, a base type reference cannot be directly assigned to a reference of a derived type, nor can unrelated reference types be directly assigned to each other.

The ARO Library has provided the `type_cast` operator for explicitly converting between reference types. Reference type casting is performed along hierarchies. Attempting to cast a reference to an unrelated type causes a `CastException` to be thrown. As such the `type_of` operator is provided to check if a referenced object is of a specific type (or one of its derived types). Both operators require that the destination class or type name be given in angle brackets. 

```cpp
RString str = “a string text”; // create a String object

RObject obj = str; // direct assignment to base class reference

if(type_of<String>(obj))
   str = type_cast<String>(obj); // cast to derived class reference
```


## The Weak Reference
The template class `Weak` is provided by the ARO Core as a wrapper object that maintains a weak reference to an instance of a class. The reference is considered as “weak” because it is not monitored by the _ARM facility_. Therefore, the existence of a weak reference to an object will not prevent the automatic deletion of memory allocated to that object. This is useful especially as it relates to preventing the circular reference problem (where two or more objects each hold active references to the other and therefore prevents any of them from being finalized and deleted even where none of them is ever otherwise actively referenced again within the program). In such instances it is more appropriate to use weak references.

```cpp
RObject obj = new Object();

// RWeak<Object> wobj = new Weak<Object>(obj); // may use constructor
RWeak<Object> wobj = obj; // or may use direct reference assignment

obj = nullref; // clear the active reference

if((obj = wobj->get()) != nullref) // get() returns an active reference if not deleted
   System::out->println(obj->toString());
```


## The Main Function
The entry point to any program built using the ARO Library is the main function. The name of the main function can be any valid identifier, but it must have the following signature:

```cpp
void functName(RArray<String> args)
```

The “args” parameter is an array of strings containing all of the arguments, if any, specified on the command line when the program is executed. To designate a function as the program’s main function, use the following syntax:

```cpp
main_function = functName; // to designate a global function, or

main_function = ClassName::functName; // to designate a static class member function
```

<u>Please note:</u> it is a link-time error to specify a standard C++ `main` function within your application.


## Exception Handling
To handle exceptions that may be thrown within a function, users of the ARO Library should wrap statements, including function calls, that may throw exceptions within an exception handling block (as demonstrated below). This enables the programmer to handle exceptions that may be thrown so as to be able to identify the exception type, retrieve the exception message, and respond appropriately.

```cpp
1.  #include <aro/core.hpp>
2.  
3.  using namespace aro;
4.  
5.  void sysMain(RArray<String> args)
6.  {
8.     ex_try
9.     {
10.       // execute the body of your code here
11.       if(args->length == 0)
12.         ex_throw new StateException(“Args required”);
13.    }
14.    ex_catch
15.    {
16.       ex_handle(StateException)
17.       {
18.          ex_var->printException();
19.       }
20.       ex_handle(Exception)
21.       {
22.          System::err->println(ex_var->getMessage());
23.       }
24.       ex_finally
25.       {
26.          System::err->println(“Always executed”);
27.       }
28.    }
29.    ex_end	
30. }
31. 
32. main_function = sysMain;
33.
```

The `ex_throw` operator causes a reference to an exception object to be thrown. An unhandled exception will cause the program (or the currently executing thread) to immediately enter finalization and then terminate.

An `ex_catch` block does not automatically handle exceptions. An `ex_handle` block must be specified inside of the `ex_catch` block in order to handle a specific exception type (or one of its derived types) otherwise the exception will remain unhandled and will be passed out into to the next enclosing function block. The `ex_handle` operator takes as its parameter the exception class type name. It also implicitly declares a reference variable `ex_var` of the exception class type specified.

The `ex_finally` block doesn't handle exceptions. It is merely a mechanism to allow for carrying out of activities that must occur whether or not an exception occurs, or whether or not it was handled. If an exception wasn't handled prior to the `ex_finally` block it will be passed along after the `ex_finally` block has executed. The `ex_finally` block must be the last or the only block within the `ex_catch` block.

An `ex_rethrow` statement causes an exception being handled to be passed along. The `ex_rethrow` may only be used in an `ex_handle` block; it has no effect in the `ex_finally` block.

The `ex_end` statement marks the end of the exception handling block and must always be specified.


## Data and Object Streaming
The ARO Library provides support for data and object streaming via its Streaming API available in the Input/Output namespace (i.e. `aro::io`). The library provides built-in support for streaming of the native types `int`, `bool`, `char`, `long`, `short`, `float` and `double`. It also offers streaming capabilities for class objects via the `Streamable` template interface. By implementing the `Streamable` interface a class enables its instances to be written to an `ObjectOutputStream` and be read from an `ObjectInputStream`. The ARO Core classes `Array`, `Array2D`, `String`, and the wrapper classes `Int`, `Bool`, `Char`, `Long`, `Short`, `Float` and `Double` all implement the `Streamable` interface. An attempt to transmit an object for a class that does not implement the `Streamable` template interface will result in an `IOException` being thrown indicating that the object is not a valid `Streamable` instance.

```cpp
1.	#include <aro/core.hpp>
2.	#include <aro/io/all.hpp>
3.	
4.	using namespace aro;
5.	
6.	class StreamObject : public Object, public io::Streamable<StreamObject>
7.	{
8.	   public:
9.	      StreamObject(int id=0, RString str=“”, float bal=0.0f)
10.	      {
11.	         idNo=id;
12.	         name=str;
13.	         balance=bal;
14.	      }
15.	
16.	      //setters and getters
17.	
18.	      RString toString()
19.	      {
20.	         return “ID#:” + String::valueOf(idNo) +
21.	                “, Name:” + name + “, Balance:” + String::valueOf(balance);
22.	      }
23.	
24.	   protected:
25.	      void writeObject(io::RObjectOutputStream os)
26.	      {
27.	         os->writeInt(idNo);
28.	         os->writeObject(name);
29.	         os->writeFloat(balance);
30.	      }
31.	
32.	      void readObject(io::RObjectInputStream is)
33.	      {
34.	         idNo = is->readInt();
35.	         name = type_cast<String>(is->readObject());
36.	         balance = is->readFloat();
37.	      }
38.	
39.	   private:
40.	      int idNo;
41.	      RString name;
42.	      float balance;
43.	};
44.	
45.	void appStart(RArray<String> args)
46.	{
47.	   ex_try
48.	   {
49.	      Ref<StreamObject> rso = new StreamObject(11, “John Doe”, 125.7f);
50.	      System::out->println(rso); // calls the toString() member function
51.	
52.	      io::RFileOutputStream fos = new io::FileOutputStream(“filename.dat”);
53.	      io::RObjectOutputStream outs = new io::ObjectOutputStream(fos);
54.	   
55.	      outs->writeObject(rso);
56.	      outs->close(); // also closes the FileOutputStream
57.	
58.	      io::RFileInputStream fis = new io::FileInputStream(“filename.dat”);
59.	      io::RObjectInputStream ins = new io::ObjectInputStream(fis);
60.	
61.	      RObject obj = ins->readObject();
62.	      ins->close(); // also closes FileInputStream
63.	
64.	      System::out->println(obj); //calls obj->toString()
65.	
66.	      Ref<StreamObject> rso2 = type_cast<StreamObject>(obj);
67.	      System::out->println(rso2);
68.	   }
69.	   ex_catch
70.	   {
71.	      ex_handle(io::IOException)
72.	      {
73.	         ex_var->printException();
74.	      }
75.	   }
76.	   ex_end
77.	}
78.	
79.	main_function = appStart;
80.	
```

All classes that implement the `Streamable` template interface are required to define the `writeObject` and `readObject` member functions. It is recommended that these be made **protected** or **private**. Additionally, all `Streamable` classes must provide a no-argument constructor. If a class doesn’t wish for a no-argument constructor to be made available to clients, then it may declare it as protected or private, but it must then, of necessity, declare `io::Streamable<T>` as a friend, where `T` is the class name.

To provide object streaming version control, `Streamable` classes may provide a `getObjectVersion` member function that returns a version number value as a `long`. If a `getObjectVersion` member function is not provided the Streaming API assumes a default object version of `1L`. When deserializing (i.e. reading) an object from a stream, if the class’ object version is different from the one in the stream, an `IOException` is thrown indicating a `Streamable` object version mismatch.

The `Streamable` interface is a template (i.e. generic) and, when implemented by a class, it operates as a tag that registers that class type with the Streaming API. As such a class that implements the interface does not automatically pass on its streaming capabilities to derived classes. A derived class that wants to be streamable must also implement the `Streamable` interface for its class type and override both the `readObject` and `writeObject` member functions. The overridden member functions should either call its base class’ `readObject` and `writeObject` member functions as either the first line of code in both or the last line of code in both. Mixing the order of writing data to and reading data from a stream is a logic error and will most likely lead to data corruption and/or undefined behaviour.

```cpp
1.	#include "StreamObject.h"
2.	
3.	class StreamDerived : public StreamObject, public io::Streamable<StreamDerived>
4.	{
5.	   public:
6.	      StreamDerived(int id=0, RString str=“”, float bal=0.0f, RString type, long version)
7.	         :StreamObject(id, str, bal)
8.	      {
9.	         systemType = type;
10.	         installedVersion = version;
11.	      }
12.	      
13.	      // setters and getters
14.	      
15.	      RString toString()
16.	      {
17.	         return StreamObject::toString() + ", System Type: " + systemType
18.	            + ", Installed Version: " + String::valueOf(installedVersion);
19.	      }
20.	   
21.	   protected:
22.	      void writeObject(io::RObjectOutputStream os)
23.	      {
24.	         StreamObject::writeObject(os); // call to base class
25.	         os->writeObject(systemType);
26.	         os->writeLong(installedVersion);
27.	      }
28.	
29.	      void readObject(io::RObjectInputStream is)
30.	      {
31.	         StreamObject::readObject(is); // call to base class
32.	         systemType = type_cast<String>(is->readObject());
33.	         installedVersion = is->readLong();
34.	      }
35.	   
36.	   private:
37.	      RString systemType;
38.	      long installedVersion;
39.	}
40.	
```
