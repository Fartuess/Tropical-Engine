
add_library(Qt5:: MODULE IMPORTED)

_populate_Sensors_plugin_properties( RELEASE "sensors/qtsensors_dummy.dll")
_populate_Sensors_plugin_properties( DEBUG "sensors/qtsensors_dummyd.dll")

list(APPEND Qt5Sensors_PLUGINS Qt5::)
