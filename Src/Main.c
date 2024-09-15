/**
 * @file Main.c
 * @author https://github.com/VKM96
 * @brief
 * @version 0.1
 * @date 2022-07-17
 *
 *
 * @copyright Copyright (c) 2022
 *
 */

///////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "Debounce.h"
#include "version.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Dummy read function : Replace with actual button read on your platform
 *
 * @return true
 * @return false
 */
bool dummyIsButtonPressed() { return true; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Function entry point
 *
 *
 * @return int
 */
int main()
{
  char buf[32];
  Version_GetVersion(buf, sizeof(buf));
  printf("%s", buf);

  sDebounceHelper_t testDebounceHelper;
  debounce_Init(&testDebounceHelper, 5, 25, 25, dummyIsButtonPressed);
  debounce_bitTrain(
      &testDebounceHelper);  ///> This needs to be called periodically through
                             /// Interrupts or tasks
  return 0;
}