//#include <stdafx.hpp>
//#include <iostream>
#include <process.h>
#include <windows.h>
#include <DbgHelp.h>
#include <aro/core/utils/Foreach.hpp>
#include <aro/io/PrintWriter.hpp>

#pragma comment( lib, "dbghelp.lib" )

namespace aro {

Exception::Exception()
   :Exception("Exception occurred")
{
   
}

Exception::Exception(RString msg)
{
   message = msg;
   
   // generate stack trace
   char* stackTrace[MAXSHORT];
   HANDLE process = GetCurrentProcess();
   SymInitialize(process, NULL, TRUE);
   USHORT frames = CaptureStackBackTrace(1, MAXSHORT, (PVOID*)stackTrace, nullptr);
   
   DWORD displacement;
   const int maxNameLength = 1024;
   SYMBOL_INFO *symbol = (SYMBOL_INFO *)malloc(sizeof(SYMBOL_INFO) + (maxNameLength - 1) * sizeof(TCHAR));;
   symbol->MaxNameLen = maxNameLength;
   symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

   IMAGEHLP_LINE64 *line = (IMAGEHLP_LINE64 *)malloc(sizeof(IMAGEHLP_LINE64));
   line->SizeOfStruct = sizeof(IMAGEHLP_LINE64);

   RString newLine = "\n";
   RStringBuilder sb = new StringBuilder(newLine);
   for(vint n=0; n<frames-(USHORT)12; n++)
   {
      SymFromAddr(process, (DWORD64)stackTrace[n], NULL, symbol);
      
      RString symName = symbol->Name;
      if(symName->endsWith("Exception") || symName->indexOf("Ref<") >= 0)
         continue;
      
      sb->append("at ")->append(symName);
      
      if(SymGetLineFromAddr64(process, (DWORD64)stackTrace[n], &displacement, line))
      {
         RString fileName = line->FileName;
         
         sb->append("(")->append(fileName->substring(fileName->lastIndexOf('\\') + 1))
             ->append(":")->append(String::valueOf((vlong)line->LineNumber))->append(")");
      }
      
      sb->append(newLine);
   }

   free(line);
   free(symbol);

   trace = sb->toString();
}

RString Exception::toString()
{
   if(message == nullref)
      return getType();
   
   return getType() + ": " + message;
}

RString Exception::getMessage()
{
   return message;
}

void Exception::printException()
{
   printException(System::err);
}

void Exception::printException(io::RPrintStream s)
{
   sync_lock(s)
   {
      s->println(toString() + trace);
   }
}

void Exception::printException(io::RPrintWriter s)
{
   sync_lock(s)
   {
      s->println(toString() + trace);
   }
}

RException Exception::setTrace(RString file, vint line)
{
   if(trace == nullref)
      trace = "\nFile: " + file + ", Line:" + String::valueOf(line);
   
   return thisref;
}

} /* namespace aro */
