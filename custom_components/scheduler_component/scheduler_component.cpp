#include "esphome/core/log.h"
#include "scheduler_component.h"



namespace esphome {
namespace scheduler_component {

static const char *TAG = "scheduler_component.component";

void SchedulerComponent::setup() {
    register_service(&SchedulerComponent::on_schedule_recieved, "send_schedule",
                   {"schedule_device_id", "event_count", "days", "hours","minutes","actions"});
    register_service(&SchedulerComponent::on_schedule_erase_recieved, "erase_schedule",{"schedule_device_id"});
       register_service(&SchedulerComponent::on_erase_all_schedules_recieved, "erase_all_schedules"); 
       // Check schedule data in eeprom is valid
       // If not eg first time this eeprom has been used write a new control structure
        // Setup next schedule next event per switch

}
void SchedulerComponent::loop() {
      
// Check schedulke events against current time
// If event time is in past then set switch states per schedule unless override is active
// Update next schedule next event per switch
}

void SchedulerComponent::dump_config(){
    ESP_LOGCONFIG(TAG, "Scheduler component");
    // TODO dump config for EEPROM and Switches
}
void SchedulerComponent:: test(){
                ESP_LOGD(TAG, "Mem size in bytes: %d",this->storage_->length());
                int myValue2 = -366;
                this->storage_->put(10, myValue2); //(location, data)
                int myRead2;
                this->storage_->get(10, myRead2); //location to read, thing to put data into
                ESP_LOGD(TAG, "I read: %d",myRead2 );
}
void SchedulerComponent:: send_log_message_to_HA(String level, String logMessage, String sender)
{
       call_homeassistant_service("system_log.write", {
                                                    {"message", logMessage.c_str()},
                                                    {"level",   level.c_str()},
                                                    {"logger", sender.c_str()},
                                                });
        call_homeassistant_service("persistent_notification.create", {
                                                    {"title", logMessage.c_str()},
                                                    {"message",   "This is a test notification"},
                                                    {"notification_id", "103"},
                                                }); 
        fire_homeassistant_event("esphome.something_happened", {
      {"my_value", "500"},
    });
}
void SchedulerComponent::on_schedule_recieved(int schedule_device_id, int event_count, std::vector<int> days ,std::vector<int> hours ,std::vector<int> minutes, std::vector<std::string> action) {
    ESP_LOGD(TAG, "Schedule Slot %d  Event Count %d recieved", schedule_device_id, event_count);
    ESP_LOGD(TAG, "Entries Count - Day:%d, Hours: %d Mins:%d, Actions: %d",days.size(),hours.size(), minutes.size(), action.size() );
     send_log_message_to_HA("error","The test message from Controller","ESPHome: boiler_controller");
    // Verify and write data to eeprom
    for (int i = 0; i < event_count; i++) {
    
    }
    // Setup next schedule next event per switch
}
void  SchedulerComponent::on_schedule_erase_recieved(int schedule_device_id){
    ESP_LOGD(TAG, "Schedule Slot %d  erase recieved", schedule_device_id);
    // Mark slot as inactive and clear data
}
void  SchedulerComponent::on_erase_all_schedules_recieved(){
        ESP_LOGD(TAG, " Erase all schedules recieved");
        // Mark all slots as inactive and clear data and disable schedule loop
}
float SchedulerComponent::get_setup_priority() const { return setup_priority::DATA; }

// TODO add switch setting code
//TODO add switch monitoring code
//TODO Add service to accept string schedule per slot from text boxes
}  // namespace scheduler_component
}  // namespace esphome