// -*- C++ -*-
/*!
 * @file  CommandIn.cpp
 * @brief Sample CommandIn
 * @date $Date$
 *
 * $Id$
 */

#include "CommandIn.h"

// Module specification
// <rtc-template block="module_spec">
static const char* commandin_spec[] =
  {
    "implementation_id", "CommandIn",
    "type_name",         "CommandIn",
    "description",       "Sample CommandIn",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "SAmple",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "0",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
CommandIn::CommandIn(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_cmdOut("cmd", m_cmd)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
CommandIn::~CommandIn()
{
}



RTC::ReturnCode_t CommandIn::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("cmd", m_cmdOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CommandIn::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CommandIn::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CommandIn::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CommandIn::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CommandIn::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t CommandIn::onExecute(RTC::UniqueId ec_id)
{
	std::string buff;
	std::cout << "Please input action name: ";
	std::cin >> buff;
	m_cmd.data = buff.c_str();
	if(strcmp(m_cmd.data, "exit") == 0) { ::exit(1); }
	m_cmdOut.write();
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CommandIn::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CommandIn::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CommandIn::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CommandIn::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CommandIn::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void CommandInInit(RTC::Manager* manager)
  {
    coil::Properties profile(commandin_spec);
    manager->registerFactory(profile,
                             RTC::Create<CommandIn>,
                             RTC::Delete<CommandIn>);
  }
  
};


