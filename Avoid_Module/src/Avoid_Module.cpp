// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  Avoid_Module.cpp
 * @brief ModuleDescription
 *
 */
// </rtc-template>

#include "Avoid_Module.h"
#include <coil-2.0/coil/Timer.h>

#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <numeric>
#include <map>

bool forward_flag;
bool input_flag;
std::string selected_motion = "";
// パターンとその確率（合計が1.0でない場合も可）
std::vector<std::string> patterns = {"Turn", "Back", "Jump"};
std::vector<double> probabilities = {4.0, 4.0, 2.0}; // 正規化される
int count = 0;
// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char *const avoid_module_spec[] =
#else
static const char *avoid_module_spec[] =
#endif
    {
        "implementation_id", "Avoid_Module",
        "type_name", "Avoid_Module",
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
Avoid_Module::Avoid_Module(RTC::Manager *manager)
    // <rtc-template block="initializer">
    : RTC::DataFlowComponentBase(manager),
      m_in_distance_leftIn("in_distance_left", m_in_distance_left),
      m_in_forwardIn("in_forward", m_in_forward),
      m_in_turnIn("in_turn", m_in_turn),
      m_in_jumpIn("in_jump", m_in_jump),
      m_in_distance_rightIn("in_distance_right", m_in_distance_right),
      m_in_envIn("in_env", m_in_env),
      m_out_forwardOut("out_forward", m_out_forward),
      m_out_turnOut("out_turn", m_out_turn),
      m_out_jumpOut("out_jump", m_out_jump)
// </rtc-template>
{
}

/*!
 * @brief destructor
 */
Avoid_Module::~Avoid_Module()
{
}

RTC::ReturnCode_t Avoid_Module::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in_distance_left", m_in_distance_leftIn);
  addInPort("in_forward", m_in_forwardIn);
  addInPort("in_turn", m_in_turnIn);
  addInPort("in_jump", m_in_jumpIn);
  addInPort("in_distance_right", m_in_distance_rightIn);
  addInPort("in_env", m_in_envIn);

  // Set OutPort buffer
  addOutPort("out_forward", m_out_forwardOut);
  addOutPort("out_turn", m_out_turnOut);
  addOutPort("out_jump", m_out_jumpOut);

  // Set service provider to Ports

  // Set service consumers to Ports

  // Set CORBA Service Ports

  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Avoid_Module::onFinalize()
{
  return RTC::RTC_OK;
}
*/

// RTC::ReturnCode_t Avoid_Module::onStartup(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Avoid_Module::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }
// 確率を正規化する関数
std::vector<double> Avoid_Module::normalize_probabilities(const std::vector<double> &probabilities)
{
  double sum = std::accumulate(probabilities.begin(), probabilities.end(), 0.0);
  std::vector<double> normalized;
  for (double p : probabilities)
  {
    normalized.push_back(p / sum);
  }
  return normalized;
}

// 重み付き選択を行う関数
std::string Avoid_Module::weighted_choice(const std::vector<std::string> &patterns, std::vector<double> probabilities)
{
  // 確率を正規化
  probabilities = normalize_probabilities(probabilities);

  // 累積和の計算
  std::vector<double> cumulative_sum(probabilities.size()); // 累積和格納用配列初期化
  std::partial_sum(probabilities.begin(), probabilities.end(), cumulative_sum.begin());

  // std::random_device rd;                                      // 乱数デバイスを生成
  // double random_value = static_cast<double>(rd()) / rd.max(); // 0.0から1.0の範囲のランダムな浮動小数点数を生成
  //  乱数デバイスと分布を初期化
  static std::random_device rd;                                // 乱数デバイス
  static std::mt19937 gen(rd());                               // メルセンヌ・ツイスタの乱数エンジン
  static std::uniform_real_distribution<double> dis(0.0, 1.0); // 0.0から1.0の範囲の分布

  // return dis(gen); // 乱数を生成して返す

  // 累積確率の範囲に基づいて選択
  for (size_t i = 0; i < cumulative_sum.size(); ++i)
  {
    if (dis(gen) < cumulative_sum[i])
    {
      return patterns[i];
    }
  }
  return patterns.back(); // 念のため、最後の要素を返す
}

void Avoid_Module::Stop_Forward()
{

  // 前進モジュールに停止命令
  std::cout << "stop forward" << std::endl;
  m_out_forward.data = 0;
  m_out_forwardOut.write();
  // 前進禁止
  forward_flag = false;
  sleep(10);
}

RTC::ReturnCode_t Avoid_Module::onActivated(RTC::UniqueId /*ec_id*/)
{
  forward_flag = true;
  input_flag = true;
  return RTC::RTC_OK;
}

RTC::ReturnCode_t Avoid_Module::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}

RTC::ReturnCode_t Avoid_Module::onExecute(RTC::UniqueId /*ec_id*/)
{
  //  std::cout << "flag=" << forward_flag << std::endl;
  //  前進モジュールに命令
  if (forward_flag == true)
  {
    std::cout << "forward" << std::endl;
    m_out_forward.data = 1;
    m_out_forwardOut.write();
  }

  // 距離センサーから入力が来たら
  if (m_in_distance_leftIn.isNew() || m_in_distance_rightIn.isNew())
  {
    m_in_distance_leftIn.read();
    m_in_distance_rightIn.read();

    // 5cm以下だったら、旋回・跳躍に切り替え
    if (m_in_distance_left.data < 5 || m_in_distance_right.data < 5)
    {
      if (input_flag) // 処理するか判断
      {
        std::cout << "next back!" << std::endl;
        input_flag = false; // 他センサの処理を禁止
        Stop_Forward();
        //  後退確率を100%にする
        probabilities[0] = 0.0;
        probabilities[1] = 1.0;
        probabilities[2] = 0.0;
      }
    }
  }

  // 環境評価でスタック判断なら（前進モジュール停止命令）
  if (m_in_envIn.isNew())
  {
    m_in_envIn.read();

    if (m_in_env.data == 2)
    {
      if (input_flag) // 処理するか判断
      {
        std::cout << "next jump!" << std::endl;
        input_flag = false; // 他センサの処理を禁止
        Stop_Forward();
        //  跳躍確率を100%
        probabilities[0] = 0.0;
        probabilities[1] = 0.0;
        probabilities[2] = 1.0;
      }
    }
  }

  if (m_in_forwardIn.isNew()) // 前進モジュールからのフィードバック待ち
  {
    std::cout << "forward in" << std::endl;
    m_in_forwardIn.read();
    if (m_in_forward.data == 1) // 停止完了の合図
    {
      // 行動を選択
      selected_motion = weighted_choice(patterns, probabilities);
    }
  }

  // 実行
  if (selected_motion == "Jump")
  {
    std::cout << "Jump" << std::endl;
    m_out_jump.data = 1;
    m_out_jumpOut.write();
    selected_motion = "";
  }
  else if (selected_motion == "Back")
  {
    std::cout << "Back" << std::endl;
    m_out_turn.data = 1;
    m_out_turnOut.write();
    selected_motion = "";
  }

  if (m_in_turnIn.isNew()) // 旋回モジュールからのフィードバック待ち
  {
    m_in_turnIn.read();
    if (m_in_turn.data == 0) // 旋回完了の合図
    {
      std::cout << "turn success!" << std::endl;
      sleep(3);

      // 前進許可
      forward_flag = true;
      input_flag = true;
    }
  }

  if (m_in_jumpIn.isNew()) // 跳躍モジュールからのフィードバック待ち
  {
    m_in_jumpIn.read();
    if (m_in_jump.data == 1) // 跳躍完了の合図
    {
      std::cout << "jump success!" << std::endl;
      sleep(3);

      // 前進許可
      forward_flag = true;
      input_flag = true;
    }
  }

  return RTC::RTC_OK;
}

// RTC::ReturnCode_t Avoid_Module::onAborting(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Avoid_Module::onError(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Avoid_Module::onReset(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Avoid_Module::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Avoid_Module::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

extern "C"
{

  void Avoid_ModuleInit(RTC::Manager *manager)
  {
    coil::Properties profile(avoid_module_spec);
    manager->registerFactory(profile,
                             RTC::Create<Avoid_Module>,
                             RTC::Delete<Avoid_Module>);
  }
}
