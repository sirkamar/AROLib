#include <iostream>
#include <aro/core.hpp>
#include <aro/io/all.hpp>
#include <aro/util/all.hpp>
#include <aro/aws/all.hpp>
#include <aro/aws/event/all.hpp>
#include <aro/cui/border/TitleBorder.hpp>
#include <aro/cui/all.hpp>
#include "AROTester.hpp"

//#pragma comment( lib, "arolib.dll" )

using namespace aro;

class Listener : public Object, public aws::event::ActionListener
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
}

main_function = aromain;

//main_function = AROTester::start_main;
