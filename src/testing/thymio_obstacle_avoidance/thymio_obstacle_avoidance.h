#ifndef THYMIO_OBSTACLE_AVOIDANCE_H
#define THYMIO_OBSTACLE_AVOIDANCE_H

#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
#include <argos3/plugins/robots/thymio/control_interface/ci_thymio_proximity_sensor.h>

#ifdef __cplusplus
#define EXPORT __attribute__((visibility("default")))
#else
#define EXPORT
#endif

using namespace argos;

class EXPORT CThymioObstacleAvoidance : public CCI_Controller {

public:
    CThymioObstacleAvoidance();
    virtual ~CThymioObstacleAvoidance() {}

    virtual void Init(TConfigurationNode& t_node);
    virtual void ControlStep();
    virtual void Reset();
    virtual void Destroy() {}

private:
    CCI_DifferentialSteeringActuator* m_pcWheels;
    CCI_ThymioProximitySensor* m_pcProximity;
    Real m_fWheelVelocity;
};

#endif