#include "esphome/core/log.h"
#include "scheduler_component.h"



namespace esphome {
namespace scheduler_component {

static const char *TAG = "scheduler_component.component";

void SchedulerComponent::setup() {
    register_service(&SchedulerComponent::on_schedule_recieved, "send_schedule",
                   {"schedule_device_id", "days", "hours","minutes","actions"});
}
void SchedulerComponent::loop() {

}

void SchedulerComponent::dump_config(){
    ESP_LOGCONFIG(TAG, "Scheduler component");
}
void SchedulerComponent:: test(){
                ESP_LOGD(TAG, "Mem size in bytes: %d",this->storage_->length());
                int myValue2 = -366;
                this->storage_->put(10, myValue2); //(location, data)
                int myRead2;
                this->storage_->get(10, myRead2); //location to read, thing to put data into
                ESP_LOGD(TAG, "I read: %d",myRead2 );
}
void SchedulerComponent::on_schedule_recieved(int schedule_device_id, std::vector<int> days ,std::vector<int> hours ,std::vector<int> minutes, std::vector<std::string> action) {
    ESP_LOGD(TAG, "Schedule Slot %d  recieved", schedule_device_id);
    ESP_LOGD(TAG, "Entries Count - Day:%d, Hours: %d Mins:%d, Actions: %d%",days.size(),hours.size(), minutes.size(), action.size() );
}
float SchedulerComponent::get_setup_priority() const { return setup_priority::DATA; }
}  // namespace scheduler_component
}  // namespace esphome