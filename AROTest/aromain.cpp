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

class TestBase : public Object, public io::Streamable<TestBase>
{
   public:
      TestBase(vint val)
      {
         value = val;
      }
      
      void readObject(io::RObjectInputStream in)
      {
         value = in->readInt();
      }
      
      void writeObject(io::RObjectOutputStream out)
      {
         out->writeInt(value);
      }
      
      RString toString()
      {
         return "Value: " + String::valueOf(value);
      }

   private:
      vint value = 0;
      
   protected:
      TestBase() = default;

      friend interface io::Streamable<TestBase>;
};

class TestDerived : public TestBase, public io::Streamable<TestDerived>
{
   public:
      TestDerived(vint val, vfloat amt)
         :TestBase(val)
      {
         amount = amt;
      }
      
      void readObject(io::RObjectInputStream in)
      {
         TestBase::readObject(in);
         
         amount = in->readFloat();
      }
      
      void writeObject(io::RObjectOutputStream out)
      {
         TestBase::writeObject(out);
         
         out->writeFloat(amount);
      }
      
      RString toString()
      {
         return TestBase::toString() + ", Amount: " + String::valueOf(amount);
      }
   
   private:
      vfloat amount = 0.0f;
      
      TestDerived() = default;
   
   friend interface io::Streamable<TestDerived>;
};


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


// Used in testing range based for with non-generics
class StringList : public util::ArrayList<String>
{
   public:
      using util::ArrayList<String>::ArrayList;
};

using RStringList = Ref<StringList>;



void aromain(RArray<String> args)
{
   /* Print commandline arguments */
   //System::out->print("Program Args: ");
   //
   //for(RString s : args)
   //   System::out->print(s + " ");
   //
   //System::out->println("\n");
   
   
   /* Testing basic String processing */
   //RString str = "This is a test string";
   //RString str2 = str->substring(0, 14);
   //System::out->println("original:" + str);
   //System::out->println("Second:" + str2);
   //System::out->println("Index Of 'a':" + String::valueOf(str->indexOf('a')));
   //System::out->println("Copy of str2: " + rnew<String>(str2));
   //System::out->println(str + ". Let's have some fun");
   //System::in->read();
   
   
   /* Thread Join Testing */
   //System::out->println("started aromain");
   //
   //Ref<AROTester> tstr = rnew AROTester();
   //
   //AROTester::start_main({});
   //
   //tstr->start();
   //
   //tstr->join();
   //
   //System::out->println("end of aromain");
   //
   //Thread::sleep(35000LL);
   //
   //System::out->println("\n\nPress Enter Key to exit");
   //
   //System::in->read();
   
   
   /* Array2D with initializer list */
   //RArray2D<String> r2s = {{"A", "B"}, {"Z", "Y", "X"}};
   //RArray2D<vint> r2n = {{1,2}, {3,4}};
   //
   //for_each(r2n, [](RArray<vint> r1n)
   //{
   //   for_each(r1n, [](vint vn)
   //   {
   //      System::out->println(vn);
   //   });
   //});
   //
   //for(RArray<String> r1n : r2s)
   //{
   //   for(RString vn : r1n)
   //   {
   //      System::out->println(vn);
   //   }
   //}
   //
   //System::in->read();
   

   //Testing String input and output streams
   //RInputStream ris = new StringInputStream("A Test String");
   //
   //ROutputStream ros = new StringOutputStream(13);
   //
   //vint byte = -1;
   //
   //while((byte = ris->read()) != -1)
   //{
   //   ros->write(byte);
   //}
   //
   //ris->close();
   //ros->close();
   //
   //System::out->println(ros);
   
   
   /* Testing stream input and outut via file */
   //RString strFile = "C:\\Users\\sirka\\AROTest.txt";
   //RString str = "Test String", str1;
   //vint vi = 15000000;
   //RArray<double> rad = {0.25, 2.74, 3.61};
   //RArray2D<String> ra2ds = { { "A", "B" }, { "Z", "Y", "X" } };
   //
   //io::RObjectOutputStream roos = new io::ObjectOutputStream(new io::FileOutputStream(strFile));
   //
   //roos->writeObject(str);
   //roos->writeObject(str1);
   //roos->writeInt(vi);
   //roos->writeObject(rad);
   //roos->writeObject(ra2ds);
   //
   //roos->close();
   //
   //io::RObjectInputStream rois = new io::ObjectInputStream(new io::FileInputStream(strFile));
   //
   //RObject str2 = rois->readObject();
   //RObject nobj = rois->readObject();
   //vint vi2 = rois->readInt();
   //RArray<vdouble> rad2 = type_cast<Array<vdouble>>(rois->readObject());
   //RArray2D<String> ras2 = type_cast<Array2D<String>>(rois->readObject());
   //
   //rois->close();
   //
   //System::out->println(str2);
   //System::out->println(nobj);
   //System::out->println(vi2);
   //
   //for(vdouble vd : rad2)
   //   System::out->println(vd);
   //
   //for(RArray<String> ras : ras2)
   //{
   //   for(RString str : ras)
   //      System::out->println(str);
   //}
   //
   //System::out->println();
   //
   //System::in->read();
   
   
   /* Stream input and output with inheritance */
   Ref<TestBase> rtb = new TestBase(15);
   Ref<TestBase> rtd = new TestDerived(27, 91.4f);
   
   io::RByteArrayOutputStream rsos = new io::ByteArrayOutputStream();
   io::RObjectOutputStream roos = new io::ObjectOutputStream(rsos);
   
   roos->writeObject(rtb);
   roos->writeObject(rtd);
   
   roos->close();
   
   io::RObjectInputStream rois = new io::ObjectInputStream(new io::ByteArrayInputStream(rsos->toByteArray()));
   
   rtb = type_cast<TestBase>(rois->readObject());
   rtd = type_cast<TestDerived>(rois->readObject());
   
   rois->close();
   
   System::out->println(rtb);
   System::out->println();
   System::out->println(rtd);
   
   System::in->read();
   
   
   /* Calculator Program - Testing Stream Input via System::in */
   //char choice;
   //float result = 0.0;
   //float num1 = 0.0, num2 = 0.0;
   //
   //RBufferedReader dat = new BufferedReader(new InputStreamReader(System::in),1);
   //
   //System::out->println("Welcome to Calculator");
   //
   //do
   //{
   //   System::out->println();
   //   System::out->println("Menu Options\n------------");
   //   System::out->println("E-Enter Values\nA-Add\nS-Subtract");
   //   System::out->println("M-Multiply\nD-Divide\nX-Exit");
   //   System::out->print(": ");
   //   
   //   RString tmp = dat->readLine();
   //   choice = tmp->length() > 0 ? tmp->charAt(0) : -1;
   //   
   //   System::out->println();
   //   
   //   switch(choice)
   //   {
   //      case 'E':
   //      case 'e':
   //      {
   //         vbool trouble;
   //         
   //         do
   //         {
   //            trouble = false;
   //            
   //            ex_try
   //            {
   //               System::out->print("Enter value 1: ");
   //               num1 = Float::parse(dat->readLine());
   //               System::out->print("Enter value 2: ");
   //               num2 = Float::parse(dat->readLine());
   //            }
   //            ex_catch
   //            {
   //               ex_type(ArgumentException)
   //               {
   //                  ex_var->printException();
   //                  
   //                  System::out->println("Try again!!!\n");
   //                  
   //                  trouble = true;
   //               }
   //            }
   //            ex_end
   //         }
   //         while(trouble);
   //         
   //         break;
   //      }
   //      
   //      case 'A':
   //      case 'a':
   //         result = num1 + num2;
   //         System::out->println("Add: " + String::valueOf(result));
   //         break;
   //      
   //      case 'S':
   //      case 's':
   //         result = num1 - num2;
   //         System::out->println("Subtract: " + String::valueOf(result));
   //         break;
   //      
   //      case 'M':
   //      case 'm':
   //         result = num1 * num2;
   //         System::out->println("Multiply: " + String::valueOf(result));
   //         break;
   //      
   //      case 'D':
   //      case 'd':
   //         if(num2 == 0.0)
   //            System::err->println("Divide: undefined");
   //         else
   //         {
   //            result = num1 / num2;
   //            System::out->println("Divide: " + String::valueOf(result));
   //         }
   //         break;
   //      
   //      case 'X':
   //      case 'x':
   //         System::out->println("Goodbye!!!");
   //         break;
   //      
   //      default:
   //         System::err->println("Invalid option selected.");
   //   }
   //   
   //   if(choice != 'E' && choice != 'e')
   //      Thread::sleep(3000L);
   //}
   //while(choice != 'X' && choice != 'x');
   
   
   //Using "range-based for" iteration with an Array object
   //RArray<vint> ar = {5, 25, 4, 179, 16, 9};
   //
   //System::out->print("array values: ");
   //
   //for(vint n : ar)
   //{
   //   System::out->print(n);
   //   System::out->print(" ");
   //}
   //
   //System::out->println();
   
   
   //Using "range-based for" iteration with an Iterator object
   //util::RLinkedList<String> ras = rnew<util::LinkedList<String>>();
   //ras->add("Orange");
   //ras->add("Purple");
   //ras->add("Magenta");
   //ras->add("Chartruese");
   //
   //for(RString el : ras->iterator())
   //   System::out->print(el + " ");
   //
   //System::out->println();
   //
   //System::in->read();
   

   //Testing for_each with Array object
   //RArray<String> rsa = new Array<String>(3);
   //
   //RArray<Object> roa = rsa;
   //
   //roa[0] = "Item 0";
   //roa[1] = "Elem 1";
   //roa[2] = "Entry 2";
   //
   //for_each(rsa , [](RString rs)
   //{
   //   System::out->println(rs);
   //});
   
   
   //Testing for_each with a non-generic Collection object
   //RStringList rsl = new StringList();
   //rsl->add("String 1");
   //rsl->add("String 2");
   //
   //for(RString s : rsl)
   //{
   //   System::out->println(s);
   //}
   //
   //for_each(rsl, [](RString s)
   //{
   //   System::out->println(s);
   //});
   //
   //System::in->read();


   //Testing for_each with a Collection object
   //util::RArrayList<String> rals = new util::ArrayList<String>(5);
   //util::RList<String> lst = rals;
   //lst->add("item 1");
   //lst->add("value 2");
   //lst->add("element 3");
   //
   //System::out->print("list values: ");
   //
   //for(RString str : lst)
   //{
   //   System::out->print(str + " ");
   //}
   //
   //System::out->println();
   //
   //for_each(lst, [](RString x)
   //{
   //   System::out->print(x+" ");
   //});
   //
   //System::out->println();
   //
   //System::in->read();
   
   
   /* Test Arrays of Derived to Base assignment */
   //RArray<String> arrStr = {"The ", "other ", "one."};
   //RArray<Object> arrObj = arrStr;
   //
   //for(RObject obj : arrObj)
   //   System::out->print(obj);
   //
   //System::out->println();
   //
   //RArray2D<String> a2dStr = { {"Sometimes ","the ","answer "}, {"is ", "very simple.\n"} };
   //RArray2D<Object> a2dObj = a2dStr;
   //
   //for(auto oa : a2dObj)
   //   for(auto o : oa)
   //      System::out->print(o);
   //
   //System::in->read();
   
   
   /* Testing Collections of Derived to Base assignment */
   //util::RList<String> rls;
   //util::RList<Object> rlo = rls; //not valid
   

   //Testing null reference with strings
   //RObject o1 = nullref, o2;
   //RString s1 = "test", s2;
   //
   //s1 += nullref;
   //System::out->println(o1 + " raw1");
   //System::out->println(o1 + s1);
   //System::out->println("raw1 " + o1);
   //System::out->println(s1 + o1);
   //System::out->println("raw1 " + s1);
   //System::out->println(s1 + " raw1");
   //System::out->println(s1 + s2);
   

   //Testing weak reference handling
   //RObject obj = new String("StrObj");
   //
   //RWeak<Object> rwo = obj;
   //
   //RObject tmp;
   //
   //if((tmp = rwo->get()) != nullref)
   //{
   //   System::out->println(tmp);
   //   tmp = nullref;
   //}
   //
   //obj = nullref;
   //
   //Thread::sleep(5000L);
   //
   //if((tmp = rwo->get()) != nullref)
   //{
   //   System::out->println(tmp);
   //   tmp = nullref;
   //}
   //
   //Thread::sleep(4000L);
   

   //Testing Cloneable Interface
   //RString str = "A test value";

   //RString str2 = type_cast<String>(str->clone());

   //System::out->println("Orig: " + str + ", clone: " + str2);
   

   //Testing the Console User Interface API
   //cui::RCSFrame win = new cui::CSFrame("Test Title");
   //
   //cui::RCSTextBox txt = new cui::CSTextBox(10);
   //
   //cui::RCSButton btn = new cui::CSButton("Exit");
   //
   //btn->addActionListener(new Listener(win));
   //
   //win->add(txt, aws::ZoneLayout::MIDDLE);
   //
   //win->add(btn, aws::ZoneLayout::BOTTOM);
   //
   //txt->setBorder(new cui::border::TitleBorder(txt->getBorder(), "Text Box"));
   //
   ////win->setSize(win->getPreferredSize());
   //win->setSize(40,20);
   ////win->pack();
   //
   //win->setLocation(1, 1);
   //
   //win->setVisible(true);
   //
   ////win->requestFocus();
   //txt->requestFocus();
}

main_function = aromain;

//main_function = AROTester::start_main;
