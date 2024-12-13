// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  jump_ssm.cpp
 * @brief ModuleDescription
 *
 */
// </rtc-template>

#include "jump_ssm.h"
// c++系
#include <iostream>
#include <iomanip>
// c系
#include <unistd.h>
#include <signal.h>
// その他
#include <pigpiod_if2.h>
#include <ssm.hpp>
#include "intSsm.h"
#include "ssm_handler.h"
// おまじない
using namespace std;

#define RIN 9
#define FIN 10
#define SW 6

int now_id = -1;
int pi;
SSMHANDLE sm("jump_ssm", "read", now_id); // モジュール名、接続モード,ssm_id
// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char *const jump_ssm_spec[] =
#else
static const char *jump_ssm_spec[] =
#endif
    {
        "implementation_id", "jump_ssm",
        "type_name", "jump_ssm",
        "description", "ModuleDescription",
        "version", "1.0.0",
        "vendor", "VenderName",
        "category", "Category",
        "activity_type", "PERIODIC",
        "kind", "DataFlowComponent",
        "max_instance", "1",
        "language", "C++",
        "lang_type", "compile",
        ""};
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
jump_ssm::jump_ssm(RTC::Manager *manager)
    // <rtc-template block="initializer">
    : RTC::DataFlowComponentBase(manager),
      m_inIn("in", m_in)
// </rtc-template>
{
}

/*!
 * @brief destructor
 */
jump_ssm::~jump_ssm()
{
}

RTC::ReturnCode_t jump_ssm::onInitialize()
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
  // </rtc-template>

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t jump_ssm::onFinalize()
{
  return RTC::RTC_OK;
}
*/

// RTC::ReturnCode_t jump_ssm::onStartup(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t jump_ssm::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

RTC::ReturnCode_t jump_ssm::onActivated(RTC::UniqueId /*ec_id*/)
{
  // pigpio初期化
  pi = pigpio_start(0, 0);
  set_mode(pi, FIN, PI_OUTPUT);
  set_mode(pi, RIN, PI_OUTPUT);
  set_mode(pi, SW, PI_INPUT);
  return RTC::RTC_OK;
}

RTC::ReturnCode_t jump_ssm::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  sm.close_ssm();
  return RTC::RTC_OK;
}

RTC::ReturnCode_t jump_ssm::onExecute(RTC::UniqueId /*ec_id*/)
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
      now_id = m_in.data;
    }
  }

  if (sm.ssm_con_flag)
  {
    if (sm.intSsm->readNew()) // ssm経由でデータが来たら
    {
      // 解放
      if (sm.intSsm->data.num == 0)
      {
        // 停止
        gpio_write(pi, FIN, 1);
        gpio_write(pi, RIN, 1);
      }
      else if (sm.intSsm->data.num == 1)
      {
        gpio_write(pi, FIN, 0);
        gpio_write(pi, RIN, 1);
        sleep(3);
        // 停止
        gpio_write(pi, FIN, 1);
        gpio_write(pi, RIN, 1);
      }
    }
  }
  return RTC::RTC_OK;
}

// RTC::ReturnCode_t jump_ssm::onAborting(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t jump_ssm::onError(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t jump_ssm::onReset(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t jump_ssm::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t jump_ssm::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

extern "C"
{

  void jump_ssmInit(RTC::Manager *manager)
  {
    coil::Properties profile(jump_ssm_spec);
    manager->registerFactory(profile,
                             RTC::Create<jump_ssm>,
                             RTC::Delete<jump_ssm>);
  }
}
