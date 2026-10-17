function d_noise = Apply_Uniform_Measurement_Noise(d, accuracy)
    d_noise = d + 2*accuracy*rand(size(d)) - accuracy;
end