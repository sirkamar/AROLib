#ifndef IO_PRINTWRITER_H
#define IO_PRINTWRITER_H

#include <aro/io/Writer.hpp>
#include <aro/io/PrintStream.hpp>

namespace aro {

namespace io {

class PrintWriter;
typedef Ref<PrintWriter> RPrintWriter;

class PrintWriter : public Writer
{
   public:
      PrintWriter(RWriter out);
      PrintWriter(RString fileName);
      PrintWriter(ROutputStream out);
      PrintWriter(RWriter out, vbool autoFlush);
      PrintWriter(ROutputStream out, vbool autoFlush);

      virtual void flush();
      virtual void close();
      virtual vbool checkError();

      virtual void write(vint c);
      virtual void write(RString str);
      virtual void write(RArray<vchar> cbuf);
      virtual void write(RString str, vint off, vint num);
      virtual void write(RArray<vchar> cbuf, vint off, vint num);

      virtual void print(vint i);
      virtual void print(char c);
      virtual void print(vbool b);
      virtual void print(vchar c);
      virtual void print(vlong l);
      virtual void print(vfloat f);
      virtual void print(vdouble d);
      virtual void print(RString s);
      virtual void print(RObject obj);
      virtual void print(const char* ch);
      virtual void print(const vchar* ch);
      virtual void print(RArray<vchar> ar);

      virtual void println();
      virtual void println(char c);
      virtual void println(vint i);
      virtual void println(vbool b);
      virtual void println(vchar c);
      virtual void println(vlong l);
      virtual void println(vfloat f);
      virtual void println(vdouble d);
      virtual void println(RString s);
      virtual void println(RObject obj);
      virtual void println(const char* ch);
      virtual void println(const vchar* ch);
      virtual void println(RArray<vchar> ar);

   protected:
      RWriter out;

      virtual void setError();
      virtual void clearError();

   private:
      vbool trouble;
      vbool autoFlush;
      RPrintStream psOut;
      RString lineSeparator;

      void newLine();
      void ensureOpen();
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_PRINTWRITER_H */
