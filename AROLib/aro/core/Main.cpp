#include <exception>
#include <aro/core/System.hpp>
#include <aro/core/Array2D-impl.hpp>
#include <aro/core/StateException.hpp>
#include <aro/core/utils/ThreadLibrary.hpp>

namespace aro {

ExceptionWrapper::ExceptionWrapper(RString file, vint line)
{
   fileName = file->substring(file->lastIndexOf("\\"));
   
   lineNo = line;
}

const RException& ExceptionWrapper::operator=(const RException& ex)
{
   ex->setTrace(fileName, lineNo);
   
   return ex;
}

MainFunction mainFunction = nullptr;

class MainThread final : public Thread
{
   public:
      RArray<String> args;
      
      MainThread(RArray<String> strArr)
         :Thread("Thread-main")
      {
         args = strArr;
      }
      
      vbool getError()
      {
         return error;
      }

      void run()
      {
         if(mainFunction == nullptr)
            ex_throw new StateException("A main function is "
               "required.\n\nUsage: main_function = functName;");
         
         mainFunction(args);
      }
};

} /* namespace aro */

using namespace aro;

int main(int argc, char **argv)
{
   RArray<String> args = new Array<String>(argc-1);
   
   for(vint n=0; n<args->length; n++)
      args[n] = argv[n+1];
   
   Ref<MainThread> mainThread = new MainThread(args);
   
   // start main thread and wait for it to finish
   mainThread->start();
   
   //mainThread->join();

   ThreadLibrary::waitForAllThreads();
   
   if(mainThread->getError())
   {
      System::err->println("\nPress enter key to exit");
      
      System::in->read();
      
      return EXIT_FAILURE;
   }
   
   return EXIT_SUCCESS;
}
