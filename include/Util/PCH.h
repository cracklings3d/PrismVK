/*****************************
 * Copyright 2025 Cracklings *
 * Created Feb 21 2025       *
 *****************************/

#pragma once

/**
 * @brief PRISM_VERSION has identical implementation as VK_MAKE_VERSION
 * @param major Major version number
 * @param minor Minor version number
 * @param patch Patch version number
 * @return Version number
 */
#define PRISM_VERSION(major, minor, patch)                                                                             \
  ((((uint32_t)(major)) << 22U) | (((uint32_t)(minor)) << 12U) | ((uint32_t)(patch)))
