// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  Forward_ModuleTest.cpp
 * @brief ModuleDescription (test code)
 *
 */
// </rtc-template>

#include "Forward_ModuleTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const forward_module_spec[] =
#else
static const char* forward_module_spec[] =
#endif
  {
    "implementation_id", "Forward_ModuleTest",
    "type_name",         "Forward_ModuleTest",
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
Forward_ModuleTest::Forward_ModuleTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_up_inOut("up_in", m_up_in),
    m_up_outIn("up_out", m_up_out),
    m_out_leftIn("out_left", m_out_left),
    m_out_rightIn("out_right", m_out_right),
    m_out_stopIn("out_stop", m_out_stop),
    m_out_inputIn("out_input", m_out_input)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Forward_ModuleTest::~Forward_ModuleTest()
{
}



RTC::ReturnCode_t Forward_ModuleTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("up_out", m_up_outIn);
  addInPort("out_left", m_out_leftIn);
  addInPort("out_right", m_out_rightIn);
  addInPort("out_stop", m_out_stopIn);
  addInPort("out_input", m_out_inputIn);
  
  // Set OutPort buffer
  addOutPort("up_in", m_up_inOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Forward_ModuleTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t Forward_ModuleTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Forward_ModuleTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t Forward_ModuleTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Forward_ModuleTest::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Forward_ModuleTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t Forward_ModuleTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Forward_ModuleTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Forward_ModuleTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Forward_ModuleTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Forward_ModuleTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool Forward_ModuleTest::runTest()
{
    return true;
}


extern "C"
{
 
  void Forward_ModuleTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(forward_module_spec);
    manager->registerFactory(profile,
                             RTC::Create<Forward_ModuleTest>,
                             RTC::Delete<Forward_ModuleTest>);
  }
  
}
