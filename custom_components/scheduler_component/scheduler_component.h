#pragma once

#include "esphome/core/component.h"
#include "esphome/components/api/custom_api_device.h"
#include "../ext_eeprom_component/ext_eeprom_component.h"
namespace esphome {
namespace scheduler_component {

struct struct_schedule_event
{
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  char action;
};

class SchedulerComponent : public Component, public api::CustomAPIDevice {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
   void test();
  void on_schedule_recieved(int schedule_device_id, std::vector<int> days ,std::vector<int> hours ,std::vector<int> minutes, std::vector<std::string> actions);
 
  void  set_Storage_Offset(uint16_t storage_offset) { this->storage_offset_ = storage_offset; }
  void set_storage(ext_eeprom_component::ExtEepromComponent *storage) { this->storage_ = storage; }
  float get_setup_priority() const override;
  protected:
        ext_eeprom_component::ExtEepromComponent *storage_;
        uint16_t storage_offset_;
};


}  // namespace scheduler_component
}  // namespace esphome