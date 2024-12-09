#include "AlarmSystem.h"
#include "Carbonator.h"
#include "CarbonationRecipe.h"
#include <vector>

/**
 *
 */
AlarmSystem::AlarmSystem(Carbonator& carbonator, CarbonationRecipe& carbonation_recipe)
  : siren(PA_3, 2000)
{

  alarms[0].message = "Barrel overpressure, BPA1 >= 4 bar.";
  alarms[0].trigger = [&carbonator]() -> bool {return carbonator.getBPA1() > 4;};
  alarms[0].state  = AlarmState::INACTIVE;
  
}

/**
 *
 */
void AlarmSystem::update()
{
  
  active_alarms.clear();

  for (AlarmRegister& alarm : alarms) {
    
    if (alarm.trigger()) {
      alarm.state = AlarmState::ACTIVE;
      active_alarms.push_back(alarm.message);
    } else {
      alarm.state = AlarmState::INACTIVE;
    }
    
  }

  if (not active_alarms.empty()) {
    siren.activate();
  } else {
    siren.deactivate();
  }

}

/**
 *
 */
const std::vector<const char *>& AlarmSystem::getActiveAlarms()
{

  return active_alarms;
  
}
