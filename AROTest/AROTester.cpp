#include "AROTester.h"

AROTester::AROTester()
   :strArr({"Andrew", "Matthew", "Mark", "Luke", "John"})
{
   System::out->println("Class AROTester constructed...");
}

void AROTester::printArray()
{
   //for_each(RString str, strArr)
   //   System::out->print(str + " ");
   for(RString str : strArr)
      System::out->print(str + " ");
   
   System::out->println();
}

void AROTester::run()
{
   ex_try
   {
      printArray();
   }
   ex_catch
   {
      ex_handle(Exception)
      {
         ex_var->printException();
      }
   }
   ex_end
}

void AROTester::finalize()
{
   System::out->println("Class AROTester finalized...");
}

void AROTester::start_main(RArray<String> args)
{
   System::out->println("begin AROTester::start_main");
   
   Ref<AROTester> test = rnew<AROTester>();
   
   test->start();
   
   System::out->println("AROTester started");
   
   test->join();
   
   System::out->println("end AROTester::start_main");
}
