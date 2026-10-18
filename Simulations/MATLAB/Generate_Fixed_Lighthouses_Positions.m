function P = Generate_Fixed_Lighthouses_Positions(~, ~, max_distance, ~)
    P = [
      0, 0, 0;
      max_distance, 0, 0;
      max_distance, max_distance, 0;
      0, max_distance, max_distance/2;
    ];
    P = P + randn(4, 3)*0.1;
end