/**
 * @file Debounce.h
 * @author https://github.com/VKM96
 * @brief
 * @version 0.1
 * @date 2022-07-17
 *
 * Algorithm courtesy https://www.embedded.com/my-favorite-software-debouncers/
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Signature of function used to read actual button
 *
 */
typedef bool (*pf_IsKeyPressed)(void);

/**
 * @struct sDebounceHelper_t
 * @brief Helper structure that contains all button related parameters
 *
 */
typedef struct
{
  uint8_t rw_buttonReadInMs;   ///< How frequently the button is being read
  uint8_t rw_pressTimeInMs;    ///< Press Time of the button
  uint8_t rw_releaseTimeInMS;  ///< Release Time of the button
  bool r_IsKeyPressed;         ///< true if button was pressed
  bool r_IsKeyChanged;         ///< True is button was changed
  pf_IsKeyPressed w_IsKeyPressedFunction;  ///< pointer to function used by
                                           ///< hardware to read button
} sDebounceHelper_t;

/**
 * @enum eDebounceStatus_t
 * @brief Status used inside the debounce module, currently unused
 *
 */
typedef enum
{
  e_SUCCESS = 0,
  e_FAILURE = 1
} eDebounceStatus_t;

eDebounceStatus_t debounce_Init(sDebounceHelper_t* const pMe,
                                uint8_t buttonReadTimeInMs,
                                uint8_t pressTimeInMs, uint8_t releaseTimeInMs,
                                pf_IsKeyPressed pfIsKeyPressed);
eDebounceStatus_t debounce_pressRelease(sDebounceHelper_t* const pMe);
eDebounceStatus_t debounce_bitTrain(sDebounceHelper_t* const pMe);

bool debounce_isKeyPressed(const sDebounceHelper_t* const pMe);
bool debounce_isKeyStateChanged(const sDebounceHelper_t* const pMe);

#endif