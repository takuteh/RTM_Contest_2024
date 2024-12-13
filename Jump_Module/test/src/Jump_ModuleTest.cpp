// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  Jump_ModuleTest.cpp
 * @brief ModuleDescription (test code)
 *
 */
// </rtc-template>

#include "Jump_ModuleTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const jump_module_spec[] =
#else
static const char* jump_module_spec[] =
#endif
  {
    "implementation_id", "Jump_ModuleTest",
    "type_name",         "Jump_ModuleTest",
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
Jump_ModuleTest::Jump_ModuleTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_up_inOut("up_in", m_up_in),
    m_in_reelOut("in_reel", m_in_reel),
    m_up_outIn("up_out", m_up_out),
    m_out_jumpIn("out_jump", m_out_jump),
    m_out_reelIn("out_reel", m_out_reel),
    m_out_stopIn("out_stop", m_out_stop),
    m_out_inputIn("out_input", m_out_input)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Jump_ModuleTest::~Jump_ModuleTest()
{
}



RTC::ReturnCode_t Jump_ModuleTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("up_out", m_up_outIn);
  addInPort("out_jump", m_out_jumpIn);
  addInPort("out_reel", m_out_reelIn);
  addInPort("out_stop", m_out_stopIn);
  addInPort("out_input", m_out_inputIn);
  
  // Set OutPort buffer
  addOutPort("up_in", m_up_inOut);
  addOutPort("in_reel", m_in_reelOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Jump_ModuleTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t Jump_ModuleTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Jump_ModuleTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t Jump_ModuleTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Jump_ModuleTest::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Jump_ModuleTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t Jump_ModuleTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Jump_ModuleTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Jump_ModuleTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Jump_ModuleTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Jump_ModuleTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool Jump_ModuleTest::runTest()
{
    return true;
}


extern "C"
{
 
  void Jump_ModuleTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(jump_module_spec);
    manager->registerFactory(profile,
                             RTC::Create<Jump_ModuleTest>,
                             RTC::Delete<Jump_ModuleTest>);
  }
  
}
