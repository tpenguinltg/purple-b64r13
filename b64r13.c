#ifndef PURPLE_PLUGINS
# define PURPLE_PLUGINS
#endif

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <glib.h>

#include <notify.h>
#include <plugin.h>
#include <version.h>
#include <cmds.h>
#include <conversation.h>

static gboolean
plugin_load(PurplePlugin *plugin)
  {
                        
  return TRUE;
  }

static PurplePluginInfo info =
  {
  PURPLE_PLUGIN_MAGIC,
  PURPLE_MAJOR_VERSION,
  PURPLE_MINOR_VERSION,
  PURPLE_PLUGIN_STANDARD,
  NULL,
  0,
  NULL,
  PURPLE_PRIORITY_DEFAULT,
  
  "core-tpenguinltg-b64r13",
  "Base64-Rot13 Encode",
  "0.0.0",
  
  "Encodes message using Base64 and Rot13.",
  "Encodes message using Base64, then encodes the result using Rot13. Adds the /b64r13 command.",
  "tPenguinLTG <tpenguinltg@hotmail.com>",
  "https://github.com/tpenguinltg/purple-b64r13",
  
  plugin_load,
  NULL,
  NULL,
  
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
  };

static void
init_plugin(PurplePlugin *plugin)
  {
  }

PURPLE_INIT_PLUGIN(hello_world, init_plugin, info)
