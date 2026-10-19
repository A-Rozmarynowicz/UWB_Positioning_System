function P = Generate_Fixed_Tag_Position(dimensions, max_distance, ~)
    if dimensions == 2
        P = [
          max_distance/2, max_distance/2;
        ];
    elseif dimensions == 3
        P = [
          max_distance/2, max_distance/2, max_distance/2;
        ];
    else
        error("Dimensions must be either 2 or 3, is %d", dimensions);
    end
    P = P + randn(1, dimensions)*max_distance*1;
end