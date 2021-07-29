// -*- C++ -*-
/*!
 * @file  GR001_Ctrl.cpp
 * @brief GR001Cotroller
 * @date $Date$
 *
 * $Id$
 */

#include "GR001_Ctrl.h"



// Module specification
// <rtc-template block="module_spec">
static const char* gr001_ctrl_spec[] =
  {
    "implementation_id", "GR001_Ctrl",
    "type_name",         "GR001_Ctrl",
    "description",       "GR001Cotroller",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "RobotController",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "0",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.portDevice", "COM1",
	"conf.default.motion_time", "250",
	"conf.default.motionDir", "",
	"conf.default.limitMode", "0",
	"conf.default.sendMargin", "20",
    // Widget
    "conf.__widget__.portDevice", "text",
	"conf.__widget__.motionDir", "text",
	"conf.__widget__.motion_time", "int",
	"conf.__widget__.limitMode", "int",
	"conf.__widget__.sendMargin", "int",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
GR001_Ctrl::GR001_Ctrl(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_qIn("qRef", m_q),
    m_servoIn("servoStateRef", m_servoRef),
    m_cmdIn("command", m_cmd),
    m_qOut("q", m_q), 
    m_servoOut("servoState", m_servo),
    m_eSigOut("emergencySignal", m_eSig),
	m_margin(20)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
GR001_Ctrl::~GR001_Ctrl()
{
}



RTC::ReturnCode_t GR001_Ctrl::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("qRef", m_qIn);
  addInPort("servoStateRef", m_servoIn);
  addInPort("command", m_cmdIn);
  
  // Set OutPort buffer
  addOutPort("q", m_qOut);
  addOutPort("servoState", m_servoOut);
  addOutPort("emergencySignal", m_eSigOut);

  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("portDevice", m_portDevice, "COM1");
  bindParameter("motion_time", m_motionTime, "500");
  bindParameter("motionDir", m_motionDir, "");
  bindParameter("limitMode", m_limitMode, "0");
  bindParameter("sendMargin", m_margin, "20");
  
  // </rtc-template>



  return RTC::RTC_OK;
}


RTC::ReturnCode_t GR001_Ctrl::onFinalize()
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t GR001_Ctrl::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t GR001_Ctrl::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t GR001_Ctrl::onActivated(RTC::UniqueId ec_id)
{
  GRobo = new GR001( (char *)m_portDevice.c_str() );
  
  recoardMotionFlag=0;
  sentPosture=NULL;
  m_prev_motionTime = m_motionTime;

  m_q.data.length(GRobo->joints + 1);
  m_servo.data.length(GRobo->joints);

  if( GRobo->connect() < 0 ){
	std::cerr << "Error: can't find G-Robot on " <<  m_portDevice << std::endl;
	//return RTC::RTC_ERROR;
  }

  if(GRobo->startThread() == 0){
	std::cerr << "Error: fail to create thread" << std::endl;
    delete GRobo;
	return RTC::RTC_ERROR;
  }
 

  GRobo->setDefaultMotionTime(m_motionTime);
  if(GRobo->com->handle != NULL) {
    GRobo->setServo(1, 0);
  }

  return RTC::RTC_OK;
}


RTC::ReturnCode_t GR001_Ctrl::onDeactivated(RTC::UniqueId ec_id)
{
	if(GRobo != NULL){
		GRobo->setServo(0, 1);
		delete GRobo;
		GRobo=NULL;
	}
	std::cerr << "DEACTIVE" << std::endl;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t GR001_Ctrl::onExecute(RTC::UniqueId ec_id)
{
	if(m_cmdIn.isNew() && GRobo->isMoving() == 0){
		m_cmdIn.read();
		std::cout << "Action:" << m_cmd.data << std::endl;

		if(strcmp(m_cmd.data, "On")== 0){
			GRobo->setServo(1, 0);
			m_servo.data[0]=1;
			m_servoOut.write();

		}else if(strcmp(m_cmd.data, "Off") == 0){
			GRobo->setServo(0,0);
			m_servo.data[0]=0;
			m_servoOut.write();

		}else if(strcmp(m_cmd.data, "Break") == 0){
			GRobo->setServo(2,0);
			m_servo.data[0]=0;
			m_servoOut.write();
		}else if(strcmp(m_cmd.data, "Free") == 0){
			GRobo->setFreeMotion(1);

		}else if(strcmp(m_cmd.data, "Init") == 0){
			GRobo->initPosition();

		}else if(strcmp(m_cmd.data, "Clear") == 0){
			GRobo->clearRecord();

		}else if(strcmp(m_cmd.data, "Push") == 0){
			GRobo->recordCurrentPosture();

		}else if(strcmp(m_cmd.data, "DoRecord") == 0){
			GRobo->doRecord();

		}else if(strcmp(m_cmd.data, "PrintRecord") == 0){
			GRobo->record->printMotion();

		}else if(strcmp(m_cmd.data, "Save") == 0){
			GRobo->setMotionDir(m_motionDir.c_str());
			GRobo->saveMotionToM(NULL);

		}else if(strcmp(m_cmd.data, "Rec") == 0){
			GRobo->clearMotion();
			recoardMotionFlag = 1;

		}else if(strcmp(m_cmd.data, "End") == 0){
			recoardMotionFlag = 0;
			GRobo->setMotionDir(m_motionDir.c_str());
			GRobo->saveMotionToM(NULL);

		}else if(strcmp(m_cmd.data, "Start") == 0){
			GRobo->setMotionCount(1);

		}else if(strcmp(m_cmd.data, "Reverse") == 0){
			GRobo->setMotionCount(-1);

		}else if(strcmp(m_cmd.data, "connect") == 0){
			GRobo->closePort();
			GRobo->connect();

		}else if(strcmp(m_cmd.data, "close") == 0){
			return RTC::RTC_ERROR;

		}else{
		  std::cout << "Motion = "<< m_cmd.data << std::endl;
		  std::string file(m_cmd.data);
		  GRobo->setMotionDir(m_motionDir.c_str());

		  if(GRobo->loadMotion((char *)file.c_str()) > 0){
		    GRobo->setMotionCount(1);
		  }
		}
	}
	while(m_qIn.isNew()){
		m_qIn.read();
        for(int i(0); i< GRobo->joints;i++){
			GRobo->setJoint(GRobo->jointIdToMotorId(i), rad2deg(m_q.data[i])*10);
		}
		int xx = (int)(m_q.data[GRobo->joints] * 1000);
		//GRobo->setMotionTime(xx);
		GRobo->setMotionTime(0);
		GRobo->startMotion();
	}

	RobotPosture *pos = GRobo->getCurrentPosture()->dupPosture();

	if(!pos->nearTo(sentPosture, m_margin))
	{
      for(int i(0); i<GRobo->joints ;i++){
		int angle = pos->getDegree(GRobo->jointIdToMotorId(i)) / 10;
		m_q.data[i] = deg2rad(angle);
	  }

#ifdef WIN32
	  _timeb tv;
	  _ftime_s(&tv);
	  m_q.tm.sec = tv.time;
	  m_q.tm.nsec = tv.millitm;
#else
	  struct timeval tv;
	  gettimeofday(&tv,NULL);
	  m_q.tm.sec = tv.tv_sec;
	  m_q.tm.nsec = tv.tv_usec;
#endif
	  m_q.data[GRobo->joints]= GRobo->getTimeout()/1000.0;

      m_qOut.write();
	  if(recoardMotionFlag == 1){
		  if(!pos->nearTo(GRobo->getLastPosture(), 100))
		  {
		    GRobo->appendCurrentPosture(250);
		  }
	  }
	  delete sentPosture;
	  sentPosture=pos;
	}

	if(m_prev_motionTime != m_motionTime){
      m_prev_motionTime = m_motionTime;
	  GRobo->setDefaultMotionTime(m_motionTime);
	}

    GRobo->setFreeMotion(m_limitMode);

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t GR001_Ctrl::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t GR001_Ctrl::onError(RTC::UniqueId ec_id)
{
	if(GRobo != NULL){
	  GRobo->closePort();
	}
	m_eSig.data = 1;
	m_eSigOut.write();
	return RTC::RTC_OK;
}


RTC::ReturnCode_t GR001_Ctrl::onReset(RTC::UniqueId ec_id)
{

  return RTC::RTC_OK;
}


/*
RTC::ReturnCode_t GR001_Ctrl::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t GR001_Ctrl::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void GR001_CtrlInit(RTC::Manager* manager)
  {
    coil::Properties profile(gr001_ctrl_spec);
    manager->registerFactory(profile,
                             RTC::Create<GR001_Ctrl>,
                             RTC::Delete<GR001_Ctrl>);
  }
  
};


