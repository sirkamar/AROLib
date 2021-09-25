#ifndef IO_BUFFEREDREADER_H
#define IO_BUFFEREDREADER_H 

#include <aro/io/Reader.h>

namespace aro {

namespace io {

class BufferedReader;
typedef Ref<BufferedReader> RBufferedReader;

class BufferedReader :  public Reader
{
   public:
      BufferedReader(RReader in);
      BufferedReader(RReader in, vint size);

      virtual vint read();
      virtual vint read(RArray<vchar> cbuf, vint off, vint len);

      virtual void mark(vint readAheadLimit);
      virtual vbool markSupported();
      virtual RString readLine();
      virtual vlong skip(vlong n);
      virtual void reset();
      virtual vbool ready();
      virtual void close();

   protected:
      virtual RString readLine(vbool ignoreLF);
   
   private:
      RReader in;
      vbool skipLF;
      vint markedChar;
      RArray<vchar> cb;
      vbool markedSkipLF;
      vint readAheadLimit;
      vint nChars, nextChar;

      static const vint UNMARKED;
      static const vint INVALIDATED;
      
      static vint defaultCharBufferSize;
      static vint defaultExpectedLineLength;

      void fill(); // throws IOException
      void ensureOpen(); //throws IOException
      vint read1(RArray<vchar> cbuf, vint off, vint len); //throws IOException
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_BUFFEREDREADER_H */
