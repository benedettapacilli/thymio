#include "ci_thymio_positioning_sensor.h"

namespace argos {

CCI_ThymioPositioningSensor::CCI_ThymioPositioningSensor() :
    m_cPosition(0.0f, 0.0f, 0.0f),
    m_cOrientation(1.0f, 0.0f, 0.0f, 0.0f) {}

const CVector3& CCI_ThymioPositioningSensor::GetPosition() const {
    return m_cPosition;
}

const CQuaternion& CCI_ThymioPositioningSensor::GetOrientation() const {
    return m_cOrientation;
}

void CCI_ThymioPositioningSensor::SetPosition(const CVector3& c_position) {
    m_cPosition = c_position;
}

void CCI_ThymioPositioningSensor::SetOrientation(const CQuaternion& c_orientation) {
    m_cOrientation = c_orientation;
}

}
