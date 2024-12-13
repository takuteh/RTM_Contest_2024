// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  right_wheel.cpp
 * @brief ModuleDescription
 *
 */
// </rtc-template>

#include "right_wheel.h"
#include <iostream>
#include <pigpiod_if2.h>
#include <unistd.h>
#include "ssm_handler.h"
#include "intSsm.h"
#include <chrono>
#define F_PIN 19
#define R_PIN 26

#define RANGE 100
#define FREQ 50000

using namespace std;
int pi;
int now_id = -1;
SSMHANDLE sm("right_wheel", "read", now_id); // モジュール名、接続モード,ssm_id
// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char *const right_wheel_spec[] =
#else
static const char *right_wheel_spec[] =
#endif
    {
        "implementation_id", "right_wheel",
        "type_name", "right_wheel",
        "description", "ModuleDescription",
        "version", "1.0.0",
        "vendor", "VenderName",
        "category", "Category",
        "activity_type", "PERIODIC",
        "kind", "DataFlowComponent",
        "max_instance", "1",
        "language", "C++",
        "lang_type", "compile",
        // Configuration variables
        "conf.default.speed", "70",
        "conf.default.time", "0.01",

        // Widget
        "conf.__widget__.speed", "text",
        "conf.__widget__.time", "text",
        // Constraints

        "conf.__type__.speed", "float",
        "conf.__type__.time", "float",

        ""};
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
right_wheel::right_wheel(RTC::Manager *manager)
    // <rtc-template block="initializer">
    : RTC::DataFlowComponentBase(manager),
      m_inIn("in", m_in)
// </rtc-template>
{
}

/*!
 * @brief destructor
 */
right_wheel::~right_wheel()
{
}

RTC::ReturnCode_t right_wheel::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in", m_inIn);

  // Set OutPort buffer

  // Set service provider to Ports

  // Set service consumers to Ports

  // Set CORBA Service Ports

  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("speed", m_speed, "70");
  bindParameter("time", m_time, "0.01");
  // </rtc-template>

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t right_wheel::onFinalize()
{
  return RTC::RTC_OK;
}
*/

// RTC::ReturnCode_t right_wheel::onStartup(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t right_wheel::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

RTC::ReturnCode_t right_wheel::onActivated(RTC::UniqueId /*ec_id*/)
{
  // pigpio初期化
  pi = pigpio_start(0, 0);
  set_mode(pi, F_PIN, PI_OUTPUT);
  set_mode(pi, R_PIN, PI_OUTPUT);

  set_PWM_range(pi, F_PIN, RANGE);
  set_PWM_frequency(pi, F_PIN, FREQ);

  set_PWM_range(pi, R_PIN, RANGE);
  set_PWM_frequency(pi, R_PIN, FREQ);
  return RTC::RTC_OK;
}

RTC::ReturnCode_t right_wheel::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  sm.close_ssm();
  return RTC::RTC_OK;
}

RTC::ReturnCode_t right_wheel::onExecute(RTC::UniqueId /*ec_id*/)
{
  if (m_inIn.isNew())
  {
    m_inIn.read();

    if (now_id == -1) // 初期入力ならそのままssmの作成
    {
      cout << "first input :" << m_in.data << endl;
      sm.ssm_id = m_in.data;
      sm.connect_ssm();
      now_id = m_in.data;
    }
    else if (now_id != -1 && now_id != m_in.data) // 現在のssm_idと入力されたidが違ければ新たにssmの作成
    {
      cout << "change id :" << m_in.data << endl;
      sm.change_ssm(m_in.data);
     auto now=std::chrono::high_resolution_clock::now();
    // エポックからの時間をマイクロ秒単位で取得
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
    
    // マイクロ秒単位で表示
    std::cout << "Current time in microseconds: " << duration.count() << " us" << std::endl;

      now_id = m_in.data;
    }
  }

  if (sm.ssm_con_flag)
  {
    if (sm.intSsm->readNew()) // ssm経由でデータが来たら
    {
      cout << sm.intSsm->data.num << endl;
      if (sm.intSsm->data.num == -1)
      {
        set_PWM_dutycycle(pi, R_PIN, m_speed);
        sleep(m_time);
      }
      else if (sm.intSsm->data.num == 0)
      {
        gpio_write(pi, F_PIN, 0);
        gpio_write(pi, R_PIN, 0);
      }
      else if (sm.intSsm->data.num == 1)
      {
        set_PWM_dutycycle(pi, F_PIN, m_speed);
        sleep(m_time);
      }
    }
  }
  return RTC::RTC_OK;
}

// RTC::ReturnCode_t right_wheel::onAborting(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t right_wheel::onError(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t right_wheel::onReset(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t right_wheel::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t right_wheel::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

extern "C"
{

  void right_wheelInit(RTC::Manager *manager)
  {
    coil::Properties profile(right_wheel_spec);
    manager->registerFactory(profile,
                             RTC::Create<right_wheel>,
                             RTC::Delete<right_wheel>);
  }
}
