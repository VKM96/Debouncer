Debouncer                      {#mainpage}
============
    Collection of Debouncing strategies from the internet suitable for embedded systems. The algorithms currently implemented are from this article by Jack Ganssle https://www.embedded.com/my-favorite-software-debouncers/

**Code Structure**

1. Source files are present in @ref Src
2. Interface files are present in @ref inc
3. PLease refer doxygen generated HTML documentation in the Doc/html subfolder for implementation details
4. The function entry point is @ref Main.c

**Usage**

1. Initialization of the debugger is achieved through @ref debounce_Init in @ref Debounce.h
2. At initialization the function for reading raw button input needs to be passed to @ref debounce_Init.
3. @ref debounce_pressRelease or @ref debounce_bitTrain need to be called periodically using an interrupt or task, Please refer to the @ref debounce_Init section for details 
4. @ref debounce_isKeyPressed is used to read debounced buttons


**Credits**
1. The algorithms implemented are based on this article by Jack Ganssle 
https://www.embedded.com/my-favorite-software-debouncers/


**Permissions**

1. PLease refer to the LICENSE file "# Debouncer-" 
