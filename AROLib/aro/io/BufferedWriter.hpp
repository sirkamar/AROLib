#ifndef IO_BUFFEREDWRITER_H
#define IO_BUFFEREDWRITER_H

#include <aro/io/Writer.hpp>

namespace aro {

namespace io {

class BufferedWriter;
typedef Ref<BufferedWriter> RBufferedWriter;

class BufferedWriter :  public Writer
{
   public:
      BufferedWriter(RWriter out);
      BufferedWriter(RWriter out, vint size);

      virtual void write(vint c);
      virtual void write(RString str, vint off, vint num);
      virtual void write(RArray<vchar> cbuf, vint off, vint num);

      virtual void newLine();
      virtual void flush();
      virtual void close();

   private:
      RWriter out;
      RArray<vchar> cb;
      vint nChars, nextChar;
      RString lineSeparator;
      static vint defaultCharBufferSize;

      void ensureOpen();
      void flushBuffer();
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_BUFFEREDWRITER_H */
