// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  Distance_left.cpp
 * @brief ModuleDescription
 *
 */
// </rtc-template>

#include "Distance_left.h"
#include "distance.h"

GP2Y0E03 gpy;

int left_addr = 0x40;
int right_addr = 0x50;
// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char *const distance_left_spec[] =
#else
static const char *distance_left_spec[] =
#endif
    {
        "implementation_id", "Distance_left",
        "type_name", "Distance_left",
        "description", "ModuleDescription",
        "version", "1.0.0",
        "vendor", "VenderName",
        "category", "Category",
        "activity_type", "PERIODIC",
        "kind", "DataFlowComponent",
        "max_instance", "1",
        "language", "C++",
        "lang_type", "compile",
        ""};
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Distance_left::Distance_left(RTC::Manager *manager)
    // <rtc-template block="initializer">
    : RTC::DataFlowComponentBase(manager),
      m_outOut("out", m_out)
// </rtc-template>
{
}

/*!
 * @brief destructor
 */
Distance_left::~Distance_left()
{
}

RTC::ReturnCode_t Distance_left::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers

  // Set OutPort buffer
  addOutPort("out", m_outOut);

  // Set service provider to Ports

  // Set service consumers to Ports

  // Set CORBA Service Ports

  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Distance_left::onFinalize()
{
  return RTC::RTC_OK;
}
*/

// RTC::ReturnCode_t Distance_left::onStartup(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Distance_left::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

RTC::ReturnCode_t Distance_left::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}

RTC::ReturnCode_t Distance_left::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}

RTC::ReturnCode_t Distance_left::onExecute(RTC::UniqueId /*ec_id*/)
{
  m_out.data = gpy.readDistance(left_addr);
  std::cout << m_out.data << std::endl;
  m_outOut.write();
  return RTC::RTC_OK;
}

// RTC::ReturnCode_t Distance_left::onAborting(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Distance_left::onError(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Distance_left::onReset(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Distance_left::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Distance_left::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

extern "C"
{

  void Distance_leftInit(RTC::Manager *manager)
  {
    coil::Properties profile(distance_left_spec);
    manager->registerFactory(profile,
                             RTC::Create<Distance_left>,
                             RTC::Delete<Distance_left>);
  }
}
