#include <zephyr/init.h>
#include <device.h>
#include <logging/log.h>
#include <zmk/behavior.h>
#include <zmk/behavior_binding.h>
#include <zmk/keymap.h>
#include <zmk/event_manager.h>
#include <zmk/events/behavior_state_changed.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/events/position_state_changed.h>
#include <zmk/hid_indicators.h>
#include <zmk/endpoints.h>
#include <zmk/studio.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static int behavior_cmd_init(const struct device *dev) {
    ARG_UNUSED(dev);
    return 0;
}

static int on_cmd_binding_pressed(struct zmk_behavior_binding *binding,
                                  struct zmk_behavior_binding_event event) {
    const char *cmd = binding->param1;

    if (strcmp(cmd, "studio_unlock") == 0) {
        zmk_studio_unlock();
        return ZMK_BEHAVIOR_OPAQUE;
    }

    return ZMK_BEHAVIOR_TRANSPARENT;
}

static int on_cmd_binding_released(struct zmk_behavior_binding *binding,
                                   struct zmk_behavior_binding_event event) {
    return ZMK_BEHAVIOR_TRANSPARENT;
}

const struct behavior_driver_api behavior_cmd_driver_api = {
    .binding_pressed = on_cmd_binding_pressed,
    .binding_released = on_cmd_binding_released,
};

DEVICE_DEFINE(behavior_cmd, "behavior_cmd", behavior_cmd_init, NULL, NULL, NULL,
              POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
              &behavior_cmd_driver_api);
