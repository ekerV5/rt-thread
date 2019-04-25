#include "rtthread.h"
#include "drv_gpio.h"
#include "button.h"

#define TASK_BTN_NAME              "tbutton"
#define TASK_BTN_STACK_SIZE        512
#define TASK_BTN_PRIORITY          3
#define TASK_BTN_TICK              10

#define PIN_KEY0                   GET_PIN(D, 10)
#define PIN_KEY1                   GET_PIN(D, 9)
#define PIN_KEY2                   GET_PIN(D, 8)
#define PIN_WKUP                   GET_PIN(C, 13)

#define BTN_ON                     1
#define BTN_OFF                    0

static rt_thread_t tid_btn = RT_NULL;
static Button_t btn0, btn1, btn2, btn_wkup;

static void hw_init_btn(void)
{
    rt_pin_mode(PIN_KEY0, PIN_MODE_INPUT);
    rt_pin_mode(PIN_KEY1, PIN_MODE_INPUT);
    rt_pin_mode(PIN_KEY2, PIN_MODE_INPUT);
    rt_pin_mode(PIN_WKUP, PIN_MODE_INPUT);
}

static rt_uint8_t read_btn0_level(void)
{
    return (rt_uint8_t)rt_pin_read(PIN_KEY0);
}

static void btn0_dowm_cb(void * param)
{
    rt_kprintf("btn0 click\n");
}

static void btn0_double_cb(void * param)
{
    rt_kprintf("btn0 double click\n");
}

static void btn0_continuos_cb(void * param)
{
    rt_kprintf("btn0 continuous press\n");
}

static void btn0_continuos_free_cb(void * param)
{
    rt_kprintf("btn0 continuous press free\n");
}

static void btn0_long_cb(void * param)
{
    rt_kprintf("btn0 long press\n");
}

static rt_uint8_t read_btn1_level(void)
{
    return (rt_uint8_t)rt_pin_read(PIN_KEY1);
}

static void btn1_dowm_cb(void * param)
{
    rt_kprintf("btn1 click\n");
}

static void btn1_double_cb(void * param)
{
    rt_kprintf("btn1 double click\n");
}

static void btn1_continuos_cb(void * param)
{
    rt_kprintf("btn1 continuous press\n");
}

static void btn1_continuos_free_cb(void * param)
{
    rt_kprintf("btn1 continuous press free\n");
}

static void btn1_long_cb(void * param)
{
    rt_kprintf("btn1 long press\n");
}

static rt_uint8_t read_btn2_level(void)
{
    return (rt_uint8_t)rt_pin_read(PIN_KEY2);
}

static void btn2_dowm_cb(void * param)
{
    rt_kprintf("btn2 click\n");
}

static void btn2_double_cb(void * param)
{
    rt_kprintf("btn2 double click\n");
}

static void btn2_continuos_cb(void * param)
{
    rt_kprintf("btn2 continuous press\n");
}

static void btn2_continuos_free_cb(void * param)
{
    rt_kprintf("btn2 continuous press free\n");
}

static void btn2_long_cb(void * param)
{
    rt_kprintf("btn2 long press\n");
}

static rt_uint8_t read_btn_wkup_level(void)
{
    return (rt_uint8_t)rt_pin_read(PIN_WKUP);
}

static void btn_wkup_dowm_cb(void * param)
{
    rt_kprintf("btn_wkup click\n");
}

static void btn_wkup_double_cb(void * param)
{
    rt_kprintf("btn_wkup double click\n");
}

static void btn_wkup_continuos_cb(void * param)
{
    rt_kprintf("btn_wkup continuous press\n");
}

static void btn_wkup_continuos_free_cb(void * param)
{
    rt_kprintf("btn_wkup continuous press free\n");
}

static void btn_wkup_long_cb(void * param)
{
    rt_kprintf("btn_wkup long press\n");
}

static void task_button_entry(void * param)
{
    hw_init_btn();

    Button_Create("key0", &btn0, read_btn0_level, BTN_OFF);
    Button_Attach(&btn0, BUTTON_DOWM, btn0_dowm_cb);                     //Click
    Button_Attach(&btn0, BUTTON_DOUBLE, btn0_double_cb);                 //Double click
    Button_Attach(&btn0, BUTTON_CONTINUOS, btn0_continuos_cb);           //Press continuously
    Button_Attach(&btn0, BUTTON_CONTINUOS_FREE, btn0_continuos_free_cb); //Press continuously free
    Button_Attach(&btn0, BUTTON_LONG, btn0_long_cb);                     //Long press

    Button_Create("key1", &btn1, read_btn1_level, BTN_OFF);
    Button_Attach(&btn1, BUTTON_DOWM, btn1_dowm_cb);                     //Click
    Button_Attach(&btn1, BUTTON_DOUBLE, btn1_double_cb);                 //Double click
    Button_Attach(&btn1, BUTTON_CONTINUOS, btn1_continuos_cb);           //Press continuously
    Button_Attach(&btn1, BUTTON_CONTINUOS_FREE, btn1_continuos_free_cb); //Press continuously free
    Button_Attach(&btn1, BUTTON_LONG, btn1_long_cb);                     //Long press

    Button_Create("key2", &btn2, read_btn2_level, BTN_OFF);
    Button_Attach(&btn2, BUTTON_DOWM, btn2_dowm_cb);                     //Click
    Button_Attach(&btn2, BUTTON_DOUBLE, btn2_double_cb);                 //Double click
    Button_Attach(&btn2, BUTTON_CONTINUOS, btn2_continuos_cb);           //Press continuously
    Button_Attach(&btn2, BUTTON_CONTINUOS_FREE, btn2_continuos_free_cb); //Press continuously free
    Button_Attach(&btn2, BUTTON_LONG, btn2_long_cb);                     //Long press

    Button_Create("wk_up", &btn_wkup, read_btn_wkup_level, BTN_ON);
    Button_Attach(&btn_wkup, BUTTON_DOWM, btn_wkup_dowm_cb);                     //Click
    Button_Attach(&btn_wkup, BUTTON_DOUBLE, btn_wkup_double_cb);                 //Double click
    Button_Attach(&btn_wkup, BUTTON_CONTINUOS, btn_wkup_continuos_cb);           //Press continuously
    Button_Attach(&btn_wkup, BUTTON_CONTINUOS_FREE, btn_wkup_continuos_free_cb); //Press continuously free
    Button_Attach(&btn_wkup, BUTTON_LONG, btn_wkup_long_cb);                     //Long press

    Get_Button_Event(&btn0);
    Get_Button_Event(&btn1);
    Get_Button_Event(&btn2);
    Get_Button_Event(&btn_wkup);

    while(1)                            
    {
        Button_Process(); //Need to call the button handler function periodically
        rt_thread_delay(20);
    }
}

void task_button_init(void)
{
    tid_btn = rt_thread_create(TASK_BTN_NAME, task_button_entry, NULL, TASK_BTN_STACK_SIZE, TASK_BTN_PRIORITY, TASK_BTN_TICK);
    if (tid_btn != RT_NULL)
    {
        if (rt_thread_startup(tid_btn) == RT_EOK)
        {
            rt_kprintf("Button thread started.\n");
        }
    }
}
MSH_CMD_EXPORT(task_button_init, task_button_init);

void task_button_uninit(void)
{
    rt_err_t ret = rt_thread_delete(tid_btn);
    if (ret != RT_EOK)
    {
        rt_kprintf("Button thread delete error.\n");
    }

    Button_Delete(&btn0);
    Button_Delete(&btn1);
    Button_Delete(&btn2);
    Button_Delete(&btn_wkup);
}