MOVE_STEPS = 100
MAX_VELOCITY = 15

n_steps = 0

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

    left_v = MAX_VELOCITY
    right_v = MAX_VELOCITY

    if max_prox > 0 then
        if max_prox_idx <= #robot.proximity / 2 then
            right_v = robot.random.uniform(0, 3)
        else
            left_v = robot.random.uniform(0, 3)
        end
        robot.wheels.set_velocity(left_v, right_v)
    else
        robot.wheels.set_velocity(robot.random.uniform(0, MAX_VELOCITY),
                                robot.random.uniform(0, MAX_VELOCITY))
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