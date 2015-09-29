/* Base64-Rot13 encoder/decoder for Pidgin
 * Copyright (C) 2015  tPenguinLTG
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#ifndef PURPLE_PLUGINS
# define PURPLE_PLUGINS
#endif

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <glib.h>
#include <string.h>

#include <version.h>
#include <plugin.h>
#include <conversation.h>
#include <cmds.h>


/* static PurplePlugin *purple_b64r13 = NULL; */
static PurpleCmdId b64r13_cmd_id, b64r13d_cmd_id;


/**
 * Encodes the given string using the Rot13 algorithm.
 * @param s  the string to encode
 * @return   the string encoded with Rot13
 */
static gchar*
rot13(gchar *s)
{
        int i=0;
	for (i=0; s[i]!='\0'; i++) {
		/*  if lowercase */
		if ('a' <= s[i] && s[i] <= 'z') {
			s[i]=(s[i]-'a'+13) % 26 + 'a';
		}
		/* else if uppercase */
		else if ('A' <= s[i] && s[i] <= 'Z') {
			s[i]=(s[i]-'A'+13) % 26 + 'A';
		}
		
		/* else not a letter; do nothing */
	}/* end for */
	
	return s;
}/* end rot13(gchar*) */


#if 0
/**
 * Encodes the given string using Base64, then Rot13.
 * @param s the string to encode
 * @return the encoded string
 */
static gchar*
encode_b64r13(gchar *s)
  {
  /* TODO */
  return s;
  }/* end encode_b64r13(gchar*) */


/**
 * Decodes the given Base64-Rot13 encoded string.
 * @param the string to decode
 * @return the decoded string
 */
static gchar*
decode_b64r13(gchar *s)
  {
  /* TODO */
  return s;
  }/* end decode_b64r13(gchar*) */
#endif


/**
 * Callback function for b64r13.
 */
static PurpleCmdRet
b64r13_cb(PurpleConversation *conv, const gchar *cmd, const gchar **args, gchar **error, void *data)
{
	guchar *encoded_str = rot13(g_base64_encode(args[0], strlen(args[0])));
	
	
	/* output to conversation */
	if (purple_conversation_get_type(conv) == PURPLE_CONV_TYPE_IM) {
		purple_conv_im_send(PURPLE_CONV_IM(conv), encoded_str);
		/* output original message as system message */
		purple_conv_im_write(PURPLE_CONV_IM(conv), NULL,
		                     args[0], PURPLE_MESSAGE_SYSTEM, time(NULL));
	} else if (purple_conversation_get_type(conv) == PURPLE_CONV_TYPE_CHAT) {
		purple_conv_chat_send(PURPLE_CONV_CHAT(conv), encoded_str);
		/* output original message as system message */
		purple_conv_chat_write(PURPLE_CONV_CHAT(conv), NULL,
		                       args[0],  PURPLE_MESSAGE_SYSTEM, time(NULL));
	}/* end if */
	
	g_free(encoded_str);
	
	return PURPLE_CMD_RET_OK;
}/* end b64r13d_cmd_id */


/**
 * Callback function for b64r13d
 */
static PurpleCmdRet
b64r13_decode_cb(PurpleConversation *conv, const gchar *cmd, gchar **args, gchar **error, void *data)
{
	gsize decoded_length=0;
	gchar *decoded_raw = g_base64_decode(rot13(args[0]), &decoded_length);
	
	char decoded_str[decoded_length+1];
	strncpy(decoded_str, decoded_raw, decoded_length);
	
	time_t _time=time(NULL);
	
	if (purple_conversation_get_type(conv) == PURPLE_CONV_TYPE_IM) {
		purple_conv_im_write(PURPLE_CONV_IM(conv), NULL,
		                     decoded_str, PURPLE_MESSAGE_NO_LOG | PURPLE_MESSAGE_SYSTEM, _time);
	} else if (purple_conversation_get_type(conv) == PURPLE_CONV_TYPE_CHAT) {
		purple_conv_chat_write(PURPLE_CONV_CHAT(conv), NULL,
		                       decoded_str, PURPLE_MESSAGE_NO_LOG | PURPLE_MESSAGE_SYSTEM, _time);
	}/* end if */
	
	g_free(decoded_raw);
	
	return PURPLE_CMD_RET_OK;
}/* end b64r13_decode_cb */


static gboolean
plugin_load(PurplePlugin *plugin)
{
	b64r13_cmd_id = purple_cmd_register("b64r13", "s", PURPLE_CMD_P_DEFAULT,
	                                    PURPLE_CMD_FLAG_CHAT | PURPLE_CMD_FLAG_IM, NULL,
	                                    b64r13_cb,
	                                    "b64r13 &lt;message&gt;: Send a message encoded with Base64 and Rot13.",
	                                    NULL);
	                                    
	b64r13d_cmd_id = purple_cmd_register("b64r13d", "s", PURPLE_CMD_P_DEFAULT,
	                                     PURPLE_CMD_FLAG_CHAT | PURPLE_CMD_FLAG_IM, NULL,
	                                     b64r13_decode_cb,
	                                     "b64r13d &lt;encoded message&gt;: Decode a message encoded with Base64 and Rot13.",
	                                     NULL);
	                                     
	return TRUE;
}/* end plugin_load(PurplePlugin*) */


static gboolean
plugin_unload(PurplePlugin *plugin)
{
	purple_cmd_unregister(b64r13_cmd_id);
	
	return TRUE;
}/* end plugin_load(PurplePlugin*) */


static PurplePluginInfo info = {
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
	"0.2.0-beta",
	
	"Encodes message using Base64 and Rot13.",
	"Encodes message using Base64, then encodes the result using Rot13."
		" Adds the /b64r13 command for encoding and /b64r13d command for decoding.",
	"tPenguinLTG <tpenguinltg@hotmail.com>",
	"https://github.com/tpenguinltg/purple-b64r13",
	
	plugin_load,
	plugin_unload,
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
}/* end init_plugin(PurplePlugin*) */

PURPLE_INIT_PLUGIN(b64r13, init_plugin, info)
