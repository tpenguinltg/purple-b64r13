# purple-b64r13
A simple libpurple plugin for encoding/decoding messages with Base64-Rot13.

Suppose you want to send an obscured message. Encoding your message using Base64 is a good way to do so, but many people can recognize a Base64 string and will be able to decode it easily. Encoding the Base64 string through Rot13 means that the message still looks like Base64, but will come out as gibberish when attempting to decode such.

## Building and Installation

1. Execute

        make
        make install

   (_Binary releases to come_)

2. Activate the plugin from Pidgin's plugin dialog (Tools > Plugins) 

<!-- TODO: build instructions, better installation instructions -->

## Usage

To send a message encoded with Base64-Rot13:
> /b64r13 Message

To decode a Base64-Rot13-encoded message:
> /b64r13d GJImp2SaMDb=

## Changelog

* v0.1.0: Initial release
