#include "thymio_obstacle_avoidance.h"
#include <argos3/core/utility/logging/argos_log.h>

CThymioObstacleAvoidance::CThymioObstacleAvoidance() :
    m_pcWheels(nullptr),
    m_pcProximity(nullptr),
    m_fWheelVelocity(5.0f) {}

void CThymioObstacleAvoidance::Init(TConfigurationNode& t_node) {
    m_pcWheels = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
    m_pcProximity = GetSensor<CCI_ThymioProximitySensor>("Thymio_proximity");
}

void CThymioObstacleAvoidance::ControlStep() {
    const CCI_ThymioProximitySensor::TReadings& tProxReads = m_pcProximity->GetReadings();
    Real fLeftWheelSpeed = m_fWheelVelocity;
    Real fRightWheelSpeed = m_fWheelVelocity;

    Real fLeftSensor = 0.0;
    Real fRightSensor = 0.0;

    for(size_t i = 0; i < tProxReads.size(); ++i) {
        LOG << "Sensor " << i << ": " << tProxReads[i].Value << std::endl;
        if(i < tProxReads.size() / 2) {
            fLeftSensor += tProxReads[i].Value;
        } else {
            fRightSensor += tProxReads[i].Value;
        }
    }

    Real fThreshold = 0.9;
    if (fLeftSensor > fThreshold) {
        fLeftWheelSpeed = m_fWheelVelocity * (1.0 - fRightSensor);
        fRightWheelSpeed = 1.0;
    } else if (fRightSensor > fThreshold) {
        fLeftWheelSpeed = 1.0;
        fRightWheelSpeed = m_fWheelVelocity * (1.0 - fLeftSensor);
    }

    m_pcWheels->SetLinearVelocity(fLeftWheelSpeed, fRightWheelSpeed);
}

void CThymioObstacleAvoidance::Reset() {
    LOG << "[Reset] Resetting Thymio controller." << std::endl;
    m_pcWheels->SetLinearVelocity(0.0f, 0.0f);
}

REGISTER_CONTROLLER(CThymioObstacleAvoidance, "thymio_obstacle_avoidance_controller")