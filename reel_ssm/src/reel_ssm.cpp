// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  reel_ssm.cpp
 * @brief ModuleDescription
 *
 */
// </rtc-template>

#include "reel_ssm.h"
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
#define RST_TIME 150
int pi;
int sw;
int now_id = -1;
bool reel_flag;
int sw_i=0;
time_t first_sw_time = 0; // 最初にスイッチに反応があった時刻
time_t current_time = 0;    // 現在時刻
SSMHANDLE sm("reel_ssm", "read", now_id); // モジュール名、接続モード,ssm_id
// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char *const reel_ssm_spec[] =
#else
static const char *reel_ssm_spec[] =
#endif
    {
        "implementation_id", "reel_ssm",
        "type_name", "reel_ssm",
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
reel_ssm::reel_ssm(RTC::Manager *manager)
    // <rtc-template block="initializer">
    : RTC::DataFlowComponentBase(manager),
      m_inIn("in", m_in),
      m_outOut("out", m_out)
// </rtc-template>
{
}

/*!
 * @brief destructor
 */
reel_ssm::~reel_ssm()
{
}

RTC::ReturnCode_t reel_ssm::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in", m_inIn);

  // Set OutPort buffer
  addOutPort("out", m_outOut);

  // Set service provider to Ports

  // Set service consumers to Ports

  // Set CORBA Service Ports

  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t reel_ssm::onFinalize()
{
  return RTC::RTC_OK;
}
*/

// RTC::ReturnCode_t reel_ssm::onStartup(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t reel_ssm::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

RTC::ReturnCode_t reel_ssm::onActivated(RTC::UniqueId /*ec_id*/)
{
  sw = 0;
  reel_flag=true;
  // pigpio初期化
  pi = pigpio_start(0, 0);
  set_mode(pi, FIN, PI_OUTPUT);
  set_mode(pi, RIN, PI_OUTPUT);
  set_mode(pi, SW, PI_INPUT);
  return RTC::RTC_OK;
}

RTC::ReturnCode_t reel_ssm::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  sm.close_ssm();
  return RTC::RTC_OK;
}

RTC::ReturnCode_t reel_ssm::onExecute(RTC::UniqueId /*ec_id*/)
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
        // スイッチの状態を取得
        sw = gpio_read(pi, SW);
        if (sw == 0)//一度スイッチに反応があったら巻き取り禁止
        {
if(sw_i==0){//sw=0が初回入力の時の時間を記録
first_sw_time = time(NULL);
}
std::cout<<"sw stop!"<<std::endl;
          reel_flag=false;
          gpio_write(pi, FIN, 1);
          gpio_write(pi, RIN, 1);
          m_out.data = 1;
          m_outOut.write();
//sleep(3);
//解放
//          gpio_write(pi, FIN, 0);
//          gpio_write(pi, RIN, 1);
        }else if(sw==1){//スイッチの反応がなければ巻き取り許可
current_time = time(NULL);
  if (current_time - first_sw_time >= RST_TIME)
  {
    reel_flag=true;
    sw_i=0;
  }
        }
    if (sm.intSsm->readNew()) // ssm経由でデータが来たら
    {
      std::cout << sm.intSsm->data.num << std::endl;
      // 入力データが1なら巻き取り
      if (sm.intSsm->data.num == 1)
      {
        if(reel_flag==true){
          // 巻き取り
          gpio_write(pi, FIN, 1);
          gpio_write(pi, RIN, 0);
        }        
      }

      // 入力データが0なら停止
      if (sm.intSsm->data.num == 0)
      {
        gpio_write(pi, FIN, 1);
        gpio_write(pi, RIN, 1);
        m_out.data = 1;
        m_outOut.write();
      }
    }
  
  }
  return RTC::RTC_OK;
}

// RTC::ReturnCode_t reel_ssm::onAborting(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t reel_ssm::onError(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t reel_ssm::onReset(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t reel_ssm::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t reel_ssm::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

extern "C"
{

  void reel_ssmInit(RTC::Manager *manager)
  {
    coil::Properties profile(reel_ssm_spec);
    manager->registerFactory(profile,
                             RTC::Create<reel_ssm>,
                             RTC::Delete<reel_ssm>);
  }
}
