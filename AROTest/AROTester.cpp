#include "AROTester.hpp"

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

TestBase::TestBase(vint val)
{
    value = val;
}

RString TestBase::toString()
{
    return "Value: " + String::valueOf(value);
}

void TestBase::readObject(io::RObjectInputStream in)
{
    value = in->readInt();
}

void TestBase::writeObject(io::RObjectOutputStream out)
{
    out->writeInt(value);
}

TestDerived::TestDerived(vint val, vfloat amt)
    :TestBase(val)
{
    amount = amt;
}

RString TestDerived::toString()
{
    return TestBase::toString() + ", Amount: " + String::valueOf(amount);
}

void TestDerived::readObject(io::RObjectInputStream in)
{
    TestBase::readObject(in);

    amount = in->readFloat();
}

void TestDerived::writeObject(io::RObjectOutputStream out)
{
    TestBase::writeObject(out);

    out->writeFloat(amount);
}
