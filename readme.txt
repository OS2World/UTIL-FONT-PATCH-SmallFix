SMALL FONTS AND ICONS FOR WARP S3 DISPLAY DRIVERS
-------------------------------------------------

** Please take time to read the disclaimer situated **
** at the bottom of this file.                      **

Introduction
------------

The SVGA display drivers from IBM have an annoying habit of using
large icons and fonts at resolutions above and including 1024x768.

The program contained within this archive was written to address
this problem by making alterations to the display drivers to give
small fonts and icons.

The program has been used with success on the following versions of
Warp, and the following display drivers:

  Warp version        Graphics adapter   Driver name

  Warp II beta        V7 SPEA Mirage     (S3 32bit drivers)
  Warp II beta        Diamond Stealth 64 (IBM/S3 864)
  Warp GA             V7 SPEA Mirage     (S3 68C801, ...)
  Warp GA             ATI Mach 32        (ATI Mach 32)


Procedure
---------

1. Install the high resolution drivers using Selective Install if you
   haven't already done so.

2. Take a backup of the file "\os2\ibms332.dll" and call it something
   like "\os2\old-ibms332.dll".

   If you are using a non-S3 adapter, then replace the "ibms332.dll"
   with the name of the display driver DLL.  This might be
   "ibmsvga.dll", or "atim32.dll", or something like that! :-)

3. Run the program "fixdisp.exe" included in this archive.  The
   program takes two parameters: 

   i.  The name of the original (unpatched) display driver DLL 
   ii. The name of the patched display driver DLL that the program 
       is to save.

   eg.
      fixdisp \os2\old-ibms332.dll \os2\new-ibms332.dll

   The program defaults to the above two parameters if none are
   specified.

4. The program will (hopefully) run and display four messages relating
   to patching fonts, icons, and DPI.

   If the program was unable to make all the necessary alterations
   then it will let you know.  You should NOT try to use the patched
   DLL that is saved; you may have tried to patch the wrong DLL.  Try
   using a different (correct) DLL name, or try to make alterations to
   the program's source code so that it works.

5. Shutdown your machine, and reboot.  When the white block appears at
   the top-left of the screen, hit ALT+F1.  This should bring up a
   menu screen, on which you should hit "C" to boot to a command
   prompt.

   Now copy the patched DLL on top of "\os2\ibms332.dll".

   eg.
      cd \os2
      copy new-ibms332.dll ibms332.dll

   Do not remove old-ibms332.dll since you may need it if the patch
   has not worked.

   Reboot (type "exit").

6. You should now have small fonts and icons at resolutions of
   1024x768 and above.

   If you experience problems, such as impossibly wide icons, black
   icons or strange fonts, then repeat step 6, copying old-ibms332.dll
   on top of ibms332.dll to undo the effects of the patch.

Finally,

  If you have tried the program with non-S3 graphics adapters and it
  has worked, then please let me know so that I can build a list of
  the adapters that it works for.  Please include the Adapter name,
  DLL name, and name of the Drivers as they appear in Selective
  Install.  Thanks.

  Please note that this program does not even attempt to address any
  problems you might currently have regarding refresh rates or the
  ability to achieve resolutions of 1024x768 or above.

The source code
---------------

The source code for fixdisp.exe is located in the source directory
contained within this archive.  It compiles with Borland C++ for OS/2,
IBM CSet++ and also gcc/emx apparently.


Acknowledgements
----------------

Daniel J Neades (djn@arac.demon.co.uk) for the information about which
bits of the display drivers need twiddling.

John J. Lehett (jlehett@gate.net) for details about compiling
fixdisp.cpp with emx/gcc and for reporting success with the ATI Mach
32.

IBM, for OS/2 Warp, and for the large fonts and icons (again).


DISCLAIMER  (very important)
----------------------------

 The authors accept absolutely NO responsiblity for any adverse
 consequences of the use or misuse of this program. IBM will probably
 not provide any form of support for modified display drivers.

 Modifying display drivers is a messy business.  If you are not 100%
 confident in your display driver twiddling abilities then DO NOT USE
 THIS PROGRAM.  You have been warned.

- J.R.Shannon (jrs@larch.demon.co.uk)
  10th December 1994


