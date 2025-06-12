/**
 * @file <argos3/plugins/robots/thymio/simulator/thymio_positioning_sensor.h>
 */
#include "thymio_positioning_sensor.h"
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/utility/logging/argos_log.h>

namespace argos {

void CThymioPositioningSensor::SetRobot(CComposableEntity& c_entity) {
    m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
}

void CThymioPositioningSensor::Update() {
    if (m_pcEmbodiedEntity) {
        m_cPosition = m_pcEmbodiedEntity->GetOriginAnchor().Position;
        m_cOrientation = m_pcEmbodiedEntity->GetOriginAnchor().Orientation;
        // LOG << "[DEBUG] Positioning Sensor Update: Position = " << m_cPosition << std::endl;
    } else {
        LOGERR << "[ERROR] Positioning Sensor: m_pcEmbodiedEntity is NULL!" << std::endl;
    }
}

void CThymioPositioningSensor::Reset() {
    m_cPosition.Set(0.0, 0.0, 0.0);
    m_cOrientation.Set(1.0, 0.0, 0.0, 0.0);
}

void CThymioPositioningSensor::CreateLuaState(lua_State* pt_lua_state) {
    // LOG << "[DEBUG] Creating Lua state for thymio_positioning sensor!" << std::endl;

    lua_pushlightuserdata(pt_lua_state, this);
    lua_setglobal(pt_lua_state, "argos_thymio_positioning_sensor");

    lua_newtable(pt_lua_state);

    lua_pushstring(pt_lua_state, "get_position");
    lua_pushcfunction(pt_lua_state, LuaGetPosition);
    lua_settable(pt_lua_state, -3);

    lua_pushstring(pt_lua_state, "get_orientation");
    lua_pushcfunction(pt_lua_state, LuaGetOrientation);
    lua_settable(pt_lua_state, -3);

    lua_setfield(pt_lua_state, -2, "thymio_positioning");
}

int CThymioPositioningSensor::LuaGetPosition(lua_State* pt_lua_state) {
    lua_getglobal(pt_lua_state, "argos_thymio_positioning_sensor");
    CThymioPositioningSensor* pcSensor =
        reinterpret_cast<CThymioPositioningSensor*>(lua_touserdata(pt_lua_state, -1));

    if (pcSensor == nullptr) {
        LOGERR << "[ERROR] LuaGetPosition: Sensor instance is NULL!" << std::endl;
        return 0;
    }

    const CVector3& cPos = pcSensor->GetPosition();

    lua_newtable(pt_lua_state);
    lua_pushstring(pt_lua_state, "x"); lua_pushnumber(pt_lua_state, cPos.GetX()); lua_settable(pt_lua_state, -3);
    lua_pushstring(pt_lua_state, "y"); lua_pushnumber(pt_lua_state, cPos.GetY()); lua_settable(pt_lua_state, -3);
    lua_pushstring(pt_lua_state, "z"); lua_pushnumber(pt_lua_state, cPos.GetZ()); lua_settable(pt_lua_state, -3);

    return 1;
}

int CThymioPositioningSensor::LuaGetOrientation(lua_State* pt_lua_state) {
    lua_getglobal(pt_lua_state, "argos_thymio_positioning_sensor");
    CThymioPositioningSensor* pcSensor =
        reinterpret_cast<CThymioPositioningSensor*>(lua_touserdata(pt_lua_state, -1));

    if (pcSensor == nullptr) {
        LOGERR << "[ERROR] LuaGetOrientation: Sensor instance is NULL!" << std::endl;
        return 0;
    }

    const CQuaternion& cOrient = pcSensor->GetOrientation();

    lua_newtable(pt_lua_state);
    lua_pushstring(pt_lua_state, "w"); lua_pushnumber(pt_lua_state, cOrient.GetW()); lua_settable(pt_lua_state, -3);
    lua_pushstring(pt_lua_state, "x"); lua_pushnumber(pt_lua_state, cOrient.GetX()); lua_settable(pt_lua_state, -3);
    lua_pushstring(pt_lua_state, "y"); lua_pushnumber(pt_lua_state, cOrient.GetY()); lua_settable(pt_lua_state, -3);
    lua_pushstring(pt_lua_state, "z"); lua_pushnumber(pt_lua_state, cOrient.GetZ()); lua_settable(pt_lua_state, -3);

    return 1;
}

void CThymioPositioningSensor::ReadingsToLuaState(lua_State* pt_lua_state) {
    //
}

REGISTER_SENSOR(CThymioPositioningSensor,
                "thymio_positioning", "default",
                "Benedetta Pacilli - Valentina Pieri", "1.0",
                "The Thymio positioning sensor.",
                "This sensor provides the position and orientation of the Thymio robot.",
                "Usable"
);

}