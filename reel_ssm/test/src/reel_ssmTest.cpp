// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  reel_ssmTest.cpp
 * @brief ModuleDescription (test code)
 *
 */
// </rtc-template>

#include "reel_ssmTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const reel_ssm_spec[] =
#else
static const char* reel_ssm_spec[] =
#endif
  {
    "implementation_id", "reel_ssmTest",
    "type_name",         "reel_ssmTest",
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
reel_ssmTest::reel_ssmTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inOut("in", m_in),
    m_outIn("out", m_out)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
reel_ssmTest::~reel_ssmTest()
{
}



RTC::ReturnCode_t reel_ssmTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("out", m_outIn);
  
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
RTC::ReturnCode_t reel_ssmTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t reel_ssmTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t reel_ssmTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t reel_ssmTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t reel_ssmTest::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t reel_ssmTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t reel_ssmTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t reel_ssmTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t reel_ssmTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t reel_ssmTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t reel_ssmTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool reel_ssmTest::runTest()
{
    return true;
}


extern "C"
{
 
  void reel_ssmTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(reel_ssm_spec);
    manager->registerFactory(profile,
                             RTC::Create<reel_ssmTest>,
                             RTC::Delete<reel_ssmTest>);
  }
  
}
