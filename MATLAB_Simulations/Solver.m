function P = Solver(P_vec, R_vec)
    sz = size(P_vec);
    N = sz(1);
    D = sz(2);
    A = zeros([N-1, D]);
    B = zeros([N-1, 1]);
    
    P1 = P_vec(1, :);
    R1 = R_vec(1);
    for j=2:N
        Pj = P_vec(j, :);
        Rj = R_vec(j);
        A(j-1, :) = -2*Pj + 2*P1;
        B(j-1) = Rj^2 - R1^2 - sum(Pj.^2) + sum(P1.^2);
    end
    P = (transpose(A)*A)^(-1) * transpose(A)*B;
    P = transpose(P);
end