// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  Distance_rightTest.cpp
 * @brief ModuleDescription (test code)
 *
 */
// </rtc-template>

#include "Distance_rightTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const distance_right_spec[] =
#else
static const char* distance_right_spec[] =
#endif
  {
    "implementation_id", "Distance_rightTest",
    "type_name",         "Distance_rightTest",
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
Distance_rightTest::Distance_rightTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_outIn("out", m_out)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Distance_rightTest::~Distance_rightTest()
{
}



RTC::ReturnCode_t Distance_rightTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("out", m_outIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Distance_rightTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t Distance_rightTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Distance_rightTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t Distance_rightTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Distance_rightTest::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Distance_rightTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t Distance_rightTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Distance_rightTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Distance_rightTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Distance_rightTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Distance_rightTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool Distance_rightTest::runTest()
{
    return true;
}


extern "C"
{
 
  void Distance_rightTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(distance_right_spec);
    manager->registerFactory(profile,
                             RTC::Create<Distance_rightTest>,
                             RTC::Delete<Distance_rightTest>);
  }
  
}
