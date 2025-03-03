#include "src/Core/Engine.h"


int main()
{
  Prism::Engine engine{Prism::HAL::Render_api::Vulkan};

  engine.initialize();

  // engine.render();

  return 0;
}
