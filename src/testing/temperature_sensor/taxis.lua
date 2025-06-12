MAX_VELOCITY = 15
TURN_GAIN = 2.0
TARGET_DISTANCE_THRESHOLD = 0.1

n_steps = 0

source_position = {x = 0.0, y = 0.0, z = 0.0}

function get_robot_position()
    if robot.thymio_positioning == nil then
        log("ERROR: thymio_positioning sensor is missing!")
        return {x = 0, y = 0, z = 0}
    end

    local position = robot.thymio_positioning.get_position()

    if not position or not position.x then
        log("ERROR: Positioning sensor returned an invalid value!")
        return {x = 0, y = 0, z = 0}
    else
        return {x = position.x, y = position.y, z = position.z}
    end
end

function compute_distance(pos1, pos2)
    local dx = pos1.x - pos2.x
    local dy = pos1.y - pos2.y
    local dz = pos1.z - pos2.z
    return math.sqrt(dx * dx + dy * dy + dz * dz)
end

function compute_temperature(r)
    local Tb = 15
    local T0 = 40
    local epsilon = 0.5
    if r > epsilon then
        return Tb + ((T0 - Tb) / r)
    else
        return T0
    end
end

function get_robot_heading()
    if robot.thymio_positioning == nil then
        log("ERROR: thymio_positioning sensor is missing!")
        return 0
    end

    local orientation = robot.thymio_positioning.get_orientation()
    if not orientation or not orientation.w then
        log("ERROR: Orientation sensor returned an invalid value!")
        return 0
    end

    local w = orientation.w
    local x = orientation.x
    local y = orientation.y
    local z = orientation.z

    local siny_cosp = 2 * (w * z + x * y)
    local cosy_cosp = 1 - 2 * (y * y + z * z)
    return math.atan2(siny_cosp, cosy_cosp)
end

function init()
    n_steps = 0
    robot.wheels.set_velocity(MAX_VELOCITY, MAX_VELOCITY)
end

function step()
    n_steps = n_steps + 1

    local pos = get_robot_position()
    local heading = get_robot_heading()

    local dx = source_position.x - pos.x
    local dy = source_position.y - pos.y
    local distance = compute_distance(pos, source_position)

    local desired_angle = math.atan2(dy, dx)

    local angle_error = desired_angle - heading
    while angle_error > math.pi do angle_error = angle_error - 2 * math.pi end
    while angle_error < -math.pi do angle_error = angle_error + 2 * math.pi end

    if distance > TARGET_DISTANCE_THRESHOLD then
        local left_v  = MAX_VELOCITY - TURN_GAIN * angle_error
        local right_v = MAX_VELOCITY + TURN_GAIN * angle_error
        robot.wheels.set_velocity(left_v, right_v)
    else
        robot.wheels.set_velocity(0, 0)
        log("Heating source reached!")
    end

    local temperature = compute_temperature(distance)
    log(string.format("Step %d - Pos: (%.2f, %.2f, %.2f) Dist: %.2f, Temp: %.2f°C, Heading: %.2f",
                      n_steps, pos.x, pos.y, pos.z, distance, temperature, heading))
end

function reset()
    n_steps = 0
    robot.wheels.set_velocity(MAX_VELOCITY, MAX_VELOCITY)
end

function destroy()
    --
end