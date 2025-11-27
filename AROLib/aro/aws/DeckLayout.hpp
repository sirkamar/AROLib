#ifndef AWS_DECKLAYOUT_H
#define AWS_DECKLAYOUT_H

#include <aro/util/Vector.hpp>
#include <aro/aws/Container.hpp>

namespace aro {

namespace aws {

class DeckLayout;
typedef Ref<DeckLayout> RDeckLayout;

class DeckLayout extends public Object implements public Layout
{
   class Card;
   typedef Ref<Card> RCard;
   
   public:
      DeckLayout();
      DeckLayout(vint hgap,vint vgap);
      
      virtual RString toString();
      virtual void layoutContainer(RContainer target);
      virtual void removeLayoutComponent(RComponent comp);
      virtual RDimension recommendMaxSize(RContainer target);
      virtual RDimension recommendMinSize(RContainer target);
      virtual RDimension recommendPrefSize(RContainer target);
      virtual void addLayoutComponent(RComponent comp, RObject info);
      
      void show(RContainer target, RString name);
      void previous(RContainer target);
      void first(RContainer target);
      void next(RContainer target);
      void last(RContainer target);
   
   private:
      vint hgap, vgap;
      vint currentCard;
      util::RVector<Card> vector;
      
      void checkLayout(RContainer target);
      void showDefaultComponent(RContainer target);
};

class DeckLayout::Card : public Object
{
   public:
      Card(RString name, RComponent comp);
      
      RComponent comp;
      RString name;
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_DECKLAYOUT_H */
