/******************************************************************************
*               AUTOMATIC REFERENCE MANAGEMENT (ARM) PACKAGE                  *
*******************************************************************************
* Name        | class Arm                                                     *
*             |                                                               *
* Author      | Kamar Morris                                                  *
*             |                                                               *
* Version     | 1.0                                                           *
*             |                                                               *
* Description | The Arm class represents a Memory Collector for clients'      *
*             | dynamically allocated Objects. Arm is designed to work        *
*             | in collaboration with the various Reference types to perform  *
*             | automatic memory monitoring and cleanup. The Arm tracks       *
*             | all of the References within an application and will delete,  *
*             | automatically, the memory allocated to an Object as soon as   *
*             | there are no more References that are pointing to it.         *
*             |                                                               *
*             | See API documention for complete details.                     *
*             |                                                               *
*******************************************************************************
*                             REVISION HISTORY                                *
*******************************************************************************
* Date        Author         Version   Description                            *
* ----------  ---------      -------   -----------                            *
* YYYY/MM/DD  X. XXXXXX        X.X                                            *
*                                                                             *
* 2008/03/15  K. Morris        1.0     Created class.                         *
*                                                                             *
******************************************************************************/
#ifndef ARO_ARM_ARM_H
#define ARO_ARM_ARM_H

#include <aro/core/arm/Cfg.hpp>

namespace aro {

class Base;
class RefBase;

/* The class Arm implements
   an automated garbage collector
   for memory dynamically allocated
   to instances of class Object or Object-
   derived classes. Arm is designed to work
   along with the template class Ref<T> to
   carry out memory monitoring and cleanup. */
class Arm
{
   public:
      static void collect();
	  
      static bool isFinalizing();
	  
      static int getInstanceCount();
   
   private:
      Arm() = default;
      
      static void run();
      
      static void safeExit();

      static void finalize();

      static bool finalizing;
	   
      static bool isAlive(Base* obj);
      
      static void add(Base* obj, RefBase* ref);
      
      static void remove(Base* obj, RefBase* ref);
	   
      static void removeImpl(Base* obj, RefBase* ref);
   
   friend struct ThreadMap;
   template <class T> friend class Ref;
   template <class T> friend class Weak;
   template <class T> friend class RefArrayBase;
};

} /* namespace aro */

#endif /* ARO_ARM_ARM_H */
