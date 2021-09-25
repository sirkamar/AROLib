#include <ctime>
#include <iostream>
#include <aro/core/System.h>
#include <aro/core/utils/Foreach.h>
#include <aro/cui/ConsoleGraphics.h>
#include <aro/io/BufferedInputStream.h>
#include <aro/io/BufferedOutputStream.h>

namespace aro {

aws::REventQueue System::queue = new aws::EventQueue();

// since the System streams in, err and out are character streams
// and we are using two bytes to represent 1 character, set the size
// of the buffer to be two so that each character will be auto-flushed
const io::RInputStream System::in = new io::BufferedInputStream(new SysIn(),2);

const io::RPrintStream System::err = 
      new io::PrintStream(new io::BufferedOutputStream(new SysOut(true),2), true);

const io::RPrintStream System::out =
      new io::PrintStream(new io::BufferedOutputStream(new SysOut(false),2), true);

System::System()
{
   
}

void System::executeGC()
{
   RThread rt = new SysGC();
   
   rt->start();
}

vlong System::currentTime()
{
   return (vlong)time(nullptr);
}

void System::exit(vint code)
{
   if(code == 0)
      std::exit(code);
   else
      std::terminate();
}

vbool System::isFinalizing()
{
   return Arm::isFinalizing();
}

void System::setIn(io::RInputStream is)
{
   const_cast<io::RInputStream&>(in) = is;
}

void System::setErr(io::RPrintStream es)
{
   const_cast<io::RPrintStream&>(err) = es;
}

void System::setOut(io::RPrintStream os)
{
   const_cast<io::RPrintStream&>(out) = os;
}

aws::REventQueue System::getEventQueue()
{
   return queue;
}

aws::RGraphics System::getDefaultGraphics(aws::event::RPaintEvent e)
{
   return new cui::ConsoleGraphics(e);
}

void System::SysGC::run()
{
   Arm::collect();
}

System::SysIn::SysIn()
{
   isTemp = false;
}

vint System::SysIn::read()
{
   if(isTemp)
   {
      isTemp = false;
      
      return (value >> 0) & 0xFF;
   }
   
   isTemp = true;
   
   value = std::wcin.get();
   
   return (value >> 8) & 0xFF;
}

vint System::SysIn::available()
{
   return 1;
}

System::SysOut::SysOut(vbool isErr)
   :out(isErr ? std::wcerr : std::wcout)
{
   isTemp = false;
}

void System::SysOut::write(vint byte)
{
   if(isTemp)
   {
      value += (byte << 0);
      
      out.put((vchar)value);
   }
   else
   {
      value = (byte << 8);
   }

   isTemp = !isTemp;
}

} /* namespace aro */
