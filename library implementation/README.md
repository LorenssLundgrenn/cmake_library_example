How to use cmake presets:

Here is the command to run a preset:
cmake --preset <preset>

You can go into CMakePresets.json and look
under "configurePresets". replace <preset>
with the value of the "name" field to 
specify a preset configuration.

Here is how you build using a build preset:
cmake --build --preset <preset>

You can go into CMakePresets.json and look
under "buildPresets". Replace <preset> with
the value of the "name" field to specify a
preset build configuration.

To install a library you must first have
built it. Navigate to the build directory,
"bin" in this case, and run the following
command:

make install