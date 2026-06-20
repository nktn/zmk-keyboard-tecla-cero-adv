/*
 * tecla-cero タイピング中ポインタ抑制 Input Processor
 *
 * 直近のキー押下から require-prior-idle-ms 経過するまでの間、
 * ポインタイベント（トラックボール等）を破棄する。
 * 打鍵時の意図しないカーソル移動を防ぐ（パームリジェクション相当）。
 */

#define DT_DRV_COMPAT zmk_input_processor_typing_suppress

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/atomic.h>

#include <drivers/input_processor.h>

#include <zmk/event_manager.h>
#include <zmk/events/position_state_changed.h>

static atomic_t typing_suppress_last_press_ms;

struct typing_suppress_config {
    uint32_t require_prior_idle_ms;
};

static int typing_suppress_handle_event(const struct device *dev,
                                        struct input_event *event,
                                        uint32_t param1, uint32_t param2,
                                        struct zmk_input_processor_state *state) {
    ARG_UNUSED(event);
    ARG_UNUSED(param1);
    ARG_UNUSED(param2);
    ARG_UNUSED(state);

    const struct typing_suppress_config *cfg = dev->config;
    uint32_t last = (uint32_t)atomic_get(&typing_suppress_last_press_ms);
    if (last == 0) {
        return ZMK_INPUT_PROC_CONTINUE;
    }
    uint32_t elapsed = k_uptime_get_32() - last;
    if (elapsed < cfg->require_prior_idle_ms) {
        return ZMK_INPUT_PROC_STOP;
    }
    return ZMK_INPUT_PROC_CONTINUE;
}

static int typing_suppress_init(const struct device *dev) {
    ARG_UNUSED(dev);
    return 0;
}

static int typing_suppress_position_listener(const zmk_event_t *eh) {
    const struct zmk_position_state_changed *ev = as_zmk_position_state_changed(eh);
    if (ev != NULL && ev->state) {
        atomic_set(&typing_suppress_last_press_ms,
                   (atomic_val_t)k_uptime_get_32());
    }
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(typing_suppress, typing_suppress_position_listener);
ZMK_SUBSCRIPTION(typing_suppress, zmk_position_state_changed);

static const struct zmk_input_processor_driver_api typing_suppress_driver_api = {
    .handle_event = typing_suppress_handle_event,
};

#define TYPING_SUPPRESS_INST(n)                                                       \
    static const struct typing_suppress_config typing_suppress_config_##n = {         \
        .require_prior_idle_ms = DT_INST_PROP_OR(n, require_prior_idle_ms, 150),      \
    };                                                                                \
    DEVICE_DT_INST_DEFINE(n, typing_suppress_init, NULL, NULL,                        \
                          &typing_suppress_config_##n,                                \
                          POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,           \
                          &typing_suppress_driver_api);

DT_INST_FOREACH_STATUS_OKAY(TYPING_SUPPRESS_INST)
