#include "Core/Engine.h"


int main()
{
  Prism::HAL::Render_settings render_settings;

  render_settings.render_api = Prism::HAL::Render_api::Vulkan;

  Prism::Engine engine{render_settings};

  engine.initialize();

  // engine.render();

  return 0;
}
