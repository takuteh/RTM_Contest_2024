// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  Jump_Module.cpp
 * @brief ModuleDescription
 *
 */
// </rtc-template>

#include "Jump_Module.h"

int input_id = 1; // 車輪の入力をするモジュールのSSM_ID
int stop_id = 2;  // 停止入力をするモジュールのSSM_ID
// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char *const jump_module_spec[] =
#else
static const char *jump_module_spec[] =
#endif
    {
        "implementation_id", "Jump_Module",
        "type_name", "Jump_Module",
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
Jump_Module::Jump_Module(RTC::Manager *manager)
    // <rtc-template block="initializer">
    : RTC::DataFlowComponentBase(manager),
      m_up_inIn("up_in", m_up_in),
      m_in_reelIn("in_reel", m_in_reel),
      m_up_outOut("up_out", m_up_out),
      m_out_jumpOut("out_jump", m_out_jump),
      m_out_reelOut("out_reel", m_out_reel),
      m_out_stopOut("out_stop", m_out_stop),
      m_out_inputOut("out_input", m_out_input)
// </rtc-template>
{
}

/*!
 * @brief destructor
 */
Jump_Module::~Jump_Module()
{
}

RTC::ReturnCode_t Jump_Module::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("up_in", m_up_inIn);
  addInPort("in_reel", m_in_reelIn);

  // Set OutPort buffer
  addOutPort("up_out", m_up_outOut);
  addOutPort("out_jump", m_out_jumpOut);
  addOutPort("out_reel", m_out_reelOut);
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
RTC::ReturnCode_t Jump_Module::onFinalize()
{
  return RTC::RTC_OK;
}
*/

// RTC::ReturnCode_t Jump_Module::onStartup(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Jump_Module::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

RTC::ReturnCode_t Jump_Module::onActivated(RTC::UniqueId /*ec_id*/)
{
  // 書き込みのstop_idを教える
  m_out_stop.data = stop_id;
  m_out_stopOut.write();
  // 書き込みのinput_idを教える
  m_out_input.data = input_id;
  m_out_inputOut.write();

  return RTC::RTC_OK;
}

RTC::ReturnCode_t Jump_Module::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}

RTC::ReturnCode_t Jump_Module::onExecute(RTC::UniqueId /*ec_id*/)
{
  // 上位からの命令が来たら
  if (m_up_inIn.isNew())
  {
    m_up_inIn.read();
    if (m_up_in.data == 0) // 0なら緊急停止
    {
      // 糸を巻くのを停止
      m_out_reel.data = stop_id;
      m_out_reelOut.write();
      sleep(3);
      // 解放
      m_out_jump.data = input_id;
      m_out_jumpOut.write();
    }
    else if (m_up_in.data == 1)
    {
      while (1) // 巻き取りモジュールから通知があるまで
      {
        // 糸を巻く
        m_out_reel.data = input_id;
        m_out_reelOut.write();
        m_in_reelIn.read();
        if (m_in_reel.data == 1)
        {
          std::cout << "get feedback from reel!" << std::endl;
          break;
        }
      }
      // 糸を巻くのを停止
      // m_out_reel.data = stop_id;
      // m_out_reelOut.write();
      // sleep(3);
      // 解放
      m_out_jump.data = input_id;
      m_out_jumpOut.write();
      sleep(3);
      m_out_jump.data = stop_id;
      m_out_jumpOut.write();
      m_up_out.data = 1; // 跳躍が完了したことを上位にフィードバック
      m_up_outOut.write();
    }
  }
  return RTC::RTC_OK;
}

// RTC::ReturnCode_t Jump_Module::onAborting(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Jump_Module::onError(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Jump_Module::onReset(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Jump_Module::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Jump_Module::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

extern "C"
{

  void Jump_ModuleInit(RTC::Manager *manager)
  {
    coil::Properties profile(jump_module_spec);
    manager->registerFactory(profile,
                             RTC::Create<Jump_Module>,
                             RTC::Delete<Jump_Module>);
  }
}
