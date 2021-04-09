
Welcome to the Amiga Synergy Client v2.0
----------------------------------------

(C) Douglas McLaughlin
    STR Programming Services
    2005, 2006

This file was written using Synergy.

This is Release 2 of the Amiga Synergy client.  All items planned for this
version have been implemented.  For use only with Synergy Server v1.3.0 or
higher.


History
-------
--> 2.0

o Almost completely re-written.
o Upgraded to use the current synergy protocol, v1.3
o All mouse and keyboard OS operations now work properly.
o Now a commodity.
o No need for a reset handler, the server can now detect when a client
  drops offline.
o Mouse pointer blanking is much more system friendly now.  No longer
  loses the pointer image if you switch back to the Amiga mouse when the
  synergy mouse is offscreen.

--> 1.4

o Never released, it was too buggy.

--> 1.3

o Synergy's clipboard sharing is now working.

--> 1.2

o Fixed a nasty bug in the TCP receive routine that would cause the program
  to go into an infinite loop if the incoming packet was large.

--> 1.1

o Less debug output.

o Now restores any custom pointers that may have been in effect when the input
  focus left the Amiga.

o Better shutdown functionality when the Amiga is reset from the keyboard.

o Clicking on links now works as normal in IBrowse, it was indeed a bug in
  this program after all.  :-)


--> 1.0

o Implements the full current version of the Synergy protocol v1.2

o Notifies the server when the frontmost screen resolution changes.

o Attempts reconnection with the server if connection is lost and there
  were no other fatal problems.

o Clears the mouse pointer when the input focus leaves the Amiga and
  restores it when focus returns.

o Supports the Amiga reset keys, both Control-Amiga-Amiga and
  Control-Alt-Alt.

o Implements an Exec Reset-Handler to shut down the connection with the
  server when a reset happens.

o Fixed the problem with the keyboard mapping when running a Linux Synergy
  Server.


Problems
--------

None known at this time.


Unimplemented
-------------

o Screen Blanker Synchronization (Not Planned)

o Mac OS X as server (for keyboard mapping)


Starting the Client
-------------------

The client must be run from the shell and it takes two arguments, the IP
address or hostname of the machine running the Synergy server and the type
of OS the server is running.  This can be either linux or windows. For
example:

asynergyc 192.168.1.2 windows

asynergyc 192.168.1.7 linux

The keywords 'windows' and 'linux' must be all lowercase.

Run the client once with no arguments and it will report to the shell what
screen name will be sent to the server.  You can use this output to properly
configure the screen setup on the server.  If the name comes out as localhost,
this typically means that your Internet Prefs are not setup properly.  Use the
Hosts tab in the Internet Preferences program to set a hostname for your
Amiga's IP address.  The 'Name' column will be used as the screen name.

To run at startup, place asynergyc in your S:Network-Startup script.  If
you don't have one (you should!) place the client startup in your
S:User-Startup script.  It can be started like this:

Run *><>NIL: Work:Synergy2/asynergyc >NIL: 192.168.1.2 windows


Emailware
---------

If you like this program, email me.

Douglas McLaughlin
STR Programming Services
stricq AT stricq DOT com

