#include <aro/core.h>
#include <aro/aws/Graphics.h>
#include <aro/aws/TideLayout.h>
#include <aro/cui/CSPanel.h>

namespace aro {

namespace cui {

CSPanel::CSPanel()
   :CSPanel(new aws::TideLayout())
{
   
}

CSPanel::CSPanel(aws::RLayout layout)
{
   setLayout(layout);
}

void CSPanel::paintComponent(aws::RGraphics g)
{
   CSComponent::paintComponent(g);
}

} /* namespace cui */

} /* namespace aro */
