function P = Generate_Fixed_Tag_Position(~, max_distance, ~)
    P = [
      max_distance/2, max_distance/2, max_distance/2;
    ];
    P = P + randn(1, 3)*max_distance*1;
end