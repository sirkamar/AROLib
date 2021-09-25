#include <aro/core.h>
#include <aro/io/StringWriter.h>

namespace aro {

namespace io {

StringsWriter::StringsWriter()
{
   buf = new StringBuffer();
   lock = buf;
}

StringsWriter::StringsWriter(vint size)
{
   if(size < 0)
      ex_throw new ArgumentException("Negative buffer size");

   buf = new StringBuffer(size);
   lock = buf;
}

void StringsWriter::write(vint c)
{
   buf->append((vchar)c);
}

void StringsWriter::write(RArray<vchar> cbuf, vint off, vint len)
{
   if((off < 0) || (off > cbuf->length) || (len < 0) ||
     ((off + len) > cbuf->length) || ((off + len) < 0))
      ex_throw new IndexException();
   
   else if (len == 0)
      return;
   
   buf->append(cbuf, off, len);
}

void StringsWriter::write(RString str)
{

   buf->append(str);
}

void StringsWriter::write(RString str, vint off, vint len)
{
   buf->append(str->substring(off, off+len));
}

RString StringsWriter::toString()
{
   return buf->toString();
}

RStringBuffer StringsWriter::getBuffer()
{
   return buf;
}

void StringsWriter::flush()
{

}

void StringsWriter::close()
{

}

} /* namespace io */

} /* namespace aro */
