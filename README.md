# Debouncer {#mainpage}

Collection of Debouncing strategies from the internet suitable for embedded systems. The algorithms currently implemented are from this article by Jack Ganssle <https://www.embedded.com/my-favorite-software-debouncers/>

## Table of contents

- [Project Structure](#project-structure)
- [Usage](#project-structure)
- [Build-Instruction](#build-instruction)
- [Credits](#credits)
- [Contact-Me](#contact-me)

## Project Structure

1. Source files are present in @ref Src
2. Interface files are present in @ref inc
3. PLease refer doxygen generated HTML documentation in the Doc/html subfolder for implementation details
4. The function entry point is @ref Main.c

## Usage

1. Initialization of the debouncer is achieved through @ref debounce_Init in @ref Debounce.h
2. At initialization the function for reading raw button input needs to be passed to @ref debounce_Init.
3. @ref debounce_pressRelease or @ref debounce_bitTrain need to be called periodically using an interrupt or task, Please refer to the @ref debounce_Init section for details
4. @ref debounce_isKeyPressed is used to read debounced buttons

## Build-Instruction

### Build directly with CMake

1. Two presets *BUILD_DEBUG* and *BUILD_RELEASE* are created for generating the Debug build and release build respectively

    ```code
    cmake --preset BUILD_DEBUG
    cmake --build --preset BUILD_DEBUG
    ```

    ```code
    cmake --preset BUILD_RELEASE
    cmake --build --preset BUILD_RELEASE
    ```

2. For simper builds not involving Cmake Presets, the following command can be used

    ```code
    cmake -S . -B build
    cmake --build build
    ```

### Building Documentation through Doxygen

```code
cd build
doxygen Doxyfile
```

## Credits

1. The algorithms implemented are based on this article by Jack Ganssle
<https://www.embedded.com/my-favorite-software-debouncers/>

## Permissions

1. Please refer to the LICENSE file

## Contact Me

1. You can reach out to me on LinkedIn here [LinkedIn](https://www.linkedin.com/in/vishal-keshava-murthy-8a2ba1a7/)
2. Github handle [Github](https://github.com/VKM96)
