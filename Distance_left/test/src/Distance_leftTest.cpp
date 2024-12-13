// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  Distance_leftTest.cpp
 * @brief ModuleDescription (test code)
 *
 */
// </rtc-template>

#include "Distance_leftTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const distance_left_spec[] =
#else
static const char* distance_left_spec[] =
#endif
  {
    "implementation_id", "Distance_leftTest",
    "type_name",         "Distance_leftTest",
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
Distance_leftTest::Distance_leftTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_outIn("out", m_out)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Distance_leftTest::~Distance_leftTest()
{
}



RTC::ReturnCode_t Distance_leftTest::onInitialize()
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
RTC::ReturnCode_t Distance_leftTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t Distance_leftTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Distance_leftTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t Distance_leftTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Distance_leftTest::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Distance_leftTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t Distance_leftTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Distance_leftTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Distance_leftTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Distance_leftTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Distance_leftTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool Distance_leftTest::runTest()
{
    return true;
}


extern "C"
{
 
  void Distance_leftTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(distance_left_spec);
    manager->registerFactory(profile,
                             RTC::Create<Distance_leftTest>,
                             RTC::Delete<Distance_leftTest>);
  }
  
}
