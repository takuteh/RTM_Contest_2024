// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  left_wheelTest.cpp
 * @brief ModuleDescription (test code)
 *
 */
// </rtc-template>

#include "left_wheelTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const left_wheel_spec[] =
#else
static const char* left_wheel_spec[] =
#endif
  {
    "implementation_id", "left_wheelTest",
    "type_name",         "left_wheelTest",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.speed", "50",
    "conf.default.time", "1.0",

    // Widget
    "conf.__widget__.speed", "text",
    "conf.__widget__.time", "text",
    // Constraints

    "conf.__type__.speed", "int",
    "conf.__type__.time", "float",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
left_wheelTest::left_wheelTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inOut("in", m_in)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
left_wheelTest::~left_wheelTest()
{
}



RTC::ReturnCode_t left_wheelTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("in", m_inOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("speed", m_speed, "50");
  bindParameter("time", m_time, "1.0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t left_wheelTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t left_wheelTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t left_wheelTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t left_wheelTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t left_wheelTest::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t left_wheelTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t left_wheelTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t left_wheelTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t left_wheelTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t left_wheelTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t left_wheelTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool left_wheelTest::runTest()
{
    return true;
}


extern "C"
{
 
  void left_wheelTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(left_wheel_spec);
    manager->registerFactory(profile,
                             RTC::Create<left_wheelTest>,
                             RTC::Delete<left_wheelTest>);
  }
  
}
