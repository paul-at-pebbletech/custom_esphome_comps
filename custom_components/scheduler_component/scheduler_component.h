#pragma once

#include "esphome/core/component.h"
#include "esphome/components/api/custom_api_device.h"
#include "../ext_eeprom_component/ext_eeprom_component.h"
#include <string>
namespace esphome {
namespace scheduler_component {

struct struct_schedule_event
{
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  char action[6];
};
struct struct_schedule_storage
{
  uint16_t event_time;
  char action_str[6];
};

class SchedulerComponent : public Component, public api::CustomAPIDevice {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
   void test();
  void on_schedule_recieved(int schedule_device_id, int event_count,  std::vector<int> days ,std::vector<int> hours ,std::vector<int> minutes, std::vector<std::string> actions);
  void  send_log_message_to_HA(String level, String logMessage, String sender);
 void on_schedule_erase_recieved(int schedule_device_id);
 void on_erase_all_schedules_recieved();
  void  set_Storage_Offset(uint16_t storage_offset) { this->storage_offset_ = storage_offset; }
  void set_storage(ext_eeprom_component::ExtEepromComponent *storage) { this->storage_ = storage; }
  void set_Switch_Count(uint8_t switch_count) { this->switch_count_ = switch_count; }
  void set_Events_Per_Switch(uint16_t max_switch_events) { this->max_switch_events_ = max_switch_events; }
  float get_setup_priority() const override;
  protected:
        ext_eeprom_component::ExtEepromComponent *storage_;
        uint16_t storage_offset_;
        uint8_t switch_count_;
        uint16_t max_switch_events_;
        const int event_size =9;  // the event is 9 bytes (3 bytes for time and 6 for  action string)

};


}  // namespace scheduler_component
}  // namespace esphome