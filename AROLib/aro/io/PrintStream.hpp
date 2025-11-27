#ifndef IO_PRINTSTREAM_H
#define IO_PRINTSTREAM_H

#include <aro/io/FilterOutputStream.hpp>

namespace aro {

namespace io {

class PrintStream;
typedef Ref<PrintStream> RPrintStream;

class PrintStream extends public FilterOutputStream
{
   public:
      PrintStream(RString file);
      PrintStream(ROutputStream os);
      PrintStream(ROutputStream os, vbool autoFlush);
      
      void write(vint byte);
      void write(RArray<vint> bytes);
      void write(RArray<vint> bytes,vint off,vint num);
      
      void flush();
      void close();
      
      void print(vint i);
      void print(char c);
      void print(vbool b);
      void print(vchar c);
      void print(vlong l);
      void print(vfloat f);
      void print(vdouble d);
      void print(RObject obj);
      void print(RString str);
      void print(const char* ch);
      void print(const vchar* ch);
      void print(RArray<vchar> ar);
      
      void println();
      void println(vint i);
      void println(char c);
      void println(vbool b);
      void println(vchar c);
      void println(vlong l);
      void println(vfloat f);
      void println(vdouble d);
      void println(RObject obj);
      void println(RString str);
      void println(const char* ch);
      void println(const vchar* ch);
      void println(RArray<vchar> ar);
      
      virtual vbool checkError();
   
   protected:
      virtual void setError();
      virtual void clearError();
   
   private:
      vbool closing;
      vbool trouble;
      vbool autoFlush;
      RArray<vchar> buf;
      
      void newLine();
      void ensureOpen();
      void write(RString);
      void write(RArray<vchar>);
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_PRINTSTREAM_H */
