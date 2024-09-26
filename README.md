# Stark

Stark is a markup language similar to toml.
This repository is an implementation of Stark in C++.

You can make a 'store' class which you can write key-value pairs into
by doing 'Add(key, { bool, int, float, string }).
And then write those into a file with 'PrintToFile(fileName)'
You can also get a value from a pair by 'Get<type>(key)'
You can also read from a file with 'ReadFromFile(fileName)'

## Objectives

Stark aims to be a minimal configuration/markup file similar to TOML and JSON.
It's very minimal, simple and easy to read. Stark's structure consists of
key-value pairs.

## Example

```toml
# An example Stark document.

# This is a comment

name = 'Slugarius' # String
age = 999 # Integer
lightSpeed = 132.30235 # Float
lightOn = True # Boolean
```

# Getting started

Clone the repository, cd into the folder, make a 'build' folder, cd into the build folder.
Type 'cmake ..' to generate build files. cd back into the main directory and type 'cmake --build build/'
to compile the project.
