// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  Forward_Module.cpp
 * @brief ModuleDescription
 *
 */
// </rtc-template>

#include "Forward_Module.h"
#include <unistd.h>
int i = 0;
int input_id = 1; // 車輪の入力をするモジュールのSSM_ID
int stop_id = 2;  // 停止入力をするモジュールのSSM_ID
bool write_flag;

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char *const forward_module_spec[] =
#else
static const char *forward_module_spec[] =
#endif
    {
        "implementation_id", "Forward_Module",
        "type_name", "Forward_Module",
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
Forward_Module::Forward_Module(RTC::Manager *manager)
    // <rtc-template block="initializer">
    : RTC::DataFlowComponentBase(manager),
      m_up_inIn("up_in", m_up_in),
      m_up_outOut("up_out", m_up_out),
      m_out_leftOut("out_left", m_out_left),
      m_out_rightOut("out_right", m_out_right),
      m_out_stopOut("out_stop", m_out_stop),
      m_out_inputOut("out_input", m_out_input)
// </rtc-template>
{
}

/*!
 * @brief destructor
 */
Forward_Module::~Forward_Module()
{
}

RTC::ReturnCode_t Forward_Module::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("up_in", m_up_inIn);

  // Set OutPort buffer
  addOutPort("up_out", m_up_outOut);
  addOutPort("out_left", m_out_leftOut);
  addOutPort("out_right", m_out_rightOut);
  addOutPort("out_stop", m_out_stopOut);
  addOutPort("out_input", m_out_inputOut);

  // Set service provider to Ports

  // Set service consumers to Ports

  // Set CORBA Service Ports

  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Forward_Module::onFinalize()
{
  return RTC::RTC_OK;
}
*/

// RTC::ReturnCode_t Forward_Module::onStartup(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Forward_Module::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

RTC::ReturnCode_t Forward_Module::onActivated(RTC::UniqueId /*ec_id*/)
{
  write_flag = true;
  // 書き込みのstop_idを教える
  m_out_stop.data = stop_id;
  m_out_stopOut.write();
  // 書き込みのinput_idを教える
  m_out_input.data = input_id;
  m_out_inputOut.write();

  return RTC::RTC_OK;
}

RTC::ReturnCode_t Forward_Module::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}

RTC::ReturnCode_t Forward_Module::onExecute(RTC::UniqueId /*ec_id*/)
{
  // 上位からの命令が来たら
  if (m_up_inIn.isNew())
  {
    m_up_inIn.read();
    if (m_up_in.data == 0) // 0なら停止
    {
      // 右車輪
      m_out_right.data = stop_id;
      // 左車輪
      m_out_left.data = stop_id;
      if (write_flag)
      {
        std::cout << "stop" << std::endl;
        m_out_rightOut.write();
        m_out_leftOut.write();
        // 一度停止したら前進命令があるまで書き込み停止
        write_flag = false;
        sleep(1);
      }

      m_up_out.data = 1; // 停止が完了したことを上位にフィードバック
      m_up_outOut.write();
    }
    else if (m_up_in.data == 1) // 1なら前進
    {
      write_flag = true;
      std::cout << "move" << std::endl;
      // 右車輪
      m_out_right.data = input_id;
      m_out_rightOut.write();
      // 左車輪
      m_out_left.data = input_id;
      m_out_leftOut.write();
    }
  }
  return RTC::RTC_OK;
}

// RTC::ReturnCode_t Forward_Module::onAborting(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Forward_Module::onError(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Forward_Module::onReset(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Forward_Module::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Forward_Module::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

extern "C"
{

  void Forward_ModuleInit(RTC::Manager *manager)
  {
    coil::Properties profile(forward_module_spec);
    manager->registerFactory(profile,
                             RTC::Create<Forward_Module>,
                             RTC::Delete<Forward_Module>);
  }
}
