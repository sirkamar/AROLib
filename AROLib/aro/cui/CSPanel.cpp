#include <aro/core.hpp>
#include <aro/aws/Graphics.hpp>
#include <aro/aws/TideLayout.hpp>
#include <aro/cui/CSPanel.hpp>

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
