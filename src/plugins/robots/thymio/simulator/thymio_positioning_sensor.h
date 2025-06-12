#ifndef THYMIO_POSITIONING_SENSOR_H
#define THYMIO_POSITIONING_SENSOR_H

#include <argos3/plugins/robots/thymio/control_interface/ci_thymio_positioning_sensor.h>
#include <argos3/core/simulator/sensor.h>
#include <argos3/core/simulator/entity/embodied_entity.h>

namespace argos {

class CThymioPositioningSensor : public CCI_ThymioPositioningSensor,
                                 public CSimulatedSensor {
public:
    void SetRobot(CComposableEntity& c_entity) override;
    void Update() override;
    void Reset() override;

    void CreateLuaState(lua_State* pt_lua_state) override;
    void ReadingsToLuaState(lua_State* pt_lua_state) override;

    static int LuaGetPosition(lua_State* pt_lua_state);
    static int LuaGetOrientation(lua_State* pt_lua_state);

    const CQuaternion& GetOrientation() const { return m_cOrientation; }

private:
    CEmbodiedEntity* m_pcEmbodiedEntity;
    CQuaternion m_cOrientation;
};

}

#endif  // THYMIO_POSITIONING_SENSOR_H