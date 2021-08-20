idf_component_register(
    SRCS mcp4725_t.c
    INCLUDE_DIRS .
    REQUIRES i2cdev log esp_idf_lib_helpers
)
