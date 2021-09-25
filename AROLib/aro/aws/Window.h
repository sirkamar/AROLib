#ifndef AWS_WINDOW_H
#define AWS_WINDOW_H

#include <aro/util/Vector.h>
#include <aro/aws/Container.h>
#include <aro/aws/event/WindowListener.h>
#include <aro/aws/event/WindowFocusListener.h>

namespace aro {

namespace aws {

class Window;
interface FocusPolicy;
typedef Ref<Window> RWindow;
typedef Ref<FocusPolicy> RFocusPolicy;

class Window : public Container
{
   public:
      Window();
      Window(RWindow owner);
      
      virtual void pack();
      virtual void dispose();
      virtual void repaint();
      virtual vbool isActive();
      virtual vbool isFocused();
      virtual vbool isShowing();
      virtual RWindow getOwner();
      virtual void setVisible(vbool b);
      virtual vbool isFocusableWindow();
      virtual RComponent getFocusOwner();
      virtual RFocusPolicy getFocusPolicy();
      virtual vbool getFocusableWindowState();
      virtual RComponent getMostRecentFocusOwner();
      virtual void setFocusableWindowState(vbool b);
      virtual void addWindowListener(event::RWindowListener l);
      virtual void removeWindowListener(event::RWindowListener l);
      virtual void addWindowFocusListener(event::RWindowFocusListener l);
      virtual void removeWindowFocusListener(event::RWindowFocusListener l);
   
   protected:
      virtual void hide();
      virtual void show();
      virtual void finalize();
      virtual void paint(RGraphics g);
      virtual void processEvent(RAWSEvent e);
      RComponent getTemporaryLostComponent();
      virtual void fireWindowEvent(event::RWindowEvent e);
      virtual void postProcessKeyEvent(event::RKeyEvent e);
      RComponent setTemporaryLostComponent(RComponent comp);
      virtual void processWindowEvent(event::RWindowEvent e);
      virtual void processWindowFocusEvent(event::RWindowEvent e);

   private:
      vint state;
      class WinRunThread;
      RWeak<Window> owner;
      RWeak<Window> weakThis;
      Ref<WinRunThread> runner;
      vbool running, disposing;
      vbool focusableWindowState;
      RComponent temporaryLostComp;
      vbool isInShow, beforeFirstShow;

      util::RVector<Weak<Window>> ownedWindowList;

      void doDispose();
      void disposeImpl();
      void addToWindowList();
      void removeFromWindowList();

      void postWindowEvent(vint eventID);

      void connectOwnedWindow(RWindow child);
      void addOwnedWindow(RWeak<Window> win);
      void removeOwnedWindow(RWeak<Window> win);

   
   friend class FocusManager;
   friend class DefaultFocusManager;
};

class Window::WinRunThread : public Thread
{
   public:
      WinRunThread(RWindow w);
      RWindow window;
      vbool running;
      void stop();
      void run();
   
   protected:
      void finalize();
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_WINDOW_H */
