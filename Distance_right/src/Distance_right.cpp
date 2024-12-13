// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  Distance_right.cpp
 * @brief ModuleDescription
 *
 */
// </rtc-template>

#include "Distance_right.h"
#include "distance.h"

GP2Y0E03 gpy;

int left_addr = 0x40;
int right_addr = 0x50;
// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char *const distance_right_spec[] =
#else
static const char *distance_right_spec[] =
#endif
    {
        "implementation_id", "Distance_right",
        "type_name", "Distance_right",
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
Distance_right::Distance_right(RTC::Manager *manager)
    // <rtc-template block="initializer">
    : RTC::DataFlowComponentBase(manager),
      m_outOut("out", m_out)
// </rtc-template>
{
}

/*!
 * @brief destructor
 */
Distance_right::~Distance_right()
{
}

RTC::ReturnCode_t Distance_right::onInitialize()
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
RTC::ReturnCode_t Distance_right::onFinalize()
{
  return RTC::RTC_OK;
}
*/

// RTC::ReturnCode_t Distance_right::onStartup(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Distance_right::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

RTC::ReturnCode_t Distance_right::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}

RTC::ReturnCode_t Distance_right::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}

RTC::ReturnCode_t Distance_right::onExecute(RTC::UniqueId /*ec_id*/)
{
  m_out.data = gpy.readDistance(right_addr);
  std::cout << m_out.data << std::endl;
  m_outOut.write();
  return RTC::RTC_OK;
}

// RTC::ReturnCode_t Distance_right::onAborting(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Distance_right::onError(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Distance_right::onReset(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Distance_right::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t Distance_right::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

extern "C"
{

  void Distance_rightInit(RTC::Manager *manager)
  {
    coil::Properties profile(distance_right_spec);
    manager->registerFactory(profile,
                             RTC::Create<Distance_right>,
                             RTC::Delete<Distance_right>);
  }
}
