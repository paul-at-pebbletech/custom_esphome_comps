import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.components import ext_eeprom_component

DEPENDENCIES = ['api']

CONF_EXT_EEPROM ='storage'
CONF_EXT_EEPROM_OFFSET ='storage_offset'
CONF_SCHEDULE_SWITCH_MAX_EVENTS = 'number_events_per_switch'
CONF_SCHEDULE_SWITCH_CNT = 'number_of_switches'
scheduler_component_ns = cg.esphome_ns.namespace('scheduler_component')
SchedulerComponent = scheduler_component_ns.class_('SchedulerComponent', cg.Component)
# TODO validate the slot data in final validate routine
# TODO Validate data is in real range
CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SchedulerComponent),
        cv.Required(CONF_EXT_EEPROM): cv.use_id(ext_eeprom_component.ExtEepromComponent),
        cv.Required(CONF_EXT_EEPROM_OFFSET): cv.uint16_t,
        cv.Required(CONF_SCHEDULE_SWITCH_CNT): cv.uint8_t,
        cv.Required(CONF_SCHEDULE_SWITCH_MAX_EVENTS): cv.uint16_t,       
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    store = await cg.get_variable(config[CONF_EXT_EEPROM])
    cg.add(var.set_storage(store))
    cg.add(var.set_Storage_Offset(config[CONF_EXT_EEPROM_OFFSET]))
    cg.add(var.set_Switch_Count(config[CONF_SCHEDULE_SWITCH_CNT]))
    cg.add(var.set_Events_Per_Switch(config[CONF_SCHEDULE_SWITCH_MAX_EVENTS]))