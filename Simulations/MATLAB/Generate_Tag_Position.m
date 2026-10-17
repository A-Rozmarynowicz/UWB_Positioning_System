function P = Generate_Tag_Position(dimensions, max_distance)
    P = rand(1, dimensions)*2*max_distance - max_distance;
end