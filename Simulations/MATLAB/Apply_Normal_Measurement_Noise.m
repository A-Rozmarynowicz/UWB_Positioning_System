function d_noise = Apply_Normal_Measurement_Noise(d, accuracy)
    d_noise = d + accuracy*randn(size(d));
end