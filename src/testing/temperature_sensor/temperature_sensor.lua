MOVE_STEPS = 100
MAX_VELOCITY = 15

n_steps = 0

source_position = {x = 0.0, y = 0.0, z = 0.0}

Tb = 15
T0 = 40
epsilon = 0.5

function get_robot_position()
    if robot.thymio_positioning == nil then
        log("ERROR: thymio_positioning sensor is missing!")
        return {x = 0, y = 0, z = 0}
    end

    local position = robot.thymio_positioning.get_position()

    if position == nil then
        log("ERROR: Positioning sensor returned nil!")
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
    if r > epsilon then
        return Tb + ((T0 - Tb)/r)
    elseif r <= epsilon then
        return T0
    end
end

function init()
    left_v = robot.random.uniform(0, MAX_VELOCITY)
    right_v = robot.random.uniform(0, MAX_VELOCITY)
    robot.wheels.set_velocity(left_v, right_v)
    n_steps = 0
end

function step()
    n_steps = n_steps + 1

    max_prox = -1
    max_prox_idx = -1
    for i=1,#robot.proximity do
        if robot.proximity[i].value > max_prox then
            max_prox = robot.proximity[i].value
            max_prox_idx = i
        end
    end

    left_v = robot.random.uniform(0, MAX_VELOCITY)
    right_v = robot.random.uniform(0, MAX_VELOCITY)

    if max_prox > 0 then
        if max_prox_idx <= #robot.proximity / 2 then
            right_v = robot.random.uniform(0, 3)
        else
            left_v = robot.random.uniform(0, 3)
        end
    end

    robot.wheels.set_velocity(left_v, right_v)

    local robot_position = get_robot_position()

    if robot_position then
        local distance_r = compute_distance(robot_position, source_position)
        local temperature = compute_temperature(distance_r)

        log(string.format("Step %d - Thymio pos: (%.2f, %.2f, %.2f) - Temp: %.2f°C",
                          n_steps, robot_position.x, robot_position.y, robot_position.z, temperature))
    else
        log(string.format("Step %d - ERROR: Could not retrieve robot position!", n_steps))
    end
end

function reset()
    left_v = robot.random.uniform(0, MAX_VELOCITY)
    right_v = robot.random.uniform(0, MAX_VELOCITY)
    robot.wheels.set_velocity(left_v, right_v)
    n_steps = 0
end

function destroy()
end