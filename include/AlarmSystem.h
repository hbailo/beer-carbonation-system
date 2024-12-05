#ifndef ALARM_SYSTEM_H
#define ALARM_SYSTEM_H

#include <array>
#include <vector>

#include "CarbonationRecipe.h"
#include "Carbonator.h"
#include "Siren.h"

class AlarmSystem {

public:
  /** @brief Initializes the alarm manager. */
  AlarmSystem(Carbonator& carbonator, CarbonationRecipe& carbonation_recipe);

  /** @brief Updates the alarm manager. */
  void update();

  /** @brief Returns the active alarms. */
  const std::vector<const char *>& getActiveAlarms();
  
private:
  /** @brief States of an alarm. */
  enum class AlarmState { INACTIVE, ACTIVE };

  /** */
  struct AlarmRegister {
    const char* message;
    std::function<bool()> trigger;
    AlarmState state;
  } ;

  /** @brief Registered alarms. */
  std::array<AlarmRegister, 1> alarms;

  /** @brief Active alarms. */
   std::vector<const char *> active_alarms;
  
  /** @brief Siren. */
  Siren siren;
  
};

#endif
