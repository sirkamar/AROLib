#pragma once

#include <aro/core.h>

using namespace aro;

class AROTester : public Thread
{
   public:
      AROTester();
      
      void printArray();
      
      virtual void run();
      
      static void start_main(RArray<String> args);
   
   protected:
      virtual void finalize();
   
   private:
      RArray<String> strArr;
};
