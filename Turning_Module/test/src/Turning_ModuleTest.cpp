﻿// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  Turning_ModuleTest.cpp
 * @brief ModuleDescription (test code)
 *
 */
// </rtc-template>

#include "Turning_ModuleTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const turning_module_spec[] =
#else
static const char* turning_module_spec[] =
#endif
  {
    "implementation_id", "Turning_ModuleTest",
    "type_name",         "Turning_ModuleTest",
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
Turning_ModuleTest::Turning_ModuleTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_up_inOut("up_in", m_up_in),
    m_up_outIn("up_out", m_up_out),
    m_out_rightIn("out_right", m_out_right),
    m_out_leftIn("out_left", m_out_left),
    m_out_longIn("out_long", m_out_long),
    m_out_shortIn("out_short", m_out_short)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Turning_ModuleTest::~Turning_ModuleTest()
{
}



RTC::ReturnCode_t Turning_ModuleTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("up_out", m_up_outIn);
  addInPort("out_right", m_out_rightIn);
  addInPort("out_left", m_out_leftIn);
  addInPort("out_long", m_out_longIn);
  addInPort("out_short", m_out_shortIn);
  
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
RTC::ReturnCode_t Turning_ModuleTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t Turning_ModuleTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Turning_ModuleTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t Turning_ModuleTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Turning_ModuleTest::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Turning_ModuleTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t Turning_ModuleTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Turning_ModuleTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Turning_ModuleTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Turning_ModuleTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Turning_ModuleTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool Turning_ModuleTest::runTest()
{
    return true;
}


extern "C"
{
 
  void Turning_ModuleTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(turning_module_spec);
    manager->registerFactory(profile,
                             RTC::Create<Turning_ModuleTest>,
                             RTC::Delete<Turning_ModuleTest>);
  }
  
}