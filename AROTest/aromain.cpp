#include <iostream>
#include <aro/core.hpp>
#include <aro/io/all.hpp>
#include <aro/util/all.hpp>
#include <aro/aws/all.hpp>
#include <aro/aws/event/all.hpp>
#include <aro/cui/border/TitleBorder.hpp>
#include <aro/cui/all.hpp>
#include "AROTester.hpp"
#include "SyncCounter.hpp"

//#pragma comment( lib, "arolib.dll" )

using namespace aro;

class Listener extends public Object implements public aws::event::ActionListener
{
   public:
      aws::RWindow owner;
      
      Listener(aws::RWindow win)
         :owner(win)
      {
         
      }
      
      void actionOccurred(aws::event::RActionEvent e) override
      {
         if(e->getCommand()->equals("Exit"))
            owner->dispose();
      }
};


void aromain(RArray<String> args)
{
   /* Print commandline arguments */
   //System::out->print("Program Args: ");
   //
   //for(RString s : args)
   //   System::out->print(s + " ");
   //
   //System::out->println("\n");
   
   /* Test Array and for_each */
   RArray<vint> intArr = { 1, 2, 3, 4, 5 };
   vint total = 0;
   
   for_each(intArr, [&total](vint num) {
        System::out->println("Total: " + String::valueOf(total) + ", Num: " + String::valueOf(num));
        total = total + num;
   });
   
   System::out->println("Final Total: " + String::valueOf(total));

   util::RVector<String> strVec = new util::Vector<String>(2);
   strVec->add("A String");
   strVec->add("Another");

   for_each(strVec, [](RObject obj) {
       System::out->println(obj->getType() + "[" + obj + "]");
   });

   
   /* Stream input and output with inheritance */
   //Ref<TestBase> rtb = new TestBase(15);
   //Ref<TestBase> rtd = new TestDerived(27, 91.4f);
   //
   //io::RByteArrayOutputStream rsos = new io::ByteArrayOutputStream();
   //io::RObjectOutputStream roos = new io::ObjectOutputStream(rsos);
   //
   //roos->writeObject(rtb);
   //roos->writeObject(rtd);
   //
   //roos->close();
   //
   //io::RObjectInputStream rois = new io::ObjectInputStream(new io::ByteArrayInputStream(rsos->toByteArray()));
   //
   //rtb = type_cast<TestBase>(rois->readObject());
   //rtd = type_cast<TestDerived>(rois->readObject());
   //
   //rois->close();
   //
   //System::out->println(rtb);
   //System::out->println();
   //System::out->println(rtd);
   //
   //System::in->read();
   

   //Testing Cloneable Interface
   //RString str = "A test value";

   //RString str2 = type_cast<String>(str->clone());

   //System::out->println("Orig: " + str + ", clone: " + str2);
   
   /*
   //Testing the Console User Interface API
   cui::RCSFrame win = new cui::CSFrame("Test Title");
   
   cui::RCSTextBox txt = new cui::CSTextBox(10);
   
   cui::RCSButton btn = new cui::CSButton("Exit");
   
   btn->addActionListener(new Listener(win));
   
   win->add(txt, aws::ZoneLayout::MIDDLE);
   
   win->add(btn, aws::ZoneLayout::BOTTOM);
   
   txt->setBorder(new cui::border::TitleBorder(txt->getBorder(), "Text Box"));
   
   //win->setSize(win->getPreferredSize());
   win->setSize(40,20);
   //win->pack();
   
   win->setLocation(1, 1);
   
   win->setVisible(true);
   
   //win->requestFocus();
   txt->requestFocus();
   */
   
   /*
   //Testing multi-threading synchronization
    RSyncCounter counter = new SyncCounter();

    RThread thread1 = new Runner(counter);
    RThread thread2 = new Runner(counter);

    thread1->start();
    thread2->start();

    thread1->join();
    thread2->join();

    System::out->println("Final count:" + String::valueOf(counter->getCount()));
    */
}

main_function = aromain;

//main_function = AROTester::start_main;
