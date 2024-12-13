// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  Avoid_ModuleTest.cpp
 * @brief ModuleDescription (test code)
 *
 */
// </rtc-template>

#include "Avoid_ModuleTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const avoid_module_spec[] =
#else
static const char* avoid_module_spec[] =
#endif
  {
    "implementation_id", "Avoid_ModuleTest",
    "type_name",         "Avoid_ModuleTest",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Avoid_ModuleTest::Avoid_ModuleTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_in_distance_leftOut("in_distance_left", m_in_distance_left),
    m_in_forwardOut("in_forward", m_in_forward),
    m_in_turnOut("in_turn", m_in_turn),
    m_in_jumpOut("in_jump", m_in_jump),
    m_in_distance_rightOut("in_distance_right", m_in_distance_right),
    m_in_envOut("in_env", m_in_env),
    m_out_forwardIn("out_forward", m_out_forward),
    m_out_turnIn("out_turn", m_out_turn),
    m_out_jumpIn("out_jump", m_out_jump)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Avoid_ModuleTest::~Avoid_ModuleTest()
{
}



RTC::ReturnCode_t Avoid_ModuleTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("out_forward", m_out_forwardIn);
  addInPort("out_turn", m_out_turnIn);
  addInPort("out_jump", m_out_jumpIn);
  
  // Set OutPort buffer
  addOutPort("in_distance_left", m_in_distance_leftOut);
  addOutPort("in_forward", m_in_forwardOut);
  addOutPort("in_turn", m_in_turnOut);
  addOutPort("in_jump", m_in_jumpOut);
  addOutPort("in_distance_right", m_in_distance_rightOut);
  addOutPort("in_env", m_in_envOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Avoid_ModuleTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t Avoid_ModuleTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Avoid_ModuleTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t Avoid_ModuleTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Avoid_ModuleTest::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Avoid_ModuleTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t Avoid_ModuleTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Avoid_ModuleTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Avoid_ModuleTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Avoid_ModuleTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Avoid_ModuleTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool Avoid_ModuleTest::runTest()
{
    return true;
}


extern "C"
{
 
  void Avoid_ModuleTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(avoid_module_spec);
    manager->registerFactory(profile,
                             RTC::Create<Avoid_ModuleTest>,
                             RTC::Delete<Avoid_ModuleTest>);
  }
  
}
