// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  jump_ssmTest.cpp
 * @brief ModuleDescription (test code)
 *
 */
// </rtc-template>

#include "jump_ssmTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const jump_ssm_spec[] =
#else
static const char* jump_ssm_spec[] =
#endif
  {
    "implementation_id", "jump_ssmTest",
    "type_name",         "jump_ssmTest",
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
jump_ssmTest::jump_ssmTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inOut("in", m_in)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
jump_ssmTest::~jump_ssmTest()
{
}



RTC::ReturnCode_t jump_ssmTest::onInitialize()
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
RTC::ReturnCode_t jump_ssmTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t jump_ssmTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t jump_ssmTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t jump_ssmTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t jump_ssmTest::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t jump_ssmTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t jump_ssmTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t jump_ssmTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t jump_ssmTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t jump_ssmTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t jump_ssmTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool jump_ssmTest::runTest()
{
    return true;
}


extern "C"
{
 
  void jump_ssmTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(jump_ssm_spec);
    manager->registerFactory(profile,
                             RTC::Create<jump_ssmTest>,
                             RTC::Delete<jump_ssmTest>);
  }
  
}
