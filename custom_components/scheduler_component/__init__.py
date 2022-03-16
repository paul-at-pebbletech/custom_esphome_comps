import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.components import ext_eeprom_component

DEPENDENCIES = ['api']

CONF_EXT_EEPROM ='storage'
CONF_EXT_EEPROM_OFFSET ='storage_offset'
scheduler_component_ns = cg.esphome_ns.namespace('scheduler_component')
SchedulerComponent = scheduler_component_ns.class_('SchedulerComponent', cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SchedulerComponent),
        cv.Required(CONF_EXT_EEPROM): cv.use_id(ext_eeprom_component.ExtEepromComponent),
        cv.Required(CONF_EXT_EEPROM_OFFSET): cv.uint16_t,
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    store = await cg.get_variable(config[CONF_EXT_EEPROM])
    cg.add(var.set_storage(store))
    cg.add(var.set_Storage_Offset(config[CONF_EXT_EEPROM_OFFSET]))