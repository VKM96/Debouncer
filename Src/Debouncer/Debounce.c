/**
 * @file Debounce.c
 * @author vishal k
 * @brief Source files for a a few debounce routines
 * @version 0.1
 * @date 2022-07-17
 *
 * @copyright Copyright (c) 2022
 *
 */

///////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Debounce.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////

static bool gIsKeyPressedDebounced =
    false;  ///> This is the global variable that maintains the debounced key
            /// state

///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Utility function to creating 16 bit masks with leading ones
 *
 * @param leadingOnes : NUmber of leading ones to set
 * @return uint16_t : Mask with as many @ref leadingOnes
 */
static uint16_t debounce_setLeadingOnes(uint8_t leadingOnes)
{
  uint16_t resMask = 0;

  for (uint8_t index = 15; index > (15 - leadingOnes); index--)
  {
    uint16_t mask = 1 << index;
    resMask = resMask | mask;
  }
  return resMask;
}

/**
 * @brief utility function to prepare press mask
 *
 * The pressMask determines the press time of the button. This is to be a
 * multiple of button polling interval A press mask 0xF000 (0b 1111 0000 0000
 * 0000)would mean a Pres time of 4 * (button read time)
 *
 * @param pMe : handler of type pointer to @ref sDebounceHelper_t
 * @return uint16_t : prepared PressMask
 */
static uint16_t debounce_setPressMask(sDebounceHelper_t* const pMe)
{
  uint16_t leadingOnesCount = pMe->rw_pressTimeInMs / pMe->rw_buttonReadInMs;
  uint16_t PressMask = debounce_setLeadingOnes(leadingOnesCount);
  return PressMask;
}

/**
 * @brief utility function to prepare debounce  mask
 *
 * The debounce release mask determines how much debouncing is added, This is to
 * be a multiple of button polling interval A debounce mask of 0xF000 (0b 1111
 * 0000 0000 0000) would mean a debouncing period of 4 * (button read time)
 *
 * @param pMe : handler of type pointer to @ref sDebounceHelper_t
 * @return uint16_t : prepared debounce Ignore mask
 */
static uint16_t debounce_setDebounceIgnoreMask(sDebounceHelper_t* const pMe)
{
  uint16_t leadingOnesCount = pMe->rw_buttonReadInMs * 3;
  uint16_t debounceIgnoreMask = debounce_setLeadingOnes(leadingOnesCount);
  return debounceIgnoreMask;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initialization function for debouncing routines
 *
 * @param pMe : handler of type pointer to @ref sDebounceHelper_t
 * @param buttonReadTimeInMs : Frequency with which button is being read from
 * the hardware
 * @param pressTimeInMs : Desired time ti be treated as a button press
 * @param releaseTimeInMs : Desired time to be treated as release
 * @param pfIsKeyPressed : Pointer to a function that reads the actual hardware
 * @return eDebounceStatus_t : return status
 */
eDebounceStatus_t debounce_Init(sDebounceHelper_t* const pMe,
                                uint8_t buttonReadTimeInMs,
                                uint8_t pressTimeInMs, uint8_t releaseTimeInMs,
                                pf_IsKeyPressed pfIsKeyPressed)
{
  assert(NULL != pMe);
  assert(NULL != pfIsKeyPressed);
  assert((buttonReadTimeInMs < pressTimeInMs) &&
         (buttonReadTimeInMs < releaseTimeInMs));

  pMe->r_IsKeyPressed = false;
  pMe->r_IsKeyChanged = false;
  pMe->rw_buttonReadInMs = buttonReadTimeInMs;
  pMe->rw_pressTimeInMs = pressTimeInMs;
  pMe->rw_releaseTimeInMS = releaseTimeInMs;

  return e_SUCCESS;
}

/**
 * @brief Function to check if key is pressed
 *
 * @param pMe : handler of type pointer to @ref sDebounceHelper_t
 * @return true
 * @return false
 */
bool debounce_isKeyPressed(const sDebounceHelper_t* const pMe)
{
  return (pMe->r_IsKeyPressed);
}

/**
 * @brief Function to check if key state has changed
 *
 * @param pMe : handler of type pointer to @ref sDebounceHelper_t
 * @return true
 * @return false
 */
bool debounce_isKeyStateChanged(const sDebounceHelper_t* const pMe)
{
  return (pMe->r_IsKeyChanged);
}

/**
 * @brief Debounce algorithm that handles both press time and release time
 *
 * This function needs to be called periodically at the rate set in @ref
 * debounce_Init routine The result of if the button was pressed or not is
 * updated in member r_IsKeyPressed of @ref sDebounceHelper_t The result of it
 * the key was changed or not is updated in member r_IsKeyChanged of @ref
 * sDebounceHelper_t
 *
 * @param pMe : handler of type pointer to @ref sDebounceHelper_t
 * @return eDebounceStatus_t  return status
 */
eDebounceStatus_t debounce_pressRelease(sDebounceHelper_t* const pMe)
{
  assert(NULL != pMe);

  static bool isFirstPass = true;
  static uint16_t count = 0;
  static uint16_t pressTimeCount = 0;
  static uint16_t releaseTimeCount = 0;

  ///> During first pass count needs to be set to release count
  if (isFirstPass)
  {
    isFirstPass = false;
    pressTimeCount = pMe->rw_pressTimeInMs / pMe->rw_buttonReadInMs;
    releaseTimeCount = pMe->rw_releaseTimeInMS / pMe->rw_buttonReadInMs;
    count = releaseTimeCount;
  }

  pMe->r_IsKeyChanged = false;
  pMe->r_IsKeyPressed = gIsKeyPressedDebounced;

  ///> read actual keys here
  bool isRawKeyPressed = pMe->w_IsKeyPressedFunction();

  ///> if the current key press state and global key press state are same,
  /// update count
  if (isRawKeyPressed == gIsKeyPressedDebounced)
  {
    ///> setup the timer to monitor next change
    count =
        (true == gIsKeyPressedDebounced) ? releaseTimeCount : pressTimeCount;
  }
  else
  {
    ///> Wait unit the key state is stabilized
    if (0 == --count)
    {
      ///> Accept the change and update the result booleans accordingly
      gIsKeyPressedDebounced = isRawKeyPressed;
      pMe->r_IsKeyChanged = true;
      pMe->r_IsKeyPressed = gIsKeyPressedDebounced;
      count =
          (true == gIsKeyPressedDebounced) ? releaseTimeCount : pressTimeCount;
    }
    else
    {
      count = pressTimeCount;
    }
  }

  return e_SUCCESS;
}

/**
 * @brief Debounce strategy based on turning the button reads into a bitTrain
 *
 * This function needs to be called periodically at the rate set in @ref
 * debounce_Init routine
 *
 * @param pMe : handler of type pointer to @ref sDebounceHelper_t
 * @return eDebounceStatus_t  return status
 * @todo : return statuses to be utilized
 */
eDebounceStatus_t debounce_bitTrain(sDebounceHelper_t* const pMe)
{
  assert(NULL != pMe);

  static bool isFirstPass = true;

  static uint16_t pressedMask = 0;
  static uint16_t debounceIgnoreMask = 0;
  static uint16_t state = 0;

  bool prevIsKeyPressed =
      pMe->r_IsKeyPressed;  ///> Setting up previous state by copying state
                            /// before update

  ///> During first pass compute press mask and debounce ignore mask
  if (isFirstPass)
  {
    isFirstPass = false;
    pressedMask = debounce_setPressMask(pMe);
    debounceIgnoreMask = debounce_setDebounceIgnoreMask(pMe);
  }

  ///> Pin readings converted to bit train here. @ref debounceIgnoreMask creates
  /// a ignore condition on the bounces
  state = (state << 1) | pMe->w_IsKeyPressedFunction() | debounceIgnoreMask;
  pMe->r_IsKeyPressed = (state == pressedMask) ? true : false;
  pMe->r_IsKeyChanged =
      (prevIsKeyPressed == pMe->r_IsKeyPressed) ? true : false;

  return e_SUCCESS;
}
