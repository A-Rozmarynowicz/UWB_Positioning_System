function P = Generate_Fixed_Lighthouses_Positions(n_lighthouses, ~, max_distance, ~)
    if n_lighthouses == 4
        P = [
          0, 0, 0;
          max_distance, 0, 0;
          max_distance, max_distance, 0;
          0, max_distance, max_distance/2;
        ];
    elseif n_lighthouses == 5
        P = [
          0, 0, 0;
          max_distance, 0, 0;
          max_distance, max_distance, 0;
          0, max_distance, max_distance/2;
          max_distance, 0, max_distance/2;
        ];
    elseif n_lighthouses == 6
        P = [
          0, 0, 0;
          max_distance, 0, 0;
          max_distance, max_distance, 0;
          0, max_distance, max_distance/2;
          max_distance, 0, max_distance/2;
          max_distance, max_distance, max_distance/2;
        ];
    else
        error("Fixed LGHS positions not implemented");
    end
    P = P + randn(n_lighthouses, 3)*0.1;
end