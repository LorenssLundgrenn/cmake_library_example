CMake can't find my package:

Make sure the library is installed in a standard
location, such as usr/lib/ on linux.

Directly specifying package directory:

In CMakePresets.json, set "CMAKE_PREFIX_PATH" to the
installed library directory. You can specify multiple 
directories by separating directories with colon (:)
on Linux/MacOS. Use semicolon (;) instead on Windows.

Windows example:
"CMAKE_PREFIX_PATH": "C:/Program Files (x86)/my-library;C:/Program Files (x86)/my-library2"

Linux example:
"CMAKE_PREFIX_PATH": "usr/lib/my-library:usr/lib/my-library2"