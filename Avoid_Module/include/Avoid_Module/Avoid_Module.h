// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  Avoid_Module.h
 * @brief ModuleDescription
 *
 */
// </rtc-template>

#ifndef AVOID_MODULE_H
#define AVOID_MODULE_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "BasicDataTypeStub.h"

// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

// <rtc-template block="component_description">
/*!
 * @class Avoid_Module
 * @brief ModuleDescription
 *
 */
// </rtc-template>
class Avoid_Module
    : public RTC::DataFlowComponentBase
{
public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  Avoid_Module(RTC::Manager *manager);

  /*!
   * @brief destructor
   */
  ~Avoid_Module() override;

  // <rtc-template block="public_attribute">

  // </rtc-template>

  // <rtc-template block="public_operation">

  // </rtc-template>

  // <rtc-template block="activity">
  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  RTC::ReturnCode_t onInitialize() override;

  /***
   *
   * The finalize action (on ALIVE->END transition)
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onFinalize() override;

  /***
   *
   * The startup action when ExecutionContext startup
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id) override;

  /***
   *
   * The shutdown action when ExecutionContext stop
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id) override;

  /***
   *
   * The activated action (Active state entry action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id) override;

  /***
   *
   * The deactivated action (Active state exit action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id) override;

  /***
   *
   * The execution action that is invoked periodically
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id) override;

  /***
   *
   * The aborting action when main logic error occurred.
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id) override;
  void Stop_Forward();
  std::vector<double> normalize_probabilities(const std::vector<double> &probabilities);
  std::string weighted_choice(const std::vector<std::string> &patterns, std::vector<double> probabilities);
  /***
   *
   * The error action in ERROR state
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onError(RTC::UniqueId ec_id) override;

  /***
   *
   * The reset action that is invoked resetting
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onReset(RTC::UniqueId ec_id) override;

  /***
   *
   * The state update action that is invoked after onExecute() action
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id) override;

  /***
   *
   * The action that is invoked when execution context's rate is changed
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id) override;
  // </rtc-template>

protected:
  // <rtc-template block="protected_attribute">

  // </rtc-template>

  // <rtc-template block="protected_operation">

  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedFloat m_in_distance_left;
  /*!
   */
  RTC::InPort<RTC::TimedFloat> m_in_distance_leftIn;
  RTC::TimedLong m_in_forward;
  /*!
   */
  RTC::InPort<RTC::TimedLong> m_in_forwardIn;
  RTC::TimedLong m_in_turn;
  /*!
   */
  RTC::InPort<RTC::TimedLong> m_in_turnIn;
  RTC::TimedLong m_in_jump;
  /*!
   */
  RTC::InPort<RTC::TimedLong> m_in_jumpIn;
  RTC::TimedFloat m_in_distance_right;
  /*!
   */
  RTC::InPort<RTC::TimedFloat> m_in_distance_rightIn;
  RTC::TimedLong m_in_env;
  /*!
   */
  RTC::InPort<RTC::TimedLong> m_in_envIn;

  // </rtc-template>

  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedLong m_out_forward;
  /*!
   */
  RTC::OutPort<RTC::TimedLong> m_out_forwardOut;
  RTC::TimedLong m_out_turn;
  /*!
   */
  RTC::OutPort<RTC::TimedLong> m_out_turnOut;
  RTC::TimedLong m_out_jump;
  /*!
   */
  RTC::OutPort<RTC::TimedLong> m_out_jumpOut;

  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">

  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">

  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">

  // </rtc-template>

private:
  // <rtc-template block="private_attribute">

  // </rtc-template>

  // <rtc-template block="private_operation">

  // </rtc-template>
};

extern "C"
{
  DLL_EXPORT void Avoid_ModuleInit(RTC::Manager *manager);
};

#endif // AVOID_MODULE_H
