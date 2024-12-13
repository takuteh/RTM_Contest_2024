// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  Turning_Module.cpp
 * @brief ModuleDescription
 *
 */
// </rtc-template>

#include "Turning_Module.h"

#define RST_TIME 150

int i = 0;
int input_id = 3;           // 車輪の入力をするモジュールのSSM_ID
int stop_id = 2;            // 停止入力をするモジュールのSSM_ID
float short_time = 1.2;     // 入力(短)の秒数
float long_time = 2;        // 入力(長)の秒数
time_t last_input_time = 0; // 最後に上位から旋回命令があった時刻
time_t current_time = 0;    // 現在時刻
bool read_flag;
// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char *const turning_module_spec[] =
#else
static const char *turning_module_spec[] =
#endif
    {
        "implementation_id", "Turning_Module",
        "type_name", "Turning_Module",
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
Turning_Module::Turning_Module(RTC::Manager *manager)
    // <rtc-template block="initializer">
    : RTC::DataFlowComponentBase(manager),
      m_up_inIn("up_in", m_up_in),
      m_up_outOut("up_out", m_up_out),
      m_out_rightOut("out_right", m_out_right),
      m_out_leftOut("out_left", m_out_left),
      m_out_stopOut("out_stop", m_out_stop),
      m_out_inputOut("out_input", m_out_input)
// </rtc-template>
{
}

/*!
 * @brief destructor
 */
Turning_Module::~Turning_Module()
{
}

RTC::ReturnCode_t Turning_Module::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("up_in", m_up_inIn);

  // Set OutPort buffer
  addOutPort("up_out", m_up_outOut);
  addOutPort("out_right", m_out_rightOut);
  addOutPort("out_left", m_out_leftOut);
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
RTC::ReturnCode_t Turning_Module::onFinalize()
{
  return RTC::RTC_OK;
}
*/

// RTC::ReturnCode_t Turning_Module::onStartup(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Turning_Module::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }
void Turning_Module::control_wheel(float left_second, float right_second)
{

  // 右車輪
  m_out_right.data = input_id;
  m_out_rightOut.write();
  sleep(right_second);
  // 停止
  m_out_right.data = stop_id;
  m_out_rightOut.write();
  sleep(1.2);
  // 左車輪
  m_out_left.data = input_id;
  m_out_leftOut.write();
  sleep(left_second);
  // 停止
  m_out_left.data = stop_id;
  m_out_leftOut.write();
  sleep(1.2);
}

void Turning_Module::stop_wheel()
{
  m_out_left.data = stop_id;
  m_out_right.data = stop_id;
  m_out_leftOut.write();
  m_out_rightOut.write();
  sleep(3);
}
RTC::ReturnCode_t Turning_Module::onActivated(RTC::UniqueId /*ec_id*/)
{
  // 書き込みのstop_idを教える
  m_out_stop.data = stop_id;
  m_out_stopOut.write();
  // 書き込みのinput_idを教える
  m_out_input.data = input_id;
  m_out_inputOut.write();

  read_flag = true;
  return RTC::RTC_OK;
}

RTC::ReturnCode_t Turning_Module::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}

RTC::ReturnCode_t Turning_Module::onExecute(RTC::UniqueId /*ec_id*/)
{
  // 上位からの旋回命令が来たら
  if (m_up_inIn.isNew())
  {
    m_up_inIn.read();
    if (m_up_in.data == 1)
    {
      if (read_flag)
      {
        read_flag = false;
        last_input_time = time(NULL);
        std::cout << i << std::endl;
        switch (i) // 現在の旋回回数
        {
        case 0: // 1回目 右短・左短
          control_wheel(short_time, short_time);
          // control_wheel(short_time, short_time);
          m_up_out.data = 0;
          read_flag = true;
          break;
        case 1: // 2回目　右短・左長
          control_wheel(short_time, long_time);
          // control_wheel(short_time, long_time);
          m_up_out.data = 0;
          read_flag = true;
          break;
        case 2: // 3回目　右長・左短
          control_wheel(long_time, short_time);
          // control_wheel(long_time, short_time);
          m_up_out.data = 0;
          read_flag = true;
          break;
        case 3: // 4回目　右長・左長
          control_wheel(long_time, long_time);
          // control_wheel(long_time, long_time);
          m_up_out.data = 0;
          read_flag = true;

          break;
        default:
          m_up_out.data = 1;
          read_flag = true;
          break;
        }
        // i++; // 旋回回数をインクリメント
        m_up_outOut.write();
      } // 上位にフィードバック
    }
  }
  // ◯秒経過したらi=0にリセット
  current_time = time(NULL);
  if (current_time - last_input_time >= RST_TIME)
  {
    i = 0;
  }
  return RTC::RTC_OK;
}

// RTC::ReturnCode_t Turning_Module::onAborting(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Turning_Module::onError(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Turning_Module::onReset(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Turning_Module::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Turning_Module::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

extern "C"
{

  void Turning_ModuleInit(RTC::Manager *manager)
  {
    coil::Properties profile(turning_module_spec);
    manager->registerFactory(profile,
                             RTC::Create<Turning_Module>,
                             RTC::Delete<Turning_Module>);
  }
}
