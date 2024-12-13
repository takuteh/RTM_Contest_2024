// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  Input_0_ssm.cpp
 * @brief ModuleDescription
 *
 */
// </rtc-template>

// c++系
#include <iostream>
#include <iomanip>
// c系
#include <unistd.h>
#include <signal.h>
// その他
#include <ssm.hpp>
#include "intSsm.h"
#include "ssm_handler.h"
// おまじない
using namespace std;

#include "Input_0_ssm.h"

int now_id = -1;
SSMHANDLE sm("write", "create", now_id); // モジュール名、接続モード,ssm_id
int i = 0;

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char *const input_0_ssm_spec[] =
#else
static const char *input_0_ssm_spec[] =
#endif
    {
        "implementation_id", "Input_0_ssm",
        "type_name", "Input_0_ssm",
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
Input_0_ssm::Input_0_ssm(RTC::Manager *manager)
    // <rtc-template block="initializer">
    : RTC::DataFlowComponentBase(manager),
      m_inIn("in", m_in)
// </rtc-template>
{
}

/*!
 * @brief destructor
 */
Input_0_ssm::~Input_0_ssm()
{
}

RTC::ReturnCode_t Input_0_ssm::onInitialize()
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
RTC::ReturnCode_t Input_0_ssm::onFinalize()
{
  return RTC::RTC_OK;
}
*/

// RTC::ReturnCode_t Input_0_ssm::onStartup(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Input_0_ssm::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

RTC::ReturnCode_t Input_0_ssm::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}

RTC::ReturnCode_t Input_0_ssm::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  sm.close_ssm();
  return RTC::RTC_OK;
}

RTC::ReturnCode_t Input_0_ssm::onExecute(RTC::UniqueId /*ec_id*/)
{
  // SSM_IDが来たら
  if (m_inIn.isNew())
  {
    m_inIn.read();

    if (now_id == -1) // 初期入力ならそのままssmの作成
    {
      cout << "first input :" << m_in.data << endl;
      sm.ssm_id = m_in.data;
      sm.create_ssm();
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
  { // 接続済フラグが立っていたら、書き込みを行う
    sm.intSsm->data.num = 0;
    sm.intSsm->write();
  }
  return RTC::RTC_OK;
}

// RTC::ReturnCode_t Input_0_ssm::onAborting(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Input_0_ssm::onError(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Input_0_ssm::onReset(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Input_0_ssm::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Input_0_ssm::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

extern "C"
{

  void Input_0_ssmInit(RTC::Manager *manager)
  {
    coil::Properties profile(input_0_ssm_spec);
    manager->registerFactory(profile,
                             RTC::Create<Input_0_ssm>,
                             RTC::Delete<Input_0_ssm>);
  }
}
