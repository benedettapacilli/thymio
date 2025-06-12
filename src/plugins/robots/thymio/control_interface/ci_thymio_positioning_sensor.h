#ifndef CI_THYMIO_POSITIONING_SENSOR_H
#define CI_THYMIO_POSITIONING_SENSOR_H

#include <argos3/core/control_interface/ci_sensor.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/utility/math/quaternion.h>

namespace argos {

class CCI_ThymioPositioningSensor : public CCI_Sensor {
public:
    CCI_ThymioPositioningSensor();
    virtual ~CCI_ThymioPositioningSensor() {}

    const CVector3& GetPosition() const;
    const CQuaternion& GetOrientation() const;

    void SetPosition(const CVector3& c_position);
    void SetOrientation(const CQuaternion& c_orientation);

protected:
    CVector3 m_cPosition;
    CQuaternion m_cOrientation;
};

}

#endif  // CI_THYMIO_POSITIONING_SENSOR_H