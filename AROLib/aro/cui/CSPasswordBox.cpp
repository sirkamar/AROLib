#include <aro/core.hpp>
#include <aro/cui/CSPasswordBox.hpp>

namespace aro {

namespace cui {

CSPasswordBox::CSPasswordBox()
   :CSPasswordBox(10)
{
   //echoChar = '*';
}

CSPasswordBox::CSPasswordBox(vint width)
   :CSPasswordBox("",width)
{
   //echoChar = '*';
}

CSPasswordBox::CSPasswordBox(RString str)
   :CSPasswordBox(str,10)
{
   //echoChar = '*';
}

CSPasswordBox::CSPasswordBox(RString str, vint width)
   :CSTextBox(str, width)
{
   echoChar = '*';
}

} /* namespace cui */

} /* namespace aro */
