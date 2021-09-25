#include <aro/core.h>
#include <aro/io/FileWriter.h>
#include <aro/io/PrintWriter.h>
#include <aro/io/IOException.h>
#include <aro/io/BufferedWriter.h>
#include <aro/io/OutputStreamWriter.h>

namespace aro {

namespace io {

PrintWriter::PrintWriter(RWriter out)
   :PrintWriter(out, false)
{
   //trouble = false;
   //thisref->out = out;
   //lineSeparator = "\n";
   //thisref->autoFlush = false;
}

PrintWriter::PrintWriter(RString fileName)
   :PrintWriter(new BufferedWriter(new FileWriter(fileName)))
{
   //trouble = false;
   //lineSeparator = "\n";
   //thisref->autoFlush = false;
   //thisref->out = type_cast<Writer>(lock);
}

PrintWriter::PrintWriter(ROutputStream out)
   :PrintWriter(out, false)
{
   //trouble = false;
   //lineSeparator = "\n";
   //thisref->autoFlush = false;
   //thisref->out = type_cast<Writer>(lock);
   //
   //if(type_of<PrintStream>(out))
   //   psOut = type_cast<PrintStream>(out);
}

PrintWriter::PrintWriter(RWriter out, vbool autoFlush)
   :Writer(out)
{
   trouble = false;
   thisref->out = out;
   lineSeparator = "\n";
   thisref->autoFlush = autoFlush;
}

PrintWriter::PrintWriter(ROutputStream out, vbool autoFlush)
   :PrintWriter(new BufferedWriter(new OutputStreamWriter(out)), autoFlush)
{
   //trouble = false;
   //lineSeparator = "\n";
   //thisref->autoFlush = autoFlush;
   //thisref->out = type_cast<Writer>(lock);
   
   if(type_of<PrintStream>(out))
      psOut = type_cast<PrintStream>(out);
}

void PrintWriter::ensureOpen()
{
   if(out == nullref)
      ex_throw new IOException("stream closed");
}

void PrintWriter::flush()
{
   ex_try
   {
      sync_lock(lock)
      {
         ensureOpen();

         out->flush();
      }
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

void PrintWriter::close()
{
   ex_try
   {
      sync_lock(lock)
      {
         if(out == nullref)
            return;

         out->close();
         out = nullref;
      }
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

vbool PrintWriter::checkError()
{
   if(out != nullref)
      flush();
   
   if(type_of<PrintWriter>(out))
   {
      RPrintWriter pw = type_cast<PrintWriter>(out);
      return pw->checkError();
   }
   else if(psOut != nullref)
   {
      return psOut->checkError();
   }

   return trouble;
}

void PrintWriter::setError()
{
   trouble = true;
}

void PrintWriter::clearError()
{
   trouble = false;
}

void PrintWriter::write(vint c)
{
   ex_try
   {
      sync_lock(lock)
      {
         ensureOpen();

         out->write(c);
      }
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

void PrintWriter::write(RArray<vchar> cbuf, vint off, vint num)
{
   ex_try
   {
      sync_lock(lock)
      {
         ensureOpen();

         out->write(cbuf, off, num);
      }
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

void PrintWriter::write(RArray<vchar> cbuf)
{
   write(cbuf, 0, cbuf->length);
}

void PrintWriter::write(RString s, vint off, vint num)
{
   ex_try
   {
      sync_lock(lock)
      {
         ensureOpen();

         out->write(s, off, num);
      }
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

void PrintWriter::write(RString s)
{
   write(s, 0, s->length());
}

void PrintWriter::newLine()
{
   ex_try
   {
      sync_lock(lock)
      {
         ensureOpen();
         
         out->write(lineSeparator);

         if(autoFlush)
            out->flush();
      }
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

void PrintWriter::print(char c)
{
   write(String::valueOf(c));
}

void PrintWriter::print(vint i)
{
   write(String::valueOf(i));
}

void PrintWriter::print(vbool b)
{
   write(b ? "true" : "false");
}

void PrintWriter::print(vchar c)
{
   write(String::valueOf(c));
}

void PrintWriter::print(vlong l)
{
   write(String::valueOf(l));
}

void PrintWriter::print(vfloat f)
{
   write(String::valueOf(f));
}

void PrintWriter::print(vdouble d)
{
   write(String::valueOf(d));
}

void PrintWriter::print(RObject obj)
{
   write(String::valueOf(obj));
}

void PrintWriter::print(RString str)
{
   if(str == nullref)
      str = "null";
   
   write(str);
}

void PrintWriter::print(const char* ch)
{
   write(ch);
}

void PrintWriter::print(const vchar* ch)
{
   write(ch);
}

void PrintWriter::print(RArray<vchar> ar)
{
   write(ar);
}

void PrintWriter::println()
{
   newLine();
}

void PrintWriter::println(char c)
{
   sync_lock(lock)
   {
      print(c);
      newLine();
   }
}

void PrintWriter::println(vint i)
{
   sync_lock(lock)
   {
      print(i);
      newLine();
   }
}

void PrintWriter::println(vbool b)
{
   sync_lock(lock)
   {
      print(b);
      newLine();
   }
}

void PrintWriter::println(vchar c)
{
   sync_lock(lock)
   {
      print(c);
      newLine();
   }
}

void PrintWriter::println(vlong l)
{
   sync_lock(lock)
   {
      print(l);
      newLine();
   }
}

void PrintWriter::println(vfloat f)
{
   sync_lock(lock)
   {
      print(f);
      newLine();
   }
}

void PrintWriter::println(vdouble d)
{
   sync_lock(lock)
   {
      print(d);
      newLine();
   }
}

void PrintWriter::println(RObject obj)
{
   RString s = String::valueOf(obj);

   sync_lock(lock)
   {
      print(s);
      newLine();
   }
}

void PrintWriter::println(RString str)
{
   sync_lock(lock)
   {
      print(str);
      newLine();
   }
}

void PrintWriter::println(const char* ch)
{
   sync_lock(lock)
   {
      print(ch);
      newLine();
   }
}

void PrintWriter::println(const vchar* ch)
{
   sync_lock(lock)
   {
      print(ch);
      newLine();
   }
}

void PrintWriter::println(RArray<vchar> ar)
{
   sync_lock(lock)
   {
      print(ar);
      newLine();
   }
}

} /* namespace io */

} /* namespace aro */
