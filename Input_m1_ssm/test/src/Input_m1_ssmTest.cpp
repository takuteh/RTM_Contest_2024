// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  Input_m1_ssmTest.cpp
 * @brief ModuleDescription (test code)
 *
 */
// </rtc-template>

#include "Input_m1_ssmTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const input_m1_ssm_spec[] =
#else
static const char* input_m1_ssm_spec[] =
#endif
  {
    "implementation_id", "Input_m1_ssmTest",
    "type_name",         "Input_m1_ssmTest",
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
Input_m1_ssmTest::Input_m1_ssmTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inOut("in", m_in)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Input_m1_ssmTest::~Input_m1_ssmTest()
{
}



RTC::ReturnCode_t Input_m1_ssmTest::onInitialize()
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
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Input_m1_ssmTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t Input_m1_ssmTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Input_m1_ssmTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t Input_m1_ssmTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Input_m1_ssmTest::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Input_m1_ssmTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t Input_m1_ssmTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Input_m1_ssmTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Input_m1_ssmTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Input_m1_ssmTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Input_m1_ssmTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool Input_m1_ssmTest::runTest()
{
    return true;
}


extern "C"
{
 
  void Input_m1_ssmTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(input_m1_ssm_spec);
    manager->registerFactory(profile,
                             RTC::Create<Input_m1_ssmTest>,
                             RTC::Delete<Input_m1_ssmTest>);
  }
  
}
