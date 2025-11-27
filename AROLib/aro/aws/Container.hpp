#ifndef AWS_CONTAINER_H
#define AWS_CONTAINER_H

#include <aro/util/List.hpp>
#include <aro/aws/Layout.hpp>
#include <aro/aws/Component.hpp>

namespace aro {

namespace aws {

class Insets;
typedef Ref<Insets> RInsets;
// Container and RContainer declared in <aro/aws/Component.hpp>

/** Class Container is a holder for components that
 * are to be displayed on the screen. */
class Container extends public Component
{
   public:
      virtual void add(RComponent comp); // adds component to container
      virtual RDimension getMaximumSize(); // returns the container's maximum size
      virtual RDimension getMinimumSize(); // returns the container's minimum size
      virtual RDimension getPreferredSize(); // returns the container's preferred size
      virtual void remove(RComponent comp); // removes specified component from container
      virtual vint getComponentCount(); // returns number of components in container
      virtual void add(RComponent comp,vint index); // adds component to container at index
      virtual void add(RComponent comp,RObject info); // adds component with a constraint
      virtual void add(RComponent comp,RObject info,vint index); // adds with a constraint at index
      virtual RComponent getComponent(vint index); // returns component at given index
      virtual RArray<Component> getComponents(); // returns an Array of components
      virtual void setLayout(RLayout l); // sets the container's layout scheme
      virtual void remove(vint index); // removes component at index
      virtual RInsets getInsets(); // returns the containers insets
      virtual RLayout getLayout(); // returns the container's layout scheme
      virtual void invalidate(); // marks container as bein invalid
      virtual void removeAll(); // removes all components
      virtual void doLayout(); // executes the layout scheme
      virtual void validate(); // marks container as being valid
      
      // Checks if the component is contained in the
      // component hierarchy of this container.
      vbool isAncestorOf(RComponent comp);
   
   protected:
      Container(); // default constructor
      Container(RLayout l); // primary constructor
      virtual void validateTree(); // validate component tree
      virtual void paint(RGraphics g); // paints container and sub-components
      virtual void update(RGraphics g); // updates container
      virtual void paintComponents(RGraphics g); // paints children
      virtual void preProcessKeyEvent(event::RKeyEvent e);
      virtual void postProcessKeyEvent(event::RKeyEvent e);
      virtual void validateUnconditionally() final; // ignore validity

      /** Returns the focusable component at the component position index */
      RComponent getPrevious(); // returns previous focusable element in component tree
      RComponent getCurrent(); // returns current focusable element in component tree
      RComponent getNext(); // returns next focusable element in component tree
      RComponent getFirst(); // returns first focusable element in component tree
      RComponent getLast(); // returns last focusable element in component tree
   
   private:
      static const RArray<Component> EMPTY_ARRAY;
      
      util::RList<Component> cmp; // list of components
      vbool ignoreValidity; // when validating contents
      RLayout manager; // the container's layout scheme
      RComponent cur; // the component at pos
      vbool inSub; // traversing sub-components 
      vint pos; // sub-component position index
   
   friend class Window;
   friend class Component;
   friend class DefaultFocusManager;
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_CONTAINER_H */
