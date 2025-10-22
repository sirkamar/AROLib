#pragma once

#include <aro/core.hpp>

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

class TestBase : public Object, public io::Streamable<TestBase>
{
    public:
        TestBase(vint val);

        virtual RString toString();

        virtual void readObject(io::RObjectInputStream in);

        virtual void writeObject(io::RObjectOutputStream out);

    protected:
        TestBase() = default;

    private:
        vint value = 0;

    friend interface io::Streamable<TestBase>;
};

class TestDerived : public TestBase, public io::Streamable<TestDerived>
{
    public:
        TestDerived(vint val, vfloat amt);

        virtual RString toString();

        virtual void readObject(io::RObjectInputStream in);

        virtual void writeObject(io::RObjectOutputStream out);

    private:
        vfloat amount = 0.0f;

        TestDerived() = default;

    friend interface io::Streamable<TestDerived>;
};

