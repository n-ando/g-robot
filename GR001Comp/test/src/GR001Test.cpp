// -*- C++ -*-
/*!
 * @file  GR001Test.cpp
 * @brief G-Robot GR001 controller component
 * @date $Date$
 *
 * $Id$
 */

#include "GR001Test.h"

// Module specification
// <rtc-template block="module_spec">
static const char* gr001_spec[] =
  {
    "implementation_id", "GR001Test",
    "type_name",         "GR001Test",
    "description",       "G-Robot GR001 controller component",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "Humanoid Robot",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.portDevice", "COM1",
    "conf.default.motionTime", "500",
    "conf.default.limitMode", "0",
    "conf.default.prev_motionTime", "250",
    "conf.default.recoardMotionFlag", "0",
    "conf.default.count", "0",
    "conf.default.motionDir", "C:\",
    "conf.default.margin", "20",

    // Widget
    "conf.__widget__.portDevice", "text",
    "conf.__widget__.motionTime", "text",
    "conf.__widget__.limitMode", "text",
    "conf.__widget__.prev_motionTime", "text",
    "conf.__widget__.recoardMotionFlag", "text",
    "conf.__widget__.count", "text",
    "conf.__widget__.motionDir", "text",
    "conf.__widget__.margin", "text",
    // Constraints

    "conf.__type__.portDevice", "string",
    "conf.__type__.motionTime", "int",
    "conf.__type__.limitMode", "int",
    "conf.__type__.prev_motionTime", "int",
    "conf.__type__.recoardMotionFlag", "int",
    "conf.__type__.count", "int",
    "conf.__type__.motionDir", "string",
    "conf.__type__.margin", "int",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
GR001Test::GR001Test(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_qIn("q", m_q),
    m_servoIn("servo", m_servo),
    m_cmdIn("cmd", m_cmd),
    m_qoutOut("qout", m_qout),
    m_servooutOut("servoout", m_servoout),
    m_eSigOut("eSig", m_eSig)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
GR001Test::~GR001Test()
{
}



RTC::ReturnCode_t GR001Test::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("qout", m_qoutIn);
  addInPort("servoout", m_servooutIn);
  addInPort("eSig", m_eSigIn);

  // Set OutPort buffer
  addOutPort("q", m_qOut);
  addOutPort("servo", m_servoOut);
  addOutPort("cmd", m_cmdOut);

  // Set service provider to Ports

  // Set service consumers to Ports

  // Set CORBA Service Ports

  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("portDevice", m_portDevice, "COM1");
  bindParameter("motionTime", m_motionTime, "500");
  bindParameter("limitMode", m_limitMode, "0");
  bindParameter("prev_motionTime", m_prev_motionTime, "250");
  bindParameter("recoardMotionFlag", m_recoardMotionFlag, "0");
  bindParameter("count", m_count, "0");
  bindParameter("motionDir", m_motionDir, "C:\");
  bindParameter("margin", m_margin, "20");
  // </rtc-template>

  return RTC::RTC_OK;
}


RTC::ReturnCode_t GR001Test::onFinalize()
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t GR001Test::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t GR001Test::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t GR001Test::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GR001Test::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GR001Test::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t GR001Test::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t GR001Test::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GR001Test::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t GR001Test::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t GR001Test::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{

  void GR001TestInit(RTC::Manager* manager)
  {
    coil::Properties profile(gr001_spec);
    manager->registerFactory(profile,
                             RTC::Create<GR001Test>,
                             RTC::Delete<GR001Test>);
  }

};


