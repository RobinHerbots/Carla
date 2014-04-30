/*
 * Carla Native Plugins
 * Copyright (C) 2012-2014 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * For a full copy of the GNU General Public License see the doc/GPL.txt file.
 */

// Plugin Code
#include "powerjuice/PowerJuiceArtwork.cpp"
#include "powerjuice/PowerJuicePlugin.cpp"
#include "powerjuice/PowerJuiceUI.cpp"

// DISTRHO Code
#define DISTRHO_PLUGIN_TARGET_CARLA
#include "DistrhoPluginMain.cpp"
#include "DistrhoUIMain.cpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

static const NativePluginDescriptor powerjuiceDesc = {
    /* category  */ PLUGIN_CATEGORY_UTILITY,
    /* hints     */ static_cast<NativePluginHints>(PLUGIN_IS_RTSAFE|PLUGIN_HAS_UI|PLUGIN_USES_TIME|PLUGIN_USES_PARENT_ID),
    /* supports  */ static_cast<NativePluginSupports>(0x0),
    /* audioIns  */ DISTRHO_PLUGIN_NUM_INPUTS,
    /* audioOuts */ DISTRHO_PLUGIN_NUM_OUTPUTS,
    /* midiIns   */ 0,
    /* midiOuts  */ 0,
    /* paramIns  */ PowerJuicePlugin::paramCount,
    /* paramOuts */ 0,
    /* name      */ DISTRHO_PLUGIN_NAME,
    /* label     */ "powerjuice",
    /* maker     */ "Andre Sklenar",
    /* copyright */ "GPL v2+",
    PluginDescriptorFILL(PluginCarla)
};

END_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

CARLA_EXPORT
void carla_register_native_plugin_powerjuice()
{
    USE_NAMESPACE_DISTRHO
    carla_register_native_plugin(&powerjuiceDesc);
}

// -----------------------------------------------------------------------
