#include <list>
#include <iostream>
#include <algorithm>
#include <aro/core/arm/Arm.hpp>
#include <aro/core/utils/Foreach.hpp>

namespace aro {

/* A wrapper for
  an object pointer */
struct ObjectInfo
{
   Base* obj;
   int refCount;
   bool finalized;
   //std::list<RefBase*> refs;

   ObjectInfo(Base* refPtr)
   {
      obj = refPtr;
      refCount = 1;
      finalized = false;
   }

   ObjectInfo() = default;
};

/* A custom linked-list for managing
 the instances of ObjectInfo */
class ArmList
{
   struct Node
   {
      ObjectInfo data;
      Node *next, *prev;

      Node(const ObjectInfo& info, Node* next, Node* prev)
          : data(info), next(next), prev(prev)
      {
         
      }
   };
   
   int count;
   Node* head;

   public:
      struct Itr
      {
         Node* cur;

         Itr(Node* n)
            :cur(n)
         {
            
         }

         Itr operator++()
         {
            cur = cur->next;
            
            return *this;
         }
         
         Itr operator--()
         {
            cur = cur->prev;
            
            return *this;
         }
         
         ObjectInfo& operator*()
         {
            return cur->data;
         }
         
         ObjectInfo* operator->() const
         {
            return &cur->data;
         }
         
         bool operator!=(const Itr& itr)
         {
            return cur != itr.cur;
         }
      };
      
      ArmList()
      {
         count = 0;

         head = new Node(ObjectInfo(nullptr), nullptr, nullptr);

         head->next = head->prev = head;
      }

      ~ArmList()
      {
         clear();
         
         delete head;
      }
      
      int size()
      {
         return count;
      }
      
      bool empty()
      {
         return count == 0;
      }
      
      void clear()
      {
         while(head->next != head)
         {
            Node* tmp = head->next;
            head->next = tmp->next;

            delete tmp;
         }
         
         head->prev = head;

         count = 0;
      }
      
      ObjectInfo* add(Base* refPtr)
      {
         Node* tmp = new Node(refPtr, head, head->prev);

         head->prev->next = tmp;
         head->prev = tmp;

         count++;

         return &tmp->data;
      }
	  
      ObjectInfo* get(Base* refPtr)
      {
         if(count > 0)
         {
            Node* cur = head->next;

            while(cur != head)
            {
               if(cur->data.obj == refPtr)
                  return &cur->data;
               
               cur = cur->next;
            }
         }
         
         return nullptr;
      }
      
      Itr erase(Itr i)
      {
         return erase(i, true);
      }
      
      Itr erase(Itr i, bool next)
      {
         if(i.cur != head)
         {
            Node* prev = i.cur->prev;
            
            Node* nxt = i.cur->next;
            
            prev->next = nxt;

            nxt->prev = prev;
            
            delete i.cur;
            
            count--;
            
            return next ? nxt : prev;
         }

         return head;
      }

      Itr rbegin()
      {
         return Itr(head->prev);
      }

      Itr begin()
      {
         return Itr(head->next);
      }

      Itr rend()
      {
         return Itr(head);
      }

      Itr end()
      {
         return rend();
      }
};

// Arm's list of Refs
ArmList* armList = nullptr;

// Arm's multithreading mutex
std::recursive_mutex* armMutex = nullptr;

// Dynamically allocating both the
// armList and armMutex has to be done
// as the order of static declarations is
// determined by the compiler/runtime and
// could potentially cause the ARM functions
// to fail due to an attempt to access memory
// locations that have not yet been initialized.
std::recursive_mutex& getArmMutex()
{
   if(armMutex == nullptr)
   {
      armList = new ArmList();

      armMutex = new std::recursive_mutex();
   }

   return *armMutex;
}

/* The ARM's Implementation */

bool Arm::finalizing = false;

// safely exit and
// prevent call to abort 
void Arm::safeExit()
{
   if(finalizing)
      Arm::collect();
   else
      Arm::finalize();
}

void Arm::collect()
{
   std::lock_guard<std::recursive_mutex> lock(getArmMutex());

   if(!armList->empty())
   {
      auto itr = armList->rbegin();
      // reverse iterate thru the list to collect child objects first
      while(itr != armList->rend())
      {
         Base* obj = itr->obj;
         
         if(itr->refCount <= 0 && !itr->finalized)
         {
            try
            {
               // flag object as finalized
               itr->finalized = true;
               
               // finalize object
               obj->finalize();
            }
            catch(...)
            {
               // Discard exception
            }
         }
         
         if(itr->refCount <= 0 && itr->finalized)
         {
            try
            {
               // delete finalized object
               delete obj;
            }
            catch(...)
            {
               
            }
            
            // remove from the armList
            itr = armList->erase(itr, false);
         }
         else
         {
            --itr;
         }
      }
   }
}

bool Arm::isFinalizing()
{
   return finalizing;
}

int Arm::getInstanceCount()
{
   if(armList == nullptr)
      return 0;
   
   return armList->size();
}

void Arm::run()
{
   while(getInstanceCount() > 0)
   {
      collect();
      
      Sleep(500);
   }
   
   //collect();
}

void Arm::finalize()
{
   // use anonymous block to ensure the
   // mutex is released before deleted
   if(true)
   {
      // if currently locked, wait and acquire lock on mutex
      std::lock_guard<std::recursive_mutex> lock(getArmMutex());
      
      finalizing = true; // flag as finalizing
      
      if(!armList->empty()) // references exist
      {
         // mark all references for finalization
         for(auto& info : *armList)
         {
            info.refCount = 0;
            
            //std::list<RefBase*>& sv = info.refs;
            //// clear all references to the object, i.e. set their ptr to null.
            //std::for_each(sv.begin(), sv.end(), [](RefBase* ref) {ref->clear();});
         }
         
         collect(); // recover memory
         
         // should not happen
         if(!armList->empty())
            armList->clear();
      }
   }

   delete armMutex; 
   delete armList;

   armMutex = nullptr;
   armList = nullptr;
}

void Arm::add(Base* refPtr, RefBase* ref)
{
   if(finalizing)
      return;
   
   std::lock_guard<std::recursive_mutex> lock(getArmMutex());
   
   bool firstObj = false;
   
   if(armList->empty())
   {
      firstObj = true; // flag as first Object

      atexit(finalize); // run finalizer on exit
      
      set_terminate(safeExit); // avoid sudden failure
   }
   
   auto gci = armList->get(refPtr);
   
   if(gci)
      gci->refCount++;
   else
      gci = armList->add(refPtr);
   
   //gci->refs.push_back(ref);

   if(firstObj) // if first run
   {
      std::thread t(run); // start ARM thread

      t.detach(); // maintain thread
   }
}

void Arm::remove(Base* refPtr, RefBase* ref)
{
   //std::thread t(removeImpl, refPtr, ref);
   
   //t.detach(); // run without handle
   
   removeImpl(refPtr, ref);
}

void Arm::removeImpl(Base* refPtr, RefBase* ref)
{
   if(finalizing)
      return;
   
   std::lock_guard<std::recursive_mutex> lock(getArmMutex());
   
   auto gci = armList->get(refPtr);
   
   if(gci)
   {
      gci->refCount--;
      
      //std::list<RefBase*>& sv = gci->refs;
      //auto var = sv.begin();
      //while(var != sv.end())
      //{
      //   if((*var) == ref)
      //   {
      //      sv.erase(var);
      //      break;
      //   }
      //   
      //   var++;
      //}
   }
}

bool Arm::isAlive(Base* refPtr)
{
   std::lock_guard<std::recursive_mutex> lock(getArmMutex());
   
   if(armList->get(refPtr))
      return true;
   
   return false;
}

} /* namespace aro */
