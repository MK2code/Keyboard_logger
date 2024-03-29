# Key Remapper
This program, written in C++, allows users to remap keys on their keyboard according to predefined mappings or a custom configuration file. Below are instructions and explanations for using and understanding the Key Remapper program.

# How to Use:
- Compilation: Compile the program using a C++ compiler such as g++.
- Execution: Run the compiled executable in a Windows environment.
- Key Mapping: The program allows for two modes of key mapping: default and custom.
  - Default Mapping: The default key mappings are predefined within the program. These mappings substitute specific keys with other keys, as per the provided mappings.
  - Custom Mapping: Users can define their key mappings by creating a config.txt file in the same directory as the executable. Each line of the file should contain the original key code followed by the remapped key code, separated by a space.
- Switching Mapping Modes: Users can switch between default and custom mapping modes during runtime. Pressing the Shift key toggles between the two modes.
# Dependencies:
- Windows.h: Header file for Windows API functions.
- iostream: Standard input/output stream.
- map: Standard template library for associative containers.
- fstream: Input/output stream class to operate on files.
- sstream: String stream functionality.
- Sleep(): Function for suspending execution of a thread for a specified interval.
- If getting .dll missing errors, please install Visual C++ redistributable on your system from - https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170
# Functionality:
- The program captures key presses using GetAsyncKeyState() function.
- It remaps keys based on predefined or user-defined mappings using keyMap and keyMap1 maps.
- Users can switch between default and custom mappings during runtime.
- Special functionality is provided for specific key combinations, like Ctrl+A (Select All).
