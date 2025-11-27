#ifndef CORE_SYSTEM_H
#define CORE_SYSTEM_H

#include <aro/core/Thread.hpp>
#include <aro/aws/Graphics.hpp>
#include <aro/io/InputStream.hpp>
#include <aro/io/PrintStream.hpp>
#include <aro/aws/EventQueue.hpp>
#include <aro/aws/event/PaintEvent.hpp>

#ifdef ARO_GRAPHICS_CLASS

#ifndef ARO_GRAPHICS_FILE
#error "The ARO_""GRAPHICS_""FILE for the ARO_""GRAPHICS_""CLASS must be defined"
#endif

#include "ARO_GRAPHICS_FILE"

#endif

namespace aro {

class System final extends public Object
{
   public:
      static const io::RInputStream in; // System standad input stream
      static const io::RPrintStream err; // System standard error stream
      static const io::RPrintStream out; // System standard output stream
      
      static void executeGC(); // initiate garbage collection routine
      static vlong currentTime(); // seconds since 1970-01-01 00:00:00
      static void exit(vint code); // terminate application safely
      
      static vbool isFinalizing(); // is system finalization running
      static void setIn(io::RInputStream in); // redirects input to another source
      static void setErr(io::RPrintStream os); // redirects error to another stream
      static void setOut(io::RPrintStream os); // redirects output to another stream
      
      static aws::REventQueue getEventQueue(); // returns the system event queue
      
      static aws::RGraphics getGraphics(aws::event::RPaintEvent e) // get graphics implementation
      {
         #ifndef ARO_GRAPHICS_CLASS
            return getDefaultGraphics(e);
         #else
            return new ARO_GRAPHICS_CLASS(e);
         #endif
      }
   
   private:
      System(); // prevent instantiation
      
      class SysGC; // Private GC Thread
      class SysIn; // System character input stream
      class SysOut; // System character output streams
      
      static aws::REventQueue queue; // the system event queue

      static aws::RGraphics getDefaultGraphics(aws::event::RPaintEvent e);
};

// Private GC Thread
class System::SysGC : public Thread
{
   public:
      virtual void run();
};

// System character input stream
class System::SysIn : public io::InputStream
{
   public:
      SysIn();
      vint read();
      vint available();
   
   private:
      vchar value;
      vbool isTemp;
};

// System character output streams
class System::SysOut : public io::OutputStream
{
   public:
      SysOut(vbool err);
      void write(vint byte);
   
   private:
      vint value;
      vbool isTemp;
      std::wostream& out;
};

} /* namespace aro */

#endif /* CORE_SYSTEM_H */
