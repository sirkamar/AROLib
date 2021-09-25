#include <aro/core.h>
#include <aro/io/IOException.h>
#include <aro/io/PrintStream.h>
#include <aro/io/FileOutputStream.h>

namespace aro {

namespace io {

PrintStream::PrintStream(RString file)
   :FilterOutputStream(new FileOutputStream(file))
{
   closing = false;
   trouble = false;
   autoFlush = false;
}

PrintStream::PrintStream(ROutputStream os)
   :FilterOutputStream(os)
{
   if(out == nullref)
      ex_throw new NullException("Null output stream");
   
   closing = false;
   trouble = false;
   autoFlush = false;
}

PrintStream::PrintStream(ROutputStream os, vbool autoflush)
   :FilterOutputStream(os)
{
   if(out == nullref)
      ex_throw new NullException("Null output stream");
   
   closing = false;
   trouble = false;
   autoFlush = autoflush;
}

void PrintStream::newLine()
{
   sync_lock(thisref)   
   {
      ex_try
      {
         ensureOpen();
         
         write(('\n' >> 8) & 0xFF);
         write(('\n' >> 0) & 0xFF);
         
         if(autoFlush)
            out->flush();
      }
      ex_catch
      {
         ex_handle(IOException)
         {
            trouble = true;
         }
      }
      ex_end
   }
}

void PrintStream::ensureOpen()
{
   if(out == nullref)
      ex_throw new IOException("Stream closed");
}

void PrintStream::write(RString s)
{
   sync_lock(thisref)
   {
      ex_try
      {
         ensureOpen();
         
         vint len = s->length();
         
         if(buf == nullref || buf->length < len)
            buf = new Array<vchar>(len);
         
         s->getChars(0, len, buf, 0);
         
         for(vint n=0; n<len; n++)
         {
            out->write((buf[n] >> 8) & 0xFF);
            out->write((buf[n] >> 0) & 0xFF);
         }
         
         if(autoFlush && s->indexOf('\n') >= 0)
            out->flush();
      }
      ex_catch
      {
         ex_handle(IOException)
         {
            trouble = true;
         }
      }
      ex_end
   }
}

void PrintStream::write(RArray<vchar> ar)
{
   sync_lock(thisref)
   {
      ex_try
      {
         ensureOpen();
         
         vbool found = false;
         
         for(vchar c : ar)
         {
            out->write((c >> 8) & 0xFF);
            out->write((c >> 0) & 0xFF);
            
            if(c == '\n')
               found = true;
         }
         
         if(autoFlush && found)
            out->flush();
      }
      ex_catch
      {
         ex_handle(IOException)
         {
            trouble = true;
         }
      }
      ex_end
   }
}

void PrintStream::setError()
{
   trouble = true;
}

void PrintStream::clearError()
{
   trouble = false;
}

vbool PrintStream::checkError()
{
   if(out != nullref)
      flush();
   
   if(type_of<PrintStream>(out))
   {
      RPrintStream ps = type_cast<PrintStream>(out);
      return ps->checkError();
   }
   
   return trouble;
}

void PrintStream::write(vint byte)
{
   sync_lock(thisref)
   {
      ex_try
      {
         ensureOpen();
         
         out->write(byte);
         
         if(byte == '\n' && autoFlush)
            out->flush();
      }
      ex_catch
      {
         ex_handle(IOException)
         {
            trouble = true;
         }
      }
      ex_end
   }
}

void PrintStream::write(RArray<vint> bytes)
{
   write(bytes,0,bytes->length);
}

void PrintStream::write(RArray<vint> bytes, vint off, vint num)
{
   sync_lock(thisref)
   {
      ex_try
      {
         ensureOpen();
         
         out->write(bytes, off, num);
         
         if(autoFlush)
            out->flush();
      }
      ex_catch
      {
         ex_handle(IOException)
         {
            trouble = true;
         }
      }
      ex_end
   }
}

void PrintStream::print(char c)
{
   write(String::valueOf(c));
}

void PrintStream::print(vint i)
{
   write(String::valueOf(i));
}

void PrintStream::print(vbool b)
{
   write(b ? "true" : "false");
}

void PrintStream::print(vchar c)
{
   write(String::valueOf(c));
}

void PrintStream::print(vlong l)
{
   write(String::valueOf(l));
}

void PrintStream::print(vfloat f)
{
   write(String::valueOf(f));
}

void PrintStream::print(vdouble d)
{
   write(String::valueOf(d));
}

void PrintStream::print(RObject obj)
{
   write(String::valueOf(obj));
}

void PrintStream::print(RString str)
{
   if(str == nullref)
      str = "null";
   
   write(str);
}

void PrintStream::print(const char* ch)
{
   write(ch);
}

void PrintStream::print(const vchar* ch)
{
   write(ch);
}

void PrintStream::print(RArray<vchar> ar)
{
   write(ar);
}

void PrintStream::println()
{
   newLine();
}

void PrintStream::println(char c)
{
   sync_lock(thisref)
   {
      print(c);
      newLine();
   }
}

void PrintStream::println(vint i)
{
   sync_lock(thisref)
   {
      print(i);
      newLine();
   }
}

void PrintStream::println(vbool b)
{
   sync_lock(thisref)
   {
      print(b);
      newLine();
   }
}

void PrintStream::println(vchar c)
{
   sync_lock(thisref)
   {
      print(c);
      newLine();
   }
}

void PrintStream::println(vlong l)
{
   sync_lock(thisref)
   {
      print(l);
      newLine();
   }
}

void PrintStream::println(vfloat f)
{
   sync_lock(thisref)
   {
      print(f);
      newLine();
   }
}

void PrintStream::println(vdouble d)
{
   sync_lock(thisref)
   {
      print(d);
      newLine();
   }
}

void PrintStream::println(RObject obj)
{
   sync_lock(thisref)
   {
      print(obj);
      newLine();
   }
}

void PrintStream::println(RString str)
{
   sync_lock(thisref)
   {
      print(str);
      newLine();
   }
}

void PrintStream::println(const char* ch)
{
   sync_lock(thisref)
   {
      print(ch);
      newLine();
   }
}

void PrintStream::println(const vchar* ch)
{
   sync_lock(thisref)
   {
      print(ch);
      newLine();
   }
}

void PrintStream::println(RArray<vchar> ar)
{
   sync_lock(thisref)
   {
      print(ar);
      newLine();
   }
}

void PrintStream::flush()
{
   sync_lock(thisref)
   {
      ex_try
      {
         ensureOpen();
         out->flush();
      }
      ex_catch
      {
         ex_handle(IOException)
         {
            trouble = true;
         }
      }
      ex_end
   }
}

void PrintStream::close()
{
   sync_lock(thisref)
   {
      if(!closing)
      {
         closing = true;
         
         ex_try
         {
            out->flush();
            out->close();
         }
         ex_catch
         {
            ex_handle(IOException)
            {
               trouble = true;
            }
         }
         ex_end
         
         out = nullref;
      }
   }
}

} /* namespace io */

} /* namespace aro */
