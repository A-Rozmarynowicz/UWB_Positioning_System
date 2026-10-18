function P = Generate_Random_Tag_Position(dimensions, max_distance, all_positive_cords)
    if ~ismember(dimensions, [2, 3])
        error('dimensions must be either 2 or 3.');
    end

    if all_positive_cords
        P = rand(1, dimensions)*max_distance;
    else
        P = rand(1, dimensions)*2*max_distance - max_distance;
    end
end