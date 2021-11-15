#ifndef CORE_EXCEPTION_H
#define CORE_EXCEPTION_H

#include <aro/core/String.hpp>

namespace aro {

namespace io {
class PrintStream;
class PrintWriter;

typedef Ref<PrintStream> RPrintStream;
typedef Ref<PrintWriter> RPrintWriter;
}

class Exception;
typedef Ref<Exception> RException;

class Exception : public Object
{
   public:
      Exception();
      Exception(RString msg);
      
      virtual RString toString();
      virtual RString getMessage();
      
      virtual void printException();
      virtual void printException(io::RPrintStream s);
      virtual void printException(io::RPrintWriter s);
      
      virtual RException setTrace(RString file, vint line) final;
   
   private:
      RString message, trace;

};

} /* namespace aro */

#endif /* CORE_EXCEPTION_H */
