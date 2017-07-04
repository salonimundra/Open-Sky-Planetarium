# Open Sky Planetarium plugin for Stellarium


Plugin for controlling the Arduino-Based Laser and Stellarium to create Planetarium shows.


## BUILDING THE PLUGIN

Please note, these instructions are only directly applicable to Linux.
Windows and OSX targets will probably require modification of the
CMakeLists.txt file.

1.  Install and build the SVN version of Stellarium as per the 
instructions on the Stellarium wiki:

  http://stellarium.org/wiki/index.php/Compilation_on_Linux

2.  Set the environment variable STELROOT to the root of the Stellarium
source tree.  The Stellarium build directory is expected to be:

  $STELROOT/builds/unix 

3.  Change into the builds/unix directory in your plugin folder.

4.  Run:
```
  cmake ../.. 
  make
  make install
```
If all goes well, the relevant files should be built and copied to your 
~/.stellarium/modules directory.


